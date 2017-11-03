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
Java_jni_dgbc_com_myapplication_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";


    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_jni_dgbc_com_myapplication_jni_JNI_CopyArray(JNIEnv *env, jclass type, jdoubleArray pIn_,
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
//extern "C"
//JNIEXPORT void JNICALL
//Java_jni_dgbc_com_myapplication_jni_JNI_CopyArray(JNIEnv *env, jclass type, jdoubleArray pIn_,
//                                                  jdoubleArray pOut_) {
//    jdouble *pIn = env->GetDoubleArrayElements(pIn_, NULL);
//    jdouble *pOut = env->GetDoubleArrayElements(pOut_, NULL);
//
//    // TODO
//
//    env->ReleaseDoubleArrayElements(pIn_, pIn, 0);
//    env->ReleaseDoubleArrayElements(pOut_, pOut, 0);
//}
extern "C"
JNIEXPORT void JNICALL
Java_jni_dgbc_com_myapplication_jni_JNI_ReadINI(JNIEnv *env, jclass type, jobject pAsset) {

    AAssetManager *_AssetManger = AAssetManager_fromJava(env, pAsset);

    if(_AssetManger == NULL){

        return;
    }
    string _FileName = "ServiceConfig.ini";
    AAsset* _Asset =  AAssetManager_open(_AssetManger, _FileName.c_str(), AASSET_MODE_UNKNOWN);

    if (_Asset == NULL) {

        return;
    }

    long size = AAsset_getLength(_Asset);//获取文件长度
    char* buffer = (char*) malloc (sizeof(char)*size+1);
    buffer[size]='\0';
    AAsset_read(_Asset,buffer,size);
    string _inistr = "[]";

    sprintf((char *) _inistr.c_str(), "%s", buffer);
    IniFile _IniFile;

    for (int i = 0; i < 12; i++) {
        string _key;
        sprintf((char *) _key.c_str(), "业务%d", i+1);

        string _InvCountStr;
        _IniFile.getValue(_inistr, "频段数", _InvCountStr);
        int _invCount = atoi(_InvCountStr.c_str());

        int ServiceType=i;//业务号
        for (int i = 0; i < _invCount; i++)
        {
            double StartFreq;
            double StopFreq;
            double bW;
            vector<double> tmpPoint;
            vector<double> tmpbwPoint;
            string startFreqSecName;
            sprintf((char*)startFreqSecName.c_str(), "起始频率%d", i+1);
//            char Val[255] = {0};
//            GetPrivateProfileString(secName.c_str(), startFreqSecName.c_str(), "0", Val, sizeof(Val), szDirFilePath);
            string _startf;
            _IniFile.getValue(_inistr, startFreqSecName, _startf);

            StartFreq = atof(_startf.c_str());

            string stopFreqSecName;
            sprintf((char*)stopFreqSecName.c_str(), "截止频率%d", i+1);
            string _Stopf;
            _IniFile.getValue(_inistr, stopFreqSecName, _Stopf);
//            char Val1[255] = {0};
//            GetPrivateProfileString(secName.c_str(), stopFreqSecName.c_str(), "0", Val1, sizeof(Val1), szDirFilePath);
            StopFreq = atof(_Stopf.c_str());
/*
        bW=0;
		string  bWSecName;
		sprintf((char*)bWSecName.c_str(), "带宽%d", i+1);
		char Val2[255] = {0};
		GetPrivateProfileString(secName.c_str(), bWSecName.c_str(), "0", Val2, sizeof(Val2), szDirFilePath);
		bW = atof(Val2);
*/
            string FreqPointSecName,freqp;
            sprintf((char*)FreqPointSecName.c_str(), "频点%d", i+1);
            _IniFile.getValue(_inistr, FreqPointSecName, freqp);
//            char Val3[255] = {0};
//            GetPrivateProfileString(secName.c_str(),FreqPointSecName.c_str(), "0", Val3, sizeof(Val3), szDirFilePath);	;

            const char* split=",";//分割频点串
            char* Val4;
            Val4=strtok((char *) freqp.c_str(), split);
            while(Val4!=NULL)
            {
                double Val5 = atof(Val4);
                tmpPoint.push_back(Val5);
                Val4=strtok(NULL,split);
            }
            //带宽kHz，对应每个频点，
            string bwPointSecName,bw;
            sprintf((char*)bwPointSecName.c_str(), "带宽%d", i+1);
            _IniFile.getValue(_inistr, bwPointSecName, bw);
//            char Val6[255] = {0};
//            GetPrivateProfileString(secName.c_str(),bwPointSecName.c_str(), "0", Val6, sizeof(Val6), szDirFilePath);	;
            char* Val7;
            Val7=strtok((char *) bw.c_str(), split);
            while(Val7!=NULL)
            {
                double Val8 = atof(Val7);
                tmpbwPoint.push_back(Val8);
                Val7=strtok(NULL,split);
            }


            SignalConfig tmpService;
            tmpService.type =ServiceType;
            tmpService.StartF = StartFreq;
            tmpService.StopF =StopFreq;
            //tmpService.BW=bW;
            tmpService.FrePoint=tmpPoint;
            tmpService.bwPoint=tmpbwPoint;

            vector<SignalConfig> SignalConf;

            SignalConf.push_back(tmpService);
        }



    }






}

extern "C"
JNIEXPORT void JNICALL
Java_jni_dgbc_com_myapplication_jni_JNI_ReadIni(JNIEnv *env, jclass type) {

    IniFile _IniFile;
    string _FileName = "/storage/sdcard/ServiceConfig.ini";

    int _flag = _IniFile.load(_FileName);




}