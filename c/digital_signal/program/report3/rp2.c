#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Pi 3.14159265358979

int main()
{
  char x_filename[128]="oto.raw";
  char h_filename[128]="filter_h.dat";
  char y_filename[128]="tatami.raw";
  int size=8000;
  float h[50],y[8049];
  short x[8000];
  int n,k,tmp;
  FILE *file_input;
  FILE *file_output;

  //h[n]を読み込む
  if((file_input=fopen(h_filename,"rb"))==NULL){
    fprintf(stderr,"Cannot read %s .\n",h_filename);exit(-1);}
  //spwaveで、データ数が50であることを確認した為、っの長さを50にしました
  fread(h,sizeof(float),50,file_input);
  fclose(file_input);

  //x[n]を読み込む
  if((file_input=fopen(x_filename,"rb"))==NULL){
    fprintf(stderr,"Cannot read %s .\n",x_filename);exit(-1);
  }
  fread(x,sizeof(short),8000,file_input);
  fclose(file_input);

  //時間領域での畳み込み
  for(n=0;n<(size+49);n++)
    {
      y[n]=0.0;
      if(n>=size)continue;
      for(k=0;k<size;k++){
	if (k>50)continue;
	else if(n-k>=size)continue;
	y[n]+=(float)x[n-k]*(float)h[k];
      }
    }

  //ファイルへの書き込み
    if((file_output = fopen(y_filename,"wb")) == NULL){
    fprintf(stderr, "Cannot write %s\n", y_filename);  exit(-1);
    }
    for(n=0;n<size+49;n++){
      tmp = (short)y[n];
      fwrite(&tmp, sizeof(short), 1, file_output);
    }

    fclose(file_output);
    
    
  return 0;
}
  
