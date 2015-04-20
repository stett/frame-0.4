Frame
=====

Yet another innocent programmer's attempt to create a nice, pragmatic entity system.


I am roughly following test driven development principals, and using the [Google Test](https://code.google.com/p/googletest/) unit testing library.

The project is cross-platform (theoretically :P) and can be built using [CMake](http://www.cmake.org/), but I've only tried it on Linux.


Overview
--------

The Frame engine is built, quite predictably, around an object called a *frame*.
A frame is a collection of *systems*, *components*, and *entities*, and is intended to represent an independent, self-contained part of a program.


Usage
-----

To create a component, simply create a class that inherits from `frame::Component`.

    // Create a component
    class Name : public frame::Component {
        string str;
    public:
        Name() : str("name") {}

        void set(const string& str_) {
            str = str_;
        }

        const string& get() const {
            return str;
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

Currently, the only way to retrieve components from the system is to create and iterate over nodes.

    // Create a node which will return all entities with Name components
    auto named_entities = f->add_node<Name>();

    // Loop over all named entities
    for (auto e : *named_entities) {

        // Get the name component of the entity
        auto name = e->get_component<Name>();
    }

Normally, a node would be a member of a system, but it doesn't need to be.
Here's an example of a system which prints the names of all named entities at startup.

    class NameSystem : public frame::System {
        Node* named_entities;

    protected:
        void start() {

            // Create a node which will select all named entities
            named_entities = f->add_node<Name>();

            // Loop over all entities selected by the node, printing their names
            for (auto e : named_entities) {
                cout << e->get_component<Name>().get() << endl;
            }
        }
    };


Building
--------

To build the Frame library and the FrameTest unit testing program, perform the following commands from the root of this repository.

    mkdir build
    ./scripts/build.sh

And from there, to run FrameTest

    ./frame_test/FrameTest