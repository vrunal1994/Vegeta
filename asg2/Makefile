# Change the following values to suit your system.

CFLAGS=`sdl-config --cflags` -g -W -Wall -Weffc++ -Wextra -pedantic -O0
SDL_LIB=`sdl-config --libs` -lSDL_ttf -lSDL_image -lSDL_gfx
CCC=g++

OBJECTS = iomanager.o Manager.o table.o ball.o  generateFrames.o

run: main.o $(OBJECTS)
	$(CCC) $(CFLAGS)  main.cpp -o run $(OBJECTS) $(SDL_LIB)

table.o: table.cpp table.h
	$(CCC) $(CFLAGS) -c table.cpp

generateFrames.o: generateFrames.cpp generateFrames.h
	$(CCC) $(CFLAGS) -c generateFrames.cpp




ball.o: ball.cpp ball.h
	$(CCC) $(CFLAGS) -c ball.cpp

iomanager.o: iomanager.cpp iomanager.h
	$(CCC) $(CFLAGS) -c iomanager.cpp



Manager.o: Manager.cpp Manager.h
	$(CCC) $(CFLAGS) -c Manager.cpp

main.o: main.cpp  
	$(CCC) $(CFLAGS) -c main.cpp


clean:
	rm -f run *.o
	rm -f *~
	rm -f frames/*.bmp
