library(RMeCab)                     # 読み取り
setwd("workspace/rstudio/fuji/Q8")  # csvの場所を設定

okinawa <- read.csv(file('H18koe.csv' ,encoding='Shift_JIS')) # 日本語文字コードへ変更

nrow(okinawa)                       # 331行
summary(okinawa[,-1])               # 一番最初(概要)の要素を取り除いて、それ以外を整理する
                                    # 1/3は関東、  女性がほとんど、などが分かる。

# 続きはscript2.txtへ



setwd("/Users/ukohank517")          # おまじない

