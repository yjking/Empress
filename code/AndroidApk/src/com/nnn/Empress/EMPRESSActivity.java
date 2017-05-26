package com.nnn.Empress;

import android.os.Bundle;
import com.nnn.lib.nnnView;
import com.nnn.lib.nnnActivity;

public class EMPRESSActivity extends nnnActivity
{
	static
	{
		System.loadLibrary("Empress");
	}

	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
	}

	@Override
	protected nnnView CreateView()
	{
		return new nnnView(this, 16, 0);
	}
}
