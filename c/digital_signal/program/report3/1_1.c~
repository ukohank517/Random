#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Pi 3.14159265358979

int main(void)
{
  char filename[128] = "sin21.raw";
  int n, length;
  short tmp;
  float samp_freq, time, *data;
  double a, f0;
  FILE *file_output;

  samp_freq = 8000;  // Hz
  time = 0.5;  // second
  a = 6000;
  f0 = 500;   // Hz

  if((file_output = fopen(filename,"wb")) == NULL){
    fprintf(stderr, "Cannot write %s\n", filename);  exit(-1);
  }

  length = (int)(time*samp_freq);
  data = calloc(length, sizeof(float));

  for(n=0;n<length;n++){
    data[n] = a * sin(2.0*Pi*f0*n/samp_freq);
    tmp = (short)data[n];
    fwrite(&tmp, sizeof(short), 1, file_output);
  }

  fclose(file_output);
}
