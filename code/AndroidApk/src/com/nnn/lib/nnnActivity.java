package com.nnn.lib;

import android.app.Activity;
import android.content.Context;
import android.content.res.AssetManager;
import android.content.res.Configuration;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.util.DisplayMetrics;
import android.view.inputmethod.InputMethodManager;
import android.view.WindowManager;
import android.widget.EditText;

public class nnnActivity extends Activity implements SensorEventListener
{
	private nnnView				m_View;
	private SensorManager		m_sensorMgr;

	private static nnnActivity	m_activity;
	private EditText			m_textbox;
	private Handler				m_handler			= new Handler(){};

	private boolean				m_use_accelerometer	= false;	// �Ƿ�ʹ�ü��ټƣ����ٶȼƣ�
	private boolean				m_use_gyrometer		= false;	// �Ƿ�ʹ�����ݲ����ǣ����������ǣ�
	private boolean				m_use_magnetometer	= false;	// �Ƿ�ʹ�õش��ǣ���ǿ�ơ��ų���Ӧ����

	private boolean				m_supported_accelerometer;		// ϵͳ�Ƿ�֧�ּ��ټƣ����ٶȼƣ�
	private boolean				m_supported_gyrometer;			// ϵͳ�Ƿ�֧�����ݲ����ǣ����������ǣ�
	private boolean				m_supported_magnetometer;		// ϵͳ�Ƿ�֧�ֵش��ǣ���ǿ�ơ��ų���Ӧ����

	private Sensor				m_accelerometer;				// ���ټƣ����ٶȼƣ�
	private Sensor				m_gyrometer;					// ���ݲ����ǣ����������ǣ�
	private Sensor				m_magnetometer;					// �ش��ǣ���ǿ�ơ��ų���Ӧ����

	private void Add_EditText()
	{
		Context ctx = getWindow().getContext();
		m_textbox = new EditText(ctx);
	}

	public static void ShowKeyboard()
	{
		Context ctx = m_activity.getWindow().getContext();
		InputMethodManager imm = (InputMethodManager)ctx.getSystemService(Context.INPUT_METHOD_SERVICE);
		imm.showSoftInput(m_activity.m_textbox, 0);
	}

	public static void HideKeyboard()
	{
		Context ctx = m_activity.getWindow().getContext();
		InputMethodManager imm = (InputMethodManager)ctx.getSystemService(Context.INPUT_METHOD_SERVICE);
		imm.hideSoftInputFromWindow(m_activity.m_textbox.getWindowToken(), 0);
	}

	public static String IME_GetString()
	{
		return m_activity.m_textbox.getText().toString();
	}

	public static void IME_SetString(final String txt)
	{
		m_activity.m_handler.post(	new Runnable()
									{
										@Override
										public void run()
										{
											m_activity.m_textbox.setText(txt.toCharArray(), 0, txt.length());
										}
									}
		);
	}

	public static void IME_SetSelection(final int start_index, final int end_index)
	{
		m_activity.m_handler.post(	new Runnable()
									{
										@Override
										public void run()
										{
											m_activity.m_textbox.setSelection(start_index, end_index);
										}
									}
		);
	}

	public static int IME_GetSelectionStart()
	{
		return m_activity.m_textbox.getSelectionStart();
	}

	public static int IME_GetSelectionEnd()
	{
		return m_activity.m_textbox.getSelectionEnd();
	}

	public static void exit_mainloop()
	{
		nnnLib.FinalIME();
		m_activity.m_View.onFinal();

		System.exit(0);
	}

	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);

		m_View = CreateView();
		setContentView(m_View);
		m_View.requestFocus();

		DisplayMetrics outMetrics = new DisplayMetrics();

		Context ctx = getWindow().getContext();
		WindowManager manager = (WindowManager)ctx.getSystemService(Context.WINDOW_SERVICE);
		manager.getDefaultDisplay().getMetrics(outMetrics);

		nnnLib.OnSizeChanged(outMetrics.widthPixels, outMetrics.heightPixels);

		m_activity = this;
		Add_EditText();
		nnnLib.InitIME(this, m_textbox);

		m_sensorMgr = (SensorManager)getSystemService(SENSOR_SERVICE);

		// ���ټƣ����ٶȼƣ�
		if(m_use_accelerometer)
		{
			m_supported_accelerometer = m_sensorMgr.getSensorList(Sensor.TYPE_ACCELEROMETER).size() > 0;
			if(m_supported_accelerometer)
				m_accelerometer = m_sensorMgr.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
		}

		// ���ݲ����ǣ����������ǣ�
		if(m_use_gyrometer)
		{
			m_supported_gyrometer = m_sensorMgr.getSensorList(Sensor.TYPE_GYROSCOPE).size() > 0;
			if(m_supported_gyrometer)
				m_gyrometer = m_sensorMgr.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
		}

		// �ش��ǣ���ǿ�ơ��ų���Ӧ����
		if(m_use_magnetometer)
		{
			m_supported_magnetometer = m_sensorMgr.getSensorList(Sensor.TYPE_MAGNETIC_FIELD).size() > 0;
			if(m_supported_magnetometer)
				m_magnetometer = m_sensorMgr.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
		}

		// ���� sdcard ·��
		String sdcard_path = Environment.getExternalStorageDirectory().getAbsolutePath();
		nnnLib.OnReciveSdcardPath(sdcard_path);

		// ��ʼ�� AssetManager
		AssetManager assetManager = getAssets();
		nnnLib.OnInitAssetManager(assetManager);
	}

	protected nnnView CreateView()
	{
		return new nnnView(this, 16, 0);
	}

	@Override
	protected void onDestroy()
	{
		super.onDestroy();
		exit_mainloop();
	}

	@Override
	protected void onPause()
	{
		super.onPause();

		// ���ټƣ����ٶȼƣ�
		if(m_use_accelerometer)
		{
			if(m_supported_accelerometer)
				m_sensorMgr.unregisterListener(this, m_accelerometer); 
		}

		// ���ݲ����ǣ����������ǣ�
		if(m_use_gyrometer)
		{
			if(m_supported_gyrometer)
				m_sensorMgr.unregisterListener(this, m_gyrometer); 
		}

		// �ش��ǣ���ǿ�ơ��ų���Ӧ����
		if(m_use_magnetometer)
		{
			if(m_supported_magnetometer)
				m_sensorMgr.unregisterListener(this, m_magnetometer); 
		}

		m_View.queueEvent(	new Runnable()
							{
								@Override
								public void run()
								{
									nnnLib.OnPaused();
								}
							}
		);
	}

	@Override
	protected void onResume()
	{
		super.onResume();

		// ���ټƣ����ٶȼƣ�
		if(m_use_accelerometer)
		{
			if(m_supported_accelerometer)
				m_sensorMgr.registerListener(this, m_accelerometer, SensorManager.SENSOR_DELAY_GAME);
		}

		// ���ݲ����ǣ����������ǣ�
		if(m_use_gyrometer)
		{
			if(m_supported_gyrometer)
				m_sensorMgr.registerListener(this, m_gyrometer, SensorManager.SENSOR_DELAY_GAME);
		}

		// �ش��ǣ���ǿ�ơ��ų���Ӧ����
		if(m_use_magnetometer)
		{
			if(m_supported_magnetometer)
				m_sensorMgr.registerListener(this, m_magnetometer, SensorManager.SENSOR_DELAY_GAME);
		}

		m_View.queueEvent(	new Runnable()
							{
								@Override
								public void run()
								{
									nnnLib.OnResume();
								}
							}
		);
	}

	@Override
	public void onAccuracyChanged(Sensor sensor, int accuracy)
	{
		// nothing to do
	}

	@Override
	public void onSensorChanged(final SensorEvent event)
	{
		m_View.queueEvent(	new Runnable()
							{
								@Override
								public void run()
								{
									float x = event.values[m_sensorMgr.DATA_X];
									float y = event.values[m_sensorMgr.DATA_Y];
									float z = event.values[m_sensorMgr.DATA_Z];

									switch(event.sensor.getType())
									{
									case Sensor.TYPE_ACCELEROMETER:	// ���ټƣ����ٶȼƣ�
										nnnLib.OnAccelerometer(x, y, z);
										break;

									case Sensor.TYPE_GYROSCOPE:		// ���ݲ����ǣ����������ǣ�
										nnnLib.OnGyrometer(x, y, z);
										break;

									case Sensor.TYPE_MAGNETIC_FIELD:// �ش��ǣ���ǿ�ơ��ų���Ӧ����
										nnnLib.OnMagnetometer(x, y, z);
										break;
									}
								}
							}
		);
	}

	@Override
	public void onConfigurationChanged(final Configuration newConfig)
	{
		super.onConfigurationChanged(newConfig);

		m_View.queueEvent(	new Runnable()
							{
								@Override
								public void run()
								{
									int rotation = c_RotationType.Identity;
									switch(newConfig.orientation)
									{
									case Configuration.ORIENTATION_PORTRAIT:
										rotation = c_RotationType.Identity;
										break;

									case Configuration.ORIENTATION_LANDSCAPE:
										rotation = c_RotationType.Rotate90;
										break;
									}

									nnnLib.OnRotation(rotation);
								}
							}
		);
	}
}
