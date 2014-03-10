CC = g++
CFLAGS = -Wall
PROG = catchme

SRCS = catchme.cpp 
LIBS = -lglut -lGL -lGLU -lalut -lopenal

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
