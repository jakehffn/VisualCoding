#OBJS specifies which files to compile as part of the project
SRC_DIR = src

#SRC_SUB_DIRS specifies sub directories in source
SRC_SUB_DIRS = util
OBJS := $(wildcard $(SRC_DIR)/*.cpp) $(foreach dir,$(SRC_SUB_DIRS),$(wildcard $(SRC_DIR)/$(dir)/*.cpp))

#CC specifies which compiler we're using
CC = g++

HEADER_DIR = headers
HEADER_SUB_DIRS = util
#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I.\$(HEADER_DIR) -I.\$(foreach dir,$(HEADER_SUB_DIRS),$(HEADER_DIR)\$(dir)) -IC:\mingw_dev_lib\SDL2\include\SDL2 -IC:\mingw_dev_lib\glew-2.1.0\include

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\mingw_dev_lib\SDL2\lib -LC:\mingw_dev_lib\glew-2.1.0\lib\Release\Win32

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = 

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lglew32 -lglu32 -lopengl32 -lgdi32

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = graphics

#This is the target that compiles our executable
all : $(OBJS)
	$(info $(OBJS))
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)