#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define Pi 3.14159265358979
#define alpha 0.01
#define K 50   //changed everytime to ensure the output
#define MAX 300000

int main(){
  char d_filename[128]="observed_song1.raw";//short
  char x_filename[128]="song1.raw";//short
  char h_filename[128]="imp.dat";//float,60
  char s_filename[128]="speech1.raw";//short
  char e_filename[128]="e.raw";
  
  int samp_freq = 8000;
  int k,n,size_d,size_x;
  
  short *d,*x,s[MAX],tmp;
  FILE *file_input;
  FILE *file_output;

  double e[160000];
  double h_n[K]={0},h_n1[K]={0},norm;
  //double h;

  int count =0;

  //operation of d
  if((file_input=fopen(d_filename,"rb"))==NULL){
    fprintf(stderr,"Cannot read %s .\n",d_filename);exit(-1);
  }
  size_d=fread(s,sizeof(short),MAX,file_input);
  d=(short *)calloc(size_d,sizeof(float));
  fclose(file_input);
  if((file_input=fopen(d_filename,"rb"))==NULL){
    fprintf(stderr,"Cannot read %s .\n",d_filename);exit(-1);
  }
  fread(d,sizeof(short),size_d,file_input);
  fclose(file_input);





  //operation of x
  if((file_input=fopen(x_filename,"rb"))==NULL){
    fprintf(stderr,"Cannot read %s.\n",x_filename);exit(-1);
  }
  size_x=fread(s,sizeof(short),MAX,file_input);
  x=(short *)calloc(size_x,sizeof(short));
  fclose(file_input);
  if((file_input=fopen(x_filename,"rb"))==NULL){
    fprintf(stderr,"Cannot read %s.\n",x_filename);exit(-1);
  }
  fread(x,sizeof(short),size_x,file_input);
  fclose(file_input);
  

  for(n=0;n<size_d;n++){
    if(n==8000*2){
      printf("%lf\n",h_n[k]);
    }

    

    
    e[n]=(double)d[n];
    //∵at this time,n=n+1 ∴update the h_n1 to h_n
    for(k=0;k<K;k++){
      h_n[k]=h_n1[k];
      e[n]-=h_n[k]*x[n-k];

    }
    norm=0.0;//initial norm
    for(k=0;k<K;k++){
      if(n>k){
	norm+=x[n-k]*x[n-k];
      }
    }
    
    for(k=0;k<K;k++){
      h_n1[k]=h_n[k];
      if(norm==0){
	  norm = 1;
      }
      h_n1[k]=h_n[k]+alpha*e[n]*x[n-k]/norm;
    }
  }
  
  
  
  if((file_output = fopen(e_filename,"wb")) == NULL){
    fprintf(stderr, "Cannot write %s\n", e_filename);  exit(-1);
  }
  for(n=0;n<size_d;n++){
    //printf("%lf\n",e[n]);  //use gnuplot to plot error
    tmp = (short)e[n];
    fwrite(&tmp, sizeof(short), 1, file_output);
  }
  
  //output the filter coefficient
  for(k=0;k<K;k++){
    printf("%f\n",h_n[k]);
  }
  fclose(file_output);





  short a[300000];
  

  free(d);
  free(x);
  return 0;
}
