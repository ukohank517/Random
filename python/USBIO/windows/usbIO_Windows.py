# -*- coding: utf-8 -*-
import os
import subprocess

#参考URL:http://computermemo.blog33.fc2.com/blog-entry-70.html

#結果をそのまま表示できる
def res_cmd(cmd):
    return subprocess.Popen(
        cmd, stdout=subprocess.PIPE,
        shell=True).communicate()[0]

#結果をリストに、しかも改行コードあり
def res_cmd_lfeed(cmd):
    return subprocess.Popen(
        cmd, stdout=subprocess.PIPE,
        shell=True).stdout.readlines()

#結果をリストに、改行コードなし
def res_cmd_no_lfeed(cmd):
    return [str(x).rstrip("\n") for x in res_cmd_lfeed(cmd)]


#空白も削除
def res_cmd_no_useless_lfeed(cmd):
    return [str(x).strip("\n") for x in res_cmd_no_lfeed(cmd)]

if __name__ == "__main__":
    cmd = ("mountvol")
    result = (res_cmd_no_useless_lfeed(cmd))
    path =""
    for i in range(len(result)):
        #print result[i]
        if(result[i] == "        F:\\\r"):
            path+=result[i-1]
            break

    print u"-----pathは以下のようになってます。-----"
    print path
    print u"-------------------------------------"
    if len(path)==0:
        print u"ドライブFが存在しません。エンターキー押してアプリを終了させてください。"
        raw_input()
        exit()
        
    time=1
    while(1):
        raw_input()
        if(time==1):
            print u"Fドライブの読み込みを中止"
            cmd = "mountvol F: /D"
        else:
            print u"Fドライブの読み込みを開始"
            cmd = "mountvol F:\\ "+path

        os.system(cmd)
        time*=-1
    #cmd = "mountvol"
    #os.system(cmd)
    
    #cmd = "ipconfig /all > D:\\ipconfig.txt"
    #os.system(cmd)
    
    #cmd = "tree D:\\Doc /f > D:\\tree.txt"
    #os.system(cmd)
    
