CC		= g++
CFLAGS	= -O2 -W -Wall
PROGRAM	= rpn
OBJS	= strfunc.o main.o
LIBS	= -lm

all:		$(PROGRAM)

$(PROGRAM):	$(OBJS)
			$(CC) $(OBJS) $(LIBS) -o $(PROGRAM)
			
clean:;		rm -f *.o *~ $(PROGRAM)

.cpp.o:		$(CC) -c $<

main.o:		init.h typeenum.h element.h interpret.h strfunc.h
#strfunc.o:	init.h 


