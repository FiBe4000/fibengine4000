IDIR = include
EXE = gengine
CC=g++
CFLAGS=-I $(IDIR)

ODIR = obj
SDIR = src
LIBS =  -lsfml-graphics -lsfml-window -lsfml-system

_DEPS = GameEngine.h AIManager.h Behavior.h Character.h \
		Game.h GameState.h Intro.h IntroState.h Menu.h \
		MenuState.h NPC.h Player.h RandomWalking.h \
		State.h Tilegrid.h Tile.h AnimatedSprite.h \
		Animation.h pugiconfig.h pugixml.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o AIManager.o Behavior.o Character.o GameEngine.o \
	   Game.o GameState.o Intro.o IntroState.o Menu.o \
	   MenuState.o NPC.o Player.o RandomWalking.o \
	   State.o Tilegrid.o Tile.o AnimatedSprite.o \
	   Animation.o pugixml.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(EXE): $(OBJ)
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ $(EXE)

