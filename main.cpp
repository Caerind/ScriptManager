#include <iostream>

#include "ScriptManager.hpp"

class A
{
    public:
        A() {}

        void setPosition(int x, int y) { mX = x; mY = y; }
        void setX(int x) { mX = x; }
        int getX() { return mX; }
        void setY(int y) { mY = y; }
        int getY() { return mY; }

        static void registerClass(sel::State& state)
        {
            state["A"].SetClass<A>("setX", &A::setX,
                                   "getX", &A::getX,
                                   "setY", &A::setY,
                                   "getY", &A::getY,
                                   "setPosition", &A::setPosition);
        }

        void registerObject(sel::State& state, std::string const& name)
        {
            state[name.c_str()].SetObj(*this,
                                       "setX", &A::setX,
                                       "getX", &A::getX,
                                       "setY", &A::setY,
                                       "getY", &A::getY,
                                       "setPosition", &A::setPosition);
        }

    private:
        int mX;
        int mY;
};

void test(int a)
{
    std::cout << " " << a << std::endl;
}

void printMessage(std::string const& message)
{
    std::cout << message << std::endl;
}

int main()
{
    // ScriptManager class
    ScriptManager scripts;

    // Add your libraries (functions usefull in every lua script)
    scripts.addLibrary([&](sel::State& state)
    {
        state["test"] = test;
        state["printMessage"] = printMessage;
    });

    // Register a class
    A::registerClass(scripts["script.lua"]);

    // Run a function requiring the class and functions from the library
    scripts["script.lua"]["testA"]();

    // Get a Lua function as C++ function, and reuse it later
    sel::Selector func = scripts["script.lua"]["foo"];
    func();

    // Use some Lua function, with parameters and return
    int a = scripts["script.lua"]["sumNb"](4, 5);
    int b = scripts["script.lua"]["multiplyNb"](4, 5);
    std::cout << a << " " << b << std::endl;

    // Creation of an A object
    A object;

    // Registering the object
    object.registerObject(scripts["script.lua"], "object");

    // Modify in C++, check result in Lua
    object.setX(11);
    test(scripts["script.lua"]["object"]["getX"]());

    // Modify in Lua, check in C++
    scripts["script.lua"]["object"]["setX"](22);
    test(object.getX());

    // Use the object from Lua
    scripts["script.lua"]["testobject"]();

    return 0;
}
