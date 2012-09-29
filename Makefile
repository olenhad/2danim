#es to compile as part of the project
OBJS = main.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

#This is the target that compiles our executable
all :$(OBJS)
	g++ $(OBJS) -lGL -lGLU -lglut -o $(OBJ_NAME)
