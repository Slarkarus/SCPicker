RAYLIB ?= ./raylib_external
all:
	g++ src/main.cpp -I $(RAYLIB) -L $(RAYLIB) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
