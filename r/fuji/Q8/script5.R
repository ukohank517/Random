library(RMeCab)                     # 読み取り
setwd("/Users/ukohank517/workspace/rstudio/fuji/Q8")  # csvの場所を設定

# 問題点:
# 右にF, 左にMが集まってる。
# 図の下には20,30代が集中してる
# 原点の近くの情報「自然、料理、店、海」が特徴のない一般な意見


# 20Fの近くに「離島、北部」-> 若い女性の好みだろう



# 50, 60代の女性の近くには「ホテル、時間」がプロットされている。
for(i in 1:length(res)){
  if(!is.na(okinawa$Sex[i]) & okinawa$Sex[i] == "女性" & !is.na(okinawa$Age[i]) & ( okinawa$Age[i] == "６０代" |  okinawa$Age[i] == "５０代")){
    if(any( res[[i]] %in% c( "時間", "ホテル")  )){
      print(as.character(okinawa[i, "opinion"]))
    }
  }
}
# これらの情報を加工すればよろしいだろう。


for(i in 1:length(res)){
  if(!is.na(okinawa$Sex[i]) & okinawa$Sex[i] == "男性" & !is.na(okinawa$Age[i]) & okinawa$Age[i] == "５０代" ){
    if(any( res[[i]] %in%  "道路"  )){
      print(as.character(okinawa[i, "opinion"]))
    }
  }
}




for(i in 1:length(res)){
  if(!is.na(okinawa$Sex[i]) & okinawa$Sex[i] == "男性" & !is.na(okinawa$Age[i]) & (okinawa$Age[i] == "６０代" )){
    #   print(i)
    if(any( res[[i]] %in%  "必要" )){
      print(as.character(okinawa[i, "opinion"]))
    }
  }
}

for(i in 1:length(res)){
  if(!is.na(okinawa$Sex[i]) & okinawa$Sex[i] == "男性" & !is.na(okinawa$Age[i]) & okinawa$Age[i] == "２０代" ){
    #   print(i)
    if(any( res[[i]] %in%  "整備"  | res[[i]] %in%  "充実" )){
      print(as.character(okinawa[i, "opinion"]))
    }
  }
}



setwd("/Users/ukohank517")              # おまじない

