clean:
	rm Makefile
	rm *.o
	rm *.pro
	rm moc_*.cpp
doit:
	qmake -project
	qmake
	make -f Makefile
	rm Makefile
	rm *.o
	rm *.pro
	rm moc_*.cpp
	./SenseShell
	#rm SenseShell