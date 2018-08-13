#並列計算を行わないkmeans
library(kernlab)
data(spam)
dim(spm) #行数、列数を表示
head(spam,3)
head(subset(spam,select=-type),3) #58列目を除去したデータ
system.time(res<-kmeans(subset(spam, select=-type),4,nstart=200))



#並列化を行わないrandomForest
library(kernlab)
library(randomForest)
data(spam)
set.seed(123)#ブーとストラップ法で同じ結果を出すために設定
set.seed(123)
system.time(fit.rf<-randomForest(type~.,data=spam,ntree=1000))
fit.rf



#snowパッケージを用いたkmeans
#install.packages("snow")
library(snow)
#クラスターの生成(4つのワーカープロセスをソケットにより通信する)
cl<-makeCluster(4,type="SOCK")
#spamデータセットを利用するためにkernlabパッケージを読み込む
invisible(clusterEvalQ(cl,{
library(kernlab)
data(spam)
}))
#四つのワーカプロセスで50回ずつk平均法を実行
system.time(res<-clusterApply(cl,rep(50,4), function(nstart)
kmeans(subset(spam,select=-type),4,nstart=nstart)))
#クラスターの終了
stopCluster(cl)



#snowパッケージを用いたrandomForest
library(snow)
library(randomForest)
cl<-makeCluster(4,type="SOCK")
invisible(clusterEvalQ(cl,{
library(randomForest)
library(kernlab)
data(spam)
}))
#4つのワーカープロセスで250個ずつ決定木を生成
system.time(fit.rf<-clusterApply(cl,rep(250,4),function(ntree)
randomForest(type~.,data=spam,ntree=ntree)))
#結果をcombine関数で結合
fit.rf.all<-do.call("combine",fit.rf)
fit.rf.all
stopCluster(cl)



#parallelパッケージによるkmeans(mclapply関数をしようする場合)
library(parallel)
library(kernlab)
data(spam)
#L'Ecuyerのアルゴリズムを用いた乱数生成
RNGkind("L'Ecuyer-CMRG")
#スレッド数の検出
mc.cores<-detectCores()
mc.cores
#初期値を50回変えながらkmeansをmc.cores回繰り返す
system.time(res<-mclapply(rep(50,mc.cores),function(nstart)
kmeans(subset(spam,select=-type),mc.cores,nstart=nstart)))



#parallelパッケージによるkmeans(clusterApply関数をしようする場合)
library(parallel)
library(kernlab)
cores<-detectCores()
#クラスタの生成
cl<-makeCluster(cores,type="PSOCK")
invisible(clusterEvalQ(cl,{
library(kernlab)
data(spam)
}))
set.seed(123)
#乱数の発生
clusterSetRNGStream(cl)
system.time(res<-clusterApply(cl,rep(50,cores),function(nstart)
kmeans(subset(spam, select=-type),4,nstart=nstart)))
stopCluster(cl)
