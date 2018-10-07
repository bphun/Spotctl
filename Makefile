SRCS:=src/spotifycli.cpp src/api/SpotifyAPI.cpp src/MediaPlayer/MediaPlayer.cpp src/Terminal_UI/PlayerView.cpp src/Terminal_UI/ViewManager.cpp
CFLAGS:= -c -g -Wall -std=c++11
LDFLAGS:=-lpanel -lncurses -lcurl
OBJ:=SpotifyAPI.o PlayerView.o MediaPlayer.o ViewManager.o spotifycli.o

spotifycli: src/spotifycli.cpp
	g++ $(CFLAGS) $(SRCS)
	g++ -o spotifycli $(OBJ) $(LDFLAGS)

clean:
	rm spotifycli *.o