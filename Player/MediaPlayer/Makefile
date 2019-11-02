INCLUDE		:= -I. -I../thirdparty/other -I../thirdparty/ -I../thirdparty/freetype/include/freetype2/ -I../thirdparty/assimp/include

LIBS		:= -lGLEW -lglut -lGL -lpthread -lfreetype -lassimp
LIBRARIES	:= -L../thirdparty/freetype/lib/ -L../thirdparty/assimp/lib/

OUTDIR	:= ./bin
DEBUG	:= -ggdb
FLAGS	:=	-Wall -std=c++11
CC		:= g++
CFLAGS 	:= $(FLAGS) $(INCLUDE)
LFAGS	:= $(FLAGS)
SRC		:= $(wildcard *.cpp)
OBJ		:= $(patsubst %.cpp, ./bin/%.o, $(SRC))


.PHONY: all clean

all: game

game-release: $(OBJ)
	$(CC) $(LFAGS) $(OBJ)  -o $(OUTDIR)/$@ $(LIBS) $(LIBRARIES)

game-debug: $(OBJ)
	$(CC) $(LFAGS) $(DEBUG) $(OBJ)  -o $(OUTDIR)/$@ $(LIBS) $(LIBRARIES)

$(OUTDIR)/%.o : %.cpp
	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@ $(INCLUDE)

clean:
	-rm -f $(OUTDIR)/*.o $(OUTDIR)/game-release $(OUTDIR)/game-debug