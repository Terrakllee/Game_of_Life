/* 
 * Conway's Game of Life — by Terrakllee
 * Copyright (C) 2025  Terrakllee
 *
 * This file is part of Conway's Game of Life — by Terrakllee.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: GPL-3.0
 */

#include <iostream>
#include <chrono>
#include <thread>
#include "engine.h"
#include "main_menu.h"

namespace main_menu
{
    void UserAddCell(GameOfLife& g)
    {
        // int user;
        int x, y;
        g.SetShowCoords(true);
        g.SetShowCage(false);

        std::cout << "\nCоздание клетки";
        std::cout << "\nВведите позицию клетки: \n";

        std::cout << "x = ";

        do
        {
            std::cin >> x;
            if (x < 1)
            {
                std::cout << "Слишком малые координаты x!\n";
                std::cout << "\nx = ";
            }
            else if(x > g.GetActualGridSizeCols())
            {
                std::cout << "Слишком большие координаты x!\n";
                std::cout << "\nx = ";
            }
            
        } while (x < 1 || x > g.GetActualGridSizeCols());
        
        std::cout << "y = ";

        do
        {
            std::cin >> y;
            if (y < 1)
            {
                std::cout << "Слишком малые координаты y!\n";
                std::cout << "\ny = ";
            }
            else if(y > g.GetActualGridSizeRows())
            {
                std::cout << "Слишком большие координаты y!\n";
                std::cout << "\ny = ";
            }
        } while (y < 1 || y > g.GetActualGridSizeRows());
        std::cout << "Клетка создана (x " << x << ";y " << y << ")\n";
        g.InitCell(x, y, true);
    }

    void UserKillCell(GameOfLife& g)
    {
        // int user;
        int x, y;
        g.SetShowCoords(true);
        g.SetShowCage(false);

        std::cout << "\nCоздание клетки";
        std::cout << "\nВведите позицию клетки: \n";

        std::cout << "x = ";

        do
        {
            std::cin >> x;
            if (x < 1)
            {
                std::cout << "Слишком малые координаты x!\n";
                std::cout << "\nx = ";
            }
            else if(x > g.GetActualGridSizeCols())
            {
                std::cout << "Слишком большие координаты x!\n";
                std::cout << "\nx = ";
            }
            
        } while (x < 1 || x > g.GetActualGridSizeCols());
        
        std::cout << "y = ";

        do
        {
            std::cin >> y;
            if (y < 1)
            {
                std::cout << "Слишком малые координаты y!\n";
                std::cout << "\ny = ";
            }
            else if(y > g.GetActualGridSizeRows())
            {
                std::cout << "Слишком большие координаты y!\n";
                std::cout << "\ny = ";
            }
        } while (y < 1 || y > g.GetActualGridSizeRows());
        std::cout << "Клетка удалена (x " << x << ";y " << y << ")\n";
        g.InitCell(x, y, false);
    }

    void Launch(GameOfLife& g)
    {
        double generation = 1; // Start of a Generation
        double stopWhen;
        g.SetShowCoords(false);
        g.SetShowCage(true);

        std::cout << "\n-------!-!!Запуск!!-!-------\n";
        std::cout << "Введите сколько итераций хотите увидеть \n";
        std::cout << "Если вы поставили низкую скорость (более 800), рекомендуется поставить мало итераций (~100-200)\n";
        std::cout << "Если вы поставили высокую скорость (менее 150), рекомендуется поставить больше итераций (~600-800)\n";
        std::cout << "В ином случае это может быть очень долго, тогда закройте и перезапустите игру\n";
        std::cout << "Ввод: ";
        std::cin >> stopWhen;

        g.CheckNeighbours();
        g.SetShowCoords(false);
        do
        {
            g.CellPhysics();
            std::this_thread::sleep_for(std::chrono::milliseconds(g.GetTickTime())); //ChatGPT AI
            g.PrintGrid();
            std::cout << "Популяция: " << g.GetPopulation(); 
            std::cout << "\t\tГенерация: " << generation << "\n";
            generation++;
            g.CheckNeighbours();
        } while (generation != stopWhen+1); // +1 for last generation to appear

        std::cout << "\nСимуляция завершена!\n";
        std::cout << "Вы можете продолжить симуляцию или что то изменить в ней через меню\n";
    }

    void SummonConstructionMenu(GameOfLife& g)
    {
        bool exitConstructionMenu = false;
        char summon;

        do
        {
            std::cout << "\n+---+----+--Строитель конструкций--+----+---+\n";
            std::cout << "Размер вашего поля: " << g.GetActualGridSizeCols() << "x" << g.GetActualGridSizeRows() << "\n"; 
            std::cout << "Введите 'b' для призыва конструкции \"Blinker\" (3x3) \n";
            std::cout << "Введите 'g' для призыва конструкции \"Glider\" (5x5)\n";
            std::cout << "Введите 'p' для призыва конструкции \"Pulsar\"(17x17)\n";
            std::cout << "Введите 'e' для призыва конструкции \"Pentadecathlon\" (11x18)\n";
            std::cout << "Введите 'r' для призыва конструкции \"The R-Pentomino\" (5x5)\n";
            std::cout << "Введите 't' для призыва конструкции \"Toad\" (4x4)\n";
            std::cout << "Введите 'o' для призыва конструкции \"Beacon\" (4x4)\n";
            std::cout << "Введите 'd' для призыва конструкции \"Diehard\" (10x5)\n";
            std::cout << "Введите 'a' для призыва конструкции \"Acorn\" (9x5)\n";
            std::cout << "Введите 'n' для призыва конструкции \"Nuke Line\" (41x3)\n";
            std::cout << "Введите 'l' для призыва конструкции \"Diagonal Nuke\" (10x8)\n";
            std::cout << "Введите 'c' для призыва конструкции \"Compact Nuke\" (5x5)\n";
            std::cout << "Введите 's' для призыва конструкции \"Amogus\" (6x7)\n";
            std::cout << "Введите 'q' чтобы вернуться в меню\n";
            std::cout << "Ввод: ";
            std::cin >> summon;

            switch (summon)
            {
            case 'b':
                {
                    GameOfLife::Pattern blinker(3, 3, "Blinker", 1);
                    g.SummonPattern(blinker);
                }
                exitConstructionMenu = true;
                break;
            case 't':
                {
                    GameOfLife::Pattern toad(5, 5, "Toad", 2);
                    g.SummonPattern(toad);
                }
                exitConstructionMenu = true;
                break;
            case 'o':
                {
                    GameOfLife::Pattern beacon(4, 4, "Beacon", 3);
                    g.SummonPattern(beacon);
                }
                exitConstructionMenu = true;
                break;
            case 'p':
                {
                    GameOfLife::Pattern pulsar(17, 17, "Pulsar", 4);
                    g.SummonPattern(pulsar);
                }
                exitConstructionMenu = true;
                break;
            case 'e':
                {
                    GameOfLife::Pattern pentadecathlon(11, 18, "Pentadecathlon", 5);
                    g.SummonPattern(pentadecathlon);
                }
                exitConstructionMenu = true;
                break;
            case 'g':
                {
                    GameOfLife::Pattern glider(5, 5, "Glider", 6);
                    g.SummonPattern(glider);
                }
                exitConstructionMenu = true;
                break;
            case 'r':
                {
                    GameOfLife::Pattern theRPentomino(5, 5, "The R-Pentomino", 7);
                    g.SummonPattern(theRPentomino);
                }
                exitConstructionMenu = true;
                break;
            case 'd':
                {
                    GameOfLife::Pattern diehard(10, 5, "Diehard", 8);
                    g.SummonPattern(diehard);
                }
                exitConstructionMenu = true;
                break;
            case 'a':
                {
                    GameOfLife::Pattern acorn(9, 5, "Acorn", 9);
                    g.SummonPattern(acorn);
                }
                exitConstructionMenu = true;
                break;
            case 'l':
                {
                    GameOfLife::Pattern diagonalNuke(10, 8, "Diagonal Nuke", 10);
                    g.SummonPattern(diagonalNuke);
                }
                exitConstructionMenu = true;
                break;
            case 'c':
                {
                    GameOfLife::Pattern compactNuke(5, 5, "Compact Nuke", 11);
                    g.SummonPattern(compactNuke);
                }
                exitConstructionMenu = true;
                break;
            case 'n':
                {
                    GameOfLife::Pattern nukeLine(41, 3, "Nuke Line", 12);
                    g.SummonPattern(nukeLine);
                }
                exitConstructionMenu = true;
                break;
            case 's':
                {
                    GameOfLife::Pattern amogus(6, 7, "Amogus", 13);
                    g.SummonPattern(amogus);
                }
                exitConstructionMenu = true;
                break;
            case 'q':
                exitConstructionMenu = true;
                break;
            
            
            default:
                std::cout << "\nТакого объекта не существует!\n";
                break;
            }
        } while (!exitConstructionMenu);
    }

    void RandomizeManyCellsBySeed(GameOfLife& g)
    {
        int amountOfCellsToCreation;

        if (g.GetUserChangedSeed() == false)
        {
            srand(time(nullptr));
        }

        std::cout << "\n@*@**@**@****@***@~~Генерация случайного паттерна~~@***@****@**@**@*@";
        std::cout << "\nВаш сид: " << g.GetSeed();
        std::cout << "\nВведите количество клеток к созданию, сейчас максимум можно сгенерировать: " << g.HowMuchFreeSpaceIsLeft() << " клеток\n";
        std::cout << "Сейчас живо: " << g.CountAliveCellsOnGrid() << " Клеток\n";
        std::cout << "Сейчас мертво: " << g.CountDeadCellsOnGrid() << " Клеток\n";
        std::cout << "В сумме: " << ((g.GetRows()-2)*(g.GetCols())-2) << " Клеток\n";
        std::cout << "Ввод: ";


        do
        {
            std::cin >> amountOfCellsToCreation;
            if (amountOfCellsToCreation < 0)
            {
                std::cout << "Невозможно создать негативное число клеток!\n";
                std::cout << "Ввод: ";
            }
            else if (amountOfCellsToCreation > (g.GetActualGridSizeRows()*g.GetActualGridSizeCols()))
            {
                std::cout << "Невозможно создать больше чем " << g.HowMuchFreeSpaceIsLeft() << " клеток!" << " или " << (g.GetActualGridSizeRows()*g.GetActualGridSizeCols()) << "\n";
                std::cout << "Ввод: ";
            }
        } while (amountOfCellsToCreation < 0 || amountOfCellsToCreation > g.HowMuchFreeSpaceIsLeft());

        if (amountOfCellsToCreation != 0)
        {
            
            for (int i = 0; i < amountOfCellsToCreation; i++)
            {
                g.AliveRandomCell();
            }
        }
        std::cout << "\nБыло сгенерированно: " << g.GetCellsGenerated();
        std::cout << " Клеток\n";
    }
}