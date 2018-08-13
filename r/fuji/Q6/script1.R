library(RMeCab)                     # 読み取り
setwd("workspace/rstudio/fuji/Q6")  # phone.txtの場所を設定
phone <- RMeCabFreq("phone.txt")    # ファイル読み込み
phone[1:3,]                         # 内容確認
phone[phone$Term == "こと",]        # "こと"という単語について詳しく見る




phone2 <- phone[ (
                   phone$Info1 == "名詞" | 
                   phone$Info1 == "形容詞" |
                   phone$Info1 == "動詞" |
                   phone$Info1 == "助動詞"
                  )  
                 &
                 (
                  phone$Info2 != "非自立"  & phone$Info2 != "数" 
                 ) ,]
                                    # 名詞、形容詞、動詞、助動詞の中、自立の数ではないものをphone2に入れる。
nrow(phone2)                        # 274行ある。それでも多いでしょう？




phone3 <- phone2[phone2$Freq > 2,]  # 2回以上出現するもののみ保存
nrow(phone3)                        # 37行
phone3[rev(order(phone3$Freq)),]    # 出現頻度でソート
                                    # 日本、国内、米、黒船  -> 海外からの輸入が多い。
                                    # 売れる、使えるなどの動詞もある、否定の可能性もあるので、文脈からの判断が必要。 -> script2を見よう



setwd("/Users/ukohank517")          # おまじない
