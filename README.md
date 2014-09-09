Frame
=====

My own innocent little attempt at a simple Entity/Component/System engine.
Frame follows a generic design, but is being built with Metabox in mind as its client program.
It is *most definitely* a work in progress.


I am roughly following test driven development principals, and using the [Google Test](https://code.google.com/p/googletest/) unit testing library.

The project is cross-platform and can be built using [CMake](http://www.cmake.org/).


What is this... "Frame"?
------------------------

The Frame engine is built, quite predictably, around an object called a *frame*.
A frame is a collection of *systems* and *components*, and is intended to represent an independent part of a program.


For example, one might have a frame for the main game process and one for the game menu.
The primary game process can start/stop/pause any of its frames, save or load a frame's state, or load the data from one frame into another.


Usage
-----


Internal Design
---------------


Building
--------

To build the Frame library and the FrameTest unit testing program, perform the following commands from the root of this repository.

    mkdir build
    cd build
    cmake ../src
    make

And from there, to run FrameTest

    ./frame_test/FrameTest