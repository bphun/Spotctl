SRCS:=src/spotifycli
EXTRA_SRCS:= src/*.cpp include/spotifyapi/Models/*.cpp include/spotifyapi/SpotifyAPI.cpp
CFLAGS:= -c -g -Wall -std=c++11
INCLUDE:=-I. -lncurses

spotifycli: $(SRCS).cpp
	g++ $(CFLAGS) $(SRCS).cpp $(EXTRA_SRCS)
	g++ -o spotifycli *.o $(INCLUDE)

clean:
	rm spotifycli *.o
