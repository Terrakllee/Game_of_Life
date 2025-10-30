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
#include "engine.h"

namespace patterns
{
    ///////////////////////////////////////////  CREATE OSCILLATORS

    // Creates Blinker 3x3
    void CreateBlinker(GameOfLife& g);
    // Creates Toad 4x4
    void CreateToad(GameOfLife& g);
    // Creates Beacon 4x4
    void CreateBeacon(GameOfLife& g);
    // Creates Pulsar 17x17
    void CreatePulsar(GameOfLife& g);
    // Creates Pentadecathlon 11x18
    void CreatePentadecathlon(GameOfLife& g);

    /////////////////////////////////////////// CREATE SPACESHIPS

    // Creates Glider 5x5
    void CreateGlider(GameOfLife& g);

    /////////////////////////////////////////// CREATE METHUSELAHS

    // Creates The R-pentomino 5x5
    void CreateTheRPentomino(GameOfLife& g);
    // Creates Diehard 10x5
    void CreateDiehard(GameOfLife& g);
    // Creates Acorn 9x5
    void CreateAcorn(GameOfLife& g);

    ///////////////////////////////////////////  CREATE NUKES

    // Creates Diagonal Nuke 10x8
    void CreateDiagonalNuke(GameOfLife& g);
    // Creates Compact Nuke 5x5
    void CreateCompactNuke(GameOfLife& g);
    // Creates Nuke Line 41x3
    void CreateNukeLine(GameOfLife& g);

    /////////////////////////////////////////// CUSTOM USER MADE PATTERNS

    // Creates Amogus 6x7
    void CreateAmogus(GameOfLife& g);

}
