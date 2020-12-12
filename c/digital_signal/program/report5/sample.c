#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <getopt.h>

int main(argc,argv)
     int argc;
     char *argv[];
{
  int i, j, k, t, num_dim, num_out_nodes, num_frames, num_second_nodes;
  int iteration, genre, total_iterations, total_frames, tmp_count;
  char opt, *inf, *datafn;
  float tmp_f, ***data, **W1, **W2, *teacher, **old_W2, error, total_error;
  float *y, *o, mean;
  double **tmp_W1, **tmp_W2;
  FILE *fin;
  extern char *optarg;

  if( (inf=(char *) calloc( 1024, sizeof(char))) == NULL ){
    fprintf(stderr,"cannot allocate memory.\n");    exit(-1);
  }

  for(i=0;i<argc &&(opt=getopt(argc,argv,"i:a:b:c:s:t:"))
	;i++){
    switch(opt){
    case 'i': strcpy(inf,optarg);  break;
    case 'a': num_dim = atoi(optarg);  break;
    case 'b': num_out_nodes = atoi(optarg);   break;
    case 'c': num_frames = atoi(optarg);   break;
    case 's': num_second_nodes = atoi(optarg);   break;
    case 't': total_iterations = atoi(optarg);   break;
    }
  }

  if ( (fin = fopen(inf,"rb")) == NULL){
    fprintf(stderr,"Cannot read %s\n",inf); exit(-1);
  }


  if( (W1=(float **) calloc( num_second_nodes, sizeof(float *))) == NULL ){
    fprintf(stderr,"cannot allocate memory.\n");    exit(-1);
  }
  for(i=0;i<num_second_nodes;i++){
    if( (W1[i]=(float *) calloc( num_dim, sizeof(float ))) == NULL ){
      fprintf(stderr,"cannot allocate memory.\n");    exit(-1);
    }
  }

  if( (W2=(float **) calloc( num_out_nodes, sizeof(float *))) == NULL ){
    fprintf(stderr,"cannot allocate memory.\n");    exit(-1);
  }
  for(i=0;i<num_out_nodes;i++){
    if( (W2[i]=(float *) calloc( num_second_nodes, sizeof(float ))) == NULL ){
      fprintf(stderr,"cannot allocate memory.\n");    exit(-1);
    }
  }

  mean = 0.0;
  for(i=0;i<num_second_nodes;i++){
    for(j=0;j<num_dim;j++){
      W1[i][j] = 0.1*(double)rand()/RAND_MAX;
      mean += W1[i][j];
    }
  }
  mean = mean/(num_dim*num_second_nodes);
  for(i=0;i<num_second_nodes;i++){
    for(j=0;j<num_dim;j++){
      W1[i][j] = W1[i][j] - mean;
    }
  }
  //////

  mean = 0.0;
  for(i=0;i<num_out_nodes;i++){
    for(j=0;j<num_second_nodes;j++){
      W2[i][j] = 0.1*(double)rand()/RAND_MAX;
      mean += W2[i][j];
    }
  }
  mean = mean/(num_second_nodes*num_out_nodes);
  for(i=0;i<num_out_nodes;i++){
    for(j=0;j<num_second_nodes;j++){
      W2[i][j] = W2[i][j] - mean;
    }
  }


  /***
      tmp_count = 0;
      while(1){
      if (fread(&tmp_f, sizeof(float), 1, fin) != 1) {
      break;
      }
      tmp_count++;
      }

      total_frames = num_frames*num_out_nodes;

      if( tmp_count/num_dim != total_frames ){
      fprintf(stderr, "Error in input-file.\n"); 
      fprintf(stderr, "%d %d\n", tmp_count/num_dim, total_frames ); 
      exit(-1);
      }

      fseek(fin, 0, SEEK_SET);

      if( (data=(float ***) calloc( num_out_nodes, sizeof(float **))) == NULL ){
      fprintf(stderr,"cannot allocate memory.\n");    exit(-1);
      }
      for(k=0;k<num_out_nodes;k++){
      if( (data[k]=(float **) calloc( num_frames, sizeof(float *))) == NULL ){
      fprintf(stderr,"cannot allocate memory.\n");    exit(-1);
      }
      for(i=0;i<num_frames;i++){
      if( (data[k][i]=(float *) calloc( num_dim, sizeof(float ))) == NULL ){
      fprintf(stderr,"cannot allocate memory.\n");    exit(-1);
      }
      }
      }
  ***/



}
