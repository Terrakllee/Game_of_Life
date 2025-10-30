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
#include <thread>
#include <string>

static const std::string VERSION = "1.1";

#ifdef _WIN32
#include <windows.h>
#endif

#include "engine.h"

// TO-DO: fix bug when enabling coordinates and bugs when entering char, not number, when number is needed

void Greetings() // Greeting message
{
    std::cout << "|====|====|Игра Жизнь|====|====|\n";
    std::cout << "Разработчик: Terrakllee\n";
    std::cout << "Версия: " << VERSION << "\n\n";
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

    std::ios::sync_with_stdio(false); //Grok AI made for faster console frame
    std::cout.setf(std::ios::unitbuf); //Grok AI
    
    Greetings();
    GameOfLife gameOfLife;
    gameOfLife.Play();
    
    return 0;
}