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

  //**************************
  //下準備
  //フーリエ変換した結果
  if((power=(double ***)calloc(5,sizeof(double **)))==NULL){
    fprintf(stderr,"cannot calloc ***power.\n");
  }
  for(i=A;i<=O;i++){
    size=(MAX_SIZE-(192-32))/32;
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
  double err[500];
  double sum;
  int n,num_update;
  double wei;

  wei=1.0/95.0;
  if((heikin=(double *)calloc(95,sizeof(double )))==NULL){
    fprintf(stderr,"cannot calloc *heikin.\n");
  }

  for(i=0;i<95;i++){
    heikin[i]=0;
    for(j=0;j<5;j++){
      for(k=0;k<size;k++){
	heikin[i]+=(1/(5*95))*power[j][k][i];
      }
    }
    printf("%lf\n",heikin[i]);
  }

  for(i=0;i<5;i++){
    for(j=0;j<size;j++){
      for(k=0;k<95;k++){
	power[i][j][k]=power[i][j][k]-heikin[k];
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
      w1[i][j]=0.00001*(double)rand()/RAND_MAX;
      sum+=w1[i][j];
    }
  }

  sum=sum/4;
  for(i=0;i<N;i++){
    for(j=0;j<95;j++){
      w1[i][j]=w1[i][j]-sum;
    }
  }
  //w2の初期化
  sum=0.0;
  for(i=0;i<5;i++){
    for(j=0;j<N;j++){
      w2[i][j]=0.001*(double)rand()/RAND_MAX;
      sum+=w2[i][j];
    }
  }

  sum=sum/4;
  for(i=0;i<5;i++){
    for(j=0;j<N;j++){
      w2[i][j]=w2[i][j]-sum;//平均を0にするために      
    }
  }

  for(num_update=0;num_update<500;num_update++){
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
      for(j=0;j<50;j++){
	uj[j]=0;
	gj[j]=0;
      }
      for(j=0;j<5;j++){
	uk[j]=0;
      }
      //重みが変わる時に変数の変化
      for(j=0;j<50;j++){
	for(i=0;i<95;i++){
	  uj[j]+=w1[j][i]*power[n/size][n%size][i];//
      	}

	gj[j]=function(uj[j]);
      }
      for(k=0;k<5;k++){
	for(j=0;j<50;j++){
	  uk[k]+=w2[k][j]*gj[j];
	}
	y[k]=function(uk[k]);

      }
      for(k=0;k<5;k++){
	err[num_update]+=(y[k]-d[n/size][k])*(y[k]-d[n/size][k]);
      }
      
      
      //2-3層の間の重みw2を更新
      for(k=0;k<5;k++){
	for(j=0;j<50;j++){
	  n_w2[k][j]+=wei*(d[n/size][k]-y[k])*diff_function(uk[k])*gj[j];
	}
      }
      //1-2層の間の重みw1を更新
      for(j=0;j<N;j++){
	for(i=0;i<95;i++){
	  sum=0;
	  for(k=0;k<5;k++){
	    sum+=(d[n/size][k]-y[k])*diff_function(uk[k])*w2[k][j];
	  }
	  n_w1[j][i]+=1/(5*95)*sum*diff_function(uj[j])*power[n/size][n%size][i];
	}
      }
    }
    //更新した重みn_wをwに代入する
    
    for(i=0;i<N;i++){
      for(j=0;j<95;j++){
	w1[i][j]=n_w1[i][j];
      }
      for(j=0;j<5;j++){
	w2[j][i]=n_w2[j][i];
      }
    }
    fprintf(stderr,"%lf\n",err[num_update]);
  }



    


  printf("w1\n");
  for(i=0;i<N;i++){
    for(j=0;j<95;j++){
      w1[i][j]=n_w1[i][j];
      printf("%lf\n",w1[i][j]);
    }
  }
  printf("w2\n");
  for(i=0;i<N;i++){
    for(j=0;j<5;j++){
      printf("%lf\n",w2[j][i]);
    }
  }
  
  

  
  
  
  
  
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
