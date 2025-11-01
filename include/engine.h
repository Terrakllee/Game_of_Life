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
#include <string>

class GameOfLife
{
public:

    // INNER CLASSES

    class Cell
    {
        // VARIABLES

        private:
        bool isAlive;
        short neigboursAliveCount = 0;
        bool upperLeftCornerAlive = false;
        bool upperMiddleAlive = false;
        bool upperRightCornerAlive = false;
        bool leftMiddleAlive = false;
        bool rightMiddleAlive = false;
        bool downLeftCornerAlive = false;
        bool downMiddleAlive = false;
        bool downRightCornerAlive = false;

        public:

        // CONSTRUCTORS

        Cell() : isAlive(0){}

        Cell(bool alive) : isAlive(alive) {}

        // GETTERS

        bool GetIsAlive() {return isAlive;}
        short GetNeigboursAliveCount() {return neigboursAliveCount;}
        bool GetUpperLeftCornerAlive() {return upperLeftCornerAlive;}
        bool GetUpperMiddleAlive() {return upperMiddleAlive;}
        bool GetUpperRightCornerAlive() {return upperRightCornerAlive;}
        bool GetLeftMiddleAlive() {return leftMiddleAlive;}
        bool GetRightMiddleAlive() {return rightMiddleAlive;}
        bool GetDownLeftCornerAlive() {return downLeftCornerAlive;}
        bool GetDownMiddleAlive() {return downMiddleAlive;}
        bool GetDownRightCornerAlive() {return downRightCornerAlive;}

        // SETTERS

        void SetIsAlive(bool isAlive) {this->isAlive = isAlive;}
        void SetNeigboursAliveCount(short neigboursAliveCount) {this->neigboursAliveCount = neigboursAliveCount;}
        void SetUpperLeftCornerAlive(bool ULCA) {upperLeftCornerAlive = ULCA;}
        void SetUpperMiddleAlive(bool UMA) {upperMiddleAlive = UMA;}
        void SetUpperRightCornerAlive(bool URCA) {upperRightCornerAlive = URCA;}
        void SetLeftMiddleAlive(bool LMA) {leftMiddleAlive = LMA;}
        void SetRightMiddleAlive(bool RMA) {rightMiddleAlive = RMA;}
        void SetDownLeftCornerAlive(bool DLCA) {downLeftCornerAlive = DLCA;}
        void SetDownMiddleAlive(bool DMA) {downMiddleAlive = DMA;}
        void SetDownRightCornerAlive(bool DRCA) {downRightCornerAlive = DRCA;}

    };

    class Pattern
    {
        // VARIABLES

        private:
        int sizeX = 0;
        int sizeY = 0;
        std::string name = "Nun";
        int patternID = 0;

        public:

        // CONSTRUCTORS

        Pattern(int sizeX, int sizeY, std::string name, int patternID) : sizeX(sizeX), sizeY(sizeY), name(name), patternID(patternID) {};

        // GETTERS

        int GetSizeX() {return sizeX;}
        int GetSizeY() {return sizeY;}
        std::string GetName() {return name;}
        int GetPatternID() {return patternID;}

        // METHODS

        void MessageSummonSuccess();
    };

    // GETTERS
    
    int GCMX()const{return cMX;}
    int GCMY()const{return cMY;}

    int GetActualGridSizeRows()const{return actualGridSizeRows;}
    int GetActualGridSizeCols()const{return actualGridSizeCols;}

    int GetMAX_ROWS()const{return MAX_ROWS;}
    int GetMAX_COLS()const{return MAX_COLS;}

    int GetTickTime()const{return tickTime;}

    bool GetGridView()const{return gridView;}
    bool IsGridSizeXEven()const{return actualGridSizeCols % 2 == 0;}
    bool IsGridSizeYEven()const{return actualGridSizeRows % 2 == 1;}
    bool GetFrameHistory()const{return frameHistory;}

    short GetBgCharChoose()const{return bgCharChoose;}
    char GetBgChar()const{return bgChar;}

    bool GetShowCage()const{return showCage;}
    bool GetShowCoords()const{return showCoords;}
    bool GetUserChangedSeed()const{return userChangedSeed;}

    int GetPopulation()const{return population;}

    int GetRows()const{return rows;}
    int GetCols()const{return cols;}
    int GetCellsGenerated()const{return cellsGenerated;}
    double GetSeed()const{return seed;}

    // SETTERS

    void SetFrameHistory(bool framHistory){this->frameHistory = frameHistory;}

    void SetActualGridSizeRows(int actualGridSizeRows){this->actualGridSizeRows = actualGridSizeRows;}
    void SetActualGridSizeCols(int actualGridSizeCols){this->actualGridSizeCols = actualGridSizeCols;}

    void SetRows(int rows){this->rows = rows;}
    void SetCols(int cols){this->cols = cols;}
    
    void SetGridView(bool gridView){this->gridView = gridView;}

    void SetTickTime(int tickTime){this->tickTime = tickTime;}

    void SetBgCharChoose(short bgCharChoose){this->bgCharChoose = bgCharChoose;}

    void SetBgChar(char bgChar){this->bgChar = bgChar;}

    void SetShowCage(bool showCage){this->showCage = showCage;}
    void SetShowCoords(bool showCoords){this->showCoords = showCoords;}

    void SetUserChangedSeed(bool userChangedSeed){this->userChangedSeed = userChangedSeed;}

    void SetPopulation(int population){this->population = population;}

    // METHODS

    bool IsEdge(int &i, int &j);
    bool IsCellEdge(int &i, int &j);
    bool IsUpEdge(int &i);
    bool IsDownEdge(int &i);
    bool IsLeftEdge(int &j);
    bool IsRightEdge(int &j);

    bool IsUpLeftCorner(int &i, int &j);
    bool IsUpRightCorner(int &i, int &j);
    bool IsDownLeftCorner(int &i, int &j);
    bool IsDownRightCorner(int &i, int &j);

    // Prints entire grid as it is (for debugging)
    void RawPrintGrid();
    void PrintBG(int &i, int &j);
    void PrintCage(int &i, int &j);
    void PrintCoords(int &i, int &j, char &numbericRows, char &numbericCols);
    void PrintCell(int &i, int &j);
    
    // Clears the output frame in CMD, Grok AI Made this one
    void ClearScreen();

    // Prints grid with custom BG and Coordinates, displays life cells, for coordinates (if enabled) A = 10, B = 20 etc
    void PrintGrid();

    bool CheckIfPatternFits(Pattern &pattern);
    void CreatePatternByID(int patternID);
    void SummonPattern(Pattern &pattern);

    // Counts and returns number of alive cells on the entire grid
    int CountAliveCellsOnGrid();
    // Counts and returns number of dead cells on the entire grid
    int CountDeadCellsOnGrid();
    // Counts how many dead cells are here
    int HowMuchFreeSpaceIsLeft();

    // Clears the grid, basicaly kills all the cells
    void ClearGrid();
    // Checks who is neighbouring current cell and how many neighbours
    void CheckNeighbours();
    // Logic of the cell
    void CellPhysics();
    // Initializes Cell
    void InitCell(int x, int y, bool alive);
    // Makes random cell alive
    void AliveRandomCell();

    // Main function to play a game
    void Play();
    void InitGrid();
    void DeleteGrid();

    GameOfLife();
    ~GameOfLife();

private:

    // VARIABLES

    Cell **Grid;
    std::string frame;
    int rows = 36; //default 36, 46 is max
    int cols = 86; //default 86, 106 is max
    int actualGridSizeRows = rows-2;
    int actualGridSizeCols = cols-2;
    int coordColibrX = 0; // Fixes user coordinates cell placement X //Half size of a pattern to paste (center)
    int coordColibrY = 0; // Fixes user coordinates cell placement Y //Half size of a pattern to paste (center)
    int cMX = 0; // Changing coords x (moving by x) to half of the screen (center) + size of Pattern
    int cMY = 0; // Changing coords y (moving by y) to half of the screen (center)
    char bgChar = ' '; //default ' '
    short bgCharChoose = 5; //default 5
    double seed = 0; //default 0
    int tickTime = 125; //default 125
    int population = 0;
    int cellsGenerated = 0;

    // CONSTANTS

    const int MAX_ROWS = 46;
    const int MAX_COLS = 104;

    // FLAGS

    bool showCoords = false; // Show coordinates on the grid
    bool showCage = true; // Show borderds on the grid
    bool gridView = false; // Shows grid view 3x1 symbols each cell
    bool userChangedSeed = false; // If user changed seed (useful for many random cell generation)
    bool frameHistory = true; // If true, shows all frames, and doesn't clear the console output
};