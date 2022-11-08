CC = g++ -std=c++17
CFLAGS  = -g -Wall
RM = rm

OPENCV = `pkg-config --cflags --libs opencv4`
XLIB = `pkg-config --cflags --libs x11`

LIBS = $(OPENCV) $(XLIB)

all: main run

main: main.o ConvexHull.o
	$(CC) $(CFLAGS) -o main -lX11 main.o ConvexHull.o $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $< $(LIBS)

run:
	./main
	
clean:
	rm *.o main
