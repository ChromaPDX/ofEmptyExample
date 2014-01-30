package cc.openframeworks.EmptyExample;

import android.os.Bundle;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import cc.openframeworks.OFAndroid;

import android.util.Log;
import java.util.List;

import android.annotation.SuppressLint;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorManager;
import android.hardware.SensorEventListener;

@SuppressLint("MissingSuperCall")
public class OFActivity extends cc.openframeworks.OFActivity implements SensorEventListener{

    private SensorManager sensorManager;
    private Sensor accelerometerSensor;
    private Sensor compassSensor;

    float[] accelerometer = new float[3];
    float[] compass = new float[3];
    float[] gyroscope = new float[3];
    float[] mOrientation = new float[3]; 
    float[] mRotationM = new float[16];
    float[] mRemapedRotationM = new float[16]; 
    Boolean bool = false, bool1 = false;
    float gravity[] = new float [3];

	@Override
    public void onCreate(Bundle savedInstanceState)
    { 
        super.onCreate(savedInstanceState);
        String packageName = getPackageName();

        ofApp = new OFAndroid(packageName,this);

        sensorManager = (SensorManager)getSystemService(SENSOR_SERVICE);
    }
	
	@Override
	public void onDetachedFromWindow() {
	}
	
    @Override
    protected void onPause() {
        super.onPause();
        ofApp.pause();
        sensorManager.unregisterListener(this);
    }

    @Override
    protected void onResume() {
        super.onResume();
        ofApp.resume();
        List<Sensor> sensors = sensorManager.getSensorList(Sensor.TYPE_ACCELEROMETER);
        if(sensors.size() > 0)
        {
        	accelerometerSensor = sensors.get(0);
        	sensorManager.registerListener(this, accelerometerSensor, SensorManager.SENSOR_DELAY_GAME);
        	Log.v("OF", "accelerometer set up correctly");
        }else{
        	Log.e("OF","no accelerometer available");
        }
        sensors = sensorManager.getSensorList(Sensor.TYPE_MAGNETIC_FIELD);
        if(sensors.size() > 0)
        {
        	compassSensor = sensors.get(0);
        	sensorManager.registerListener(this, compassSensor, SensorManager.SENSOR_DELAY_GAME);
        	Log.v("OF", "compass set up correctly");
        }else{
        	Log.e("OF","no compass available");
        }
    }
    
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
    	if (OFAndroid.keyDown(keyCode, event)) {
    		return true;
    	} else {
    		return super.onKeyDown(keyCode, event);
    	}
    }
    
    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event) {
    	if (OFAndroid.keyUp(keyCode, event)) {
    		return true;
    	} else {
    		return super.onKeyUp(keyCode, event);
    	}
    }


	OFAndroid ofApp;
    
	
	
    // Menus
    // http://developer.android.com/guide/topics/ui/menus.html
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
    	// Create settings menu options from here, one by one or inflating an xml
        return super.onCreateOptionsMenu(menu);
    }
    
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
    	// This passes the menu option string to OF
    	// you can add additional behavior from java modifying this method
    	// but keep the call to OFAndroid so OF is notified of menu events
    	if(OFAndroid.menuItemSelected(item.getItemId())){
    		
    		return true;
    	}
    	return super.onOptionsItemSelected(item);
    }
    

    @Override
    public boolean onPrepareOptionsMenu (Menu menu){
    	// This method is called every time the menu is opened
    	//  you can add or remove menu options from here
    	return  super.onPrepareOptionsMenu(menu);
    }

	@Override
	public void onAccuracyChanged(Sensor sensor, int accuracy) {
		// TODO Auto-generated method stub
	}

	@Override
	public void onSensorChanged(SensorEvent event) {
		// TODO Auto-generated method stub
	
		switch (event.sensor.getType()) {
		    case Sensor.TYPE_ACCELEROMETER:
		    	// alpha is calculated as t / (t + dT)
		        // with t, the low-pass filter's time-constant
		        // and dT, the event delivery rate

		        final float alpha = (float)0.8;

		        gravity[0] = alpha * gravity[0] + (1 - alpha) * event.values[0];
		        gravity[1] = alpha * gravity[1] + (1 - alpha) * event.values[1];
		        gravity[2] = alpha * gravity[2] + (1 - alpha) * event.values[2];

		        accelerometer[0] = event.values[0] - gravity[0];
		        accelerometer[1] = event.values[1] - gravity[1];
		        accelerometer[2] = event.values[2] - gravity[2];
		    break;
		    case Sensor.TYPE_MAGNETIC_FIELD:
		        for(int i=0; i<3; i++){
		            compass[i] = event.values[i];
		        }
		    break;
		}
		boolean success = SensorManager.getRotationMatrix(mRotationM, null, gravity, compass);
		if	(success){
			updateRotationMatrix(mRotationM[0], mRotationM[1], mRotationM[2], mRotationM[3], 
		        				 mRotationM[4], mRotationM[5], mRotationM[6], mRotationM[7], 
		        				 mRotationM[8], mRotationM[9], mRotationM[10], mRotationM[11], 
		        				 mRotationM[12], mRotationM[13], mRotationM[14], mRotationM[15]);
//		    System.out.println(mRotationM[0] + " " + mRotationM[1] + " " + mRotationM[2] + " " + mRotationM[3]);
//		    System.out.println(mRotationM[4] + " " + mRotationM[5] + " " + mRotationM[6] + " " + mRotationM[7]);
//		    System.out.println(mRotationM[8] + " " + mRotationM[9] + " " + mRotationM[10] + " " + mRotationM[11]); 
//		    System.out.println(mRotationM[12] + " " + mRotationM[13] + " " + mRotationM[14] + " " + mRotationM[15]);
//		    System.out.println("---------------------------------------------");
		}
		else {
			System.out.println("COMPASS FAIL" + compass[0] +compass[1]);
		}
	}
    
    public native void updateRotationMatrix(float m00, float m10, float m20, float m30,
            float m01, float m11, float m21, float m31,
            float m02, float m12, float m22, float m32,
            float m03, float m13, float m23, float m33);

}



