# Salut

SOURCES = \
	Status/main.cpp \
	GUI/ssGUIManager.cpp \
	Business/ssBusinessManager.cpp \
	Data/ssDataManager.cpp

build:
	gcc -Wall $(SOURCES) -I./Business -I./GUI -I./Data -I./Status -o app

clean:
	rm app

run: build
	./app

