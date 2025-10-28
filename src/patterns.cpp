#include "GameOfLife.h"
#include "patterns.h"
#include <iostream>

namespace patterns
{
    void CreateBlinker(GameOfLife& g) //Blinker 3x3
    {
        g.InitCell(2+g.GCMX(), 1+g.GCMY(), 1);
        g.InitCell(2+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(2+g.GCMX(), 3+g.GCMY(), 1);
    }

    void Test()
    {
        std::cout << "Hello World!\n";
    }
}

