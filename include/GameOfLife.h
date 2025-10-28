#pragma once
#include <string>

class GameOfLife
{
public:
    int GetActualGridSizeRows();
    int GetActualGridSizeCols();
    class Cell
    {
        ///// VARIABLES

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

        ///// CONSTRUCTORS

        Cell() : isAlive(0){}

        Cell(bool alive) : isAlive(alive) {}

        ///// GETTERS

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

        ///// SETTERS

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

    bool IsGridSizeXEven();
    bool IsGridSizeYEven();

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

    void RawPrintGrid(); //Prints entire grid as it is (for debugging)
    void PrintBG(int &i, int &j);
    void PrintCage(int &i, int &j);
    void PrintCoords(int &i, int &j, char &numbericRows, char &numbericCols);
    void PrintCell(int &i, int &j);
    
    void ClearScreen(); //Grok AI

    void PrintGrid(); //Prints grid with custom BG and Coordinates, displays life cells
    
    void CheckNeighbours();


    class Pattern
    {
        private:
        int sizeX = 0;
        int sizeY = 0;
        std::string name = "Nun";
        int patternID = 0;

        public:

        Pattern(int sizeX, int sizeY, std::string name, int patternID) : sizeX(sizeX), sizeY(sizeY), name(name), patternID(patternID) {};

        int GetSizeX() {return sizeX;}
        int GetSizeY() {return sizeY;}
        std::string GetName() {return name;}
        int GetPatternID() {return patternID;}

        void MessageSummonSuccess();
    };

    bool CheckIfPatternFits(Pattern &pattern);
    void CreatePatternByID(int patternID);
    void SummonPattern(Pattern &pattern);

    void SummonConstructionMenu(); // Menu of summoning different life cell ships like patterns

    void CreateBlinker(); //Blinker 3x3

    void ChooseBackground(); // Menu to change BG of grid
    void SetGameSpeed(); // Sets game speed int milliseconds

    int CountAliveCellsOnGrid(); // Counts and returns number of alive cells on the entire grid
    int CountDeadCellsOnGrid(); // Counts and returns number of dead cells on the entire grid
    int HowMuchFreeSpaceIsLeft(); // Counts how many dead cells are here?

    void ClearGrid(); // Clears the grid, basicaly kills all the cells
    void CellPhysics(); // Logic of the cell
    void InitCell(int x, int y, bool alive); // Initializes Cell
    void AliveRandomCell(); // Makes random cell alive
    void UserKillCell(); // User deletes cell at a specific coordinates
    void UserAddCell(); // User places cell at a specific coordinates
    void ChangeSeed();
    void RandomizeManyCellsBySeed(); // Spawns many random cells using specific user entered seed
    void ChangeCage(); //Changes cage design from coordinates to borders, or opposite

    void DebugMenu(); // Debug menu for testing different parts of the game mechanics
    void Launch();
    void ChangeGridSize();
    void Info();
    void Settings();
    void MainMenu();
    void Greetings(); // Greeting message
    void Play(); // Main function to play a game
    void InitGrid();
    void DeleteGrid();

    GameOfLife();
    ~GameOfLife();

private:
    Cell **Grid;
    int rows = 36; //default 36, 46 is max
    int cols = 86; //default 86, 106 is max
    const int MAX_ROWS = 46;
    const int MAX_COLS = 106;
    int actualGridSizeRows = rows-2;
    int actualGridSizeCols = cols-2;
    int coordColibrX = 0; //fixes user coordinates cell placement X //Half size of a building to paste (center)
    int coordColibrY = 0; //fixes user coordinates cell placement Y //Half size of a building to paste (center)
    int cMX = 0; // changing coords x (moving by x) to half of the screen (center) + size of Pattern
    int cMY = 0; // changing coords y (moving by y) to half of the screen (center)
    char bgChar = ' '; //default ' '
    short bgCharChoose = 5; //default 5
    double seed = 0; //default 0
    int tickTime = 125; //default 125
    int population = 0;
    int cellsGenerated = 0;
    bool showCoords = false; // Show coordinates on the grid
    bool showCage = true; // Show borderds on the grid
    bool gridView = false; //Shows grid view 3x1 symbols each cell
    bool userChangedSeed = false;
    bool frameHistory = true;
    std::string frame;
};