#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Pi 3.14159265358979
#define alpha 0.01
#define K 50   //changed everytime to ensure the output



int main()
{
  char d_filename[128]="observed_song1.raw";//short
  char x_filename[128]="song1.raw";//short
  char h_filename[128]="imp.dat";//float,60
  char s_filename[128]="speech1.raw";//short
  char e_filename[128]="e.raw";
  
  int samp_freq = 8000;
  int k,n;
  
  float h[8000];
  short d[160000],x[160000],s[8000],tmp;
  FILE *file_input;
  FILE *file_output;

  double e[160000];
  double h_n[K]={0.0},h_n1[K]={0.0},norm;
  //double h;
  
  if((file_input=fopen(d_filename,"rb"))==NULL){
    fprintf(stderr,"Cannot read %s .\n",d_filename);exit(-1);
  }
  fread(d,sizeof(short),160000,file_input);
  fclose(file_input);

  if((file_input=fopen(x_filename,"rb"))==NULL){
    fprintf(stderr,"Cannot read %s.\n",x_filename);exit(-1);
  }
  fread(x,sizeof(float),160000,file_input);
  fclose(file_input);

  for(n=0;n<160000;n++){
    e[n]=(double)d[n];
    norm=0.0;
    for(k=0;k<K;k++){
      h_n1[k]=h_n[k];
      if (n>k){
	norm+=(double)x[n-k]*(double)x[n-k];
      }
    }

    for(k=0;k<K;k++){
      if (n>k){
	e[n]-=h_n[k]*(double)x[n-k];
      }
    }

    for(k=0;k<K;k++){
      if (n>k){
	h_n1[k]=h_n[k]+(double)alpha*(double)e[n]*(double)x[n-k]/norm;      
      }
    }
  }

  

  if((file_output = fopen(e_filename,"wb")) == NULL){
    fprintf(stderr, "Cannot write %s\n", e_filename);  exit(-1);
  }
  for(n=0;n<160000;n++){
    tmp = (short)e[n];
    fwrite(&tmp, sizeof(short), 1, file_output);
  }
  
  fclose(file_output);



  return 0;
}
  
