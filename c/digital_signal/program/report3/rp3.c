#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Pi 3.14159265358979

int main()
{
  char x_filename[128]="oto.raw";
  char h_filename[128]="filter_h.dat";
  char y_filename[128]="tatami.raw";
  float h[50],y[8000];
  short x[8000];
  float F_h[8000],F_x[8000],F_y[8000];
  int n,k,tmp;
  FILE *file_input;
  FILE *file_output;

  double real_x[8000],imag_x[8000];
  double real_h[8000],imag_h[8000];
  double real_y[8000],imag_y[8000];
  double real[8000],imag[8000];
  
  if((file_input=fopen(h_filename,"rb"))==NULL){
    fprintf(stderr,"Cannot read %s .\n",h_filename);exit(-1);
  }
  fread(h,sizeof(float),50,file_input);
  fclose(file_input);

  
  if((file_input=fopen(x_filename,"rb"))==NULL){
    fprintf(stderr,"Cannot read %s .\n",x_filename);exit(-1);
  }
  fread(x,sizeof(short),8000,file_input);
  fclose(file_input);

  
  //xのフーリエ変換    
  for(k=0;k<8000;k++){
    real_x[k]=0;
    imag_x[k]=0;
    for(n=0;n<8000;n++){
      if(n>8000) continue;
      real_x[k]+=(double)x[n]*cos(2*Pi*k*n/8000.0)/15000.0; 
      imag_x[k]+=(double)x[n]*sin(2*Pi*k*n/8000.0)/15000.0;
    }
    F_x[k]=sqrt(real_x[k]*real_x[k]+imag_x[k]*imag_x[k]);
  }
  
  //hのフーリエ変換
    for(k=0;k<8000;k++){
    real_h[k]=0;
    imag_h[k]=0;
    for(n=0;n<50;n++){
      if(n>50) continue;
      real_h[k]+=(double)h[n]*cos(2*Pi*k*n/8000.0)/15000.0;
      imag_h[k]+=(double)h[n]*sin(2*Pi*k*n/8000.0)/15000.0;
    }
    F_h[k]=sqrt(real_h[k]*real_h[k]+imag_h[k]*imag_h[k]);
  }
  
  //フィルタリング
  for(k=0;k<8000;k++){
    real_y[k]=real_x[k]*real_h[k]-imag_x[k]*imag_h[k];
    imag_y[k]=real_x[k]*imag_h[k]+imag_x[k]*real_h[k];
    F_y[k]=sqrt(real_y[k]*real_y[k]+imag_y[k]*imag_y[k]);
    //F_y[k]=F_x[k]*F_h[k];
    printf("%lf\n",F_y[k]);
  }
  //逆フーリエ
  for(n=0;n<8000;n++){
    real[n]=0;
    imag[n]=0;
    for(k=0;k<8000;k++){
       real[n]+=(double)real_y[k]*cos(2*Pi*k*n/8000.0);
       real[n]-=(double)imag_y[k]*sin(2*Pi*k*n/8000.0);//実部だけ使う為、虚部を省略
    }    
  }

  
  if((file_output = fopen(y_filename,"wb")) == NULL){
    fprintf(stderr, "Cannot write %s\n", y_filename);  exit(-1);
  }
  for(n=0;n<8000;n++){
    tmp = (short)(real[n]*8000);
    fwrite(&tmp, sizeof(short), 1, file_output);
  }

  fclose(file_output);
  
  
  
  return 0;
}

