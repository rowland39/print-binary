all : print-binary

print-bits : print-binary.o
	${CC} ${CFLAGS} -o $@ $?

clean :
	rm -f *.o *~ print-binary
