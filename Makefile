objects	= main.o dcl.o gettoken.o bsearch.o
dcl	:	$(objects)
		cc -o ./bin/dcl $(objects); rm $(objects)
main.o		:	dcl.h
dcl.o		:	dcl.h  
gettoken.o	:	dcl.h
clean		:
				rm dcl $(objects)
