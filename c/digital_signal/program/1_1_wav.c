#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Pi 3.14159265358979

int length;
float *data;
int samp_freq;


void write_wav(char *filename)
{
  short tmp_short;
  int i;
  char s[4];
  short channel, var_short;
  int x, file_size;
  FILE *file_output;

  // file open
  if((file_output = fopen(filename,"wb")) == NULL){
    fprintf(stderr, "Cannot write %s\n", filename);  exit(-1);
  }
  // output header info.
  s[0] = 'R'; s[1] = 'I'; s[2] = 'F'; s[3] = 'F';
  fwrite(s, 1, 4, file_output);

  // filesize
  x = length * 2 + 36; // 16 bit = 2 byte
  fwrite(&x, 4, 1, file_output);

  // WAVE 
  s[0] = 'W'; s[1] = 'A'; s[2] = 'V'; s[3] = 'E';
  fwrite(s, 1, 4, file_output);

  // chunkID
  s[0] = 'f'; s[1] = 'm'; s[2] = 't'; s[3] = ' ';
  fwrite(s, 1, 4, file_output);

  // 
  x = 16;
  fwrite(&x, 4, 1, file_output);  

  //
  tmp_short = 1;
  fwrite(&tmp_short, 2, 1, file_output);

  //
  channel = 1;
  fwrite(&channel, 2, 1, file_output);  

  //
  fwrite(&samp_freq, 4, 1, file_output);

  //
  x = 2 * channel * samp_freq;
  fwrite(&x, 4, 1, file_output);

  //
  var_short = 2 * channel;
  fwrite(&var_short, 2, 1, file_output);  

  // bit/sample
  var_short = 16;
  fwrite(&var_short, 2, 1, file_output);  

  //
  s[0] = 'd'; s[1] = 'a'; s[2] = 't'; s[3] = 'a';
  fwrite(s, 1, 4, file_output);

  //
  file_size = length * 2 * channel;
  fwrite(&file_size, 4, 1, file_output);

  // end of header info.
  if( ftell(file_output) != 44 ){
    fprintf(stderr, "%s: wav header error.\n", filename);
  }

  // output data.
  for(i=0;i<length;i++){
    tmp_short = (short)data[i];
    fwrite(&tmp_short, sizeof(short), 1, file_output);
  }

  fclose(file_output);

  return;

} 


int main(int argc, char **argv)
{
  int n;
  short tmp;
  float time;
  double a, f0;

  samp_freq = 8000;  // Hz
  time = 0.5;  // second
  a = 1000;
  f0 = 500;   // Hz

  length = (int)(time*samp_freq);
  data = calloc(length, sizeof(float));

  for(n=0;n<length;n++){
    data[n] = a * sin(2.0*Pi*f0*n/samp_freq);
    //tmp = (short)data[n];
    //fprintf(file_output, "%d\n", tmp);
  }

  write_wav(argv[1]);

}
