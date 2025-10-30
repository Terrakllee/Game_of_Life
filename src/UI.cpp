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
#include "ui.h"
#include "settings.h"
#include "main_menu.h"

namespace UI
{
    void MainMenu(GameOfLife& g)
    {
        bool exit = false;
        char menu;
        do
        {
            std::cout << "\n##~~~~~~~~~~~###~~~~~~~~Меню~~~~~~~~###~~~~~~~~~~~~##\n";
            std::cout << "Введите 'a' для добавления клетки\n";
            std::cout << "Введите 'p' для запуска\n";
            std::cout << "Введите 'c' для появления определенной конструкции\n";
            std::cout << "Введите 'r' для появления случайного паттерна клеток\n";
            std::cout << "Введите 'v' для отображения поля\n";
            std::cout << "Введите 'k' для удаления клетки\n";
            std::cout << "Введите 'd' для очистки поля\n";
            std::cout << "Введите 's' для настроек\n";
            std::cout << "Введите 'i' для большей информации по игре\n";
            std::cout << "Введите 'q' для выхода\n";
            std::cout << "Ввод: ";
            std::cin >> menu;

            switch (menu)
            {
            case 'a':
                main_menu::UserAddCell(g);
                g.PrintGrid();
                break;
            case 'p':
                main_menu::Launch(g);
                break;
            case 'c':
                main_menu::SummonConstructionMenu(g);
                g.PrintGrid();
                break;
            case 'r':
                main_menu::RandomizeManyCellsBySeed(g);
                g.PrintGrid();
                break;
            case 'v':
                g.PrintGrid();
                break;
            case 'k':
                main_menu::UserKillCell(g);
                g.PrintGrid();
                break;
            case 'd':
                g.ClearGrid();
                g.PrintGrid();
                break;
            case '~':
                DebugMenu(g);
                break;
            case 's':
                Settings(g);
                break;
            case 'i':
                Info();
                break;
            case '/':
                std::cout << "\nZezamade, это ты? :D\n";
                break;
            case 'q':
                exit = true;
                break;
            
            default:
                std::cout << "\nНет такого пункта меню '" << menu << "'\n";
                break;
            }
            
        } while (!exit);

    }

    void Settings(GameOfLife& g)
    {
        char userSettings;
        bool exitSettings = false;

        do
        {
            std::cout << "\n~~()~~()~~()~~~Настройки~~~()~~()~~()~~\n";
            std::cout << "Введите 's' для изменения размера поля\n";
            std::cout << "Введите 't' для изменения скорости игры\n";
            std::cout << "Введите 'b' для изменения фона\n";
            std::cout << "Введите 'c' для изменения оконтовки\n";
            std::cout << "Введите 'r' для изменения сида\n";
            std::cout << "Введите 'f' для включения/отключения историю кадров\n";
            std::cout << "Введите 'q' для выхода из настроек\n";
            std::cout << "Ввод: ";

            std::cin >> userSettings;

            switch (userSettings)
            {
            case 's':
                settings::ChangeGridSize(g);
                g.PrintGrid();
                break;
            case 't':
                settings::SetGameSpeed(g);
                break;
            case 'b':
                settings::ChooseBackground(g);
                g.PrintGrid();
                break;
            case 'c':
                settings::ChangeCage(g);
                g.PrintGrid();
                break;
            case 'r':
                settings::ChangeSeed(g);
                break;
            case 'f':
                if (g.GetFrameHistory())
                {
                    g.SetFrameHistory(false);
                    std::cout << "История кадров отключена!\n";
                }
                else
                {
                    g.SetFrameHistory(true);
                    std::cout << "История кадров включена!\n";
                }
                break;
            case 'q':
                exitSettings = true;
                break;
            
            default:
                std::cout << "\nНет такого пункта настроек '" << userSettings << "'\n";
                break;
            }
        } while (!exitSettings);
    }

    void Info()
    {
        std::cout << "\n?.?.?.?...Информация по игре...?.?.?.?.?\n";

        std::cout << "Это игра где есть поле и клетки, у клеток есть только 2 состояния\n";
        std::cout << "Либо живые, либо мертвые, а цель игрока просто наблюдать за сложными и красивыми паттернами развития клеток\n";

        std::cout << "\nПо сути у клетки есть только 4 правила";
        std::cout << "\n *1 Если у клетки больше 3 соседей, то она погибает от перенаселения";
        std::cout << "\n *2 Если у клетки меньше 2 соседей, то она погибает из-за вымирания";
        std::cout << "\n *3 Если у клетки 2 или 3 соседа, то она продолжает жить до следующей генерации";
        std::cout << "\n *4 Любая мертвая клетка, у которой есть 3 соседа, оживает, из-за репродукции\n";

        std::cout << "\nВопрос-Ответ";
        std::cout << "\n - Что обозначают буквы на шкале координат?";
        std::cout << "\n > Буквы на шкале координат означают десятки, тоесть, A = 10, и цифры после A будут складываться с A (т.е.10)";
        std::cout << "\n > И например \"A 1 2 3 \" означает по сути \"10 11 12 13\"";
        std::cout << "\n - Для чего это было сделано и почему нельзя было использовать обычные цифры?";
        std::cout << "\n > Это было сделанно специально, потому что иначе, десятки занимали бы 2 символа, и все поле бы съезжало\n";

        std::cout << "\nРекомендации по настройкам\n";
        std::cout << "\nЛучше всего ставить время на 100-150 миллисекунд, и точно не следет ставить 2000 или 3000, так как это очень долго";
        std::cout << "\nЕсли поставить больше половины клеток на карту, то тогда они все очень быстро вымрут и ничего крутого не выйдет";
        std::cout << "\nТак что рекомундую ставить примерно половину или чуть меньше половины клеток на поле";
        std::cout << "\nТак же рекомендую использовать другие виды фона, особенно когда нужно ставить клетки вручную";
        std::cout << "\nНекоторые конструкции могут некорректно спавниться :(\n";
    }

    void DebugMenu(GameOfLife& g)
    {
        char user;
        std::cout << "\n~~$$~$~$$~~Debug Menu~~$$~$~$$~~\n";
        std::cout << "Press 'p' for calling method RawPrintGrid()\n";
        std::cout << "Press 'i' for Debug Preset\n";
        std::cout << "Enter: ";
        std::cin >> user;
        
        switch (user)
        {
        case 'p':
            g.RawPrintGrid();
            break;
        case 'i':
            // showCoords = true; //bugged
            // showCage = false;

            g.SetBgCharChoose(5);
            g.SetBgChar(' ');
            g.SetTickTime(100);
            g.PrintGrid();
            for (int i = 0; i < ((g.GetRows()*g.GetCols()) / 3); i++)
            {
                g.AliveRandomCell(); 
            }
            g.PrintGrid();
            main_menu::Launch(g);
        default:
            break;
        }
    }
}