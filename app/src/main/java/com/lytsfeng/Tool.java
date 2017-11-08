package com.lytsfeng;

import android.content.res.AssetManager;
import android.util.Log;

import com.lytsfeng.jni.JNI;

/**
 * Created by zhangyafeng on 2017/11/3.
 */

public class Tool {

    static {
        System.loadLibrary("native-lib");
    }

    public static void test() {
        double[] _in = new double[]{1, 2, 3, 4, 5, 6, 7};
        double[] _out = new double[6];
        JNI.CopyArray(_in,_out);

        int _l = _out.length;
        for (int i = 0; i < _l; i++) {
            System.out.printf(_out[i] +"");
        }
    }

    public static void ReadINi(AssetManager assetManager) {
       // JNI.ReadINI(assetManager);
        JNI.ReadIni();
    }

    public static void arrayopt() {
        double[] _In = new double[]{
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int _inNum = _In.length;

        double[] _out = new double[_inNum];
        int[] _OutNum = new int[1];

        JNI.ArrayOpt(_inNum, _In, _OutNum, _out);

        if (_OutNum[0] > 0) {
            for (int i = 0; i < _OutNum[0]; i++) {
                Log.e("hello", "" + _out[i]);
            }
        }




    }





}
