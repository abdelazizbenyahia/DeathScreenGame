#
# Makefile for saucer shoot game using Dragonfly
#
# Copyright Mark Claypool and WPI, 2016
#
# 'make depend' to generate new dependency list
# 'make clean' to remove all constructed files
# 'make' to build executable
#
# Variables of interest:
#   GAMESRC is the source code files for the game
#   GAME is the game main() source
#

CC= g++ 

### Uncomment only 1 of the below! ###


LINKLIB= -ldragonfly-mac64 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
#uncomment this line for li
#LINKLIB= -ldragonfly -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lrt

LINKDIR= -L../engine/ -L/usr/local/lib # path to dragonfly library
INCDIR= -I../include/ -I/usr/local/include # path to dragonfly includes

GAMESRC=Hero.cpp Explosion.cpp ErrorsObject.cpp ErrorsObjectList.cpp GameOver.cpp
GAME= game.cpp
EXECUTABLE= game
OBJECTS= $(GAMESRC:.cpp=.o)

all: $(EXECUTABLE) Makefile

$(EXECUTABLE): $(ENGINE) $(OBJECTS) $(GAME) $(GAMESRC) 
	$(CC) $(GAME) $(OBJECTS) -o $@ $(INCDIR) $(LINKDIR) $(LINKLIB) 

.cpp.o: 
	$(CC) -std=c++11 -g  -c $(INCDIR) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) core dragonfly.log Makefile.bak *~

depend: 
	makedepend *.cpp 2> /dev/null

# DO NOT DELETE

