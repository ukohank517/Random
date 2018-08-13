library(RMeCab)                     # 使用library
setwd("workspace/rstudio/fuji/Q6")  # 保存phone.txt的地方


phoneRaw <- readLines("phone.txt")    # ???取???一行
length(phoneRaw)                      # 共100行
phoneMorp <- list(100)                # 
for(i in 1:100){
  phoneMorp[[i]] <- unlist(RMeCabC(phoneRaw[i]))    # 用RMeCabC解析的???果是list
  if(any( phoneMorp[[i]]   %in%   c("売れる", "使える", "ない" ))){
    # print(phoneMorp[[i]])
    print(as.vector( phoneMorp[[i]]))                  
  }
}
                                    # 看了???果，有什???感受？

setwd("/Users/ukohank517")          # おまじない
