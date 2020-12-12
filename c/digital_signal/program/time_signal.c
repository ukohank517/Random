#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Pi 3.14159265358979
#define sampRate  12000 //サンプリング周波数[Hz]
#define timelen   5     //出力データの長さ[sec]
#define Amplitude 10000 //音圧

int main (void)
{
    char filename1[64] = "NHK.pcm";
    char filename2[64] = "telephone.pcm";
    FILE *file1, *file2;
    
    double *data1, *data2;
    short tmp;
    int nSamples;      //サンプル数
    int freq1a = 440;  //単位は[Hz]
    int freq1b = 880;
    int freq2a = 500;
    int freq2b = 1000;
    int start, nlen;   //サイン波の開始，長さ
    int i,j;
    
    
    if((file1 = fopen(filename1,"wb")) == NULL){
        fprintf(stderr,"Cannot read %s\n",filename1);exit(-1);
    }
    if((file2 = fopen(filename2,"wb")) == NULL){
        fprintf(stderr,"Cannot read %s\n",filename2);exit(-1);
    }
    
    nSamples = sampRate*timelen;
    if((data1=(double *)calloc(nSamples, sizeof(double))) == NULL){
        fprintf(stderr,"cannot allocate memory.\n");exit(-1);
    }
    if((data2=(double *)calloc(nSamples, sizeof(double))) == NULL){
        fprintf(stderr,"cannot allocate memory.\n");exit(-1);
    }
    
    /*短音(0.1秒)*/
    nlen = 0.1*sampRate;
    for(i=0; i<3; i++){
        start = i*sampRate+1;
        for(j=0; j<nlen; j++){
            data1[start+j] = Amplitude * sin(freq1a*j*2*Pi/sampRate);
            data2[start+j] = Amplitude * sin(freq2a*j*2*Pi/sampRate);
        }
    }
    
    /*長音(2秒)*/
    start = 3*sampRate+1;
    nlen = 2*sampRate;
    for(j=0; j<nlen; j++){
        data1[start+j] = Amplitude * sin(freq1b*j*2*Pi/sampRate);
        data2[start+j] = Amplitude * sin(freq2b*j*2*Pi/sampRate);
    }
    /*フェードアウト*/
    start = 4*sampRate+1;
    nlen = 1*sampRate;
    for(j=0; j<nlen; j++){
        data1[start+j] = data1[start+j]*(nlen-j)/nlen;
        data2[start+j] = data2[start+j]*(nlen-j)/nlen;
    }
    
    /*書き込み*/
    for(i=0; i<nSamples; i++){
        tmp = (short)data1[i];
        fwrite(&tmp, sizeof(short), 1, file1);
        tmp = (short)data2[i];
        fwrite(&tmp, sizeof(short), 1, file2);
    }
    
    free(data1);
    free(data2);
    fclose(file1);
    fclose(file2);
    return 0;
}

