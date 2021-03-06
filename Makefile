rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC_DIR = src
HEADER_DIR = headers

OBJS := $(call rwildcard,$(SRC_DIR),*.cpp)

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I./$(HEADER_DIR) -I./$(HEADER_DIR)/libs -IC:\mingw_dev_lib\SDL2\include\SDL2 -IC:\mingw_dev_lib\glew-2.1.0\include

INCLUDE_SUB_PATHS = util util/camera util/camera/controllers vprograms util/camera/controllers/pathCameraController/paths util/camera/controllers/pathCameraController 
INCLUDE_SUB_PATHS += util/scene shaderPrograms
INCLUDE_PATHS += $(foreach dir, $(INCLUDE_SUB_PATHS), -I./$(HEADER_DIR)/$(dir))

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

#CC specifies which compiler we're using
CC = g++

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)