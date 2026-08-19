package com.recycleledger.bixolon_plugin

import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothManager
import android.content.Context
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.net.Uri
import android.os.Build
import android.os.Handler
import android.os.Looper
import android.util.Log
import androidx.annotation.NonNull
import androidx.annotation.RequiresApi
import com.bxl.config.editor.BXLConfigLoader
import com.google.gson.Gson
import io.flutter.embedding.engine.plugins.FlutterPlugin
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel
import io.flutter.plugin.common.MethodChannel.MethodCallHandler
import io.flutter.plugin.common.MethodChannel.Result
import jpos.JposConst
import jpos.JposException
import jpos.MSR
import jpos.POSPrinter
import jpos.POSPrinterConst
import jpos.events.DataEvent
import jpos.events.DirectIOEvent
import jpos.events.ErrorEvent
import jpos.events.OutputCompleteEvent
import jpos.events.StatusUpdateEvent
import java.io.File
import java.io.FileOutputStream
import java.nio.ByteBuffer
import java.util.concurrent.Callable
import java.util.concurrent.ExecutionException
import java.util.concurrent.Executors
import java.util.concurrent.TimeUnit
import java.util.concurrent.TimeoutException

/** BixolonPlugin */
class BixolonPlugin : FlutterPlugin, MethodCallHandler {
    companion object {
        private const val DISPOSE_TIMEOUT_MS = 4000L
        private const val DEVICE_ENABLE_TIMEOUT_MS = 8000L
    }

    private val CHANNEL = "bixolon_plugin"

    private lateinit var channel: MethodChannel
    private lateinit var context: Context

    lateinit var bluetoothAdapter: BluetoothAdapter
    var pairedDeviceList: ArrayList<BluetoothData> = arrayListOf()
    var currentPrinter: BluetoothData? = null

    private val gson: Gson = Gson()

    // SDK Variable
    var posPrinter: POSPrinter? = null
    var bxlConfigLoader: BXLConfigLoader? = null
    val msr: MSR = MSR()

    // JavaPOS(posPrinter)의 open/claim/close 등은 내부적으로 Bluetooth 소켓 I/O를
    // 동기적으로 수행한다. 특정 기기·펌웨어 조합에서는 이 호출이 예외를 던지지
    // 않고 그냥 응답 없이 멈춰버리는 경우가 있어(Android BluetoothSocket 관련
    // 고질적 문제), try/catch(JposException)만으로는 막을 수 없다. 이런 호출은
    // 별도 스레드에서 실행하고 시간 내에 끝나지 않으면 호출자에게는 실패를
    // 반환한다 — 멈춘 스레드 자체는 강제 종료할 수 없어 그대로 흘려보낸다.
    private val ioExecutor = Executors.newCachedThreadPool()
    private val mainHandler = Handler(Looper.getMainLooper())

    private fun <T> runWithTimeout(
        timeoutMs: Long,
        block: () -> T,
        onSuccess: (T) -> Unit,
        onError: (Throwable) -> Unit,
    ) {
        val future = ioExecutor.submit(Callable { block() })
        ioExecutor.submit {
            try {
                val value = future.get(timeoutMs, TimeUnit.MILLISECONDS)
                mainHandler.post { onSuccess(value) }
            } catch (e: TimeoutException) {
                mainHandler.post { onError(e) }
            } catch (e: ExecutionException) {
                mainHandler.post { onError(e.cause ?: e) }
            } catch (e: Exception) {
                mainHandler.post { onError(e) }
            }
        }
    }

    @RequiresApi(Build.VERSION_CODES.JELLY_BEAN_MR2)
    override fun onAttachedToEngine(flutterPluginBinding: FlutterPlugin.FlutterPluginBinding) {
        channel = MethodChannel(flutterPluginBinding.binaryMessenger, "bixolon_plugin")
        channel.setMethodCallHandler(this)
        context = flutterPluginBinding.applicationContext
        bluetoothAdapter = (context.getSystemService(Context.BLUETOOTH_SERVICE) as BluetoothManager).adapter
    }

    override fun onMethodCall(call: MethodCall, result: Result) {
        when (call.method) {
            "init" -> {
                printerInit()
                result.success(null)
            }
            "checkConnection" -> {
                checkConnection(result)
            }
            "deviceEnableSetting" -> {
                deviceEnableSetting(result)
            }
            "dispose" -> {
                disposeWithTimeout(result)
            }
            "pairedDevices" -> scanPairedDevices(result)
            "connectPrinter" -> connectPrinter(call.arguments as String, result)
            "currentPrinter" -> {
                if (currentPrinter == null) {
                    result.success(null)
                } else {
                    result.success(gson.toJson(currentPrinter))
                }
            }
            "printText" -> printText(call.arguments as String, result)
            "printImage" -> printImage(call.arguments as ByteArray, result)
            "printPDF" -> printPDF(call.arguments as String, result)
        }
    }

    override fun onDetachedFromEngine(binding: FlutterPlugin.FlutterPluginBinding) {
        channel.setMethodCallHandler(null)
    }

    private fun scanPairedDevices(result: Result) {
        val bondedDeviceSet: Set<BluetoothDevice> = bluetoothAdapter.bondedDevices
        pairedDeviceList.clear()
        for (device in bondedDeviceSet) {
            // device.name(getName())은 캐시된 이름이 없거나 권한 문제 등으로 null을 반환할 수 있다.
            // null이면 Dart 쪽 파싱이 깨지므로 주소를 대체 표시 이름으로 사용한다.
            pairedDeviceList.add(
                BluetoothData(
                    device.name ?: device.address,
                    device.address,
                )
            )
        }
        result.success(gson.toJson(pairedDeviceList))
    }

    private fun connectPrinter(macAddress: String, result: Result) {
        val selectDevice = pairedDeviceList.find { it.macAddress == macAddress }
        if (selectDevice == null) {
            result.error("0", "Not found device", null)
            return
        }
        if (bxlConfigLoader == null) {
            bxlConfigLoader = BXLConfigLoader(context)
        }
        currentPrinter = selectDevice
        bxlConfigLoader?.removeAllEntries()
        bxlConfigLoader?.newFile()
        bxlConfigLoader?.addEntry(
            selectDevice.logicalName,
            BXLConfigLoader.DEVICE_CATEGORY_POS_PRINTER,
            BXLConfigLoader.PRODUCT_NAME_SPP_R200III,
            BXLConfigLoader.DEVICE_BUS_BLUETOOTH,
            selectDevice.macAddress,
        )
        bxlConfigLoader?.saveFile()
        result.success(true)
    }

    private fun checkConnection(result: Result) {
        try {
            if (bxlConfigLoader == null) {
                bxlConfigLoader = BXLConfigLoader(context)
            }
            bxlConfigLoader?.openFile()
            result.success(true)
            for (entry in bxlConfigLoader!!.entries) {
                val logicalName = entry.logicalName
                currentPrinter = BluetoothData(
                    logicalName,
                    bxlConfigLoader!!.getAddress(logicalName),
                )
            }
        } catch (e: JposException) {
            result.success(false)
        }
    }

    private fun printerInit() {
        posPrinter = POSPrinter(context)
        addListener()
    }

    private fun deviceEnableSetting(result: Result) {
        runWithTimeout(
            timeoutMs = DEVICE_ENABLE_TIMEOUT_MS,
            block = {
                posPrinter?.open(currentPrinter?.logicalName ?: "SPP-R200III")
                // Device 정보에 포함 되어 있는 Port를 실제로 Open 하는 작업
                posPrinter?.claim(5000)
                // 장치 사용 여부
                posPrinter?.deviceEnabled = true
            },
            onSuccess = { result.success(null) },
            onError = { error ->
                if (error is JposException) {
                    result.error(error.errorCode.toString(), error.message, null)
                } else {
                    // open/claim이 예외 없이 응답 없는 상태로 멈춘 경우(타임아웃).
                    result.error("TIMEOUT", "Printer device enable timed out", null)
                }
            },
        )
    }

    private fun dispose() {
        // release/close는 미연결(claim 전) 상태에서 JposException을 던질 수 있고,
        // 체크 예외라 MethodChannel 핸들러가 잡아주지 않으므로 각각 무시한다.
        try {
            posPrinter?.deviceEnabled = false
        } catch (e: JposException) {
        }
        try {
            posPrinter?.release()
        } catch (e: JposException) {
        }
        try {
            posPrinter?.close()
        } catch (e: JposException) {
        }
    }

    private fun disposeWithTimeout(result: Result) {
        // dispose()는 원래도 모든 예외를 삼키고 항상 성공으로 취급했으므로,
        // 타임아웃이 나도 동일하게 성공 응답을 보낸다 — 목적은 어차피 새로
        // open/claim할 것이므로, 응답 없는 release/close를 기다리다 전체
        // 연결 흐름이 멈추는 것을 막는 것이다.
        runWithTimeout(
            timeoutMs = DISPOSE_TIMEOUT_MS,
            block = { dispose() },
            onSuccess = { result.success(null) },
            onError = { result.success(null) },
        )
    }

    private fun printText(text: String, result: Result) {
        try {
            posPrinter?.printNormal(
                POSPrinterConst.PTR_S_RECEIPT, // 고정값
                text,
            )
            result.success(true)
        } catch (e: JposException) {
            result.error(e.errorCode.toString(), e.message, null)
        }
    }

    fun resizeBitmap(bitmap: Bitmap): Bitmap {
        val width = bitmap.width
        val height = bitmap.height
        val ratio = width.toFloat() / height.toFloat()

        val targetWidth = 384
        val targetHeight = (targetWidth / ratio).toInt()

        return Bitmap.createScaledBitmap(bitmap, targetWidth, targetHeight, false)
    }


    private fun printImage(byteArray: ByteArray, result: Result) {
        try {
            val butter: ByteBuffer = ByteBuffer.allocate(4)
            butter.put(POSPrinterConst.PTR_S_RECEIPT.toByte())
            butter.put(70.toByte()) // brightness
            butter.put(0x01) // compress
            butter.put(0x00)

            val bitmap = BitmapFactory.decodeByteArray(byteArray, 0, byteArray.size)

            // create file
//            val path: String = "${context.cacheDir}/print.png";
//            Log.d(TAG, path)
//            val fileOutputStream = FileOutputStream(path)
//            bitmap.compress(Bitmap.CompressFormat.PNG, 100, fileOutputStream)
//            fileOutputStream.close()

            posPrinter?.printBitmap(
                butter.getInt(0),
                bitmap,
                posPrinter!!.recLineWidth,
                POSPrinterConst.PTR_BM_LEFT,
            )
            result.success(true)
        } catch (e: JposException) {
            result.error(e.errorCode.toString(), e.message, null)
        }
    }

    private fun printPDF(filePath: String, result: Result) {
        try {
            val butter: ByteBuffer = ByteBuffer.allocate(4)
            butter.put(POSPrinterConst.PTR_S_RECEIPT.toByte())
            butter.put(80.toByte()) // brightness
            butter.put(0x01) // compress
            butter.put(0x00)

            posPrinter?.printPDFFile(
                butter.getInt(0),
                Uri.parse("file://$filePath"),
                posPrinter!!.recLineWidth,
                POSPrinterConst.PTR_BM_LEFT,
                1, 1,
            )
        } catch (e: JposException) {
            result.error(e.errorCode.toString(), e.message, null)
        }
    }

    private fun addListener() {
        posPrinter?.apply {
            addErrorListener { error: ErrorEvent? ->
                val errorMsg: String = when (error?.errorCodeExtended) {
                    POSPrinterConst.JPOS_EPTR_COVER_OPEN -> "Cover open"
                    POSPrinterConst.JPOS_EPTR_REC_EMPTY -> "Paper empty"
                    JposConst.JPOS_SUE_POWER_OFF_OFFLINE -> "Power off"
                    else -> "Unknown"
                }
            }
            addStatusUpdateListener { update: StatusUpdateEvent ->
                val statusMsg = when (update.status) {
                    JposConst.JPOS_SUE_POWER_ONLINE -> "Power on"
                    JposConst.JPOS_SUE_POWER_OFF_OFFLINE -> "Power off"
                    POSPrinterConst.PTR_SUE_COVER_OPEN -> "Cover open"
                    POSPrinterConst.PTR_SUE_COVER_OK -> "Cover ok"
                    POSPrinterConst.PTR_SUE_REC_EMPTY -> "Receipt paper empty"
                    POSPrinterConst.PTR_SUE_REC_NEAREMPTY -> "Receipt paper near empty"
                    POSPrinterConst.PTR_SUE_REC_PAPEROK -> "Receipt paper ok"
                    POSPrinterConst.PTR_SUE_IDLE -> "Printer Idle"
                    POSPrinterConst.PTR_SUE_BAT_LOW -> "Battery-Low"
                    POSPrinterConst.PTR_SUE_BAT_OK -> "Battery_OK"
                    else -> "Unknown"
                }
            }
            // 프린트 완료
            addOutputCompleteListener { complete: OutputCompleteEvent ->
            }
            addDirectIOListener { io: DirectIOEvent ->
            }
        }
        msr.addDataListener { data: DataEvent ->
            try {
                var strData: String = String(msr.track1Data)
                strData += String(msr.track2Data)
                strData += String(msr.track3Data)
            } catch (e: JposException) {
            }
        }
    }
}
