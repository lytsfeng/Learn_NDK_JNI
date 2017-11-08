package com.lytsfeng.jni;

import android.content.res.AssetManager;

/**
 * Created by zhangyafeng on 2017/11/3.
 */

public class JNI {


    public static native void CopyArray(double[] pIn, double[] pOut);



    public static native void ReadIni();


    public static native void ReadAssetFile(AssetManager assetManager);


    public static native int ArrayOpt(int pNum, double[] pInDate, int[] pOutName, double[] pOutDate);

}
