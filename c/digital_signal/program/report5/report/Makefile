#このファイルはtexのないファイルを消除してくれるファイルです。
all:1 2 clean 3


1:
	platex jikken

2:
	dvipdfmx jikken

clean:
	$(RM) *.o *~ core *.dvi *.aux *.toc *.log
3:
	open jikken.pdf
