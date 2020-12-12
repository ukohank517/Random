#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define A 0
#define I 1
#define U 2
#define E 3
#define O 4
#define MAX_SIZE 28000 //8000*3.5
#define Pi 3.14159265358979

int main()
{
  char filename[5][128]={"a.raw","i.raw","u.raw","e.raw","o.raw"};

  int size,i,j,n,k,count;

  short **data;//ファイルデータ
  short ***data_data;//分割されたデータを保存する場所
  double ***real_data_data;
  double ***image_data_data;
  double ***F_data_data;
  FILE *file_input;
  FILE *file_output;
  
  double ***power;

  size=(MAX_SIZE-(192-32))/32;

  //dataは全部アイウエオで五種類
  if( (data=(short **)calloc(5,sizeof(short *))) == NULL ){
    fprintf(stderr,"cannot calloc memory **data.\n");    exit(-1);
  }
  //一種類のデータにはデータ数3.5*8000=28000個
  for(i=A;i<=O;i++){
    if( (data[i]=(short *)calloc(MAX_SIZE,sizeof(short))) == NULL ){
      fprintf(stderr,"cannot calloc memory *data%d.\n",i+1);    exit(-1);
    }
  }
  //とりあえずファイルを読み込む
  for(i=A;i<=O;i++){
    if((file_input=fopen(filename[i],"rb"))==NULL){
      fprintf(stderr,"cannot read %s. \n",filename[i]);exit(-1);
    }
    fread(data[i],sizeof(short),MAX_SIZE,file_input);//結果をdataに保存する
    fclose(file_input);
  }
  
  //分割データの保存先
  if((data_data=(short ***)calloc(5,sizeof(short **)))==NULL){
    fprintf(stderr,"cannot calloc ***data_data.\n");
  }
  //      フーリエ変換した実数部
  if((real_data_data=(double ***)calloc(5,sizeof(double **)))==NULL){
    fprintf(stderr,"cannot calloc ***real_data_data.\n");
  }
  //      フーリエ変換した虚数部
  if((image_data_data=(double ***)calloc(5,sizeof(double **)))==NULL){
    fprintf(stderr,"cannot calloc ***image_data_data.\n");
  }
  //      フーリエ変換した結果
  if((F_data_data=(double ***)calloc(5,sizeof(double **)))==NULL){
    fprintf(stderr,"cannot calloc ***F_data_data.\n");
  }
  //      パワースペクトルの自然対数を保存する
  if((power=(double ***)calloc(5,sizeof(double **)))==NULL){
    fprintf(stderr,"cannot calloc ***power.\n");
  }
  
  for(i=A;i<=O;i++){
    if((data_data[i]=(short **)calloc(size,sizeof(short *)))==NULL){
      fprintf(stderr,"cannot calloc **data_data[%d]\n",i+1);exit(-1);
    }
    if((real_data_data[i]=(double **)calloc(size,sizeof(double *)))==NULL){
      fprintf(stderr,"cannot calloc **real_data_data[%d]\n",i+1);exit(-1);
    }
    if((image_data_data[i]=(double **)calloc(size,sizeof(double *)))==NULL){
      fprintf(stderr,"cannot calloc **image_data_data[%d]\n",i+1);exit(-1);
    }
    if((F_data_data[i]=(double **)calloc(size,sizeof(double *)))==NULL){
      fprintf(stderr,"cannot calloc **F_data_data[%d]\n",i+1);exit(-1);
    }
    if((power[i]=(double **)calloc(size,sizeof(double *)))==NULL){
      fprintf(stderr,"cannot calloc **power[%d]\n",i+1);exit(-1);
    }
    
    for(j=0;j<size;j++){
      if((data_data[i][j]=(short *)calloc(192,sizeof(short)))==NULL){
	fprintf(stderr,"cannot calloc *data_data[%d][%d]\n",i+1,j+1);exit(-1);
      }
      if((real_data_data[i][j]=(double *)calloc(192,sizeof(double)))==NULL){
	fprintf(stderr,"cannot calloc *real_data_data[%d][%d]\n",i+1,j+1);exit(-1);
      }
      if((image_data_data[i][j]=(double *)calloc(192,sizeof(double)))==NULL){
	fprintf(stderr,"cannot calloc *image_data_data[%d][%d]\n",i+1,j+1);exit(-1);
      }
      if((F_data_data[i][j]=(double *)calloc(192,sizeof(double)))==NULL){
	fprintf(stderr,"cannot calloc *F_data_data[%d][%d]\n",i+1,j+1);exit(-1);
      }
      if((power[i][j]=(double *)calloc(192,sizeof(double)))==NULL){
	fprintf(stderr,"cannot calloc *power[%d][%d]\n",i+1,j+1);exit(-1);
      }//自然対数だけは1〜95までの95個のデータ
    }
  }
  
  
  //データ分割且つ格納手順
  count=0;
  for(i=A;i<=O;i++){
    j=0;
    for(n=0;j<size;n++,count++){
      data_data[i][j][count]=data[i][n];
      if(count==191){      
	count=-1;
	j++;
	n=j*32-2;
      }
    }
  }
  //読み込んだデータはもう使わないので、メモリーの節約の為に解放する
  for(i=A;i<=O;i++){
    free(data[i]);
  }
  free(data);
  

  
  //次にdata_dataのフーリエ変換
  for(i=A;i<=O;i++){
    for(j=0;j<size;j++){
      for(k=0;k<192;k++){
	real_data_data[i][j][k]=0;
	real_data_data[i][j][k]=0;
	for(n=0;n<192;n++){
	  real_data_data[i][j][k]+=(double)data_data[i][j][n]*cos(2*Pi*k*n/192);
	  image_data_data[i][j][k]+=(double)data_data[i][j][n]*sin(2*Pi*k*n/192);
	}
	F_data_data[i][j][k]=(real_data_data[i][j][k]*real_data_data[i][j][k]+image_data_data[i][j][k]*image_data_data[i][j][k]);
      }
    }
  }
  //ここも、フーリエ変換する前のメモリー領域はもう使わない為、メモリーを各階層に渡って順次解放する
  for(i=A;i<=O;i++){
    for(j=0;j<size;j++){
      free(data_data[i][j]);
    }
    free(data_data[i]);
  }
  free(data_data);
  
  
  
  //パワースペクトルの自然対数  
  for(i=0;i<5;i++){
    for(j=0;j<size;j++){
      for(k=0;k<95;k++){
	power[i][j][k]=log(F_data_data[i][j][k+1]);
      }
    }
  }
  //上の動作によって、フーリエ変換したデータはもう使わないので、領域解放
  for(i=A;i<=O;i++){
    for(j=0;j<size;j++){
      free(F_data_data[i][j]);
      free(real_data_data[i][j]);
      free(image_data_data[i][j]);
    }
    free(F_data_data[i]);
    free(real_data_data[i]);
    free(image_data_data[i]);
  }
  free(F_data_data);
  free(real_data_data);
  free(image_data_data);




  
  
  //一時的にパワースペクトルの自然対数値をファイルに出力する。
  //計算時間を短縮する為に
  char P[5][128]={"P_a.dat","P_i.dat","P_u.dat","P_e.dat","P_o.dat"};

  for(i=0;i<5;i++){
    if((file_output = fopen(P[i],"wb")) == NULL){
      fprintf(stderr, "Cannot write %s\n", P[i]);  exit(-1);
    }
    for(j=0;j<size;j++){
      for(k=0;k<95;k++){
	fwrite(&power[i][j][k],sizeof(double),1,file_output);
      }
    }
    fclose(file_output);

  }
  
 
  


  //後始末、領域確保によって格納された場所を各階層に渡って順次解放
  for(i=A;i<=O;i++){
    for(j=0;j<size;j++){
      free(power[i][j]);
    }
    free(power[i]);
  }
  free(power);

  
  return 0;
}
