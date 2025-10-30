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
#include "engine.h"
#include "settings.h"

using namespace std;

namespace settings
{
    void ChangeGridSize(GameOfLife& g)
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
            else if (changeSizeX > g.GetMAX_COLS())
            {
                cout << "\nВы не можете создать поле на больше чем " << g.GetMAX_COLS() << " ячеек!\n";
            }
        } while (changeSizeX < 1 || changeSizeX > g.GetMAX_COLS());

        do
        {
            cout << "Введите размер по шкале Y\n";
            cout << "Ввод: ";
            cin >> changeSizeY;

            if (changeSizeY < 1)
            {
                cout << "\nВы не можете создать поле на отрицательное количество ячеек!\n";
            }
            else if (changeSizeY > g.GetMAX_ROWS())
            {
                cout << "\nВы не можете создать поле на больше чем " << g.GetMAX_ROWS() << " ячеек!\n";
            }
        } while (changeSizeY < 1 || changeSizeY > g.GetMAX_ROWS());

        cout << "\nВы действительно хотите изменить размер с " << g.GetActualGridSizeCols() << "x" << g.GetActualGridSizeRows() << " на " << changeSizeX << "x" << changeSizeY << " ?\n";
        cout << "Ввод: ";
        cin >> userValidation;

        g.SetActualGridSizeCols(changeSizeX);
        g.SetActualGridSizeRows(changeSizeY);

        changeSizeX+=2;
        changeSizeY+=2;
        

        if (userValidation == 1)
        {
            g.DeleteGrid();

            g.SetCols(changeSizeX);
            g.SetRows(changeSizeY);
            g.InitGrid();
        }
    }

    void SetGameSpeed(GameOfLife& g) // Sets game speed int milliseconds
    {
        int tempTickTime;
        cout << "\nСейчас скорость = ";
        g.GetTickTime();
        cout << "\nВведите время каждого такта игры (В миллисекундах)\n";
        cout << "Ввод: ";

        do
        {
            cin >> tempTickTime;
            if (tempTickTime < 1)
            {
                cout << "\nСлишком короткий интервал между тактами!\n";
                cout << "Введите больше времени\n";
            }
            
        } while (tempTickTime < 1);
        g.SetTickTime(tempTickTime);
    }

    void ChooseBackground(GameOfLife& g) // Menu to change BG of grid
    {
        short tempBgCharChoose;
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
            cin >> tempBgCharChoose;
        } while (tempBgCharChoose < 1 || tempBgCharChoose > 20);

        g.SetBgCharChoose(tempBgCharChoose);

        switch (tempBgCharChoose)
        {
        case 1:
            g.SetBgChar('.');
            break;
        case 2:
            g.SetBgChar(':');
            break;
        case 3:
            g.SetBgChar('|');
            break;
        case 4:
            g.SetBgChar('_');
            break;
        case 5:
            g.SetBgChar(' ');
            break;
        
        default:
            break;
        }

        cout << "\nВыбран символ: '";
        if (tempBgCharChoose < 6)
        {
            g.GetBgChar();
            cout << "'\n";
        }

        switch (tempBgCharChoose)
        {
        case 6:
            cout << "░'\n";
            g.SetGridView(false);
            break;
        case 7:
            cout << "█'\n";
            g.SetGridView(false);
            break;
        case 8:
            cout << "▓'\n";
            g.SetGridView(false);
            break;
        case 9:
            cout << "▒'\n";
            g.SetGridView(false);
            break;
        case 10:
            cout << "䷀'\n";
            g.SetGridView(false);
            break;
        case 11:
            cout << "𝌆'\n";
            g.SetGridView(false);
            break;
        case 12:
            cout << "⣿'\n";
            g.SetGridView(false);
            break;
        case 13:
            cout << "⠐'\n";
            g.SetGridView(false);
            break;
        case 14:
            cout << "∙'\n";
            g.SetGridView(false);
            break;
        case 15:
            cout << "▏'\n";
            g.SetGridView(false);
            break;
        case 16:
            cout << "╲'\n";
            g.SetGridView(false);
            break;
        case 17:
            cout << "╱'\n";
            g.SetGridView(false);
            break;
        case 18:
            cout << "─'\n";
            g.SetGridView(false);
            break;
        case 19:
            cout << "Сетка'\n";
            g.SetGridView(true);
            break;
        
        default:
            break;
        }
    }

    void ChangeCage(GameOfLife& g) //Changes cage design from coordinates to borders, or opposite
    {
        short user = 0;
        cout << "\n&&&&&& Выбор оконтовки &&&&&&\n";
        cout << "Введите 1 если хотите увидеть оконтовку и убрать координаты, и 0 если наоборот\n";
        cout << "Ввод: ";
        cin >> user;

        if (user == 1)
        {
            g.SetShowCage(true);
            g.SetShowCoords(false);
        }
        else
        {
            g.SetShowCage(false);
            g.SetShowCoords(true);
        }
    }

    void ChangeSeed(GameOfLife& g)
    {
        unsigned int seed;
        cout << "\nВведите сид, положительное, целое число (Случайное число для генерации одного и того же паттерна, по тому же сиду)\n";
        cout << "Ввод: ";
        cin >> seed;
        cout << "Ваш сид: " << seed;
        g.SetUserChangedSeed(true);
        srand(seed);
    }
}