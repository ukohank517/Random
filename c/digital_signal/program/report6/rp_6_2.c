#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define A 0
#define I 1
#define U 2
#define E 3
#define O 4
#define MAX_SIZE 28000
#define Pi 3.14159265358979






#define N 50//中間層の数

double function(double u){
  return 1/(1+exp(-u));
}

float diff_function(float u){
  return (1-function(u))*function(u);
}


int main()
{

  double ***power;
  int size,i,j,k,count;

  FILE *file_input;
  FILE *file_output;



  fprintf(stderr,"初期化中.\n");
  //**************************
  //下準備
  size=(MAX_SIZE-(192-32))/32;
    
  //フーリエ変換した結果
  if((power=(double ***)calloc(5,sizeof(double **)))==NULL){
    fprintf(stderr,"cannot calloc ***power.\n");
  }
  for(i=A;i<=O;i++){
    if((power[i]=(double **)calloc(size,sizeof(double *)))==NULL){
      fprintf(stderr,"cannot calloc **power[%d]\n",i+1);exit(-1);
    }
    for(j=0;j<size;j++){
      if((power[i][j]=(double *)calloc(95,sizeof(double)))==NULL){
	fprintf(stderr,"cannot calloc *power[%d][%d]\n",i+1,j+1);exit(-1);
      }
    }
  }

  char F[5][128]={"P_a.dat","P_i.dat","P_u.dat","P_e.dat","P_o.dat"};
  double data[167040];
  for(i=0;i<5;i++){
    if((file_input = fopen(F[i],"rb")) == NULL){
      fprintf(stderr, "Cannot open %s\n", F[i]);  exit(-1);
    }
    fread(data,sizeof(double),167040,file_input);
    fclose(file_input);
    for(j=0;j<size;j++){
      for(k=0;k<95;k++){
	power[i][j][k]=data[j*95+k];
      }
    }
  }


  //==============================
  //ここから
  double *heikin;
  double d[5][5];//d[class][あ〜う]
  double w1[N][95],w2[5][N],n_w1[N][95],n_w2[5][N];
  double uj[N],uk[5],gj[N],y[5];
  double err[300];
  double sum;
  int n,num_update;
  double wei;

  wei=1.0/(95.0*5.0);
  if((heikin=(double *)calloc(95,sizeof(double )))==NULL){
    fprintf(stderr,"cannot calloc *heikin.\n");
  }

  for(i=0;i<95;i++){
    heikin[i]=0;
    for(j=0;j<5;j++){
      for(k=0;k<size;k++){
	heikin[i]+=power[j][k][i];
      }
    }
    heikin[i]=(1.0/(5.0*(double)size))*heikin[i];
  }
  for(i=0;i<5;i++){
    for(j=0;j<size;j++){
      for(k=0;k<95;k++){
	power[i][j][k]-=heikin[k];
      }
    }
  }

  for(i=0;i<5;i++){
    for(j=0;j<5;j++){
      if(i==j)d[i][j]=1.0;
      else d[i][j]=0.0;
    }
  }

  //実行する度に違う乱数を得られる。信憑性を高まる。
  srand((unsigned)time(NULL));
  //w1の初期化
  sum=0.0;
  for(i=0;i<N;i++){
    for(j=0;j<95;j++){
      w1[i][j]=0.1*(double)rand()/RAND_MAX;
      sum+=w1[i][j];
    }
  }

  sum=sum/((double)N*95.0);
  for(i=0;i<N;i++){
    for(j=0;j<95;j++){
      w1[i][j]=w1[i][j]-sum;
    }
  }
  //w2の初期化
  sum=0.0;
  for(i=0;i<5;i++){
    for(j=0;j<N;j++){
      w2[i][j]=0.1*(double)rand()/RAND_MAX;
      sum+=w2[i][j];
    }
  }
  
  sum=sum/((double)N*5.0);
  for(i=0;i<5;i++){
    for(j=0;j<N;j++){
      w2[i][j]=w2[i][j]-sum;//平均を0にするために
    }
  }

  fprintf(stderr,"初期化完了、計算に入ります.\n");
  for(num_update=0;num_update<300;num_update++){
    for(i=0;i<N;i++){
      for(j=0;j<95;j++){
	n_w1[i][j]=w1[i][j];
      }
      for(j=0;j<5;j++){
	n_w2[j][i]=w2[j][i];
      }
    }
    err[num_update]=0.0;

    for(n=0;n<size*5;n++){
      //変数の初期化
      for(j=0;j<N;j++){
	uj[j]=0;
	gj[j]=0;
      }
      for(j=0;j<5;j++){
	uk[j]=0;
      }
      //重みが変わる時に変数の変化
      for(j=0;j<N;j++){
	for(i=0;i<95;i++){
	  uj[j]+=w1[j][i]*power[n/size][n%size][i];
	}
	gj[j]=function(uj[j]);
      }

      for(k=0;k<5;k++){
	for(j=0;j<N;j++){
	  uk[k]+=w2[k][j]*gj[j];
	}
	y[k]=function(uk[k]);
      }

      for(k=0;k<5;k++){
	err[num_update]+=(y[k]-d[n/size][k])*(y[k]-d[n/size][k]);
      }

      //w2更新
      for(k=0;k<5;k++){
	for(j=0;j<N;j++){
	  n_w2[k][j]+=(1/(double)size)*(d[n/size][k]-y[k])*diff_function(uk[k])*gj[j];
	}
      }
      
      //w1更新
      for(j=0;j<N;j++){
	for(i=0;i<95;i++){
	  sum=0;
	  for(k=0;k<5;k++){
	    sum+=(d[n/size][k]-y[k])*diff_function(uk[k])*w2[k][j];
	  }
	  n_w1[j][i]+=(1/(double)size)*sum*diff_function(uj[j])*power[n/size][n%size][i];
	}
      }
    }
    //更新した値を代入
    for(i=0;i<N;i++){
      for(j=0;j<95;j++){
	w1[i][j]=n_w1[i][j];
      }
      for(j=0;j<5;j++){
	w2[j][i]=n_w2[j][i];
      }
    }
    fprintf(stderr,"%d/300回目重み更新完了.\n",num_update+1);
  }

  
  fprintf(stderr,"誤差をファイルに保存中.\n");
  //誤差の出力、保存
  if((file_output = fopen("err.dat","w")) == NULL){
    fprintf(stderr,"cannot write err.dat\n");return(-1);
  }
  for(num_update=0;num_update<300;num_update++){
    fprintf(file_output,"%f\n",err[num_update]);
  }
  fclose(file_output);

  fprintf(stderr,"重みをファイルに保存中.\n");
  //重みの出力、保存
  if((file_output = fopen("w1.dat","w")) == NULL){
    fprintf(stderr,"cannot write w1.dat\n");return(-1);
  }
  for(i=0;i<N;i++){
    for(j=0;j<95;j++){
      fprintf(file_output,"%f\n",w1[i][j]);
    }
  }
  fclose(file_output);
  if((file_output = fopen("w2.dat","w")) == NULL){
    fprintf(stderr,"cannot write w2.dat\n");return(-1);
  }
  for(i=0;i<5;i++){
    for(j=0;j<N;j++){
      fprintf(file_output,"%f\n",w2[i][j]);
    }
  }
  fclose(file_output);



  if((file_output = fopen("heikin.dat","w")) == NULL){
    fprintf(stderr,"cannot write heikin.dat\n");return(-1);
  }
  for(i=0;i<95;i++){
    fprintf(file_output,"%f\n",heikin[i]);
  }
  fclose(file_output);

  fprintf(stderr,"操作が完了しました。\n");

  
  


  
  free(heikin);
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
