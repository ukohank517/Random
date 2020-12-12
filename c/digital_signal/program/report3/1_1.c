#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Pi 3.14159265358979

int main(void)
{
  char o_filename[128] = "sin21.raw";
  char i_filename[128] ="oto.raw";
  int n,k, length;
  short tmp;
  float samp_freq, time, *data;
  short x[8000];
  double a, f0;
  double real[8000],imag[8000],result[8000];
  FILE *file_output;
  FILE *file_input;
  int size;
  
  samp_freq = 8000;  // Hz
  time = 1.0;  // second
  f0 = 500;   // Hz
  
  
  
  if((file_input= fopen(i_filename,"rb"))==NULL){
    fprintf(stderr,"Cannot read %s \n",i_filename);exit(-1);
  }

  size=8000;
  fread( x, sizeof( short ), 8000, file_input );
 
  for(k=0;k<size;k++){
   real[k]=0;
   imag[k]=0;
   for(n=0;n<size;n++){
     real[k]+=(double)x[n]*cos(2*Pi*k*n/8000);
     imag[k]+=(double)x[n]*sin(2*Pi*k*n/8000);
   }
   real[k]/=15000;
   imag[k]/=15000;
  }
  
  
  for(k=0;k<size;k++){
    result[k]=sqrt(real[k]*real[k]+imag[k]+imag[k]);
    printf("%lf\n",result[k]);
  }


  

  if((file_output = fopen(o_filename,"wb")) == NULL){
    fprintf(stderr, "Cannot write %s\n", o_filename);  exit(-1);
  }
  
  length = (int)(time*samp_freq);
  data = calloc(length, sizeof(short));
    
  for(n=0;n<length;n++){
    //data[n] = a * sin(2.0*Pi*f0*n/samp_freq);
    data[n]=result[n];
    tmp = (short)data[n];
    fwrite(&tmp, sizeof(short), 1, file_output);
  }
  
  fclose(file_output);
  fclose(file_output);
  free(data);
}
