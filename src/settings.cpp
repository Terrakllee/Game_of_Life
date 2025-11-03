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

namespace settings
{
    void ChangeGridSize(GameOfLife& g)
    {
        int changeSizeX;
        int changeSizeY;
        char userValidation;

        std::cout << "\n--##--##--Редактирование размера поля--##--##--\n";
        std::cout << "Текущий размер поля " << g.GetActualGridSizeCols() << "x" << g.GetActualGridSizeRows() << "\n";
        std::cout << "Введите размер по шкале X\n";

        while (true)
        {
            std::cout << "Ввод: ";
            if (std::cin >> changeSizeX)
            {
                if (changeSizeX < 1)
                {
                    std::cout << "\nВы не можете создать поле на отрицательное или нулевое количество ячеек!\n";
                }
                else if (changeSizeX > g.GetMAX_COLS())
                {
                    std::cout << "\nВы не можете создать поле на больше чем " << g.GetMAX_COLS() << " ячеек!\n";
                }
                else
                {
                    break;
                }
            }
            else
            {
                std::cout << "Ошибка, введено не число!\n";
            }
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

        std::cout << "Введите размер по шкале Y\n";

        while (true)
        {
            std::cout << "Ввод: ";
            if (std::cin >> changeSizeY)
            {
                if (changeSizeY < 1)
                {
                    std::cout << "\nВы не можете создать поле на отрицательное или нулевое количество ячеек!\n";
                }
                else if (changeSizeY > g.GetMAX_ROWS())
                {
                    std::cout << "\nВы не можете создать поле на больше чем " << g.GetMAX_ROWS() << " ячеек!\n";
                }
                else
                {
                    break;
                }
            }
            else
            {
                std::cout << "Ошибка, введено не число!\n";
            }
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

        std::cout << "\nВы действительно хотите изменить размер с " << g.GetActualGridSizeCols() << "x" << g.GetActualGridSizeRows() << " на " << changeSizeX << "x" << changeSizeY << " ?\n";
        std::cout << "Введите 'Y' если да, и 'N' если нет\n";
        std::cout << "Ввод: ";
        std::cin >> userValidation;

        g.SetActualGridSizeCols(changeSizeX);
        g.SetActualGridSizeRows(changeSizeY);

        changeSizeX+=2;
        changeSizeY+=2;
        
        if (userValidation == 'Y' || userValidation == 'y')
        {
            g.DeleteGrid();
            g.SetCols(changeSizeX);
            g.SetRows(changeSizeY);
            g.InitGrid();
            std::cout << "\nУспешно изменен размер поля на " << g.GetActualGridSizeCols() << "x" << g.GetActualGridSizeRows() << " !\n";
        }
        else
        {
            std::cout << "\nОтменяем изменения...\n";
        }
    }

    void SetGameSpeed(GameOfLife& g)
    {
        int tempTickTime;
        std::cout << "\nСейчас скорость = ";
        g.GetTickTime();
        std::cout << "\nВведите время каждого такта игры (В миллисекундах)\n";

        while (true)
        {
            std::cout << "Ввод: ";
            if (std::cin >> tempTickTime)
            {
                if (tempTickTime < 1)
                {
                    std::cout << "\nСлишком короткий интервал между тактами!\n";
                    std::cout << "Введите больше времени\n";
                }
                else
                {
                    break;
                }
            }
            else
            {
                std::cout << "Ошибка, введено не число!\n";
            }
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        g.SetTickTime(tempTickTime);
    }

    void ChooseBackground(GameOfLife& g)
    {
        short tempBgCharChoose;
        std::cout << "\nВыберите символ для использования в роли фона, для этого введите цифру символа\n";
        std::cout << " 1 - '.'\t";
        std::cout << " 2 - ':'\t";
        std::cout << " 3 - '|'\t";
        std::cout << " 4 - '_'\t\n";
        std::cout << " 5 - ' '\t";
        std::cout << " 6 - '░'\t";
        std::cout << " 7 - '█'\t";
        std::cout << " 8 - '▓'\t\n";
        std::cout << " 9 - '▒'\t";
        std::cout << " 10 - '䷀'\t";
        std::cout << " 11 - '𝌆'\t";
        std::cout << " 12 - '⣿'\t\n";
        std::cout << " 13 - '⠐'\t";
        std::cout << " 14 - '∙'\t";
        std::cout << " 15 - '▏'\t";
        std::cout << " 16 - '╲'\t\n";
        std::cout << " 17 - '╱'\t";
        std::cout << " 18 - '─'\t\n\n";
        std::cout << " 19 - Сетка (Размер поля по x, не более 69, для включения)\n\n";

        while (true)
        {
            std::cout << "Ввод: ";
            if (std::cin >> tempBgCharChoose)
            {
                if (tempBgCharChoose < 1 || tempBgCharChoose > 20)
                {
                    std::cout << "Ошибка, введено слишком малое или слишком большое число!\n";
                }
                else
                {
                    break;
                }
            }
            else
            {
                std::cout << "Ошибка, введено не число!\n";
            }
            std::cin.clear();
            std::cin.ignore(10000, '\n');      
        }

        if (tempBgCharChoose == 19)
        {
            if (g.GetActualGridSizeCols() > g.GetGRID_VIEW_MAX_X())
            {
                std::cout << "Текущий размер поля " << g.GetActualGridSizeCols() << "x" << g.GetActualGridSizeRows() << "\n";
                std::cout << "Необходим размер поля по координате x, не более " << g.GetGRID_VIEW_MAX_X() << "\n";
                std::cout << "Это необходимо для корректного отображения сетки\n";
                std::cout << "Изменить размер поля можно в настройках, попасть в настройки можно через главное меню\n";
                return;
            }
        }
        
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

        std::cout << "\nВыбран символ: '";
        if (tempBgCharChoose < 6)
        {
            g.GetBgChar();
            std::cout << "'\n";
        }

        switch (tempBgCharChoose)
        {
        case 6:
            std::cout << "░'\n";
            g.SetGridView(false);
            break;
        case 7:
            std::cout << "█'\n";
            g.SetGridView(false);
            break;
        case 8:
            std::cout << "▓'\n";
            g.SetGridView(false);
            break;
        case 9:
            std::cout << "▒'\n";
            g.SetGridView(false);
            break;
        case 10:
            std::cout << "䷀'\n";
            g.SetGridView(false);
            break;
        case 11:
            std::cout << "𝌆'\n";
            g.SetGridView(false);
            break;
        case 12:
            std::cout << "⣿'\n";
            g.SetGridView(false);
            break;
        case 13:
            std::cout << "⠐'\n";
            g.SetGridView(false);
            break;
        case 14:
            std::cout << "∙'\n";
            g.SetGridView(false);
            break;
        case 15:
            std::cout << "▏'\n";
            g.SetGridView(false);
            break;
        case 16:
            std::cout << "╲'\n";
            g.SetGridView(false);
            break;
        case 17:
            std::cout << "╱'\n";
            g.SetGridView(false);
            break;
        case 18:
            std::cout << "─'\n";
            g.SetGridView(false);
            break;
        case 19:
            std::cout << "Сетка'\n";
            g.SetGridView(true);
            break;
        
        default:
            break;
        }
    }

    void ChangeCage(GameOfLife& g)
    {
        char user = '0';
        std::cout << "\n&&&&&& Выбор оконтовки &&&&&&\n";
        std::cout << "Введите 1 если хотите увидеть оконтовку и убрать координаты, и 0 если наоборот\n";
        std::cout << "Ввод: ";
        std::cin >> user;

        while (true)
        {
            if (user == '1')
            {
                g.SetShowCage(true);
                g.SetShowCoords(false);
                break;
            }
            else if (user == '0')
            {
                g.SetShowCage(false);
                g.SetShowCoords(true);
                break;
            }
            else
            {
                std::cout << "Нет такого пункта, введите 1 или 0\n";
                continue;
            }
        }
    }

    void ChangeSeed(GameOfLife& g)
    {
        unsigned int seed;
        std::cout << "\nВведите сид, положительное, целое число (Случайное число для генерации одного и того же паттерна, по тому же сиду)\n";

        while (true)
        {
            std::cout << "Ввод: ";
            if (std::cin >> seed)
            {
                break;
            }
            else
            {
                std::cout << "Ошибка, введено не число!\n";
            }
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        
        std::cout << "Ваш сид: " << seed;
        g.SetUserChangedSeed(true);
        srand(seed);
    }
}