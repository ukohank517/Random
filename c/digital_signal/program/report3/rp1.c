#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Pi 3.14159265358979

int main()
{

  char i_filename[128]="oto.raw";
  int size = 8000;
  short x[8000];
  double real[8000],imag[8000],result[8000];
  int n,k;
  FILE *file_input;


  if((file_input=fopen(i_filename,"rb"))==NULL){
    fprintf(stderr,"Cannot read %s .\n",i_filename);exit(-1);
  }

  fread(x,sizeof(short),8000,file_input);

  for(k=0;k<size;k++){
    real[k]=0;
    imag[k]=0;
    for(n=0;n<size;n++){
      real[k]+=(double)x[n]*cos(2*Pi*k*n/8000.0)/15000.0;//実数部
      imag[k]+=(double)x[n]*sin(2*Pi*k*n/8000.0)/15000.0;//虚数部
    }
    result[k]=sqrt(real[k]*real[k]+imag[k]*imag[k]);     //x[n]大きさを出す
    printf("%lf\n",result[k]);
  }
  fclose(file_input);
  return 0;
}  
