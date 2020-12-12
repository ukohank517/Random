#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Pi 3.14159265358979
#define N 50


double function(double u){
  return 1/(1+exp(-u));
}


int main(){
  int i,j,k,n,size,count,data_size;
  double w1[50][95],w2[5][50];
  short *test;
  short **data;
  double **real_data,**image_data,**F_data;
  double **power,**y;
  double heikin[95];
  double uj[N],uk[5],gj[N];
  FILE *file_input;
  fpos_t sz;
  
  if((file_input = fopen("heikin.dat","r"))==NULL){
    fprintf(stderr,"cannot read heikin.dat\n");exit(-1);
  }
  for(j=0;j<95;j++){
    fscanf(file_input,"%lf",&heikin[j]);
  }
  fclose(file_input);

  
  if((file_input = fopen("w1.dat","r"))==NULL){
    fprintf(stderr,"cannot read w1.dat\n");exit(-1);
  }
  for(i=0;i<50;i++){
    for(j=0;j<95;j++){
      fscanf(file_input,"%lf",&w1[i][j]);
    }
  }
  fclose(file_input);

  if((file_input = fopen("w2.dat","r"))==NULL){
    fprintf(stderr,"cannot read w2.dat\n");exit(-1);
  }
  for(i=0;i<5;i++){
    for(j=0;j<50;j++){
      fscanf(file_input,"%lf",&w2[i][j]);
    }
  }
  fclose(file_input);
  //testデーターの中身のサイズを測る
  if((file_input=fopen("i.raw","rb"))== NULL){
    printf( "test.rawファイルが開けません¥n");exit(-1);
  }
  fseek(file_input, 0, SEEK_END);
  fgetpos(file_input, &sz);
  //その長さを使う,shortは2バイト
  data_size=sz/2;
  if((test=(short *)calloc(data_size,sizeof(short)))==NULL){
    fprintf(stderr,"cannot calloc *short.\n");
  }
  if((file_input=fopen("test.raw","rb"))== NULL){
    printf( "test.rawファイルが開けません¥n");exit(-1);
  }
  fread(test,sizeof(short),data_size,file_input);
  fclose(file_input);
  data_size=(data_size-(192-32))/32;

  if((data=(short**)calloc(data_size,sizeof(short*)))==NULL){
    fprintf(stderr,"cannot callo **data\n");exit(-1);
  }
  if((real_data=(double**)calloc(data_size,sizeof(double*)))==NULL){
    fprintf(stderr,"cannot callo **real_data\n");exit(-1);
  }
  if((image_data=(double**)calloc(data_size,sizeof(double*)))==NULL){
    fprintf(stderr,"cannot callo **image_data\n");exit(-1);
  }
  if((F_data=(double**)calloc(data_size,sizeof(double*)))==NULL){
    fprintf(stderr,"cannot callo **F_data\n");exit(-1);
  }
  if((power=(double**)calloc(data_size,sizeof(double*)))==NULL){
    fprintf(stderr,"cannot callo **power\n");exit(-1);
  }
  if((y=(double**)calloc(data_size,sizeof(double*)))==NULL){
    fprintf(stderr,"cannot callo **y\n");exit(-1);
  }
 
  for(i=0;i<data_size;i++){
    if((data[i]=(short*)calloc(192,sizeof(short)))==NULL){
      fprintf(stderr,"cannot callo *data\n");exit(-1);
    }
    if((real_data[i]=(double*)calloc(192,sizeof(double)))==NULL){
      fprintf(stderr,"cannot callo *real_data\n");exit(-1);
    }
    if((image_data[i]=(double*)calloc(192,sizeof(double)))==NULL){
      fprintf(stderr,"cannot callo *image_data\n");exit(-1);
    }
    if((F_data[i]=(double*)calloc(192,sizeof(double)))==NULL){
      fprintf(stderr,"cannot callo *F_data\n");exit(-1);
    }
    if((power[i]=(double*)calloc(95,sizeof(double)))==NULL){
      fprintf(stderr,"cannot callo *power\n");exit(-1);
    }
    if((y[i]=(double*)calloc(5,sizeof(double)))==NULL){
      fprintf(stderr,"cannot callo *y\n");exit(-1);
    }    
    
  }

  //テストデータの分割
  count=0;
  j=0;
  for(i=0;j<data_size;i++,count++){
    data[j][count]=test[i];
    if(count==191){
      count=-1;
      j++;
      i=j*32-2;
    }
  }
  //フーリエ変換
  for(j=0;j<data_size;j++){
    for(k=0;k<192;k++){
      real_data[j][k]=0;
      image_data[j][k]=0;
      for(n=0;n<192;n++){
	real_data[j][k]+=(double)data[j][n]*cos(2*Pi*k*n/192);
	image_data[j][k]+=(double)data[j][n]*sin(2*Pi*k*n/192);
      }
      F_data[j][k]=(real_data[j][k]*real_data[j][k]+image_data[j][k]*image_data[j][k]);
    }
  }
  //パワースペクトルの自然対数を出す
  for(j=0;j<data_size;j++){
    for(k=0;k<95;k++){
      power[j][k]=log(F_data[j][k+1]);
    }
  }
  //正規化
  for(j=0;j<data_size;j++){
    for(k=0;k<95;k++){
      power[j][k]-=heikin[k];
    }
  }
  
  //ニューラルネットワークに通す。
  for(n=0;n<data_size;n++){
    //変数の初期化
    for(j=0;j<N;j++){
      uj[j]=0;
      gj[j]=0;
    }
    for(j=0;j<5;j++){
      uk[j]=0;
    }
    //第一層の入出力
    for(j=0;j<N;j++){
      for(i=0;i<95;i++){
	uj[j]+=w1[j][i]*power[i][n];
      }
      gj[j]=function(uj[j]);
    }
    //第二層の入出力
    for(k=0;k<5;k++){
      for(j=0;j<N;j++){
	uk[k]+=w2[k][j]*gj[j];
      }
      y[n][k]=function(uk[k]);
    } 
  }
  //結果表示
  for(k=0;k<5;k++){
    for(j=0;j<data_size;j++){
      printf("%lf\n",y[100][k]);
    }
  }
  //領域の解放  
  free(test);

  for(i=0;i<data_size;i++){
    free(data[i]);
    free(real_data[i]);
    free(image_data[i]);
    free(F_data[i]);
    free(power[i]);
    free(y[i]);
  }
  free(data);
  free(real_data);
  free(image_data);
  free(F_data);
  free(power);
  free(y);
  return 0;
}
