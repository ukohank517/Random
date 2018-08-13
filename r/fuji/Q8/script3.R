library(RMeCab)                     # 読み取り
setwd("/Users/ukohank517/workspace/rstudio/fuji/Q8")  # csvの場所を設定

okinawa <- read.csv(file('H18koe.csv' ,encoding='Shift_JIS')) # 日本語文字コードへ変更


# データ1列目の自由記述文を形態素解析
# RMeCabDF(データ名、データの列番号、形態素原型(1))  ->  単語に分割して、単語の携帯を表示する。
res <- RMeCabDF(okinawa, "opinion", 1)  # res <- RMeCabDF(okinawa, 1, 1) # に同じ 
length(res)                             # 331   <- 331行
length(unlist(res))                     # トークン数 14464   <-  14464個単語
length(unique(unlist(res)))             # タイプ数   1966    <-  重複しない単語
res.t <- table(unlist(res))             # 1966               <-  頻度表

res.t[rev(order(res.t))][1:10]          # 形態素の頻度でソート、その上位10個の単語
                                        # 句読点、が、はなどの助詞が多い



res2 <- list()                          # 空のリスト
for(i in 1:length(res)){
  res2[[i]] <-  res[[i]][names(res[[i]]) == "名詞" | names(res[[i]]) == "形容詞"]
}                                       # 名詞と形容詞だけ取り出す。 names()で品詞情報を確認

length(unlist(res2))                    # 抽出後のトークン数 5000ぐらい（1/3）

length(unique(unlist(res2)))            # 抽出後のタイプ数

res2.t <- table(unlist(res2))           
res2.t[ rev(order(res2.t)) ][1:10]
#「沖縄」「観光」「旅行」が多いのが当然である。分析対象にふくめる必要がない。



# 回答を年齢と性別で分類しておく。
# 60代男女性、50代男女性、...20代男女性
# それぞれのグループで出現回数の大きい形態素を調べ、その頻度を数える。

res60F <- list()
for(i in 1:length(res2)){
  if(!is.na(okinawa$Sex[i]) & okinawa$Sex[i] == "女性" & !is.na(okinawa$Age[i]) & okinawa$Age[i] == "６０代"){
    
    res60F[[i]] <-  res2[[i]]
  }else{  res60F[[i]] <- NA }
}
                                        # is.na()で無回答(NA)を判別
                                        
res60F1 <- unlist(res60F) [unlist(res60F) != "沖縄" & unlist(res60F) != "観光"& unlist(res60F) != "旅行"]
res60F.t <- table(res60F1)              # 重要でない形態素を省く
res60F.t <- res60F.t [rev(order(res60F.t))][1:10]
res60F.t 


# 残りはscript3-subから読み込んで
source('script3-sub1.R', encoding = 'SHIFT-JIS', echo=TRUE)



# ラベルの作成
okinawa.lab <- unique(c(names(res20F.t), names(res20M.t), names(res30F.t), names(res30M.t), names(res40F.t), names(res40M.t),  names(res50F.t), names(res50M.t), names(res60F.t), names(res60M.t) ))
okinawa.lab             ## <- 言及回数を考慮しない。


 
oki <-  which(okinawa.lab %in%  c("さ", "の","こと","ない","私","者", "よう", "等","前","日", "那覇",  "今回", "方","大変","地", "ー") )
okinawa.lab <- okinawa.lab[ -oki ]           # 上記要素の内容を削除
okinawa.lab



# 欲しい＝ほしい、きれい＝美しい、いい＝良い
res60F1[which(res60F1 == "きれい")] <- "美しい"
res60F1[which(res60F1 == "欲しい")] <- "ほしい"
res60F1[which(res60F1 == "いい")] <- "良い"
res60F.t2 <- table(res60F1)
res60F.t3 <- res60F.t2[names(res60F.t2) %in% okinawa.lab]
res60F.t3
                                     # which()で、きれい、ほしい、いいの要素番号を取り出す。



source('script3-sub2.R', encoding = 'SHIFT-JIS', echo=TRUE)






















okinawa.DF <- NULL

okinawa.DF <- data.frame(word = names(res20M.t3), id = rep("20M",length(res20M.t3) ), Freq = as.integer(res20M.t3))
                                            # data.frame() 関数でword, id, Freqの三つの列の情報をもつデータフレームに変換する
                                            # rbindで縦方向(下に)つなげていく
okinawa.DF <- rbind(okinawa.DF,
                    data.frame(word = names(res20F.t3), id = rep("20F", length(res20F.t3)), Freq = as.integer(res20F.t3)),
                    data.frame(word = names(res30M.t3), id = rep("30M", length(res30M.t3)), Freq = as.integer(res30M.t3)),
                    data.frame(word = names(res30F.t3), id = rep("30F", length(res30F.t3)), Freq = as.integer(res30F.t3)),
                    data.frame(word = names(res40M.t3), id = rep("40M", length(res40M.t3)), Freq = as.integer(res40M.t3)),
                    data.frame(word = names(res40F.t3), id = rep("40F", length(res40F.t3)), Freq = as.integer(res40F.t3)),
                    data.frame(word = names(res50M.t3), id = rep("50M", length(res50M.t3)), Freq = as.integer(res50M.t3)),
                    data.frame(word = names(res50F.t3), id = rep("50F", length(res50F.t3)), Freq = as.integer(res50F.t3)),
                    data.frame(word = names(res60M.t3), id = rep("60M", length(res60M.t3)), Freq = as.integer(res60M.t3)),
                    data.frame(word = names(res60F.t3), id = rep("60F", length(res60F.t3)), Freq = as.integer(res60F.t3)))







setwd("/Users/ukohank517")              # おまじない

