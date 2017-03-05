package com.ispeak.handwave;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

import edu.washington.cs.touchfreelibrary.sensors.CameraGestureSensor;
import edu.washington.cs.touchfreelibrary.sensors.ClickSensor;
import edu.washington.cs.touchfreelibrary.utilities.LocalOpenCV;
import edu.washington.cs.touchfreelibrary.utilities.PermissionUtility;

public class MainActivity extends AppCompatActivity implements CameraGestureSensor.Listener, ClickSensor.Listener {

    String TAG = "Hello";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        if (PermissionUtility.checkCameraPermission(this)) {
            LocalOpenCV loader = new LocalOpenCV(MainActivity.this, MainActivity.this, MainActivity.this);
        }
    }

    @Override
    public void onResume() {
        super.onResume();
        if (PermissionUtility.checkCameraPermission(this)) {
            LocalOpenCV loader = new LocalOpenCV(MainActivity.this, MainActivity.this, MainActivity.this);
        }
    }

    @Override
    public void onGestureUp(CameraGestureSensor caller, long gestureLength) {
        Log.i(TAG, "Up");
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(MainActivity.this, "Hand Motion Up", Toast.LENGTH_SHORT).show();
            }
        });
    }

    @Override
    public void onGestureDown(CameraGestureSensor caller, long gestureLength) {
        Log.i(TAG, "Down");
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(MainActivity.this, "Hand Motion Down", Toast.LENGTH_SHORT).show();
            }
        });

    }

    @Override
    public void onGestureLeft(CameraGestureSensor caller, long gestureLength) {
        Log.i(TAG, "Left");
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(MainActivity.this, "Hand Motion Left", Toast.LENGTH_SHORT).show();
            }
        });
    }

    @Override
    public void onGestureRight(CameraGestureSensor caller, long gestureLength) {
        Log.i(TAG, "RIght");
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(MainActivity.this, "Hand Motion Right", Toast.LENGTH_SHORT).show();
            }
        });
    }

    @Override
    public void onSensorClick(ClickSensor caller) {
        Log.i(TAG, "Click");
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(MainActivity.this, "CLICK!", Toast.LENGTH_SHORT).show();
            }
        });
    }
}