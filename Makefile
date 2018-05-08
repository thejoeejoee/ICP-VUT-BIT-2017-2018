.PHONY: all build doxygen run pack clean

TARGET=blockeditor
QMAKE=/usr/local/share/Qt-5.5.1/5.5/gcc_64/bin/qmake 
QT_LIB_PATH=/usr/local/share/Qt-5.5.1/5.5/gcc_64/lib


all: build

build:
	cd src && \
	LD_LIBRARY_PATH=$(QT_LIB_PATH):$LD_LIBRARY_PATH $(QMAKE) app.pro -spec linux-g++ && \
	LD_LIBRARY_PATH=$(QT_LIB_PATH):$LD_LIBRARY_PATH make && \
	cp build/$(TARGET) ./;

run:
	test -f src/$(TARGET) && LD_LIBRARY_PATH=$(QT_LIB_PATH):$$LD_LIBRARY_PATH ./src/$(TARGET)

doxygen:
	doxygen src/Doxyfile

pack: clean
	zip -r xkolar71-xnguye16.zip README.txt Makefile src/app examples/ src/app.pro README.txt src/qt.conf src/Doxyfile

clean:
	rm -rf $(TARGET) src/build/ xkolar71-xnguye16.zip