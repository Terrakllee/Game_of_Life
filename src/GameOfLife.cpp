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

#include "GameOfLife.h"
#include "patterns.h"

using namespace std;

static const string VERSION = "1.0";

//Getters

int GameOfLife::GCMX()
{
    return cMX;
}

int GameOfLife::GCMY()
{
    return cMY;
}

int GameOfLife::GetActualGridSizeRows()
{
    return actualGridSizeRows;
}
int GameOfLife::GetActualGridSizeCols()
{
    return actualGridSizeCols;
}

bool GameOfLife::IsGridSizeXEven()
{
    return actualGridSizeCols % 2 == 0;
}

bool GameOfLife::IsGridSizeYEven()
{
    return actualGridSizeRows % 2 == 1;
}

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
        // patterns::CreateBlinker(*this);
        break;
    // case 2:
    //     CreateToad();
    //     break;
    // case 3:
    //     CreateBeacon();
    //     break;
    // case 4:
    //     CreatePulsar();
    //     break;
    // case 5:
    //     CreatePentadecathlon();
    //     break;
    // case 6:
    //     CreateGlider();
    //     break;
    // case 7:
    //     CreateTheRPentomino();
    //     break;
    // case 8:
    //     CreateDiehard();
    //     break;
    // case 9:
    //     CreateAcorn();
    //     break;
    // case 10:
    //     CreateDiagonalNuke();
    //     break;
    // case 11:
    //     CreateCompactNuke();
    //     break;
    // case 12:
    //     CreateNukeLine();
    //     break;
    // case 13:
    //     CreateAmogus();
    //     break;
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
        // case 't':
        //     {
        //         Pattern toad(5, 5, "Toad", 2);
        //         SummonPattern(toad);
        //     }
        //     exitConstructionMenu = true;
        //     break;
        // case 'o':
        //     {
        //         Pattern beacon(4, 4, "Beacon", 3);
        //         SummonPattern(beacon);
        //     }
        //     exitConstructionMenu = true;
        //     break;
        // case 'p':
        //     {
        //         Pattern pulsar(17, 17, "Pulsar", 4);
        //         SummonPattern(pulsar);
        //     }
        //     exitConstructionMenu = true;
        //     break;
        // case 'e':
        //     {
        //         Pattern pentadecathlon(11, 18, "Pentadecathlon", 5);
        //         SummonPattern(pentadecathlon);
        //     }
        //     exitConstructionMenu = true;
        //     break;
        // case 'g':
        //     {
        //         Pattern glider(5, 5, "Glider", 6);
        //         SummonPattern(glider);
        //     }
        //     exitConstructionMenu = true;
        //     break;
        // case 'r':
        //     {
        //         Pattern theRPentomino(5, 5, "The R-Pentomino", 7);
        //         SummonPattern(theRPentomino);
        //     }
        //     exitConstructionMenu = true;
        //     break;
        // case 'd':
        //     {
        //         Pattern diehard(10, 5, "Diehard", 8);
        //         SummonPattern(diehard);
        //     }
        //     exitConstructionMenu = true;
        //     break;
        // case 'a':
        //     {
        //         Pattern acorn(9, 5, "Acorn", 9);
        //         SummonPattern(acorn);
        //     }
        //     exitConstructionMenu = true;
        //     break;
        // case 'l':
        //     {
        //         Pattern diagonalNuke(10, 8, "Diagonal Nuke", 10);
        //         SummonPattern(diagonalNuke);
        //     }
        //     exitConstructionMenu = true;
        //     break;
        // case 'c':
        //     {
        //         Pattern compactNuke(5, 5, "Compact Nuke", 11);
        //         SummonPattern(compactNuke);
        //     }
        //     exitConstructionMenu = true;
        //     break;
        // case 'n':
        //     {
        //         Pattern nukeLine(41, 3, "Nuke Line", 12);
        //         SummonPattern(nukeLine);
        //     }
        //     exitConstructionMenu = true;
        //     break;
        // case 's':
        //     {
        //         Pattern amogus(6, 7, "Amogus", 13);
        //         SummonPattern(amogus);
        //     }
        //     exitConstructionMenu = true;
        //     break;
        case 'q':
            exitConstructionMenu = true;
            break;
        
        
        default:
            cout << "\nТакого объекта не существует!\n";
            break;
        }
    } while (!exitConstructionMenu);
}

////////////////////////////////////////////////////////// CREATE OSCILLATORS

// void GameOfLife::CreateBlinker() //Blinker 3x3
// {
//     InitCell(2+cMX, 1+cMY, 1);
//     InitCell(2+cMX, 2+cMY, 1);
//     InitCell(2+cMX, 3+cMY, 1);
// }

/*

void CreateToad() //Toad 4x4
{
    InitCell(3+cMX, 1+cMY, 1);
    InitCell(1+cMX, 2+cMY, 1);
    InitCell(4+cMX, 2+cMY, 1);
    InitCell(1+cMX, 3+cMY, 1);
    InitCell(4+cMX, 3+cMY, 1);
    InitCell(2+cMX, 4+cMY, 1);
}

void CreateBeacon() //Beacon 4x4
{
    InitCell(1+cMX, 1+cMY, 1);
    InitCell(2+cMX, 1+cMY, 1);
    InitCell(1+cMX, 2+cMY, 1);
    InitCell(4+cMX, 3+cMY, 1);
    InitCell(3+cMX, 4+cMY, 1);
    InitCell(4+cMX, 4+cMY, 1);
}

void CreatePulsar() //Pulsar 17x17
{
    InitCell(5+cMX, 3+cMY, 1);
    InitCell(6+cMX, 3+cMY, 1);
    InitCell(7+cMX, 3+cMY, 1);
    InitCell(11+cMX, 3+cMY, 1);
    InitCell(12+cMX, 3+cMY, 1);
    InitCell(13+cMX, 3+cMY, 1);
    InitCell(3+cMX, 5+cMY, 1);
    InitCell(8+cMX, 5+cMY, 1);
    InitCell(10+cMX, 5+cMY, 1);
    InitCell(15+cMX, 5+cMY, 1);
    InitCell(3+cMX, 6+cMY, 1);
    InitCell(8+cMX, 6+cMY, 1);
    InitCell(10+cMX, 6+cMY, 1);
    InitCell(15+cMX, 6+cMY, 1);
    InitCell(3+cMX, 7+cMY, 1);
    InitCell(8+cMX, 7+cMY, 1);
    InitCell(10+cMX, 7+cMY, 1);
    InitCell(15+cMX, 7+cMY, 1);
    InitCell(5+cMX, 8+cMY, 1);
    InitCell(6+cMX, 8+cMY, 1);
    InitCell(7+cMX, 8+cMY, 1);
    InitCell(11+cMX, 8+cMY, 1);
    InitCell(12+cMX, 8+cMY, 1);
    InitCell(13+cMX, 8+cMY, 1);
    InitCell(5+cMX, 10+cMY, 1);
    InitCell(6+cMX, 10+cMY, 1);
    InitCell(7+cMX, 10+cMY, 1);
    InitCell(11+cMX, 10+cMY, 1);
    InitCell(12+cMX, 10+cMY, 1);
    InitCell(13+cMX, 10+cMY, 1);
    InitCell(3+cMX, 11+cMY, 1);
    InitCell(8+cMX, 11+cMY, 1);
    InitCell(10+cMX, 11+cMY, 1);
    InitCell(15+cMX, 11+cMY, 1);
    InitCell(3+cMX, 12+cMY, 1);
    InitCell(8+cMX, 12+cMY, 1);
    InitCell(10+cMX, 12+cMY, 1);
    InitCell(15+cMX, 12+cMY, 1);
    InitCell(3+cMX, 13+cMY, 1);
    InitCell(8+cMX, 13+cMY, 1);
    InitCell(10+cMX, 13+cMY, 1);
    InitCell(15+cMX, 13+cMY, 1);
    InitCell(5+cMX, 15+cMY, 1);
    InitCell(6+cMX, 15+cMY, 1);
    InitCell(7+cMX, 15+cMY, 1);
    InitCell(11+cMX, 15+cMY, 1);
    InitCell(12+cMX, 15+cMY, 1);
    InitCell(13+cMX, 15+cMY, 1);
}

void CreatePentadecathlon() //Pentadecathlon 11x18
{
    InitCell(5+cMX, 6+cMY, 1);
    InitCell(6+cMX, 6+cMY, 1);
    InitCell(7+cMX, 6+cMY, 1);
    InitCell(5+cMX, 7+cMY, 1);
    InitCell(7+cMX, 7+cMY, 1);
    InitCell(5+cMX, 8+cMY, 1);
    InitCell(6+cMX, 8+cMY, 1);
    InitCell(7+cMX, 8+cMY, 1);
    InitCell(5+cMX, 9+cMY, 1);
    InitCell(6+cMX, 9+cMY, 1);
    InitCell(7+cMX, 9+cMY, 1);
    InitCell(5+cMX, 10+cMY, 1);
    InitCell(6+cMX, 10+cMY, 1);
    InitCell(7+cMX, 10+cMY, 1);
    InitCell(5+cMX, 11+cMY, 1);
    InitCell(6+cMX, 11+cMY, 1);
    InitCell(7+cMX, 11+cMY, 1);
    InitCell(5+cMX, 12+cMY, 1);
    InitCell(7+cMX, 12+cMY, 1);
    InitCell(5+cMX, 13+cMY, 1);
    InitCell(6+cMX, 13+cMY, 1);
    InitCell(7+cMX, 13+cMY, 1);
}

////////////////////////////////////////////////////////////// CREATE SPACESHIPS

void CreateGlider() //Glider 5x5
{
    InitCell(4+cMX, 2+cMY, 1);
    InitCell(3+cMX, 3+cMY, 1);
    InitCell(2+cMX, 4+cMY, 1);
    InitCell(3+cMX, 4+cMY, 1);
    InitCell(4+cMX, 4+cMY, 1);
}

//////////////////////////////////////////////////// CREATE METHUSELAHS

void CreateTheRPentomino() // The R-pentomino 5x5
{
    InitCell(3+cMX, 2+cMY, 1);
    InitCell(2+cMX, 3+cMY, 1);
    InitCell(3+cMX, 3+cMY, 1);
    InitCell(4+cMX, 3+cMY, 1);
    InitCell(4+cMX, 4+cMY, 1);
}

void CreateDiehard() // Diehard 10x5
{
    InitCell(8+cMX, 2+cMY, 1);
    InitCell(2+cMX, 3+cMY, 1);
    InitCell(3+cMX, 3+cMY, 1);
    InitCell(3+cMX, 4+cMY, 1);
    InitCell(7+cMX, 4+cMY, 1);
    InitCell(8+cMX, 4+cMY, 1);
    InitCell(9+cMX, 4+cMY, 1);
}

void CreateAcorn() // Acorn 9x5
{
    InitCell(3+cMX, 2+cMY, 1);
    InitCell(5+cMX, 3+cMY, 1);
    InitCell(2+cMX, 4+cMY, 1);
    InitCell(3+cMX, 4+cMY, 1);
    InitCell(6+cMX, 4+cMY, 1);
    InitCell(7+cMX, 4+cMY, 1);
    InitCell(8+cMX, 4+cMY, 1);
}

//////////////////////////////// CREATE NUKES

void CreateDiagonalNuke() //Diagonal Nuke 10x8
{
    InitCell(8+cMX, 2+cMY, 1);
    InitCell(6+cMX, 3+cMY, 1);
    InitCell(8+cMX, 3+cMY, 1);
    InitCell(9+cMX, 3+cMY, 1);
    InitCell(6+cMX, 4+cMY, 1);
    InitCell(8+cMX, 4+cMY, 1);
    InitCell(6+cMX, 5+cMY, 1);
    InitCell(4+cMX, 6+cMY, 1);
    InitCell(2+cMX, 7+cMY, 1);
    InitCell(4+cMX, 7+cMY, 1);
}

void CreateCompactNuke() //Compact Nuke 5x5
{
    InitCell(1+cMX, 1+cMY, 1);
    InitCell(2+cMX, 1+cMY, 1);
    InitCell(3+cMX, 1+cMY, 1);
    InitCell(5+cMX, 1+cMY, 1);
    InitCell(1+cMX, 2+cMY, 1);
    InitCell(4+cMX, 3+cMY, 1);
    InitCell(5+cMX, 3+cMY, 1);
    InitCell(2+cMX, 4+cMY, 1);
    InitCell(3+cMX, 4+cMY, 1);
    InitCell(5+cMX, 4+cMY, 1);
    InitCell(1+cMX, 5+cMY, 1);
    InitCell(3+cMX, 5+cMY, 1);
    InitCell(5+cMX, 5+cMY, 1);
}

void CreateNukeLine() //Nuke Line 41x3
{
    InitCell(2+cMX, 2+cMY, 1);
    InitCell(3+cMX, 2+cMY, 1);
    InitCell(4+cMX, 2+cMY, 1);
    InitCell(5+cMX, 2+cMY, 1);
    InitCell(6+cMX, 2+cMY, 1);
    InitCell(7+cMX, 2+cMY, 1);
    InitCell(8+cMX, 2+cMY, 1);
    InitCell(9+cMX, 2+cMY, 1);
    InitCell(11+cMX, 2+cMY, 1);
    InitCell(12+cMX, 2+cMY, 1);
    InitCell(13+cMX, 2+cMY, 1);
    InitCell(14+cMX, 2+cMY, 1);
    InitCell(15+cMX, 2+cMY, 1);
    InitCell(19+cMX, 2+cMY, 1);
    InitCell(20+cMX, 2+cMY, 1);
    InitCell(21+cMX, 2+cMY, 1);
    InitCell(28+cMX, 2+cMY, 1);
    InitCell(29+cMX, 2+cMY, 1);
    InitCell(30+cMX, 2+cMY, 1);
    InitCell(31+cMX, 2+cMY, 1);
    InitCell(32+cMX, 2+cMY, 1);
    InitCell(33+cMX, 2+cMY, 1);
    InitCell(34+cMX, 2+cMY, 1);
    InitCell(36+cMX, 2+cMY, 1);
    InitCell(37+cMX, 2+cMY, 1);
    InitCell(38+cMX, 2+cMY, 1);
    InitCell(39+cMX, 2+cMY, 1);
    InitCell(40+cMX, 2+cMY, 1);
}

/////////////////Custom user made patterns

void CreateAmogus() //Amogus 6x7
{
    InitCell(2+cMX, 2+cMY, 0);
    InitCell(3+cMX, 2+cMY, 1);
    InitCell(3+cMX, 2+cMY, 1);
    InitCell(4+cMX, 2+cMY, 1);
    InitCell(5+cMX, 2+cMY, 1);
    InitCell(2+cMX, 3+cMY, 1);
    InitCell(3+cMX, 3+cMY, 1);
    InitCell(4+cMX, 3+cMY, 0);
    InitCell(5+cMX, 3+cMY, 0);
    InitCell(2+cMX, 4+cMY, 1);
    InitCell(3+cMX, 4+cMY, 1);
    InitCell(4+cMX, 4+cMY, 1);
    InitCell(5+cMX, 4+cMY, 1);
    InitCell(2+cMX, 5+cMY, 1);
    InitCell(3+cMX, 5+cMY, 1);
    InitCell(4+cMX, 5+cMY, 1);
    InitCell(5+cMX, 5+cMY, 1);
    InitCell(2+cMX, 6+cMY, 0);
    InitCell(3+cMX, 6+cMY, 1);
    InitCell(4+cMX, 6+cMY, 0);
    InitCell(5+cMX, 6+cMY, 1);
}

*/

void GameOfLife::ChooseBackground() // Menu to change BG of grid
{
    cout << "\nВыберите символ для использования в роли фона, для этого введите цифру символа\n";
    cout << " *1 - '.'\t";
    cout << " *2 - ':'\t";
    cout << " *3 - '|'\t";
    cout << " *4 - '_'\t\n";
    cout << " *5 - ' '\t";
    cout << " *6 - '░'\t";
    cout << " *7 - '█'\t";
    cout << " *8 - '▓'\t\n";
    cout << " *9 - '▒'\t";
    cout << " *10 - '䷀'\t";
    cout << " *11 - '𝌆'\t";
    cout << " *12 - '⣿'\t\n";
    cout << " *13 - '⠐'\t";
    cout << " *14 - '∙'\t";
    cout << " *15 - '▏'\t";
    cout << " *16 - '╲'\t\n";
    cout << " *17 - '╱'\t";
    cout << " *18 - '─'\t\n\n";
    cout << " *19 - Сетка \n\n";
    cout << "Ввод: ";
    do
    {
        cin >> bgCharChoose;
    } while (bgCharChoose < 1 || bgCharChoose > 20);

    switch (bgCharChoose)
    {
    case 1:
        bgChar = '.';
        break;
    case 2:
        bgChar = ':';
        break;
    case 3:
        bgChar = '|';
        break;
    case 4:
        bgChar = '_';
        break;
    case 5:
        bgChar = ' ';
        break;
    
    default:
        break;
    }

    cout << "\nВыбран символ: '";
    if (bgCharChoose < 6)
    {
        cout << bgChar << "'\n";
    }

    switch (bgCharChoose)
    {
    case 6:
        cout << "░'\n";
        gridView = false;
        break;
    case 7:
        cout << "█'\n";
        gridView = false;
        break;
    case 8:
        cout << "▓'\n";
        gridView = false;
        break;
    case 9:
        cout << "▒'\n";
        gridView = false;
        break;
    case 10:
        cout << "䷀'\n";
        gridView = false;
        break;
    case 11:
        cout << "𝌆'\n";
        gridView = false;
        break;
    case 12:
        cout << "⣿'\n";
        gridView = false;
        break;
    case 13:
        cout << "⠐'\n";
        gridView = false;
        break;
    case 14:
        cout << "∙'\n";
        gridView = false;
        break;
    case 15:
        cout << "▏'\n";
        gridView = false;
        break;
    case 16:
        cout << "╲'\n";
        gridView = false;
        break;
    case 17:
        cout << "╱'\n";
        gridView = false;
        break;
    case 18:
        cout << "─'\n";
        gridView = false;
        break;
    case 19:
        cout << "Сетка'\n";
        gridView = true;
        break;
    
    default:
        break;
    }
}

void GameOfLife::SetGameSpeed() // Sets game speed int milliseconds
{
    cout << "\nСейчас скорость = " << tickTime;
    cout << "\nВведите время каждого такта игры (В миллисекундах)\n";
    cout << "Ввод: ";

    do
    {
        cin >> tickTime;
        if (tickTime < 1)
        {
            cout << "\nСлишком короткий интервал между тактами!\n";
            cout << "Введите больше времени\n";
        }
        
    } while (tickTime < 1);
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

void GameOfLife::ChangeSeed()
{
    double seed;
    cout << "\nВведите сид (Случайно число для генерации одного и того же паттерна, по тому же сиду)\n";
    cout << "Ввод: ";
    cin >> seed;
    cout << "Ваш сид: " << seed;
    userChangedSeed = true;
    srand(seed);
    
}

void GameOfLife::RandomizeManyCellsBySeed() // Spawns many random cells using specific user entered seed
{
    int amountOfCellsToCreation;

    if (userChangedSeed == false)
    {
        // srand(time(nullptr));
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

void GameOfLife::ChangeCage() //Changes cage design from coordinates to borders, or opposite
{
    short user = 0;
    cout << "\n&&&&&& Выбор оконтовки &&&&&&\n";
    cout << "Введите 1 если хотите увидеть оконтовку и убрать координаты, и 0 если наоборот\n";
    cout << "Ввод: ";
    cin >> user;

    if (user == 1)
    {
        showCage = 1;
        showCoords = 0;
    }
    else
    {
        showCage = 0;
        showCoords = 1;
    }
}

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

void GameOfLife::ChangeGridSize()
{
    int changeSizeX;
    int changeSizeY;
    bool userValidation;

    cout << "\n--##--##--Редактирование размера поля--##--##--\n";
    
    do
    {
        cout << "Введите размер по шкале X\n";
        cout << "Ввод: ";
        cin >> changeSizeX;

        if (changeSizeX < 1)
        {
            cout << "\nВы не можете создать поле на отрицательное количество ячеек!\n";
        }
        else if (changeSizeX > MAX_COLS)
        {
            cout << "\nВы не можете создать поле на больше чем " << MAX_COLS << " ячеек!\n";
        }
    } while (changeSizeX < 1 || changeSizeX > MAX_COLS);

    do
    {
        cout << "Введите размер по шкале Y\n";
        cout << "Ввод: ";
        cin >> changeSizeY;

        if (changeSizeY < 1)
        {
            cout << "\nВы не можете создать поле на отрицательное количество ячеек!\n";
        }
        else if (changeSizeY > MAX_ROWS)
        {
            cout << "\nВы не можете создать поле на больше чем " << MAX_ROWS << " ячеек!\n";
        }
    } while (changeSizeY < 1 || changeSizeY > MAX_ROWS);

    cout << "\nВы действительно хотите изменить размер с " << actualGridSizeCols << "x" << actualGridSizeRows << " на " << changeSizeX << "x" << changeSizeY << " ?\n";
    cout << "Ввод: ";
    cin >> userValidation;

    actualGridSizeCols = changeSizeX;
    actualGridSizeRows = changeSizeY;

    changeSizeX+=2;
    changeSizeY+=2;
    

    if (userValidation == 1)
    {
        DeleteGrid();

        cols = changeSizeX;
        rows = changeSizeY;

        InitGrid();
    }
}

void GameOfLife::Info()
{
    cout << "\n?.?.?.?...Информация по игре...?.?.?.?.?\n";

    cout << "Это игра где есть поле и клетки, у клеток есть только 2 состояния\n";
    cout << "Либо живые, либо мертвые, а цель игрока просто наблюдать за сложными и красивыми паттернами развития клеток\n";

    cout << "\nПо сути у клетки есть только 4 правила";
    cout << "\n *1 Если у клетки больше 3 соседей, то она погибает от перенаселения";
    cout << "\n *2 Если у клетки меньше 2 соседей, то она погибает из-за вымирания";
    cout << "\n *3 Если у клетки 2 или 3 соседа, то она продолжает жить до следующей генерации";
    cout << "\n *4 Любая мертвая клетка, у которой есть 3 соседа, оживает, из-за репродукции\n";

    cout << "\nВопрос-Ответ";
    cout << "\n - Что обозначают буквы на шкале координат?";
    cout << "\n > Буквы на шкале координат означают десятки, тоесть, A = 10, и цифры после A будут складываться с A (т.е.10)";
    cout << "\n > И например \"A 1 2 3 \" означает по сути \"10 11 12 13\"";
    cout << "\n - Для чего это было сделано и почему нельзя было использовать обычные цифры?";
    cout << "\n > Это было сделанно специально, потому что иначе, десятки занимали бы 2 символа, и все поле бы съезжало\n";

    cout << "\nРекомендации по настройкам\n";
    cout << "\nЛучше всего ставить время на 100-150 миллисекунд, и точно не следет ставить 2000 или 3000, так как это очень долго";
    cout << "\nЕсли поставить больше половины клеток на карту, то тогда они все очень быстро вымрут и ничего крутого не выйдет";
    cout << "\nТак что рекомундую ставить примерно половину или чуть меньше половины клеток на поле";
    cout << "\nТак же рекомендую использовать другие виды фона, особенно когда нужно ставить клетки вручную";
    cout << "\nНекоторые конструкции могут некорректно спавниться :(\n";
}

void GameOfLife::Settings()
{
    char userSettings;
    bool exitSettings = false;

    do
    {
        cout << "\n~~()~~()~~()~~~Настройки~~~()~~()~~()~~\n";
        cout << "Введите 's' для изменения размера поля\n";
        cout << "Введите 't' для изменения скорости игры\n";
        cout << "Введите 'b' для изменения фона\n";
        cout << "Введите 'c' для изменения оконтовки\n";
        cout << "Введите 'r' для изменения сида\n";
        cout << "Введите 'f' для включения/отключения историю кадров\n";
        cout << "Введите 'q' для выхода из настроек\n";
        cout << "Ввод: ";

        cin >> userSettings;

        switch (userSettings)
        {
        case 's':
            ChangeGridSize();
            PrintGrid();
            break;
        case 't':
            SetGameSpeed();
            break;
        case 'b':
            ChooseBackground();
            PrintGrid();
            break;
        case 'c':
            ChangeCage();
            PrintGrid();
            break;
        case 'r':
            ChangeSeed();
            break;
        case 'f':
            if (frameHistory)
            {
                frameHistory = false;
                cout << "История кадров отключена!\n";
            }
            else
            {
                frameHistory = true;
                cout << "История кадров включена!\n";
            }
            break;
        case 'q':
            exitSettings = true;
            break;
        
        default:
            cout << "\nНет такого пункта настроек '" << userSettings << "'\n";
            break;
        }
    } while (!exitSettings);
}

void GameOfLife::MainMenu()
{
    bool exit = false;
    char menu;
    do
    {
        cout << "\n##~~~~~~~~~~~###~~~~~~~~Меню~~~~~~~~###~~~~~~~~~~~~##\n";
        cout << "Введите 'a' для добавления клетки\n";
        cout << "Введите 'p' для запуска\n";
        cout << "Введите 'c' для появления определенной конструкции\n";
        cout << "Введите 'r' для появления случайного паттерна клеток\n";
        cout << "Введите 'v' для отображения поля\n";
        cout << "Введите 'k' для удаления клетки\n";
        cout << "Введите 'd' для очистки поля\n";
        cout << "Введите 's' для настроек\n";
        cout << "Введите 'i' для большей информации по игре\n";
        cout << "Введите 'q' для выхода\n";
        cout << "Ввод: ";
        cin >> menu;

        switch (menu)
        {
        case 'a':
            UserAddCell();
            PrintGrid();
            break;
        case 'p':
            Launch();
            break;
        case 'c':
            SummonConstructionMenu();
            PrintGrid();
            break;
        case 'r':
            RandomizeManyCellsBySeed();
            PrintGrid();
            break;
        case 'v':
            PrintGrid();
            break;
        case 'k':
            UserKillCell();
            PrintGrid();
            break;
        case 'd':
            ClearGrid();
            PrintGrid();
            break;
        case '~':
            DebugMenu();
            break;
        case 's':
            Settings();
            break;
        case 'i':
            Info();
            break;
        case 'q':
            exit = true;
            break;
        
        default:
            cout << "\nНет такого пункта меню '" << menu << "'\n";
            break;
        }
        
    } while (!exit);

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
    MainMenu();
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

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //Grok AI
    DWORD dwMode = 0;
    if (GetConsoleMode(hOut, &dwMode))
    {
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    }
#endif

    ios::sync_with_stdio(false); //Grok AI made for faster console frame
    cout.setf(ios::unitbuf); //Grok AI

    patterns::Test();
    
    GameOfLife gameOfLife;
    gameOfLife.Play();
    
    return 0;
}