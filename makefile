CXX      = g++
CFLAGS  = -g -Wall -std=c++17
TARGET  = tasque
SOURCES = src/app.cc src/help.cc src/info.cc src/list.cc src/tile.cc src/board.cc
LIBS    = -lncurses
DESTDIR = /usr/local/bin
CONFDIR = ${HOME}/.cache/tasque/

all: ${TARGET}

${TARGET}: ${SOURCES}
	${CXX} ${CFLAGS} -o ${TARGET} ${SOURCES} ${LIBS}

clean:
	rm ${TARGET}
	rm -rf ${CONFDIR}

install: all
	mkdir -p ${DESTDIR}
	cp -f ${TARGET} ${DESTDIR}
	chmod +x ${DESTDIR}/${TARGET}
	mkdir -p ${CONFDIR}
