# -*- coding: UTF-8 -*-
from oauth2client.service_account import ServiceAccountCredentials
import json
import gspread
import glob
import os
import datetime
from time import sleep

"""
This version of the Google Sheets API has a limit of
500 requests per 100 seconds per project, and 100 requests per 100 seconds per user.
Limits for reads and writes are tracked separately. There is no daily usage limit.
"""
scope=['https://spreadsheets.google.com/feeds']
credentials=ServiceAccountCredentials.from_json_keyfile_name('[###PATH TO KEYFILE###]',scope)
gc = gspread.authorize(credentials)
website = gc.open_by_key('###SPREAT SHEET FILE ID###')

skudata = website.worksheet(u'###SPREAT SHEET FILE NAME###').get_all_values()

websitewks1 = website.worksheet(u'###SHEET NAME###')

websitewks2 = website.worksheet(u'###SHEET NAME###')
websiteAllData1 = websitewks1.get_all_values()
websiteAllData2 = websitewks2.get_all_values()

lineNumber = [len(websiteAllData1), len(websiteAllData2)]
idx = [ websiteAllData1[len(websiteAllData1)-1][0] , websiteAllData2[len(websiteAllData2)-1][0] ]
writeDATA = [[],[]]


rFile=""

class DATA:
    def __init__(self):
        self.orderNum = ""
        self.SKU = ""
        self.goodsNumber = 0
        self.goodsPrice = 0.0
        self.selectedCategory = ""
        self.buyerEmail = ""
        self.receiverName = ""
        self.sendAdress = ""
        self.sendTel = ""
        self.goodsName = ""

datalst = []
year = datetime.date.today().year
today = str(datetime.date.today()).replace('-', '/').replace(str(year)+'/','')




def selectInputFile():
    global rFile

    print u"##############################"
    print u"#  請選択今天下載的訂単文件: #"
    print u"##############################"

    i = 1
    print u"  | [ 0 ] 下面都不是"
    for s in glob.glob('./*'):
        print "  | [" , str(i) , "]",s.replace('\\','')
        i+=1

    print ">>",
    ret =-1
    while True:
        ip = str(raw_input())
        if(ip.isdigit()):
            ret = int(ip)
        if(ret<0 or ret >=i):
            print u"[ !!! ]錯誤的輸入"
        else:
            break
    if(ret == 0 ):
        exit
    print "#############################################################"
    print u"# 選択的文件是 :", ("[ "+str(ret)+u" ] : "+glob.glob('./*')[ret-1].replace('\\','')).center(42), "#"
    print "#",u"[Y]es                         [No]                 ".center(57),"#"
    print "#############################################################"
    print u">>",
    ip = raw_input()
    if(ip == "Y" or ip == "Yes" or ip =="y"):
        rFile=str(glob.glob('./*')[ret-1])
        return
    else:
        print u"###########################################################"
        print u"#####                  請重頭操作                     #####"
        print u"###########################################################"
        ip = raw_input()
        exit()

def readFileData():
    global datalst

    print u"正在読取文件:" , rFile,"..."

    index = 0
    with open(rFile) as f:
        for line in f:
            if(index == 0):
                index += 1
                continue
            csvdata = line.split('\t')
            if(csvdata[25] == ""):
                continue
            price = (float(csvdata[11]) + float(csvdata[26]))*0.9*16.0

            d = DATA()

            d.orderNum=csvdata[0]
            d.SKU=csvdata[7]
            d.goodsNumber = csvdata[9]
            d.goodsPrice=price
            d.selectedCategory=csvdata[35]
            d.buyerEmail=csvdata[4]
            d.receiverName=csvdata[42]
            d.sendAdress=csvdata[22]+csvdata[21]+csvdata[20]+csvdata[17]+csvdata[18]+csvdata[19]
            d.sendTel=csvdata[25]
            d.goodsName=csvdata[8]
            datalst.append(d)
    datalst.sort(key=lambda x:x.sendAdress)
    print u"文件[", rFile , u"]読取結束"


def findFileName(sku):
    global skudata

    ret = 0
    for i in range(len(skudata)):
        #print wksdata[i][0]
        if skudata[i][0] == sku:
            if(skudata[i][8].encode('utf-8').find("中国") != -1):
                ret = 1
            return ret
    return ret

def writeSpread():
    global datalst

    for i in range(len(datalst)):
        dataidx = findFileName(datalst[i].SKU)
        if(idx[dataidx][0] == 'z'):
            idx[dataidx] = 'z' + str(int(idx[dataidx][1:])+1)
        else:
            idx[dataidx] = str(int(idx[dataidx])+1)

        lineNumber[dataidx] = lineNumber[dataidx] + 1


        writeDATA[dataidx].append([
            idx[dataidx],  # A
            str(today), # B
            "", # C
            datalst[i].orderNum, # D
            datalst[i].SKU, # E
            int(datalst[i].goodsNumber), # F
            "", # G
            "", # H
            "", # I
            "", # J
            datalst[i].goodsPrice, # K
            "", # L
            "", # M
            "", # N
            "", # O
            datalst[i].selectedCategory, # P
            datalst[i].buyerEmail, # Q
            "", # R
            datalst[i].receiverName, # S
            datalst[i].sendAdress, # T
            str(datalst[i].sendTel), # U
            datalst[i].goodsName, # V
            "", # W
            "", # X
            "", # Y
            "" # Z
        ])

    ##### 仕入れ
    startcell = u'A'+str(len(websiteAllData1) + 1)
    endcell = u'Z' + str(len(websiteAllData1) + len(writeDATA[0]))

    cell_list = websitewks1.range(startcell+':'+endcell)
    idxi = 0
    idxj = 0

    for cell in cell_list:
        cell.value = writeDATA[0][idxi][idxj]
        idxj=idxj+1
        if(idxj == 26):
            idxj = 0
            idxi = idxi+1
    websitewks1.update_cells(cell_list,value_input_option='USER_ENTERED')

    #### 仕入れ２
    startcell = u'A'+str(len(websiteAllData2) + 1)
    endcell = u'Z' + str(len(websiteAllData2) + len(writeDATA[1]))

    cell_list = websitewks2.range(startcell+':'+endcell)
    idxi = 0
    idxj = 0

    for cell in cell_list:
        cell.value = writeDATA[1][idxi][idxj]
        idxj=idxj+1
        if(idxj == 26):
            idxj = 0
            idxi = idxi+1
    websitewks2.update_cells(cell_list,value_input_option='USER_ENTERED')


    #for s,e in zip(sindex, eindex):
    #    if(datalst[s].)


if __name__ == '__main__':
    #test()
    selectInputFile()
    try:
        readFileData()
    except:
        print u"文件格式錯誤"
        raw_input()

    writeSpread()
    print u"程序運行結束、按回車鍵結束程序。然後打開spread sheet設定文字的格式。"
    raw_input()

# 参考サイト:
# https://www.yoheim.net/blog.php?q=20160205
# ライブラリーを編集、参考URL: https://github.com/burnash/gspread/issues/544
    # sht=gc.open_by_url('https://docs.google.com/spreadsheets/d/1M2SF7pANNHI6r8LdcIoyOxV9GiSXGm5HMrx1_U723HQ/edit#gid=186450351').worksheet(u'仕入れ')
    # print sht.title.encode('utf-8')
    # print wks
    # wks = gc.open_by_key('1M2SF7pANNHI6r8LdcIoyOxV9GiSXGm5HMrx1_U723HQ').worksheet(sht.title)
    #各セルにアクセス
    # print wks.acell('A1').value.encode('utf-8')
    # str = wks.acell('A1').value.encode('utf-8')
    # wks.update_acell('A2', str)
    # wks.append_row(['AAA'])

    #print len(wks.get_all_values())

    # print wks.row_count
    # wks.get_all_records(empty2zero=False, head=1, default_blank='')

    # 書き換え
    # wks.update_acell('A9807', u'中国发货编号管理')

    # cprwks = website.worksheet(u'中国库存表')
    # wksjpn = website.worksheet(u'仕入れ')
    # wkschina = website.worksheet(u'仕入れ２')
