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
#include "GameOfLife.h"
#include "patterns.h"

namespace patterns
{
    ////////////////////////////////////////////////////////// CREATE OSCILLATORS

    void CreateBlinker(GameOfLife& g) //Blinker 3x3
    {
        g.InitCell(2+g.GCMX(), 1+g.GCMY(), 1);
        g.InitCell(2+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(2+g.GCMX(), 3+g.GCMY(), 1);
    }

    void CreateToad(GameOfLife& g) //Toad 4x4
    {
        g.InitCell(3+g.GCMX(), 1+g.GCMY(), 1);
        g.InitCell(1+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(4+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(1+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(4+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(2+g.GCMX(), 4+g.GCMY(), 1);
    }

    void CreateBeacon(GameOfLife& g) //Beacon 4x4
    {
        g.InitCell(1+g.GCMX(), 1+g.GCMY(), 1);
        g.InitCell(2+g.GCMX(), 1+g.GCMY(), 1);
        g.InitCell(1+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(4+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 4+g.GCMY(), 1);
        g.InitCell(4+g.GCMX(), 4+g.GCMY(), 1);
    }

    void CreatePulsar(GameOfLife& g) //Pulsar 17x17
    {
        g.InitCell(5+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(6+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(7+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(11+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(12+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(13+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 5+g.GCMY(), 1);
        g.InitCell(8+g.GCMX(), 5+g.GCMY(), 1);
        g.InitCell(10+g.GCMX(), 5+g.GCMY(), 1);
        g.InitCell(15+g.GCMX(), 5+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 6+g.GCMY(), 1);
        g.InitCell(8+g.GCMX(), 6+g.GCMY(), 1);
        g.InitCell(10+g.GCMX(), 6+g.GCMY(), 1);
        g.InitCell(15+g.GCMX(), 6+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 7+g.GCMY(), 1);
        g.InitCell(8+g.GCMX(), 7+g.GCMY(), 1);
        g.InitCell(10+g.GCMX(), 7+g.GCMY(), 1);
        g.InitCell(15+g.GCMX(), 7+g.GCMY(), 1);
        g.InitCell(5+g.GCMX(), 8+g.GCMY(), 1);
        g.InitCell(6+g.GCMX(), 8+g.GCMY(), 1);
        g.InitCell(7+g.GCMX(), 8+g.GCMY(), 1);
        g.InitCell(11+g.GCMX(), 8+g.GCMY(), 1);
        g.InitCell(12+g.GCMX(), 8+g.GCMY(), 1);
        g.InitCell(13+g.GCMX(), 8+g.GCMY(), 1);
        g.InitCell(5+g.GCMX(), 10+g.GCMY(), 1);
        g.InitCell(6+g.GCMX(), 10+g.GCMY(), 1);
        g.InitCell(7+g.GCMX(), 10+g.GCMY(), 1);
        g.InitCell(11+g.GCMX(), 10+g.GCMY(), 1);
        g.InitCell(12+g.GCMX(), 10+g.GCMY(), 1);
        g.InitCell(13+g.GCMX(), 10+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 11+g.GCMY(), 1);
        g.InitCell(8+g.GCMX(), 11+g.GCMY(), 1);
        g.InitCell(10+g.GCMX(), 11+g.GCMY(), 1);
        g.InitCell(15+g.GCMX(), 11+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 12+g.GCMY(), 1);
        g.InitCell(8+g.GCMX(), 12+g.GCMY(), 1);
        g.InitCell(10+g.GCMX(), 12+g.GCMY(), 1);
        g.InitCell(15+g.GCMX(), 12+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 13+g.GCMY(), 1);
        g.InitCell(8+g.GCMX(), 13+g.GCMY(), 1);
        g.InitCell(10+g.GCMX(), 13+g.GCMY(), 1);
        g.InitCell(15+g.GCMX(), 13+g.GCMY(), 1);
        g.InitCell(5+g.GCMX(), 15+g.GCMY(), 1);
        g.InitCell(6+g.GCMX(), 15+g.GCMY(), 1);
        g.InitCell(7+g.GCMX(), 15+g.GCMY(), 1);
        g.InitCell(11+g.GCMX(), 15+g.GCMY(), 1);
        g.InitCell(12+g.GCMX(), 15+g.GCMY(), 1);
        g.InitCell(13+g.GCMX(), 15+g.GCMY(), 1);
    }

    void CreatePentadecathlon(GameOfLife& g) //Pentadecathlon 11x18
    {
        g.InitCell(5+g.GCMX(), 6+g.GCMY(), 1);
        g.InitCell(6+g.GCMX(), 6+g.GCMY(), 1);
        g.InitCell(7+g.GCMX(), 6+g.GCMY(), 1);
        g.InitCell(5+g.GCMX(), 7+g.GCMY(), 1);
        g.InitCell(7+g.GCMX(), 7+g.GCMY(), 1);
        g.InitCell(5+g.GCMX(), 8+g.GCMY(), 1);
        g.InitCell(6+g.GCMX(), 8+g.GCMY(), 1);
        g.InitCell(7+g.GCMX(), 8+g.GCMY(), 1);
        g.InitCell(5+g.GCMX(), 9+g.GCMY(), 1);
        g.InitCell(6+g.GCMX(), 9+g.GCMY(), 1);
        g.InitCell(7+g.GCMX(), 9+g.GCMY(), 1);
        g.InitCell(5+g.GCMX(), 10+g.GCMY(), 1);
        g.InitCell(6+g.GCMX(), 10+g.GCMY(), 1);
        g.InitCell(7+g.GCMX(), 10+g.GCMY(), 1);
        g.InitCell(5+g.GCMX(), 11+g.GCMY(), 1);
        g.InitCell(6+g.GCMX(), 11+g.GCMY(), 1);
        g.InitCell(7+g.GCMX(), 11+g.GCMY(), 1);
        g.InitCell(5+g.GCMX(), 12+g.GCMY(), 1);
        g.InitCell(7+g.GCMX(), 12+g.GCMY(), 1);
        g.InitCell(5+g.GCMX(), 13+g.GCMY(), 1);
        g.InitCell(6+g.GCMX(), 13+g.GCMY(), 1);
        g.InitCell(7+g.GCMX(), 13+g.GCMY(), 1);
    }

    ////////////////////////////////////////////////////////////// CREATE SPACESHIPS

    void CreateGlider(GameOfLife& g) //Glider 5x5
    {
        g.InitCell(4+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(2+g.GCMX(), 4+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 4+g.GCMY(), 1);
        g.InitCell(4+g.GCMX(), 4+g.GCMY(), 1);
    }

    //////////////////////////////////////////////////// CREATE METHUSELAHS

    void CreateTheRPentomino(GameOfLife& g) // The R-pentomino 5x5
    {
        g.InitCell(3+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(2+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(4+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(4+g.GCMX(), 4+g.GCMY(), 1);
    }

    void CreateDiehard(GameOfLife& g) // Diehard 10x5
    {
        g.InitCell(8+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(2+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 4+g.GCMY(), 1);
        g.InitCell(7+g.GCMX(), 4+g.GCMY(), 1);
        g.InitCell(8+g.GCMX(), 4+g.GCMY(), 1);
        g.InitCell(9+g.GCMX(), 4+g.GCMY(), 1);
    }

    void CreateAcorn(GameOfLife& g) // Acorn 9x5
    {
        g.InitCell(3+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(5+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(2+g.GCMX(), 4+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 4+g.GCMY(), 1);
        g.InitCell(6+g.GCMX(), 4+g.GCMY(), 1);
        g.InitCell(7+g.GCMX(), 4+g.GCMY(), 1);
        g.InitCell(8+g.GCMX(), 4+g.GCMY(), 1);
    }

    //////////////////////////////// CREATE NUKES

    void CreateDiagonalNuke(GameOfLife& g) //Diagonal Nuke 10x8
    {
        g.InitCell(8+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(6+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(8+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(9+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(6+g.GCMX(), 4+g.GCMY(), 1);
        g.InitCell(8+g.GCMX(), 4+g.GCMY(), 1);
        g.InitCell(6+g.GCMX(), 5+g.GCMY(), 1);
        g.InitCell(4+g.GCMX(), 6+g.GCMY(), 1);
        g.InitCell(2+g.GCMX(), 7+g.GCMY(), 1);
        g.InitCell(4+g.GCMX(), 7+g.GCMY(), 1);
    }

    void CreateCompactNuke(GameOfLife& g) //Compact Nuke 5x5
    {
        g.InitCell(1+g.GCMX(), 1+g.GCMY(), 1);
        g.InitCell(2+g.GCMX(), 1+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 1+g.GCMY(), 1);
        g.InitCell(5+g.GCMX(), 1+g.GCMY(), 1);
        g.InitCell(1+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(4+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(5+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(2+g.GCMX(), 4+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 4+g.GCMY(), 1);
        g.InitCell(5+g.GCMX(), 4+g.GCMY(), 1);
        g.InitCell(1+g.GCMX(), 5+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 5+g.GCMY(), 1);
        g.InitCell(5+g.GCMX(), 5+g.GCMY(), 1);
    }

    void CreateNukeLine(GameOfLife& g) //Nuke Line 41x3
    {
        g.InitCell(2+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(4+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(5+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(6+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(7+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(8+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(9+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(11+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(12+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(13+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(14+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(15+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(19+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(20+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(21+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(28+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(29+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(30+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(31+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(32+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(33+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(34+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(36+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(37+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(38+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(39+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(40+g.GCMX(), 2+g.GCMY(), 1);
    }

    /////////////////Custom user made patterns

    void CreateAmogus(GameOfLife& g) //Amogus 6x7
    {
        g.InitCell(2+g.GCMX(), 2+g.GCMY(), 0);
        g.InitCell(3+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(4+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(5+g.GCMX(), 2+g.GCMY(), 1);
        g.InitCell(2+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 3+g.GCMY(), 1);
        g.InitCell(4+g.GCMX(), 3+g.GCMY(), 0);
        g.InitCell(5+g.GCMX(), 3+g.GCMY(), 0);
        g.InitCell(2+g.GCMX(), 4+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 4+g.GCMY(), 1);
        g.InitCell(4+g.GCMX(), 4+g.GCMY(), 1);
        g.InitCell(5+g.GCMX(), 4+g.GCMY(), 1);
        g.InitCell(2+g.GCMX(), 5+g.GCMY(), 1);
        g.InitCell(3+g.GCMX(), 5+g.GCMY(), 1);
        g.InitCell(4+g.GCMX(), 5+g.GCMY(), 1);
        g.InitCell(5+g.GCMX(), 5+g.GCMY(), 1);
        g.InitCell(2+g.GCMX(), 6+g.GCMY(), 0);
        g.InitCell(3+g.GCMX(), 6+g.GCMY(), 1);
        g.InitCell(4+g.GCMX(), 6+g.GCMY(), 0);
        g.InitCell(5+g.GCMX(), 6+g.GCMY(), 1);
    }

}

