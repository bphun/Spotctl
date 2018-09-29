SRCS:=src/spotifycli
EXTRA_SRCS:= src/*.cpp src/api/*.cpp src/Terminal_UI/*.cpp
CFLAGS:= -c -g -Wall -std=c++11
INCLUDE:=-I. -lncurses

spotifycli: $(SRCS).cpp
	g++ $(CFLAGS) $(SRCS).cpp $(EXTRA_SRCS)
	g++ -o spotifycli *.o $(INCLUDE)

clean:
	rm spotifycli *.o
