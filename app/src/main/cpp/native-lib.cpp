#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <vector>
#include "inifile.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
using namespace inifile;



struct SignalConfig
{
    int  type;
    double StartF;
    double StopF;
    //double BW;
    vector<double> FrePoint;
    vector<double> bwPoint;
};



extern "C"
JNIEXPORT jstring

JNICALL
Java_com_lytsfeng_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";


    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_lytsfeng_jni_JNI_CopyArray(JNIEnv *env, jclass type, jdoubleArray pIn_,
                                                  jdoubleArray pOut_) {


    jdouble *pIn = env->GetDoubleArrayElements(pIn_, NULL);
    jdouble *pOut = env->GetDoubleArrayElements(pOut_, NULL);

    jint  _len = env->GetArrayLength(pIn_) * sizeof(jdouble);


    double *arr = (double *) malloc(_len);
    double *arrAddr = arr;
    memcpy(arr, pIn, _len);

    for (int i = 0; i < _len / sizeof(double); ++i) {
//        double _a = *arr;
//        printf("%f",_a);
       // *(++arr) = (*arr) + 1 ;
        arr[i] += 1;
    }

 //   free(arr);



    memcpy(pOut, arrAddr, _len);

    free(arr);

    env->ReleaseDoubleArrayElements(pIn_, pIn, 0);
    env->ReleaseDoubleArrayElements(pOut_, pOut, 0);



}
extern "C"
JNIEXPORT void JNICALL
Java_com_lytsfeng_jni_JNI_ReadIni(JNIEnv *env, jclass type) {

    IniFile _IniFile;
    string _FileName = "/storage/sdcard/ServiceConfig.ini";

    int _flag = _IniFile.load(_FileName);

    if (_flag > -1) {
        string _OutValue;
        _IniFile.getValue("业务1", "频段数", _OutValue);

        int _num = atoi(_OutValue.c_str());

        printf("%d", _num);
    }
}extern "C"
JNIEXPORT void JNICALL
Java_com_lytsfeng_JNI_ReadAssetFile(JNIEnv *env, jclass type,
                                                      jobject pAsset) {

    AAssetManager *_AssetManger = AAssetManager_fromJava(env, pAsset);

    if(_AssetManger == NULL){
      //  LOGE("open asset failed");
        return;
    }
    string _FileName = "ini/ServiceConfig.ini";
    AAsset* _Asset =  AAssetManager_open(_AssetManger, _FileName.c_str(), AASSET_MODE_UNKNOWN);

    if (_Asset == NULL) {
     //   LOGE("init asset failed");
        return;
    }

    long size = AAsset_getLength(_Asset);//获取文件长度
    char* buffer = (char*) malloc (sizeof(char)*size+1);
    buffer[size]='\0';
    AAsset_read(_Asset,buffer,size);


  //  LOGI(___STRING(buffer));


    //释放资源
    free(buffer);
    AAsset_close(_Asset);

}

void opt (unsigned int pNum, double *pInDate, int *pOutNum, double *pOutDate){
    int _count = 0;
    for (int i = 0; i < pNum; ++i) {
        if (pInDate[i] > 5) {
            pOutDate[_count] = pInDate[i];
            _count++;
        }
    }
    pOutNum[0] = _count;
}


extern "C"
JNIEXPORT jint JNICALL
Java_com_lytsfeng_jni_JNI_ArrayOpt(JNIEnv *env, jclass type, jint pNum,
                                                 jdoubleArray pInDate_, jintArray pOutName_,
                                                 jdoubleArray pOutDate_) {
    jdouble *pInDate = env->GetDoubleArrayElements(pInDate_, NULL);
    jint *pOutName = env->GetIntArrayElements(pOutName_, NULL);
    jdouble *pOutDate = env->GetDoubleArrayElements(pOutDate_, NULL);


    int _n = pNum;

    opt(pNum, pInDate, pOutName, pOutDate);


    char _name[256] ;

    sprintf(_name, "这是%d", 1);




    env->ReleaseDoubleArrayElements(pInDate_, pInDate, 0);
    env->ReleaseIntArrayElements(pOutName_, pOutName, 0);
    env->ReleaseDoubleArrayElements(pOutDate_, pOutDate, 0);
    return 1;
}