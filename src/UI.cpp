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
#include "UI.h"
#include "settings.h"

using namespace std;

namespace UI
{
    void MainMenu(GameOfLife& g)
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
                g.UserAddCell();
                g.PrintGrid();
                break;
            case 'p':
                g.Launch();
                break;
            case 'c':
                g.SummonConstructionMenu();
                g.PrintGrid();
                break;
            case 'r':
                g.RandomizeManyCellsBySeed();
                g.PrintGrid();
                break;
            case 'v':
                g.PrintGrid();
                break;
            case 'k':
                g.UserKillCell();
                g.PrintGrid();
                break;
            case 'd':
                g.ClearGrid();
                g.PrintGrid();
                break;
            case '~':
                g.DebugMenu();
                break;
            case 's':
                Settings(g);
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

    void Settings(GameOfLife& g)
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
                    cout << "История кадров отключена!\n";
                }
                else
                {
                    g.SetFrameHistory(true);
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

    void Info()
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
}