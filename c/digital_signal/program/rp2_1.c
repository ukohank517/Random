#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Pi 3.14159265358979

int main(void)
{
  char o_filename[128] = "sin21.raw";
  char i_filename[128] = "impulse_16khz.dat";
  int n,length,i,size;
  short tmp;
  float fs, f0,time, *data,h[10000],*y;
  double a;
  FILE *file_output;
  FILE *file_input;
  float freq;
  int count;

  fs = 16000;  // Hz
  time = 0.6;  // second
  a = 15000;


  if((file_output = fopen(o_filename,"wb")) == NULL){
    fprintf(stderr, "Cannot write %s\n", o_filename);  exit(-1);
  }
  if((file_input = fopen(i_filename,"rb")) == NULL){
    fprintf(stderr, "Cannot open %s\n", i_filename);  exit(-1);
  }

  size = fread( h, sizeof( float ), 10000, file_input );

  length = (int)(time*fs);
  data = calloc(length, sizeof(float));
  y = calloc(length+size-1,sizeof(float));


  count=0;  
  for(n=0;n<length;n++){
    if(n<0.1*length){f0=987.77;}
    else f0=1318.51;

    freq = 0.5*fs/f0;
    
    if(count>=freq){
      count =0;
      a*=(-1);
    }

    data[n]=a;
    count++;
    data[n]*=(1.0-(double)n/(0.6*fs));
    
  }


  for(n=0;n<size+length-1;n++){
    y[n]=0;
    for (i=0;i<size+length-1;i++){
      if (n<i) continue;
      else if (i>length) continue;
      else if (n-i>size) continue;
      else	
	y[n]+=data[i]*h[n-i];
    }
    tmp = (short)y[n];
    fwrite(&tmp, sizeof(short), 1, file_output);
  }
  
  fclose(file_input);
  fclose(file_output);
  free(data);
  free(y); 
}
