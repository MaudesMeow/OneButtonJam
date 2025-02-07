# i.e. https://itch-user.itch.io/itch-page
ITCH_USER = the-bert
ITCH_PAGE = spacemoth

PROJECT_NAME 	= "Game"
PROJECT_VERSION = "0.2"


# Define PROJECT_NAME, PROJECT_VERSION, and resolution variables for use in code
DEFINES = -DPROJECT_NAME=\"$(PROJECT_NAME)\" \
	  -DPROJECT_VERSION=\"$(PROJECT_VERSION)\" \


# Search source folder and subfolders for .c files
CFILES = $(wildcard source/*.cpp source/*/*.cpp)

INCLUDES = -Iinclude/
LIBRARIES = -lraylib

# Optimized for size | Warnings for all errors | Link with WASM Raylib | add assets folder to index.data | compatibility flags
WEB_OPT = -Os -Wall -Linclude/web $(LIBRARIES) --shell-file include/web/shell.html --preload-file assets -DPLATFORM_WEB -s USE_GLFW=3 -s GL_ENABLE_GET_PROC_ADDRESS
WEB_OUT = "build/index.html"
WEB_ZIP = "$(PROJECT_NAME)_v$(PROJECT_VERSION)_web.zip"

EMSDK_PATH = /home/hal9000/emsdk

# Use `emrun --list_browsers` for more options
BROWSER = firefox

windows_build:
	i686-w64-mingw32-g++ ./source/*.cpp -o spacemoth.exe -O1 -Wall -Wno-missing-braces -I ./include/ -L /home/hal9000/raylib-5.0_win32_mingw-w64/lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -D_GLIBCXX_DEBUG

local_build: 
	g++ $(CFILES) -o main $(DEFINES) $(INCLUDES) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

run:
	./main

clean: 
	rm main

web_build:
	mkdir -p build && \
	cd $(EMSDK_PATH) && . ./emsdk_env.sh && cd "${PWD}" && \
	emcc -o $(WEB_OUT) $(DEFINES) $(CFILES) $(INCLUDES) $(WEB_OPT)

web_run:
	cd $(EMSDK_PATH) && . ./emsdk_env.sh && cd "${PWD}" && \
	emrun $(WEB_OUT) --browser $(BROWSER)

web_zip:
	cd build && zip $(WEB_ZIP) index.*

#Local build 
local: local_build run clean

# Build and run in browser
test_web: web_build web_run

# Build and zip for itch.io
release_web: web_build web_zip

# Publish directly to itch.io (you will need to install and login to butler)
publish_web:
	/home/hal9000/butler push build/$(WEB_ZIP) $(ITCH_USER)/$(ITCH_PAGE):web --userversion $(PROJECT_VERSION)

windows: windows_build
