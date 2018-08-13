library(RMeCab)                     # 読み取り
setwd("workspace/rstudio/fuji/Q6")  # phone.txtの場所を設定


phoneRaw <- readLines("phone.txt")    # 一行ずつ読み直す
length(phoneRaw)                      # 100行
phoneMorp <- list(100)                # 
for(i in 1:100){
  phoneMorp[[i]] <- unlist(RMeCabC(phoneRaw[i]))    # RMeCabCの解析結果がリスト  
  if(any( phoneMorp[[i]]   %in%   c("売れる", "使える", "ない" ))){
    # print(phoneMorp[[i]])
    print(as.vector( phoneMorp[[i]]))                  
  }
}
                                    # 結果を見ると、どう思う？

setwd("/Users/ukohank517")          # おまじない
