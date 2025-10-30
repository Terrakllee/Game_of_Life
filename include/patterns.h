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

#pragma once
#include "GameOfLife.h"

namespace patterns
{
    ////////////////////////////////////////////////////////// CREATE OSCILLATORS
    void CreateBlinker(GameOfLife& g); //Blinker 3x3
    void CreateToad(GameOfLife& g); //Toad 4x4
    void CreateBeacon(GameOfLife& g); //Beacon 4x4
    void CreatePulsar(GameOfLife& g); //Pulsar 17x17
    void CreatePentadecathlon(GameOfLife& g); //Pentadecathlon 11x18
    ////////////////////////////////////////////////////////////// CREATE SPACESHIPS
    void CreateGlider(GameOfLife& g); //Glider 5x5
    //////////////////////////////////////////////////// CREATE METHUSELAHS
    void CreateTheRPentomino(GameOfLife& g); // The R-pentomino 5x5
    void CreateDiehard(GameOfLife& g); // Diehard 10x5
    void CreateAcorn(GameOfLife& g); // Acorn 9x5
    //////////////////////////////// CREATE NUKES
    void CreateDiagonalNuke(GameOfLife& g); //Diagonal Nuke 10x8
    void CreateCompactNuke(GameOfLife& g); //Compact Nuke 5x5
    void CreateNukeLine(GameOfLife& g); //Nuke Line 41x3
    /////////////////Custom user made patterns
    void CreateAmogus(GameOfLife& g); //Amogus 6x7

}
