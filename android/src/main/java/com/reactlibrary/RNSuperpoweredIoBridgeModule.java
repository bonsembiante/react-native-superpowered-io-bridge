
package com.reactlibrary.superpowerediobridge;

import android.content.Context;
import android.os.Build;
import android.media.AudioManager;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.Callback;

public class RNSuperpoweredIoBridgeModule extends ReactContextBaseJavaModule {
  
  private boolean playing = false;
  private int samplerate;
  private int buffersize;

  private final ReactApplicationContext reactContext;

  public RNSuperpoweredIoBridgeModule(ReactApplicationContext reactContext) {
    super(reactContext);
    this.reactContext = reactContext;
  }

  @Override
  public String getName() {
    return "RNSuperpoweredIoBridge";
  }

  @ReactMethod
  public void initialize(Promise promise) {
      // Get the device's sample rate and buffer size to enable
      // low-latency Android audio output, if available.
      String samplerateString = null, buffersizeString = null;
      if (Build.VERSION.SDK_INT >= 17) {
          AudioManager audioManager = (AudioManager) this.reactContext.getSystemService(Context.AUDIO_SERVICE);
          if (audioManager != null) {
              samplerateString = audioManager.getProperty(AudioManager.PROPERTY_OUTPUT_SAMPLE_RATE);
              buffersizeString = audioManager.getProperty(AudioManager.PROPERTY_OUTPUT_FRAMES_PER_BUFFER);
          }
      }
      if (samplerateString == null) samplerateString = "48000";
      if (buffersizeString == null) buffersizeString = "480";
      samplerate = Integer.parseInt(samplerateString);
      buffersize = Integer.parseInt(buffersizeString);
      System.loadLibrary("AudioIOBridge");    // load native library
      promise.resolve(true);
  }

  // Handle Start/Stop button toggle.
  @ReactMethod
  public void ToggleStartStop(Promise promise) {
      if (playing) {
          StopAudio();
          playing = false;
      } else {
          StartAudio(samplerate, buffersize);
          playing = true;
      }
      promise.resolve(playing);
  }

  @ReactMethod
  public void updatePanning(float left, float right, Promise promise) {
      SetPanning(left,right);
      promise.resolve(true);
  }

  // Functions implemented in the native library.
  private native void StartAudio(int samplerate, int buffersize);
  private native void StopAudio();
  private native void SetPanning(float left, float right);
  private native void onForeground();
  private native void onBackground();
}