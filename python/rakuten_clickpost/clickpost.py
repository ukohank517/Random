# -*- coding: utf-8 -*-
import os,sys,csv,pandas
from tkinter import *
from tkinter import ttk
from tkinter import filedialog
from tkinter import messagebox

Dlst = []

readfile = ""
dict={}

def make_maping():
    xlsFile ="./rakuten_product.xlsx"
    df = pandas.read_excel('./rakuten_product.xlsx', sheet_name=1)

    for row in range(len(df.index.values)):
        dict[df.iat[row, 0]]=df.iat[row, 1]


def readcsv():
    global readfile
    global Dlst

    with open(readfile, 'rb') as csvfile:
        reader = csv.reader(csvfile)
        header = next(reader) # ヘッダーを飛ばす
        for row in reader:
            d = []
            d.append(row[28] + "-" + row[29]) #d.postid = str(row[28] + "-" + str(row[29]))
            d.append(row[24] + row[25]) #d.custom_name=row[24] + str(row[25])
            d.append(u"様".encode('shift-jis')) # 敬称
            adress1 = row[30] + row[31]#d.adress1 = str(row[30])+str(row[31])
            adress2 = row[32].decode('shift-jis') #d.adress2 = str(row[32])
            adress3 = adress2[20:-1]; adress2 = adress2[0:20] #d.adress3 = d.adress2[20:-1]; d.adress2 = d.adress2[0:20]
            adress4 = adress3[20:-1]; adress3 = adress3[0:20] #d.adress4 = d.adress3[20:-1]; d.adress3 = d.adress4[0:20]
            d.append(adress1); d.append(adress2.encode('shift-jis')); d.append(adress3.encode('shift-jis')); d.append(adress4.encode('shift-jis'))
            d.append(dict[str(row[5])].encode('shift-jis')) #d.contain = dict[str(row[5])]
            Dlst.append(d)

def writecsv():
    global Dlst

    f = open('print.csv', 'wb')
    csvWriter = csv.writer(f)

    val = 0
    csvWriter.writerow([u"お届け先郵便番号".encode('shift-jis'), u"お届け先氏名".encode('shift-jis'), u"お届け先敬称".encode('shift-jis'), u"お届け先住所1行目".encode('shift-jis'), u"お届け先住所2行目".encode('shift-jis'), u"お届け先住所3行目".encode('shift-jis'), u"お届け先住所4行目".encode('shift-jis'), u"内容品".encode('shift-jis')])
    for row in Dlst:
        csvWriter.writerow(row)
    f.close()



# 参照ボタンのイベント
# button1クリック時の処理
def button1_clicked():
    fTyp = [("","*")]
    iDir = os.path.abspath(os.path.dirname(__file__))
    #iDir = os.path.abspath(os.path.dirname("C:/"))
    filepath = filedialog.askopenfilename(filetypes = fTyp,initialdir = iDir)
    file1.set(filepath)

# button2クリック時の処理
def button2_clicked():
    global readfile
    messagebox.showinfo('Info', u'参照ファイルは↓↓\n' + file1.get())
    readfile = file1.get()

    flag = True
    try:
        make_maping()
    except:
        messagebox.showinfo('Error', u'対応表[rakuten_product.xlsx]の読み込み時\nエラーが発生しました。')
        flag = False
    try:
        readcsv()
    except:
        messagebox.showinfo('Error', u'楽天情報ファイル\n'+readfile+u'\nの読み込み時にエラーが発生しました。')
        flag = False
    try:
        writecsv()
    except:
        messagebox.showinfo('Error', u'ファイル書き込み時にエラーが発生しました。')
        flag = False
    if flag:
        messagebox.showinfo('Success', u'[print.csv]の作成に成功しました。\n アプリを終了して大丈夫です。。')

def quit():
    exit()


if __name__ == '__main__':
    # rootの作成
    root = Tk()
    root.title('Click Post Tool')
    root.resizable(False, False)

    # Frame1の作成
    frame1 = ttk.Frame(root, padding=10)
    frame1.grid()

    # 参照ボタンの作成
    button1 = ttk.Button(root, text=u'参照', command=button1_clicked)
    button1.grid(row=0, column=3)

    # ラベルの作成
    # 「ファイル」ラベルの作成
    s = StringVar()
    s.set('楽天ファイル>>')
    label1 = ttk.Label(frame1, textvariable=s)
    label1.grid(row=0, column=0)

    # 参照ファイルパス表示ラベルの作成
    file1 = StringVar()
    file1_entry = ttk.Entry(frame1, textvariable=file1, width=50)
    file1_entry.grid(row=0, column=2)

    # Frame2の作成
    frame2 = ttk.Frame(root, padding=(0,5))
    frame2.grid(row=1)

    # Startボタンの作成
    button2 = ttk.Button(frame2, text='Start', command=button2_clicked)
    button2.pack(side=LEFT)

    # Cancelボタンの作成
    button3 = ttk.Button(frame2, text='Close', command=quit)
    button3.pack(side=LEFT)

    root.mainloop()
