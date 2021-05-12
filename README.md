# Opengl 3d Development
The current line is responsible for 3d development.

## Overview
### Why another guide?
There are some great resources available online on the basics of graphics programming with OpenGL. Unfortunately, most of them assume that the reader already has all the necessary libraries and software set up beforehand. For those not familiarized with the process of setting up a portable C++ project, it can be quite confusing. I decided to create this guide in order address that issue. By the time you reach the end, you should have everything you need to successfully get started with other OpenGL tutorials.

### What this guide covers
This guide will explain how to create a portable project structure (using CMake), integrate some libraries (GLFW and glad), and build / run a simple OpenGL application.

### Prerequisites
In order to follow this guide, you will need to know the basics of your build system (how to compile / run code). The guide is compatible with any build system that CMake supports (examples include Visual Studio Code, and CMakefiles).

## The build system
There are many viable operating systems and compilers available for use today. Trying to set up and manage individual project files for each of them would be a tedious, laborsome, and error-prone task. Luckily, you don't have to! There exists a great tool, named CMake, which manages the specifics of each operating system / compiler / IDE for you. To lazily quote their 'About' page:

> CMake is an extensible, open-source system that manages the build process in an operating system and in a compiler-independent manner.
> (https://cmake.org/overview/)

With CMake, we can write instructions on how to build our code once and have it work in a variety of environments. In order to make use of CMake, you'll need to download and install it from https://cmake.org/download/ (just grab the latest version available for your platform).

## Source control
This guide uses git as source control (it is hosted on GitHub, and it pulls in a library via submodules). You don't necessarily need to use git in order to follow the guide, but it is reccomended. If you don't have git, you can download it from https://git-scm.com/. If you prefer to have a visual client, you can download one from https://desktop.github.com/. If you are not familiar with git (or source control in general), there is a helpful tutorial at https://try.github.io/.

## Initial project setup

Now that our tools are set up, it's time to start on the actual project. First, we'll need to create a folder to store the project in. I'll be naming the folder "InitGL", but feel free to use whatever you'd like! Within the project folder, we're going to want to create a few subfolders: "source", where we'll store the source code of the project, and "build", where we'll store our built application.

TODO Talk about git init, committing changes, etc.
TODO Talk about .gitignore

In order to test our setup, we're going to create a simple application written in C++. In the source folder, create a file named "main.cpp" with the following contents:

```cpp
#include <stdio.h>

int main(int argc, char* argv[]) {
   printf("InitGL: simple program is running!\n");

   return 0;
}
```

Now that we have the source code in place, we need to tell CMake how our project should be built so that it can generate the proper build system files. We can do this by creating a text file in the project folder named "CMakeLists.txt" and filling it with the necessary information; go ahead and fire up your favorite text editor!

First, we need to specify what CMake version we're targeting. For this guide, we'll be targeting version 3.1: `cmake_minimum_required(VERSION 3.1)`.

Next, we need to declare a project. Once again, I'll be using the name "InitGL", but feel free to use whatever name you'd like (no spaces, though): `project(InitGL)`.

We need to let CMake know what source files will need to be compiled and the location of any header files we'll want to include. We'll need to reference the "source" folder location a few times, and it would be nice if we didn't need to write out the path every time we needed it - luckily, CMake allows us to set variables! We can set the variable "SRC_DIR" to point to our "source" folder with the following line: `set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")`.

TODO: Explain CMake variables (setting, using, ${syntax}, etc.)

Now that we have our handy "source" folder path stored, we can use it while specifying the list of source files that we want to compile: `set(SOURCES "${SRC_DIR}/main.cpp")`.

TODO: Explain CMake lists

The next step is to tell CMake what we want to do with our compiled source files. In this case, we want to use them to build an executable (as opposed to a library, for example). We can do this with CMake's "add_executable" command, where we specify the name to use for the executable (in this case, we're just using the project name, "InitGL") and the source files needed to build it: `add_executable(${PROJECT_NAME} ${SOURCES})`.

TODO Explain the concept of a CMake target

We need to tell CMake where our build system should look for header files when building our executable. While this project doesn't make use of any headers, it is quite common for them to exist in the same folder as the source (.cpp) files, so we'll go ahead and set that up for convenience's sake: `target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")`.

Finally, we'll let CMake know that we want to have access to C++11 language features (specifically for this guide, nullptr): `set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)`.

Here is the completed CMakeLists.txt file:

```cmake
# Project definition
cmake_minimum_required(VERSION 3.1)
project(InitGL)

# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(SOURCES "${SRC_DIR}/main.cpp")

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
```

At this point, your project should have the following file structure:

* /InitGL
  * CMakeLists.txt
  * build/
  * source/
    * main.cpp

Now that everything is in place, we can run CMake and have it generate our build system. We'll want to use the project folder as the CMake "source" location, and the "build" folder as the "build" location. If you're running CMake from the command line, you can do this by changing directory into the "build" folder and executing `cmake ..`. If you're using the CMake GUI, simply specify the root folder as the "source" folder, and the "build" folder as the "build" folder, and run. If all goes well, CMake should drop a bunch of files in your "build" folder to be used with your build system (Visual Studio solution, XCode project, Makefiles, etc.). Fire up your build system, build the generated project, and try running it; hopefully, you see "InitGL: simple program is running!" printed to your console / output!

Getting a console application running is a good first step, but if we want to work with OpenGL, we're going to need a window to draw to.

## The window system

Different APIs exist across operating systems for creating and managing windows. Once again, we don't want to have to worry about the specifics of each, so we'll use a handy library to deal with them for us. There are a number of such libraries available with varying capabilities and features. For this guide, I've decided to go with GLFW (link) due to its simplicity. If you're looking for additional features, feel free to check out SDL (link) and SFML (link).

The first thing we'll need to do in order to use GLFW is to grab its source code. There are a couple ways you can do this. If you're using git, you can check out GLFW as a submodule of your repository. This is nice because it allows you to pull GLFW into your repository without having to keep around an entire duplicated copy of the GLFW source code. If you don't want to use submodules, you can always clone GLFW and manually copy it into your repository. If you don't want to use git at all, you can download a copy of the source code from (link).

No matter how you decide to obtain the GLFW source code, we're going to want it to live in the same place in our project. In the project folder, along side the "build" and "source" folders, we're going to want to make a new folder named "libraries". We'll use this folder to store third-party libraries that our project needs to run. Next, we'll want to place our copy of GLFW in the "libraries" folder. If you choose to use git submodules, you can do this by entering the "libraries" folder and running `git submodule add https://github.com/glfw/glfw.git`. If you decided to clone or download GLFW instead, you'll want to copy the "glfw" folder into the "libraries" folder instead.

Now that the GLFW files are in place, we need to update our "CMakeLists.txt" file so that CMake knows we want to build and link against GLFW. Similar to how we made a CMake variable to hold the path of the "source" folder earlier, it'll be useful for us to have a variable to hold the path of the "libraries" folder, so let's start by adding that: `set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")`.

Next, we can create a variable for the GLFW folder: `set(GLFW_DIR "${LIB_DIR}/glfw")`.

As it happens, GLFW has support for being built with CMake. This means that, instead of us having to specify all the source files and rules for building it, we can just tell CMake to read the information already present within GLFW's own CMakeLists.txt file. Before we do that, however, there are a few things that GLFW has set up in its CMakeLists file that we want to disable (such as building example programs for GLFW). We can disable these options with the following lines:

TODO More fully explain CMake options

```CMake
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
```

With the options disabled, it is now safe for us to tell CMake to parse GLFW's CMakeLists.txt file: `add_subdirectory("${GLFW_DIR}")`.

GLFW is now set up to be built by our CMake setup. However, we have not yet attached it to our own project. In order to do that, we'll need to tell CMake that we want our program to link against GLFW, and we need to add GLFW's "include" folder to our list of include paths, so that we will be able to include the necessary headers in our source files:

```CMake
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
```

Finally, we need to instruct GLFW not to try to include any OpenGL headers on its own, as we will be supplying them ourselves (why we want to do this will be explained in the next section). We can do this by defining a macro, "GLFW_INCLUDE_NONE", before including any GLFW headers in our source files. It's easy to forget to do this however, so instead we can add "GLFW_INCLUDE_NONE" to the compile-time definitions of our project (macros that CMake will make sure are defined automatically): `target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")`.

Here is what your CMakeLists.txt file should look like now:

```CMake
# Project definition
cmake_minimum_required(VERSION 3.1)
project(InitGL)

# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")
set(SOURCES "${SRC_DIR}/main.cpp")

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")
```

## Loading OpenGL functions

TODO: Explain how only OpenGL version 1.x comes with each OS (I think?), and why we have to dynamically load the functions and symbols.

Once again, there are a number of options for solving this problem. I have decided to go with glad (link) due to its ease of use (alternatives include GLEW and TODO: add more). The source for glad is generated by some Python scripts, which pull down and parse the current OpenGL specification to create the C code. Additionally, a website was created to serve as a front end for generating the glad loader, which is available at http://glad.dav1d.de/.

TODO Explain how to use website to generate our loader

Extract the contents of the glad zip archive, and copy the "glad" folder into the "libraries" folder. Like with GLFW, we'll need to update our CMakeLists to compile and link against glad. Unlike with GLFW, however, glad does not come with its own CMakeLists.txt file, do we'll need to do a little extra work to get everything hooked up. Luckily glad has a pretty simple project layout (just one source file), so it's not much of a challenge.

Just like before, we'll start off by creating a variable to point to the glad folder: `set(GLAD_DIR "${LIB_DIR}/glad")`.

Next, we need to tell CMake that we want to compile the glad source file into a library with the name "glad": `add_library("glad" "${GLAD_DIR}/src/glad.c")`.

We need to let CMake know where it can find the header files it will look for while compiling glad: `target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")`.

We will also want access to those same header files from our own project: `target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")`.

Finally, we'll ask CMake to link the compiled glad library to our project, along with (TODO: explain CMAKE_DL_LIBS): `target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")`.