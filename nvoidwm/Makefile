# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c nvoidwm.c util.c
OBJ = ${SRC:.c=.o}

all: options nvoidwm

options:
	@echo nvoidwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

nvoidwm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f nvoidwm ${OBJ} nvoidwm-${VERSION}.tar.gz config.h

dist: clean
	mkdir -p nvoidwm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		nvoidwm.1 drw.h util.h ${SRC} nvoidwm.png transient.c nvoidwm-${VERSION}
	tar -cf nvoidwm-${VERSION}.tar nvoidwm-${VERSION}
	gzip nvoidwm-${VERSION}.tar
	rm -rf nvoidwm-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f nvoidwm ${DESTDIR}${PREFIX}/bin
	cp -f bar ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/nvoidwm
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < nvoidwm.1 > ${DESTDIR}${MANPREFIX}/man1/nvoidwm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/nvoidwm.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/nvoidwm\
		${DESTDIR}${MANPREFIX}/man1/nvoidwm.1

.PHONY: all options clean dist install uninstall
