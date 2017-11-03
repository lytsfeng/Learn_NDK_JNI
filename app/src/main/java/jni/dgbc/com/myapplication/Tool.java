package jni.dgbc.com.myapplication;

import android.content.res.AssetManager;

import jni.dgbc.com.myapplication.jni.JNI;

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





}
