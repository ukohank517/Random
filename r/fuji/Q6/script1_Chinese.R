library(RMeCab)                     # 使用library
setwd("workspace/rstudio/fuji/Q6")  # 保存phone.txt的地方
phone <- RMeCabFreq("phone.txt")    # ???取
phone[1:3,]                         # ??????一下内容（最初的三行）
phone[phone$Term == "こと",]        # ???"こと"???个??????的属性??????一下




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
                                    # 名詞、形容詞、動詞、助動詞之中、
                                    # 同???又不是自立???和数的成分保存与phone2
nrow(phone2)                        # 看了一下内容有274行， 内容???是很多???？




phone3 <- phone2[phone2$Freq > 2,]  # 抽出出??????率在2次以上的成分
nrow(phone3)                        # 内容有37行
phone3[rev(order(phone3$Freq)),]    # 根据出???次数排序
                                    # 日本、国内、米、黒船  -> 从外国流入日本
                                    # 売れる、使える  也很多，但是???注意??????有否定形式



setwd("/Users/ukohank517")          # おまじない
