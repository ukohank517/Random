#setwd("/Users/ukohank517/workspace/rstudio/fuji/Q8")  # csvの場所を設定


res60M <- list()
for(i in 1:length(res2)){
  if(!is.na(okinawa$Sex[i]) & okinawa$Sex[i] == "男性" & !is.na(okinawa$Age[i]) & okinawa$Age[i] == "６０代"){
    res60M[[i]] <-  res2[[i]]
    
  }else{  res60M[[i]] <- NA }
}


# 沖縄と観光，旅行 は除いた上位10
res60M1 <- unlist(res60M) [unlist(res60M) != "沖縄" & unlist(res60M) != "観光"& unlist(res60M) != "旅行"]
res60M.t <- table(res60M1)
res60M.t <- res60M.t [rev(order(res60M.t))][1:10]
res60M.t

## こと 良い   の   さ 必要 よう 整備 道路   地 多い 
##  10    9    9    8    7    7    6    5    5    5 




############ 50 

res50F <- list()
for(i in 1:length(res2)){
  if(!is.na(okinawa$Sex[i]) & okinawa$Sex[i] == "女性" & !is.na(okinawa$Age[i]) & okinawa$Age[i] == "５０代"){
    
    res50F[[i]] <-  res2[[i]]
  }else{  res50F[[i]] <- NA }
}



## 沖縄と観光，旅行 は除いた上位10
res50F1 <- unlist(res50F) [unlist(res50F) != "沖縄" & unlist(res50F) != "観光"& unlist(res50F) != "旅行"]
res50F.t <- table(res50F1)
res50F.t <- res50F.t [rev(order(res50F.t))][1:10]
res50F.t

##     人   こと     の ほしい     海   良い 美しい     店   多い     方 
##     18     13     12     11     10      9      9      9      9      6 


#####
res50M <- list()
for(i in 1:length(res2)){
  if(!is.na(okinawa$Sex[i]) & okinawa$Sex[i] == "男性" & !is.na(okinawa$Age[i]) & okinawa$Age[i] == "５０代"){
    res50M[[i]] <-  res2[[i]]
  }else{  res50M[[i]] <- NA }
}



# 沖縄と観光，旅行 は除いた上位10
res50M1 <- unlist(res50M) [unlist(res50M) != "沖縄" & unlist(res50M) != "観光"& unlist(res50M) != "旅行" ]
res50M.t <- table(res50M1)
res50M.t <- res50M.t [rev(order(res50M.t))][1:10]
res50M.t

##     の   道路   自然     さ   バス やすい   料理 美しい   大変     人 
##      8      7      6      6      5      5      4      4      4      4



############## 40


res40F <- list()
for(i in 1:length(res2)){
  if(!is.na(okinawa$Sex[i]) & okinawa$Sex[i] == "女性" & !is.na(okinawa$Age[i]) & okinawa$Age[i] == "４０代"){
    res40F[[i]] <-  res2[[i]]
  }else{  res40F[[i]] <- NA }
}



# 沖縄と観光，旅行 は除いた上位10
res40F1 <- unlist(res40F) [unlist(res40F) != "沖縄" & unlist(res40F) != "観光"& unlist(res40F) != "旅行" ]
res40F.t <- table(res40F1)
res40F.t <- res40F.t [rev(order(res40F.t))][1:10]
res40F.t 

##     の   今回     海   バス ほしい   こと     日     等     前   整備 
##      8      5      5      5      5      5      4      4      4      4


res40M <- list()
for(i in 1:length(res2)){
  if(!is.na(okinawa$Sex[i]) & okinawa$Sex[i] == "男性" & !is.na(okinawa$Age[i]) & okinawa$Age[i] == "４０代"){
    res40M[[i]] <-  res2[[i]]
  }else{  res40M[[i]] <- NA }
}



# 沖縄と観光，旅行 は除いた上位10
res40M1 <- unlist(res40M) [unlist(res40M) != "沖縄" & unlist(res40M) != "観光"& unlist(res40M) != "旅行" ]
res40M.t <- table(res40M1)
res40M.t <- res40M.t [rev(order(res40M.t))][1:10]
res40M.t

##       自然       良い     欲しい モノレール       バス         の         さ 
##          7          6          6          5          5          5          5 
##         私         海       料金 
##          4          4          3 


############## 30

res30F <- list()
for(i in 1:length(res2)){
  if(!is.na(okinawa$Sex[i]) & okinawa$Sex[i] == "女性" & !is.na(okinawa$Age[i]) & okinawa$Age[i] == "３０代"){
    res30F[[i]] <-  res2[[i]]
  }else{  res30F[[i]] <- NA }
}


# 沖縄と観光，旅行 は除いた上位10
res30F1 <- unlist(res30F) [unlist(res30F) != "沖縄" & unlist(res30F) != "観光"& unlist(res30F) != "旅行" ]
res30F.t <- table(res30F1)
res30F.t <- res30F.t [rev(order(res30F.t))][1:10]
res30F.t 

##     人     海     の ほしい きれい   いい   多い ホテル   よう   こと 
##     11     11      9      8      8      8      7      7      6      6


## 
res30M <- list()
for(i in 1:length(res2)){
  if(!is.na(okinawa$Sex[i]) & okinawa$Sex[i] == "男性" & !is.na(okinawa$Age[i]) & okinawa$Age[i] == "３０代"){
    res30M[[i]] <-  res2[[i]]# 
  }else{  res30M[[i]] <- NA }
}


# 沖縄と観光，旅行 は除いた上位10
res30M1 <- unlist(res30M) [unlist(res30M) != "沖縄" & unlist(res30M) != "観光"& unlist(res30M) != "旅行" ]
res30M.t <- table(res30M1)
res30M.t <- res30M.t [rev(order(res30M.t))][1:10]
res30M.t 

##     人   渋滞   交通 やすい   バス   こと   北部   那覇     店     さ 
##      7      5      5      5      4      4      3      3      3      3


############ 20

res20F <- list()
for(i in 1:length(res2)){
  if(!is.na(okinawa$Sex[i]) & okinawa$Sex[i] == "女性" & !is.na(okinawa$Age[i]) & okinawa$Age[i] == "２０代"){
    res20F[[i]] <-  res2[[i]]# 
  }else{  res20F[[i]] <- NA }
}




# 沖縄と観光，旅行 は除いた上位10
res20F1 <- unlist(res20F) [unlist(res20F) != "沖縄" & unlist(res20F) != "観光"& unlist(res20F) != "旅行" ]
res20F.t <- table(res20F1)
res20F.t <- res20F.t [rev(order(res20F.t))][1:10]
res20F.t 

##       の       人       海 タクシー     多い     運転   ほしい     こと 
##       15       11       10        9        7        7        7        7 
##     いい     離島 
##        7        6

#### 

res20M <- list()
for(i in 1:length(res2)){
  if(!is.na(okinawa$Sex[i]) & okinawa$Sex[i] == "男性" & !is.na(okinawa$Age[i]) & okinawa$Age[i] == "２０代"){
    res20M[[i]] <-  res2[[i]]
  }else{  res20M[[i]] <- NA }
}


# 沖縄と観光，旅行 は除いた上位10
res20M1 <- unlist(res20M) [unlist(res20M) != "沖縄" & unlist(res20M) != "観光"& unlist(res20M) != "旅行" ]
res20M.t <- table(res20M1)
res20M.t <- res20M.t [rev(order(res20M.t))][1:10]
res20M.t 

##   バス   充実   運転 ほしい     さ   良い     道   多い     車     者 
##      4      3      3      3      3      2      2      2      2      2 
## #

#setwd("/Users/ukohank517")              # おまじない

