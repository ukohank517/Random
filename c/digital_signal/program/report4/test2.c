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
  char h_filename[128]="imp.dat";//float
  char e_filename[128]="e.raw";
  
  
  int k,n,size_h,size_d,size_x;
  
  short *d,*x,s[MAX],tmp;
  float *h,f[MAX];
  FILE *file_input;
  FILE *file_output;
  
  double e[160000];
  double h_n[K]={0},h_n1[K]={0},norm;
  //double h;

  
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



  
    //operation of h
  if((file_input=fopen(h_filename,"rb"))==NULL){
    fprintf(stderr,"Cannot read %s.\n",h_filename);exit(-1);
  }
  size_h=fread(f,sizeof(float),MAX,file_input);
  h=(float *)calloc(size_h,sizeof(float));
  fclose(file_input);
  if((file_input=fopen(h_filename,"rb"))==NULL){
    fprintf(stderr,"Cannot read %s.\n",h_filename);exit(-1);
  }
  fread(h,sizeof(float),size_h,file_input);
  fclose(file_input);


  
  //for(k=0;k<size_h;k++){
  // printf("%lf\n",h[k]);
  //}
  
  
  for(n=0;n<size_d;n++){
    if(n==8000*10){
     for(k=0;k<K;k++){
    	printf("%lf\n",h_n[k]);}
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
  

  fclose(file_output);





  

  free(d);
  free(x);
  free(h);
  return 0;
}
