package jni.dgbc.com.myapplication.jni;

import android.content.res.AssetManager;

/**
 * Created by zhangyafeng on 2017/11/3.
 */

public class JNI {


    public static native void CopyArray(double[] pIn, double[] pOut);

    public static native void ReadINI(AssetManager pAsset);

    public static native void ReadIni();
}
