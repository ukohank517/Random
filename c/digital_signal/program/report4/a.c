  for(n=0;n<160000;n++){
    e[n]=(double)d[n];
    norm=0.0;
    for(k=0;k<K;k++){
      h_n1[k]=h_n[k];
      if(n<k)continue;
      norm+=(double)x[n-k]*(double)x[n-k];
    }
    //error
    //     fprintf(stderr,"aaa\n");

    for(k=0;k<K;k++){
      if(n<k)continue;
      e[n]=e[n]-h_n[k]*(double)x[n-k];
    }
    for(k=0;k<K;k++){
      h_n1[k]=h_n[k]+(double)alpha*(double)e[n]*(double)x[n-k]/norm;      

    }
  }
