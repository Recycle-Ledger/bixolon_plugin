package com.recycleledger.bixolon_plugin

import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothManager
import android.content.Context
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.net.Uri
import android.os.Build
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

/** BixolonPlugin */
class BixolonPlugin : FlutterPlugin, MethodCallHandler {
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
            "dispose" -> dispose()
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
            pairedDeviceList.add(
                BluetoothData(
                    device.name ?! 'null',
                    device.address ?! 'null',
                )
            )
        }
        result.success(gson.toJson(pairedDeviceList))
    }

    private fun connectPrinter(macAddress: String, result: Result) {
        try {
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
        } catch (e: JposException) {
            result.error(e)
        }
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
        try {
            if (posPrinter == null) {
                printerInit()
            }
            if (currentPrinter == null) {
                result.error("101", "No printer selected", null)
                return
            }

            // 이전 상태 정리
            try {
                if (posPrinter?.claimed == true) {
                    posPrinter?.release()
                    Log.d("BixolonPlugin", "Released existing claim")
                }
                if (posPrinter?.opened == true) {
                    posPrinter?.close()
                    Log.d("BixolonPlugin", "Closed existing connection")
                }
            } catch (e: JposException) {
                Log.w("BixolonPlugin", "Cleanup failed: ${e.message}")
            }

            posPrinter?.open(currentPrinter!!.logicalName)
            posPrinter?.claim(5000)
            // 장치 사용 여부
            posPrinter?.setDeviceEnabled(true)
            result.success(null)
        } catch (e: JposException) {
            Log.e("BixolonPlugin", "Device enable failed: ${e.errorCode}, ${e.message}")
            posPrinter?.release()
            posPrinter?.close()
            result.error(e.errorCode.toString(), e.message, null)
        }
    }

    private fun dispose() {
        posPrinter?.release()
        posPrinter?.close()
        posPrinter?.setDeviceEnabled(false)
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
