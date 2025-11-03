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
#include <string>

#include "engine.h"
#include "patterns.h"
#include "ui.h"
#include "settings.h"

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

void GameOfLife::RawPrintGrid()
{
    std::cout << "\n";
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (Grid[i][j].GetIsAlive() == true)
            {
                std::cout << "##";
            }
            else if (Grid[i][j].GetIsAlive() == false)
            {
                std::cout << "..";
            }
        }
        std::cout << "\n";
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
            frame += "x+";
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
            if ((j % 10) == 0)
            {
                ((frame += " ") += numbericCols++) += " ";
            }
            else
            {
                ((frame += " ") += ('0' + (j % 10))) += " ";
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
                (frame += ('0' + (j % 10))) += " ";
            }
        }
    }
    else if (IsLeftEdge(j))
    {
        if (gridView == true)
        {
            if ((i % 10) == 0)
            {
                (frame += " ") += numbericRows;
            }
            else
            {
                (frame += " ") += ('0' + (i % 10));
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
                frame += ('0' + (i % 10));
            }
        }
    }
    else if (IsDownEdge(i))
    {
        if (gridView == true)
        {
            if ((j % 10) == 0)
            {
                ((frame += " ") += numbericCols++) += " ";
            }
            else
            {
                ((frame += " ") += ('0' + (j % 10))) += " ";
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
                (frame += ('0' + (j % 10))) += " ";
            }
        }
    }
    else if (IsRightEdge(j))
    {
        if (gridView == true)
        {
            if ((i % 10) == 0)
            {
                (frame += " ") += numbericRows++;
            }
            else
            {
                (frame += " ") += ('0' + (i % 10));
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
                frame += ('0' + (i % 10));
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

void GameOfLife::ClearScreen()
{
    if (!frameHistory)
    {
        #ifdef _WIN32
        system("cls");
        #endif
    }
    std::cout << "\033[2J\033[1;1H" << std::flush;
}

void GameOfLife::PrintGrid()
{
    ClearScreen(); //Grok AI
    frame.clear(); //Grok AI
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

    std::cout << frame << std::flush; //Grok AI
}

void GameOfLife::CheckNeighbours()
{
    for (int i = 1; i < (rows-1); i++)
    {
        for (int j = 1; j < (cols-1); j++)
        {
            // CHECKS IF NEIGHBOURING CELL IS ALIVE 
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
    std::cout << "\nОбъект \""<<name<<"\" заспавнился успешно!\n";
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
        std::cout << "\nОбъекта с таким ID не существует!\n";
        break;
    }
}

void GameOfLife::SummonPattern(Pattern &pattern)
{
    if (CheckIfPatternFits(pattern))
    {
        coordColibrX = pattern.GetSizeX() / 2; //fixes user coordinates cell placement X Half size of a pattern to paste (center)
        coordColibrY = pattern.GetSizeY() / 2; //fixes user coordinates cell placement Y Half size of a pattern to paste (center)

        cMX = ((actualGridSizeCols / 2)-coordColibrX);
        cMY = ((actualGridSizeRows / 2)-coordColibrY); 

        CreatePatternByID(pattern.GetPatternID());
        pattern.MessageSummonSuccess();
        // PrintGrid();  // UNDONE
        // MovePattern();
    }
    else
    {
        std::cout << "\nНе удалось заспавнить объект \""<<pattern.GetName()<<"\", недостаточно места (Требуется " << pattern.GetSizeX() << "x" << pattern.GetSizeY() << ", а ваше поле " << GetActualGridSizeCols() << "x" << GetActualGridSizeRows() <<  ")\n";
    }
}

// UNDONE Coming soon...
// void MovePattern()
// {
//     char userMove;
//     bool exitMovingPattern;
//     std::cout << "\nВведите в какую сторону хотите переместить паттерн\n";
//     std::cout << "Если вас устраивает позиция паттерна введите - 'c'\n";
//     std::cout << "Чтобы переместить паттерн вверх, введите - 'u'\n";
//     std::cout << "Чтобы переместить паттерн вниз, введите - 'd'\n";
//     std::cout << "Чтобы переместить паттерн влево, введите - 'l'\n";
//     std::cout << "Чтобы переместить паттерн вправо, введите - 'r'\n";
//     std::cout << "Ввод: ";
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
//             std::cout << "\nНет такого направления!\n";
//             break;
//         }
//     } while (!exitMovingPattern);

// }

// void MovePatternLeft() // UNDONE!!!!
// {
//     int uM; // user chooses for how much to move
//     std::cout << "\nВведите насколько нужно сдвинуть паттерн влево (-x)\n";
//     do
//     {
//         std::cout << "Ввод: ";
//         cin >> uM;

//         if (uM > cMX)
//         {
//             std::cout << "\nЭто край поля, нельзя сдвинуть паттерн левее!\n";
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



int GameOfLife::CountAliveCellsOnGrid()
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

int GameOfLife::CountDeadCellsOnGrid()
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

int GameOfLife::HowMuchFreeSpaceIsLeft()
{
    return (actualGridSizeRows * actualGridSizeCols) - CountAliveCellsOnGrid();
}

// Clear specific area? UNDONE Coming soon...
// void ClearArea(int x, int y) 
// {

// }

void GameOfLife::ClearGrid()
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

void GameOfLife::CellPhysics()
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

void GameOfLife::InitCell(int x, int y, bool alive)
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

void GameOfLife::AliveRandomCell()
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

    // std::cout << "\nCell generated(x=" << randomX << ";y=" << randomY << ")"; //DEBUG

}

void GameOfLife::Play()
{
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

GameOfLife::GameOfLife()
{
    Grid = new Cell *[rows];
    for (int i = 0; i < rows; i++)
    {
        Grid[i] = new Cell[cols];
    }
}

GameOfLife::~GameOfLife()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] Grid[i]; 
    }
    delete[] Grid;
    Grid = nullptr;
}
