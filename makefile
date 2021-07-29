CXX			:=	g++
CXX_FLAGS	:=	-g	-std=c++17 #-Wextra -Wall

SRC			:=	src
INCLUDE		:=	./include
LIB			:=	./lib

LIBRARIES	:=	-lglad	-lglfw3dll
EXECUTABLE	:=	main

# all:
# 	./$(EXECUTABLE)
# run:	all
# 	./$(EXECUTABLE)
# $(EXECUTABLE):	$(SRC)/*.cpp
# 	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $(SRC)/glad.c -o$(EXECUTABLE) -lglfw3dll

.PHONY:	all
all: ./$(EXECUTABLE)

./$(EXECUTABLE): $(SRC)/*.cpp
	g++ -g -std=c++17  -I./include -L./lib src/main.cpp	src/stb.cpp	src/Header/Texture.cpp	src/Header/VAO.cpp	src/Header/EBO.cpp	src/Header/VBO.cpp	src/Header/shaderClass.cpp	src/glad.c -o main  -lglfw3dll

# ./obj/main.o:	./obj/VAO.o
# 	g++	-g	-std=c++17	-I./include -L./lib	./src/main.cpp	src/glad.c	-o	obj/main.o

# ./obj/VAO.o:	./obj/EBO.o
# 	g++	-g	-std=c++17	-I./include -L./lib	./src/VAO.cpp	src/glad.c	-o	obj/VAO.o

# ./obj/EBO.o:	./obj/VBO.o
# 	g++	-g	-std=c++17	-I./include -L./lib	./src/EBO.cpp	src/glad.c	-o	obj/EBO.o

# ./obj/VBO.o:	./obj/shaderClass.o
# 	g++	-g	-std=c++17	-I./include -L./lib	./src/VBO.cpp	src/glad.c	-o	obj/VBO.o

# ./obj/shaderClass.o:	./src/main.cpp	./src/Header/shaderClass.h
# 	g++	-g	-std=c++17	-I./include	-L./lib	./src/shaderClass.cpp	src/glad.c	-o	obj/shaderClass.o