package com.example.tictokapplication_kotlin

import android.app.Notification
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.Toast
import android.graphics.Color
import androidx.core.app.NotificationCompat
import android.app.NotificationManager
import android.app.NotificationChannel
import android.content.Context

import kotlin.collections.ArrayList

import android.database.Cursor
import android.database.sqlite.SQLiteDatabase
import android.graphics.Bitmap
import android.hardware.Sensor
import android.hardware.SensorManager
import android.os.Build
import android.os.Environment
import android.util.Log
import android.view.View

import android.provider.Settings.Secure;
import com.google.firebase.FirebaseApp
import com.google.firebase.database.DataSnapshot

import java.io.File
import java.io.FileOutputStream
import com.google.firebase.database.DatabaseReference

import com.google.firebase.database.FirebaseDatabase
import android.net.NetworkInfo

import android.net.ConnectivityManager
import android.widget.TextView


class MainActivity : AppCompatActivity()
{
    private lateinit var db: SQLiteDatabase
    private var lastId:Int = -1

    private var buts = ArrayList<Button>()

    private var player1 = ArrayList<Int>()
    private var player2 = ArrayList<Int>()
    private var isFirstPlayerActive: Boolean = true
    private var end: Boolean = false

    private var androidId:String = ""
    private var mFirebaseDatabase: FirebaseDatabase? = null
    private var mDatabaseReference: DatabaseReference? = null
    private var mDataSnapshot: DataSnapshot? = null

    private lateinit var notificationManager: NotificationManager

    private fun initFirebase()
    {
        FirebaseApp.initializeApp(this)
        mFirebaseDatabase = FirebaseDatabase.getInstance()
        mDatabaseReference = mFirebaseDatabase!!.getReference()
    }
    private fun initData()
    {
        val query:Cursor = db.rawQuery("SELECT win1, win2, draw, stat_date FROM stat where id=$lastId;", null)
        query.moveToFirst()

        mDatabaseReference!!.child("users").child(androidId).child("lastDate").setValue(query.getString(3))

        query.close()

    }
    private fun notStat(w1:Int, w2:Int, noW:Int)
    {
        val builder = NotificationCompat.Builder(this, "channelID")
            .setDefaults(Notification.DEFAULT_ALL)
            .setSmallIcon(android.R.drawable.ic_dialog_email)
            .setContentTitle("Результат")
            .setContentText("Побед Первого - ${w1}, Побед Второго - ${w2}, Ничеи - $noW")

        notificationManager.notify(1, builder.build())

        Toast.makeText(applicationContext, "Побед Первого - ${w1}, Побед Второго - ${w2}, Ничеи - $noW", Toast.LENGTH_LONG).show()
    }
    private fun getScreen()
    {
        val v: View = window.decorView.rootView
        v.setDrawingCacheEnabled(true)
        var screenshot: Bitmap? = null
        try {
            screenshot = Bitmap.createBitmap(v.getDrawingCache())
        } catch (e: Exception) {
            Log.e("GFG", "Failed to capture screenshot because:" + e.message)
        }
        v.setDrawingCacheEnabled(false)

        val filename = "${System.currentTimeMillis()}.jpg"
        val image = File(Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_PICTURES),
            filename)

        FileOutputStream(image).use {
            screenshot?.compress(Bitmap.CompressFormat.JPEG, 100, it)
            Toast.makeText(this , "Скриншот сохранен" , Toast.LENGTH_SHORT).show()
        }
    }

    override fun onCreate(savedInstanceState: Bundle?)
    {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        androidId = Secure.getString(contentResolver, Secure.ANDROID_ID)
        notificationManager = getSystemService(NOTIFICATION_SERVICE) as NotificationManager
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            val channel = NotificationChannel("channelID", "stat", NotificationManager.IMPORTANCE_DEFAULT)
            notificationManager.createNotificationChannel(channel)
        }

        db = baseContext.openOrCreateDatabase("phone_stat.db", MODE_PRIVATE, null)

        db.execSQL("CREATE TABLE IF NOT EXISTS stat (id INTEGER PRIMARY KEY AUTOINCREMENT," +
                                                            "win1 integer not null DEFAULT 0," +
                                                            "win2 integer not null DEFAULT 0," +
                                                            "draw integer not null DEFAULT 0," +
                                                            "stat_date date not null);")

        val query:Cursor = db.rawQuery("select * from stat where stat_date=date('now') and id=(select max(id) from stat);", null)
        //val query:Cursor = db.rawQuery("select id from stat where stat_date=date('now') and id=(select max(id) from stat);", null)
        query.moveToFirst()

        val cm = getSystemService(CONNECTIVITY_SERVICE) as ConnectivityManager
        val netInfo = cm.activeNetworkInfo
        if(query.count <= 0)
        {
            query.close()
            db.execSQL("insert into stat (stat_date) values (date('now'));")

            val query1:Cursor = db.rawQuery("select max(id), date('now'), count(*) from stat;", null)
            query1.moveToFirst()
            lastId = query1.getInt(0)
            val dd = query1.getString(1)

            if (netInfo != null && netInfo.isConnectedOrConnecting)
            {
                initFirebase()
                if (query1.getInt(2) <= 0)
                {
                    mDatabaseReference!!.child("users").child(androidId).setValue(User(androidId, dd))
                } else
                {
                    mDatabaseReference!!.child("users").child(androidId).child("lastDate").setValue(dd)
                }
            } else
            {
                Toast.makeText(applicationContext, "НЕТ ИНТЕРНЕТА!", Toast.LENGTH_LONG).show()
            }
            query1.close()
        } else
        {
            lastId = query.getInt(0)
            notStat(query.getInt(1), query.getInt(2), query.getInt(3))
            if (netInfo != null && netInfo.isConnectedOrConnecting)
            {
                initFirebase()
                mDatabaseReference!!.child("users").child(androidId).child("lastDate").setValue(query.getString(4))
            } else
            {
                Toast.makeText(applicationContext, "НЕТ ИНТЕРНЕТА!", Toast.LENGTH_LONG).show()
            }
            query.close()
        }

        val mSensorManager: SensorManager = getSystemService(SENSOR_SERVICE) as SensorManager;
        if(Build.VERSION.SDK_INT>=Build.VERSION_CODES.ICE_CREAM_SANDWICH){
            val mTemperature = mSensorManager.getDefaultSensor(Sensor.TYPE_LIGHT);
            val temperaturelabel: TextView = findViewById(R.id.tv)
            temperaturelabel.text = "степень освещённости "+mTemperature.power+" SI(люксовых единицах)(m/s2)"
        }

    }

    fun buClick(view: View)
    {
        val buSelected = view as Button
        buts.add(buSelected)

        var cellId = 0
        when (buSelected.id)
        {
            R.id.bu1 -> cellId = 1
            R.id.bu2 -> cellId = 2
            R.id.bu3 -> cellId = 3
            R.id.bu4 -> cellId = 4
            R.id.bu5 -> cellId = 5
            R.id.bu6 -> cellId = 6
            R.id.bu7 -> cellId = 7
            R.id.bu8 -> cellId = 8
            R.id.bu9 -> cellId = 9
        }
        playGame(cellId, buSelected)
        if (end)
        {
            val query:Cursor = db.rawQuery("SELECT win1, win2, draw, stat_date FROM stat where id=$lastId;", null)
            query.moveToFirst()
            notStat(query.getInt(0), query.getInt(1), query.getInt(2))
            query.close()
            getScreen()

            restartGame()
        }
    }

    private fun playGame(cellId: Int, btn: Button) {
        if (isFirstPlayerActive)
        {
            btn.text = "X"
            btn.setBackgroundColor(Color.GREEN)
            player1.add(cellId)
        } else
        {
            btn.text = "O"
            btn.setBackgroundColor(Color.RED)
            player2.add(cellId)
        }
        btn.isEnabled = false

        isFirstPlayerActive = !isFirstPlayerActive
        checkWinner()
    }
    private fun checkOne (playerActions: ArrayList<Int>): Boolean
    {
        return (playerActions.containsAll(listOf(1, 2, 3))
                || playerActions.containsAll(listOf(4, 5, 6))
                || playerActions.containsAll(listOf(7, 8, 9))
                || playerActions.containsAll(listOf(1, 4, 7))
                || playerActions.containsAll(listOf(2, 5, 8))
                || playerActions.containsAll(listOf(3, 6, 9))
                || playerActions.containsAll(listOf(1, 5, 9))
                || playerActions.containsAll(listOf(3, 5, 7))
                )
    }
    private fun checkWinner()
    {
        when {
            buts.size == 9 -> {
                db.execSQL("UPDATE stat SET draw = draw+1 where id==${lastId};")
                end = true
                Toast.makeText(applicationContext, "Ничья!", Toast.LENGTH_LONG).show()
            }
            checkOne(player1) -> {
                db.execSQL("UPDATE stat SET win1 = win1+1 where id=${lastId};")
                end = true
                Toast.makeText(applicationContext, "Первый выйграл!", Toast.LENGTH_LONG).show()
            }
            checkOne(player2) -> {
                db.execSQL("UPDATE stat SET win2 = win2+1 where id=${lastId};")
                end = true
                Toast.makeText(applicationContext, "Второй выйграл!", Toast.LENGTH_LONG).show()
            }
        }
    }

    private fun restartGame()
    {
        end = false
        isFirstPlayerActive = true
        player1.clear(); player2.clear()

        for(buSelected in buts)
        {
            buSelected.text = ""
            buSelected.setBackgroundResource(R.color.whileBu)
            buSelected.isEnabled = true
        }
        buts.clear()
    }
}