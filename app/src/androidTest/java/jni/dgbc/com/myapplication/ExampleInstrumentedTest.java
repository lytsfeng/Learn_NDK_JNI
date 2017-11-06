package jni.dgbc.com.myapplication;

import android.content.Context;
import android.support.test.InstrumentationRegistry;
import android.support.test.espresso.remote.EspressoRemoteMessage;
import android.support.test.runner.AndroidJUnit4;

import org.junit.Test;
import org.junit.runner.RunWith;

import jni.dgbc.com.myapplication.jni.JNI;

import static org.junit.Assert.*;

/**
 * Instrumented test, which will execute on an Android device.
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
@RunWith(AndroidJUnit4.class)
public class ExampleInstrumentedTest {
    @Test
    public void useAppContext() throws Exception {
        // Context of the app under test.
        Context appContext = InstrumentationRegistry.getTargetContext();

        assertEquals("jni.dgbc.com.myapplication", appContext.getPackageName());
       // Tool.ReadINi(appContext.getAssets());
        Tool.arrayopt();

    }
}
