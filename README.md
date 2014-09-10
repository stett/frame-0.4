Frame
=====

My own innocent little attempt at a simple Entity/Component/System engine. 
Frame follows a generic design, but is being built with a specific application in mind (Metabox).


Frame is *most definitely* a work in progress.


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

To create a component, simply create a class that inherits from `frame::Component`.

    // Create a component
    class Name : public frame::Component {
    public:
        Name() : str("name") {}
        virtual ~Name() {}
        string str;
        void set(const string& str_) {
            str = str_;
        }
    };

Due to the fact that the serialization system needs to dynamically instantiate component instances, 
all components must be registered using the `REGISTER_FRAME_COMPONENT(<Component Class Name>)` somewhere in the implementation.
I consider this to be a highly unfortunate constraint.

    // Register the Name component
    REGISTER_FRAME_COMPONENT(Name);

The following code sets up a frame with an entity with a basic network of entities

    // Create a frame
    Frame f;

    // Add an entity with a name component
    auto e0 = f.add_entity();
    e0->add_component<Name>()->set("Entity 0");

    // Add an entity with a name and set e0 as it's parent.
    // Adding a built in Parent component to an entity will automatically
    // add a Children component to the parent entity.
    auto e1 = f.add_entity();
    e1->add_component<Name>()->set("Entity 1");
    e1->add_component<Parent>()->set(e0);


Internal Design
---------------


Features
--------


Building
--------

To build the Frame library and the FrameTest unit testing program, perform the following commands from the root of this repository.

    mkdir build
    cd build
    cmake ../src
    make

And from there, to run FrameTest

    ./frame_test/FrameTest