all:
	gcc -o cco cco.c lib.c
	gcc -o clo clo.c lib.c
	gcc -o cssc cssc.c lib.c
	gcc -o cor cor.c
	gcc -o gs gs.c
clean:	
	rm -f *.exe
