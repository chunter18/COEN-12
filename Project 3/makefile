all: uniqueH bincountH parityH

bincountH: bincount.c table.c
	gcc -o $@ bincount.c table.c

uniqueH: unique.c table.c
	gcc -o $@ table.c unique.c

parityH: parity.c table.c
	gcc -o $@ table.c parity.c
