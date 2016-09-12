# Change the following values to suit your system.

CFLAGS=`sdl-config --cflags` -g -W -Wall -Weffc++ -Wextra -pedantic -O0
SDL_LIB=`sdl-config --libs` -lSDL_ttf -lSDL_image 
CCC=g++

OBJECTS = iomanager.o Manager.o ground.o football.o goalpost.o

run: main.o $(OBJECTS)
	$(CCC) $(CFLAGS)  main.cpp -o run $(OBJECTS) $(SDL_LIB)

ground.o: ground.cpp ground.h
	$(CCC) $(CFLAGS) -c ground.cpp

goalpost.o: goalpost.cpp goalpost.h
	$(CCC) $(CFLAGS) -c goalpost.cpp


football.o: football.cpp football.h
	$(CCC) $(CFLAGS) -c football.cpp

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
