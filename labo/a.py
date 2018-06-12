# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation


emses1 = []
emses2 = []
emses3 = []
newway1 = []
newway2 = []
newway3 = []

cnt = 0
for line in open('emses.dat', 'r'):
    cnt += 1
    if(cnt== 0):
        continue
    if( cnt % 10 != 0) :
        continue
    a,b,c = line.split()
    emses1.append(a)
    emses2.append(b)
    emses3.append(c)


print ("emsesは", cnt)


cnt = 0
for line in open('newway.dat', 'r'):
    cnt += 1
    if(cnt % 10 != 0) :
        continue
    a,b,c = line.split()
    newway1.append(a)
    newway2.append(b)
    newway3.append(c)


print ("newwayは", cnt)

fig = plt.figure()

ims = []
siz = len(newway1)

for i in range(siz):
    #rand = np.random.randn(100)     # 100個の乱数を生成
    #im = plt.plot(rand,'o')             # 乱数をグラフにする
    #ims.append(im)                  # グラフを配列 ims に追加
    x1 = [float(emses1[i]), float(emses2[i]), float(emses3[i])]
    y1 = [1.0,1.0,1.0]
    im = plt.ylim([0.5,1.5])
    im = plt.plot(x1,y1, 'ob')
    
    x2 = [float(newway1[i]), float(newway2[i]), float(newway3[i])]
    y2 = [1.2,1.2,1.2]
    im += plt.plot(x2,y2,'or')
    ims.append(im);

# 10枚のプロットを 100ms ごとに表示
ani = animation.ArtistAnimation(fig, ims, interval=1) # 描画
# ani.save("test.gif", writer="ukohank517") # gifを保存。でもなぜかできない？

plt.show() #画面に表示
