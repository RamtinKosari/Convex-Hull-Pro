CC = g++ -std=c++17
CFLAGS  = -g -Wall
RM = rm

OPENCV = `pkg-config --cflags --libs opencv4`

lIBS = $(OPENCV)

all: main run

main: main.o ConvexHull.o
	$(CC) $(CFLAGS) -o main main.o ConvexHull.o $(lIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $< $(lIBS)

run:
	./main
	
clean:
	rm *.o main