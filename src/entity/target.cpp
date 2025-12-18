#include <iostream>
#include <Windows.h>
#include "Target.hpp"


Target::Target(int posX, int posY)
{
    position = glm::ivec2(posX, posY);
}

Target::~Target() {}

void Target::move(glm::ivec2 direction)
{

}

void Target::attack()
{

}

void Target::draw()
{
    HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hc, 0x04);
    std::cout << texture;
    SetConsoleTextAttribute(hc, 0x07);
}
