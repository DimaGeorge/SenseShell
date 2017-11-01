# Salut

#SOURCES = \
	Status/main.cpp \
	Status/ssStatusTable.cpp \
	Status/ssBuffer.cpp\
	Status/ssInputBuffer.cpp \
	Status/ssOutputBuffer.cpp \
	Status/ssSugestionBuffer.cpp \
	GUI/ssGUIManager.cpp \
	Business/ssBusinessManager.cpp \
	Data/ssDataManager.cpp 

#build:
#	g++ -pthread -Wall $(SOURCES) -I./Business -I./GUI -I./Data -I./Status -I./utils -o app -std=c++11 -L/usr/X11/lib -lX11


# clean a fost integrat in run, ca sa stearga automat executabilul dupa rulare ;)
#clean:
#	rm app

#run: build
#	./app
#	rm app

doit:
	qmake -project
	qmake
	make -f Makefile
	rm Makefile
	rm *.o
	rm *.pro
	rm moc_*.cpp
	./SenseShell
#	rm SenseShell