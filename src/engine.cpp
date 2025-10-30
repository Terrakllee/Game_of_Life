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
#include <string>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#endif

#include "engine.h"
#include "patterns.h"
#include "UI.h"
#include "settings.h"

using namespace std;

static const string VERSION = "1.0";

//Getters

bool GameOfLife::IsEdge(int &i, int &j)
{
    if (i == 0 || j == 0 || i == rows-1 || j == cols-1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool GameOfLife::IsCellEdge(int &i, int &j)
{
    if (i == 1 || j == 1 || i == actualGridSizeRows || j == actualGridSizeCols)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool GameOfLife::IsUpEdge(int &i)
{
    if (i == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool GameOfLife::IsDownEdge(int &i)
{
    if (i == rows-1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool GameOfLife::IsLeftEdge(int &j)
{
    if (j == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool GameOfLife::IsRightEdge(int &j)
{
    if (j == cols-1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool GameOfLife::IsUpLeftCorner(int &i, int &j)
{
    if (i == 0 && j == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool GameOfLife::IsUpRightCorner(int &i, int &j)
{
    if (i == 0 && j == cols-1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool GameOfLife::IsDownLeftCorner(int &i, int &j)
{
    if (i == rows-1 && j == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool GameOfLife::IsDownRightCorner(int &i, int &j)
{
    if (i == rows-1 && j == cols-1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void GameOfLife::RawPrintGrid() //Prints entire grid as it is (for debugging)
{
    cout << "\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (Grid[i][j].GetIsAlive() == true)
            {
                cout << "##";
            }
            else if (Grid[i][j].GetIsAlive() == false)
            {
                cout << "..";
            }
        }
        cout << "\n";
    }
    
}

void GameOfLife::PrintBG(int &i, int &j)
{
    if (gridView == true)
    {
        if (j != 1)
        {  
            frame += "│";
        }
    }

    if (bgCharChoose < 6 && bgCharChoose != 1 && bgCharChoose != 2 && bgCharChoose != 3)
    {
        (frame += bgChar) += bgChar;
    }

    if (bgCharChoose == 1 || bgCharChoose == 2 || bgCharChoose == 3)
    {
        (frame += bgChar) += " ";
    }

    switch (bgCharChoose)
    {
    case 6:
        frame += "░░";
        break;
    case 7:
        frame += "██";
        break;
    case 8:
        frame += "▓▓";
        break;
    case 9:
        frame += "▒▒";
        break;
    case 10:
        frame += "䷀䷀";
        break;
    case 11:
        frame += "𝌆𝌆";
        break;
    case 12:
        frame += "⣿⣿";
        break;
    case 18:
        frame += "──";
        break;
    case 19:
        if (i == rows-2)
        {
            frame += "  ";
        }
        else
        {
            frame += "__";
        }
        
        
        
        break;
    
    default:
        break;
    }
}

void GameOfLife::PrintCage(int &i, int &j)
{   
    if (IsUpLeftCorner(i, j))
    {
        frame += "┏"; //╔
    }
    else if (IsUpRightCorner(i, j))
    {
        frame += "┓"; //╗
    }
    else if (IsDownLeftCorner(i, j))
    {
        frame += "┗"; //╚
    }
    else if (IsDownRightCorner(i, j))
    {
        frame += "┛"; //╝
    }
    else if (IsUpEdge(i))
    {   
        if (gridView == true)
        {
            frame += "━━━"; //══━━──
        }
        else
        {
            frame += "━━"; //══━━──
        }
    }
    else if (IsLeftEdge(j))
    {
        frame += "┃"; //║┃│
    }
    else if (IsDownEdge(i))
    {
        if (gridView == true)
        {
            frame += "━━━"; //══━━──
        }
        else
        {
            frame += "━━"; //══━━──
        }
    }
    else if (IsRightEdge(j))
    {
        if (gridView == true)
        {
            frame += " ┃"; //║┃│
        }
        else
        {
            frame += "┃"; //║┃│
        }
    }
}

void GameOfLife::PrintCoords(int &i, int &j, char &numbericRows, char &numbericCols)
{
    if (IsUpLeftCorner(i, j))
    {
        if (gridView == true)
        {
            frame += "y-";
        }
        else
        {
            frame += "#";
        }
    }
    else if (IsUpRightCorner(i, j))
    {
        if (gridView == true)
        {
            frame += "x-";
            numbericCols = 'A';
        }
        else
        {
            frame += "#";
            numbericCols = 'A';
        }
    }
    else if (IsDownLeftCorner(i, j))
    {
        if (gridView == true)
        {
            frame += "y+";
        }
        else
        {
            frame += "#";
        }
    }
    else if (IsDownRightCorner(i, j))
    {
        if (gridView == true)
        {
            frame += "x+";
        }
        else
        {
            frame += "#";
        }
    }
    else if (IsUpEdge(i))
    {   
        if (gridView == true)
        {
            if ((j % 100) == 0)
            {
                (frame += numbericCols++) += " ";
            }
            else if (j < 10)
            {
                ((frame += " ") += (j % 10)) += " ";
            }
            else
            {
                (frame += (j % 100)) += " ";
            }
        }
        else
        {
            if ((j % 10) == 0)
            {
                (frame += numbericCols++) += " ";
            }
            else
            {
                (frame += (j % 10)) += " ";
            }
        }
    }
    else if (IsLeftEdge(j))
    {
        if (gridView == true)
        {
            if ((i % 100) == 0)
            {
                frame += numbericRows;
            }
            else if (i < 10)
            {
                (frame += " ") += (i % 10);
            }
            else
            {
                frame += (i % 100);
            }
        }
        else
        {
            if ((i % 10) == 0)
            {
                frame += numbericRows;
            }
            else
            {
                frame += (i % 10);
            }
        }
    }
    else if (IsDownEdge(i))
    {
        if (gridView == true)
        {
            if ((j % 100) == 0)
            {
                (frame += numbericCols++) += " ";
            }
            else if (j < 10)
            {
                ((frame += " ") += (j % 10)) += " ";
            }
            else
            {
                (frame += (j % 100)) += " ";
            }
        }
        else
        {
            if ((j % 10) == 0)
            {
                (frame += numbericCols++) += " ";
            }
            else
            {
                (frame += (j % 10)) += " ";
            }
        }
    }
    else if (IsRightEdge(j))
    {
        if (gridView == true)
        {
            if ((i % 100) == 0)
            {
                frame += numbericRows++;
            }
            else if (i < 10)
            {
                (frame += " ") += (i % 10);
            }
            else
            {
                (frame += " ") += (i % 100);
            }
        }
        else
        {
            if ((i % 10) == 0)
            {
                frame += numbericRows++;
            }
            else
            {
                frame += (i % 10);
            }
        }
    }
        
}

void GameOfLife::PrintCell(int &i, int &j)
{
    if (gridView == true && j != 1)
    {
        frame += "│";
    }
    if (gridView == true && i == rows-2)
    {
        frame += "  ";
    }
    else if (bgCharChoose == 7 || bgCharChoose == 8 || bgCharChoose == 10)
    {
        frame += "  ";
    }
    else
    {
        frame += "██";
    }
}

void GameOfLife::ClearScreen() //Grok AI
{
    if (!frameHistory)
    {
        #ifdef _WIN32
        system("cls");
        #endif
    }
    cout << "\033[2J\033[1;1H" << flush;
}

void GameOfLife::PrintGrid() //Prints grid with custom BG and Coordinates, displays life cells
{
    ClearScreen(); //Grok AI
    frame.clear(); //Grok AI
    // For coordinates A = 10, B = 20 etc
    char numbericRows = 'A';
    char numbericCols = 'A';

    frame += "\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {

            if (showCage == true)
            {
                PrintCage(i, j);
            }

            if (showCoords == true)
            {
                PrintCoords(i, j, numbericRows, numbericCols);
            }
            if (Grid[i][j].GetIsAlive() && !IsEdge(i, j))
            {
                PrintCell(i, j);
            }
            else if (!IsEdge(i, j))
            {
                PrintBG(i, j);
            }   
        }
        frame += "\n";
    }
    frame += "\n";

    cout << frame << flush; //Grok AI
}

void GameOfLife::CheckNeighbours() //Checks who is neighbouring current cell and how many neighbours
{
    for (int i = 1; i < (rows-1); i++)
    {
        for (int j = 1; j < (cols-1); j++)
        {
            ///// CHECKS IF NEIGHBOURING CELL IS ALIVE 
            if (Grid[i-1][j-1].GetIsAlive())
            {
                if (Grid[i][j].GetUpperLeftCornerAlive() != 1)
                {
                    Grid[i][j].SetNeigboursAliveCount(Grid[i][j].GetNeigboursAliveCount() + 1);
                    Grid[i][j].SetUpperLeftCornerAlive(true);
                }
            }
            if (Grid[i-1][j].GetIsAlive())
            {
                if (Grid[i][j].GetUpperMiddleAlive() != 1)
                {
                    Grid[i][j].SetNeigboursAliveCount(Grid[i][j].GetNeigboursAliveCount() + 1);
                    Grid[i][j].SetUpperMiddleAlive(true);
                }
            }
            if (Grid[i-1][j+1].GetIsAlive())
            {
                if (Grid[i][j].GetUpperRightCornerAlive() != 1)
                {
                    Grid[i][j].SetNeigboursAliveCount(Grid[i][j].GetNeigboursAliveCount() + 1);
                    Grid[i][j].SetUpperRightCornerAlive(true);
                }
            }
            if (Grid[i][j-1].GetIsAlive())
            {
                if (Grid[i][j].GetLeftMiddleAlive() != 1)
                {
                    Grid[i][j].SetNeigboursAliveCount(Grid[i][j].GetNeigboursAliveCount() + 1);
                    Grid[i][j].SetLeftMiddleAlive(true);
                }
            }
            if (Grid[i][j+1].GetIsAlive())
            {
                if (Grid[i][j].GetRightMiddleAlive() != 1)
                {
                    Grid[i][j].SetNeigboursAliveCount(Grid[i][j].GetNeigboursAliveCount() + 1);
                    Grid[i][j].SetRightMiddleAlive(true);
                }
            }
            if (Grid[i+1][j-1].GetIsAlive())
            {
                if (Grid[i][j].GetDownLeftCornerAlive() != 1)
                {
                    Grid[i][j].SetNeigboursAliveCount(Grid[i][j].GetNeigboursAliveCount() + 1);
                    Grid[i][j].SetDownLeftCornerAlive(true);
                }
            }
            if (Grid[i+1][j].GetIsAlive())
            {
                if (Grid[i][j].GetDownMiddleAlive() != 1)
                {
                    Grid[i][j].SetNeigboursAliveCount(Grid[i][j].GetNeigboursAliveCount() + 1);
                    Grid[i][j].SetDownMiddleAlive(true);
                }
            }
            if (Grid[i+1][j+1].GetIsAlive())
            {
                if (Grid[i][j].GetDownRightCornerAlive() != 1)
                {
                    Grid[i][j].SetNeigboursAliveCount(Grid[i][j].GetNeigboursAliveCount() + 1);
                    Grid[i][j].SetDownRightCornerAlive(true);
                }
            }

            /////////////////////////////////////////////// CHECK IF NEIGBOURING CELL IS DEAD

            if (Grid[i-1][j-1].GetIsAlive() == false)
            {
                if (Grid[i][j].GetUpperLeftCornerAlive() != 0)
                {
                    Grid[i][j].SetNeigboursAliveCount(Grid[i][j].GetNeigboursAliveCount() - 1);
                    Grid[i][j].SetUpperLeftCornerAlive(false);
                }
            }
            if (Grid[i-1][j].GetIsAlive() == false)
            {
                if (Grid[i][j].GetUpperMiddleAlive() != 0)
                {
                    Grid[i][j].SetNeigboursAliveCount(Grid[i][j].GetNeigboursAliveCount() - 1);
                    Grid[i][j].SetUpperMiddleAlive(false);
                }
            }
            if (Grid[i-1][j+1].GetIsAlive() == false)
            {
                if (Grid[i][j].GetUpperRightCornerAlive() != 0)
                {
                    Grid[i][j].SetNeigboursAliveCount(Grid[i][j].GetNeigboursAliveCount() - 1);
                    Grid[i][j].SetUpperRightCornerAlive(false);
                }
            }
            if (Grid[i][j-1].GetIsAlive() == false)
            {
                if (Grid[i][j].GetLeftMiddleAlive() != 0)
                {
                    Grid[i][j].SetNeigboursAliveCount(Grid[i][j].GetNeigboursAliveCount() - 1);
                    Grid[i][j].SetLeftMiddleAlive(false);
                }
            }
            if (Grid[i][j+1].GetIsAlive() == false)
            {
                if (Grid[i][j].GetRightMiddleAlive() != 0)
                {
                    Grid[i][j].SetNeigboursAliveCount(Grid[i][j].GetNeigboursAliveCount() - 1);
                    Grid[i][j].SetRightMiddleAlive(false);
                }
            }
            if (Grid[i+1][j-1].GetIsAlive() == false)
            {
                if (Grid[i][j].GetDownLeftCornerAlive() != 0)
                {
                    Grid[i][j].SetNeigboursAliveCount(Grid[i][j].GetNeigboursAliveCount() - 1);
                    Grid[i][j].SetDownLeftCornerAlive(false);
                }
            }
            if (Grid[i+1][j].GetIsAlive() == false)
            {
                if (Grid[i][j].GetDownMiddleAlive() != 0)
                {
                    Grid[i][j].SetNeigboursAliveCount(Grid[i][j].GetNeigboursAliveCount() - 1);
                    Grid[i][j].SetDownMiddleAlive(false);
                }
            }
            if (Grid[i+1][j+1].GetIsAlive() == false)
            {
                if (Grid[i][j].GetDownRightCornerAlive() != 0)
                {
                    Grid[i][j].SetNeigboursAliveCount(Grid[i][j].GetNeigboursAliveCount() - 1);
                    Grid[i][j].SetDownRightCornerAlive(false);
                }
            }
        }
    }
}

void GameOfLife::Pattern::MessageSummonSuccess()
{
    cout << "\nОбъект \""<<name<<"\" заспавнился успешно!\n";
}

bool GameOfLife::CheckIfPatternFits(Pattern &pattern)
{
    return actualGridSizeCols >= pattern.GetSizeX() && actualGridSizeRows >= pattern.GetSizeY();
}

void GameOfLife::CreatePatternByID(int patternID)
{
    switch (patternID)
    {
    case 1:
        patterns::CreateBlinker(*this);
        break;
    case 2:
        patterns::CreateToad(*this);
        break;
    case 3:
        patterns::CreateBeacon(*this);
        break;
    case 4:
        patterns::CreatePulsar(*this);
        break;
    case 5:
        patterns::CreatePentadecathlon(*this);
        break;
    case 6:
        patterns::CreateGlider(*this);
        break;
    case 7:
        patterns::CreateTheRPentomino(*this);
        break;
    case 8:
        patterns::CreateDiehard(*this);
        break;
    case 9:
        patterns::CreateAcorn(*this);
        break;
    case 10:
        patterns::CreateDiagonalNuke(*this);
        break;
    case 11:
        patterns::CreateCompactNuke(*this);
        break;
    case 12:
        patterns::CreateNukeLine(*this);
        break;
    case 13:
        patterns::CreateAmogus(*this);
        break;
    default:
        cout << "\nОбъекта с таким ID не существует!\n";
        break;
    }
}

void GameOfLife::SummonPattern(Pattern &pattern)
{
    if (CheckIfPatternFits(pattern))
    {
        coordColibrX = pattern.GetSizeX() / 2; //fixes user coordinates cell placement X //Half size of a building to paste (center)
        coordColibrY = pattern.GetSizeY() / 2; //fixes user coordinates cell placement Y //Half size of a building to paste (center)

        cMX = ((actualGridSizeCols / 2)-coordColibrX);
        cMY = ((actualGridSizeRows / 2)-coordColibrY); 

        CreatePatternByID(pattern.GetPatternID()); // uncoment!
        pattern.MessageSummonSuccess();
        // PrintGrid();  // UNDONE
        // MovePattern();
    }
    else
    {
        cout << "\nНе удалось заспавнить объект \""<<pattern.GetName()<<"\", недостаточно места (Требуется " << pattern.GetSizeX() << "x" << pattern.GetSizeY() << ", а ваше поле " << GetActualGridSizeCols() << "x" << GetActualGridSizeRows() <<  ")\n";
    }
}

// void MovePattern() // UNDONE
// {
//     char userMove;
//     bool exitMovingPattern;
//     cout << "\nВведите в какую сторону хотите переместить паттерн\n";
//     cout << "Если вас устраивает позиция паттерна введите - 'c'\n";
//     cout << "Чтобы переместить паттерн вверх, введите - 'u'\n";
//     cout << "Чтобы переместить паттерн вниз, введите - 'd'\n";
//     cout << "Чтобы переместить паттерн влево, введите - 'l'\n";
//     cout << "Чтобы переместить паттерн вправо, введите - 'r'\n";
//     cout << "Ввод: ";
//     cin >> userMove;

//     do
//     {
//         switch (userMove)
//         {
//         case 'c':
//             exitMovingPattern = true;
//             break;
//         case 'u':
//             // MovePatternUp();
//             break;
//         case 'd':
//             // MovePatternDown();
//             break;
//         case 'l':
//             MovePatternLeft();
//             break;
//         case 'r':
//             // MovePatternRight();
//             break;
        
//         default:
//             cout << "\nНет такого направления!\n";
//             break;
//         }
//     } while (!exitMovingPattern);

// }

// void MovePatternLeft() // UNDONE!!!!
// {
//     int uM; // user chooses for how much to move
//     cout << "\nВведите насколько нужно сдвинуть паттерн влево (-x)\n";
//     do
//     {
//         cout << "Ввод: ";
//         cin >> uM;

//         if (uM > cMX)
//         {
//             cout << "\nЭто край поля, нельзя сдвинуть паттерн левее!\n";
//         }
//     } while (uM >= cMX);
    
    

//     for (int i = 1; i < actualGridSizeRows; i++)
//     {
//         for (int j = 1; j < actualGridSizeCols; j++)
//         {
//             if (!IsCellEdge(i, j))
//             {
//                 Grid[i+cMX][(j-uM)+cMY].SetIsAlive(Grid[i+cMX][j+cMY].GetIsAlive()); // bug is here
//             }
//         }
//     }
// }

void GameOfLife::SummonConstructionMenu() // Menu of summoning different life cell ships like patterns
{
    bool exitConstructionMenu = false;
    char summon;

    do
    {
        cout << "\n+---+----+--Строитель конструкций--+----+---+\n";
        cout << "Размер вашего поля: " << actualGridSizeCols << "x" << actualGridSizeRows << "\n"; 
        cout << "Введите 'b' для призыва конструкции \"Blinker\" (3x3) \n";
        cout << "Введите 'g' для призыва конструкции \"Glider\" (5x5)\n";
        cout << "Введите 'p' для призыва конструкции \"Pulsar\"(17x17)\n";
        cout << "Введите 'e' для призыва конструкции \"Pentadecathlon\" (11x18)\n";
        cout << "Введите 'r' для призыва конструкции \"The R-Pentomino\" (5x5)\n";
        cout << "Введите 't' для призыва конструкции \"Toad\" (4x4)\n";
        cout << "Введите 'o' для призыва конструкции \"Beacon\" (4x4)\n";
        cout << "Введите 'd' для призыва конструкции \"Diehard\" (10x5)\n";
        cout << "Введите 'a' для призыва конструкции \"Acorn\" (9x5)\n";
        cout << "Введите 'n' для призыва конструкции \"Nuke Line\" (41x3)\n";
        cout << "Введите 'l' для призыва конструкции \"Diagonal Nuke\" (10x8)\n";
        cout << "Введите 'c' для призыва конструкции \"Compact Nuke\" (5x5)\n";
        cout << "Введите 's' для призыва конструкции \"Amogus\" (6x7)\n";
        cout << "Введите 'q' чтобы вернуться в меню\n";
        cout << "Ввод: ";
        cin >> summon;

        switch (summon)
        {
        case 'b':
            {
                Pattern blinker(3, 3, "Blinker", 1);
                SummonPattern(blinker);
            }
            exitConstructionMenu = true;
            break;
        case 't':
            {
                Pattern toad(5, 5, "Toad", 2);
                SummonPattern(toad);
            }
            exitConstructionMenu = true;
            break;
        case 'o':
            {
                Pattern beacon(4, 4, "Beacon", 3);
                SummonPattern(beacon);
            }
            exitConstructionMenu = true;
            break;
        case 'p':
            {
                Pattern pulsar(17, 17, "Pulsar", 4);
                SummonPattern(pulsar);
            }
            exitConstructionMenu = true;
            break;
        case 'e':
            {
                Pattern pentadecathlon(11, 18, "Pentadecathlon", 5);
                SummonPattern(pentadecathlon);
            }
            exitConstructionMenu = true;
            break;
        case 'g':
            {
                Pattern glider(5, 5, "Glider", 6);
                SummonPattern(glider);
            }
            exitConstructionMenu = true;
            break;
        case 'r':
            {
                Pattern theRPentomino(5, 5, "The R-Pentomino", 7);
                SummonPattern(theRPentomino);
            }
            exitConstructionMenu = true;
            break;
        case 'd':
            {
                Pattern diehard(10, 5, "Diehard", 8);
                SummonPattern(diehard);
            }
            exitConstructionMenu = true;
            break;
        case 'a':
            {
                Pattern acorn(9, 5, "Acorn", 9);
                SummonPattern(acorn);
            }
            exitConstructionMenu = true;
            break;
        case 'l':
            {
                Pattern diagonalNuke(10, 8, "Diagonal Nuke", 10);
                SummonPattern(diagonalNuke);
            }
            exitConstructionMenu = true;
            break;
        case 'c':
            {
                Pattern compactNuke(5, 5, "Compact Nuke", 11);
                SummonPattern(compactNuke);
            }
            exitConstructionMenu = true;
            break;
        case 'n':
            {
                Pattern nukeLine(41, 3, "Nuke Line", 12);
                SummonPattern(nukeLine);
            }
            exitConstructionMenu = true;
            break;
        case 's':
            {
                Pattern amogus(6, 7, "Amogus", 13);
                SummonPattern(amogus);
            }
            exitConstructionMenu = true;
            break;
        case 'q':
            exitConstructionMenu = true;
            break;
        
        
        default:
            cout << "\nТакого объекта не существует!\n";
            break;
        }
    } while (!exitConstructionMenu);
}

int GameOfLife::CountAliveCellsOnGrid() // Counts and returns number of alive cells on the entire grid
{
    int amountOfCellsAliveOnGrid = 0;
    for (int i = 1; i < (rows-1); i++)
    {
        for (int j = 1; j < (cols-1); j++)
        {
            if (Grid[i][j].GetIsAlive() == true)
            {
                amountOfCellsAliveOnGrid++;
            }
        }
    }
    return amountOfCellsAliveOnGrid;
}

int GameOfLife::CountDeadCellsOnGrid() // Counts and returns number of dead cells on the entire grid
{
    int amountOfCellsDeadOnGrid = 0;
    for (int i = 1; i < (rows-1); i++)
    {
        for (int j = 1; j < (cols-1); j++)
        {
            if (Grid[i][j].GetIsAlive() == false)
            {
                amountOfCellsDeadOnGrid++;
            }
        }
    }
    return amountOfCellsDeadOnGrid;
}

int GameOfLife::HowMuchFreeSpaceIsLeft() // Counts how many dead cells are here?
{
    return (actualGridSizeRows * actualGridSizeCols) - CountAliveCellsOnGrid();
}

// void ClearArea(int x, int y) /////////////////////////////////////////////////////////////////////////////
// {

// }

void GameOfLife::ClearGrid() // Clears the grid, basicaly kills all the cells
{
    for (int i = 1; i < (rows-1); i++)
    {
        for (int j = 1; j < (cols-1); j++)
        {
            if (Grid[i][j].GetIsAlive() == true)
            {
                Grid[i][j].SetIsAlive(false);
                population--;
            }
        }
    }
}

void GameOfLife::CellPhysics() // Logic of the cell
{
    for (int i = 1; i < (rows-1); i++)
    {
        for (int j = 1; j < (cols-1); j++)
        {
            if (Grid[i][j].GetIsAlive()  == false)
            {
                if (Grid[i][j].GetNeigboursAliveCount() == 3) // Reproduction
                {
                    Grid[i][j].SetIsAlive(true);
                    population++;
                }
            }
            else if (Grid[i][j].GetIsAlive()  == true)
            {
                if (Grid[i][j].GetNeigboursAliveCount() < 2) // Underpopulation
                {
                    Grid[i][j].SetIsAlive(false);
                    population--;
                }
                else if (Grid[i][j].GetNeigboursAliveCount() > 3) // Overpopulation
                {
                    Grid[i][j].SetIsAlive(false);
                    population--;
                }
            }
        }
    }
}

void GameOfLife::InitCell(int x, int y, bool alive) // Initializes Cell
{
    if (Grid[y][x].GetIsAlive() == true && alive == false)
    {
        Grid[y][x].SetIsAlive(alive);
        population--;
    }

    if (Grid[y][x].GetIsAlive() == false && alive == true)
    {
        Grid[y][x].SetIsAlive(alive);
        population++;
    }
}

void GameOfLife::AliveRandomCell() // Makes random cell alive
{
    short randomX;
    short randomY;

    do
    {
        randomX = rand() % (cols-2) + 1;
        randomY = rand() % (rows-2) + 1;
    } while (Grid[randomY][randomX].GetIsAlive() == true);

    Grid[randomY][randomX].SetIsAlive(true);

    cellsGenerated++;
    population++;

    // cout << "\nCell generated(x=" << randomX << ";y=" << randomY << ")"; //DEBUG

}

void GameOfLife::UserKillCell() // User deletes cell at a specific coordinates
{
    // int user;
    int x, y;
    showCoords = 1;
    showCage = 0;
    
    cout << "\nУдаление клетки";
    cout << "\nВведите позицию клетки: \n";

    cout << "x = ";

    do
    {
        cin >> x;
        if (x < 1)
        {
            cout << "Слишком малые координаты x!\n";
        }
        else if(x > (rows-1))
        {
            cout << "Слишком большие координаты x!\n";
        }
        
    } while (x < 1 || x > (rows-1));
    
    cout << "y = ";

    do
    {
        cin >> y;
        if (y < 1)
        {
            cout << "Слишком малые координаты y!\n";
        }
        else if(y > (cols-1))
        {
            cout << "Слишком большие координаты y!\n";
        }
    } while (y < 1 || y > (cols-1));
    cout << "Клетка удалена (x " << x << ";y " << y << ")\n";
    InitCell(x, y, false);
}

void GameOfLife::UserAddCell() // User places cell at a specific coordinates
{
    // int user;
    int x, y;
    showCoords = 1;
    showCage = 0;

    cout << "\nCоздание клетки";
    cout << "\nВведите позицию клетки: \n";

    cout << "x = ";

    do
    {
        cin >> x;
        if (x < 1)
        {
            cout << "Слишком малые координаты x!\n";
            cout << "\nx = ";
        }
        else if(x > actualGridSizeCols)
        {
            cout << "Слишком большие координаты x!\n";
            cout << "\nx = ";
        }
        
    } while (x < 1 || x > actualGridSizeCols);
    
    cout << "y = ";

    do
    {
        cin >> y;
        if (y < 1)
        {
            cout << "Слишком малые координаты y!\n";
            cout << "\ny = ";
        }
        else if(y > actualGridSizeRows)
        {
            cout << "Слишком большие координаты y!\n";
            cout << "\ny = ";
        }
    } while (y < 1 || y > actualGridSizeRows);
    cout << "Клетка создана (x " << x << ";y " << y << ")\n";
    InitCell(x, y, true);
}

void GameOfLife::RandomizeManyCellsBySeed() // Spawns many random cells using specific user entered seed
{
    int amountOfCellsToCreation;

    if (userChangedSeed == false)
    {
        srand(time(nullptr));
    }

    cout << "\n@*@**@**@****@***@~~Генерация случайного паттерна~~@***@****@**@**@*@";
    cout << "\nВаш сид: " << seed;
    cout << "\nВведите количество клеток к созданию, сейчас максимум можно сгенерировать: " << HowMuchFreeSpaceIsLeft() << " клеток\n";
    cout << "Сейчас живо: " << CountAliveCellsOnGrid() << " Клеток\n";
    cout << "Сейчас мертво: " << CountDeadCellsOnGrid() << " Клеток\n";
    cout << "В сумме: " << ((rows-2)*(cols-2)) << " Клеток\n";
    cout << "Ввод: ";


    do
    {
        cin >> amountOfCellsToCreation;
        if (amountOfCellsToCreation < 0)
        {
            cout << "Невозможно создать негативное число клеток!\n";
            cout << "Ввод: ";
        }
        else if (amountOfCellsToCreation > (actualGridSizeRows*actualGridSizeCols))
        {
            cout << "Невозможно создать больше чем " << HowMuchFreeSpaceIsLeft() << " клеток!" << " или " << (actualGridSizeRows*actualGridSizeCols) << "\n";
            cout << "Ввод: ";
        }
    } while (amountOfCellsToCreation < 0 || amountOfCellsToCreation > HowMuchFreeSpaceIsLeft());

    if (amountOfCellsToCreation != 0)
    {
        
        for (int i = 0; i < amountOfCellsToCreation; i++)
        {
            AliveRandomCell();
        }
    }
    cout << "\nБыло сгенерированно: " << cellsGenerated << " Клеток\n";
}

// void GameOfLife::ChangeCage() //Changes cage design from coordinates to borders, or opposite
// {
//     short user = 0;
//     cout << "\n&&&&&& Выбор оконтовки &&&&&&\n";
//     cout << "Введите 1 если хотите увидеть оконтовку и убрать координаты, и 0 если наоборот\n";
//     cout << "Ввод: ";
//     cin >> user;

//     if (user == 1)
//     {
//         showCage = 1;
//         showCoords = 0;
//     }
//     else
//     {
//         showCage = 0;
//         showCoords = 1;
//     }
// }

void GameOfLife::DebugMenu() // Debug menu for testing different parts of the game mechanics
{
    char user;
    cout << "\n~~$$~$~$$~~Debug Menu~~$$~$~$$~~\n";
    cout << "Press 'p' for calling method RawPrintGrid()\n";
    cout << "Press 'i' for Debug Preset\n";
    cout << "Enter: ";
    cin >> user;
    
    switch (user)
    {
    case 'p':
        RawPrintGrid();
        break;
    case 'i':
        // showCoords = true; //bugged
        // showCage = false;
        bgCharChoose = 5;
        bgChar = ' ';
        tickTime = 100;
        PrintGrid();
        for (int i = 0; i < ((rows*cols) / 3); i++)
        {
            AliveRandomCell(); 
        }
        PrintGrid();
        Launch();
    default:
        break;
    }
}

void GameOfLife::Launch()
{
    double generation = 1; // Start of a Generation
    double stopWhen;
    showCoords = false;
    showCage = true;

    cout << "\n-------!-!!Запуск!!-!-------\n";
    cout << "Введите сколько итераций хотите увидеть \n";
    cout << "Если вы поставили низкую скорость (более 800), рекомендуется поставить мало итераций (~100-200)\n";
    cout << "Если вы поставили высокую скорость (менее 150), рекомендуется поставить больше итераций (~600-800)\n";
    cout << "В ином случае это может быть очень долго, тогда закройте и перезапустите игру\n";
    cout << "Ввод: ";
    cin >> stopWhen;

    CheckNeighbours();
    showCoords = false;
    do
    {
        CellPhysics();
        this_thread::sleep_for(chrono::milliseconds(tickTime)); //ChatGPT AI
        PrintGrid();
        cout << "Популяция: " << population << "\t\tГенерация: " << generation << "\n";
        generation++;
        CheckNeighbours();
    } while (generation != stopWhen+1); // +1 for last generation to appear

    cout << "\nСимуляция завершена!\n";
    cout << "Вы можете продолжить симуляцию или что то изменить в ней через меню\n";
}

void GameOfLife::Greetings() // Greeting message
{
    cout << "|====|====|Игра Жизнь|====|====|\n";
    cout << "Разработчик: Terrakllee\n";
    cout << "Версия: " << VERSION << "\n\n";
}

void GameOfLife::Play() // Main function to play a game
{
    Greetings();
    PrintGrid();
    UI::MainMenu(*this);
}

void GameOfLife::InitGrid()
{
    Grid = new Cell *[rows];
    for (int i = 0; i < rows; i++)
    {
        Grid[i] = new Cell[cols];
    }
}

void GameOfLife::DeleteGrid()
{
    ClearGrid();
    for (int i = 0; i < rows; i++)
    {
        delete[] Grid[i]; 
    }
    delete[] Grid;
    Grid = nullptr;
}

//Constructor

GameOfLife::GameOfLife()
{
    Grid = new Cell *[rows];
    for (int i = 0; i < rows; i++)
    {
        Grid[i] = new Cell[cols];
    }
}

//Destructor

GameOfLife::~GameOfLife()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] Grid[i]; 
    }
    delete[] Grid;
    Grid = nullptr;
}

// int main()
// {
//     setlocale(LC_ALL, "ru_RU.UTF-8");

// #ifdef _WIN32
//     SetConsoleCP(CP_UTF8);
//     SetConsoleOutputCP(CP_UTF8);

//     HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //Grok AI
//     DWORD dwMode = 0;
//     if (GetConsoleMode(hOut, &dwMode))
//     {
//         dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
//         SetConsoleMode(hOut, dwMode);
//     }
// #endif

//     ios::sync_with_stdio(false); //Grok AI made for faster console frame
//     cout.setf(ios::unitbuf); //Grok AI
    
//     GameOfLife gameOfLife;
//     gameOfLife.Play();
    
//     return 0;
// }