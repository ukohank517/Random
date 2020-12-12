#include <stdio.h>

int main(){
  int i;
  FILE *file_output;
  
  if((file_output = fopen("err.dat","w")) == NULL){
    fprintf(stderr,"cannot write err.dat\n");return(-1);
  }
  for(i=0;i<100;i++){
    fprintf(file_output,"%d\n",i);
  }
  fclose(file_output);

  return 0;

}
