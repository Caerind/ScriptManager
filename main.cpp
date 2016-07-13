#include <iostream>

#include "ScriptManager.hpp"

class A
{
    public:
        A() {}

        void setPosition(int x, int y) { mX = x; mY = y; }

    public:
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
    scripts["script.lua"]["A"].SetClass<A>("x", &A::mX, "y", &A::mY, "setPosition", &A::setPosition);

    // Run a function requiring the class and functions from the library
    scripts["script.lua"]["testA"]();

    // Get a Lua function as C++ function, and reuse it later
    sel::Selector func = scripts["script.lua"]["foo"];
    func();

    // Use some Lua function, with parameters and return
    int a = scripts["script.lua"]["sumNb"](4, 5);
    int b = scripts["script.lua"]["multiplyNb"](4, 5);
    std::cout << a << " " << b << std::endl;

    return 0;
}
