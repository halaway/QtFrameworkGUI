#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <thread>
#include <future>
#include "sudoko.h"

// Create 2D Vector Function
std::vector<std::vector<std::string>> CreateVect(int size)
{
    std::vector<std::vector<std::string>> vect(size);
    for (int i = 0; i < size; i++)
    {
        vect[i] = std::vector<std::string>(size);
        for (int j = 0; j < size; j++)
        {
            vect[i][j] = "-";
        }
    }
    return vect;
}

// Read Text File & return 2D Matrix
std::vector<std::vector<std::string>> readIn(std::ifstream &fileInput, int size)
{

    // Create new vector
    auto newVector = CreateVect(size);

    // Row & Columns
    int row, col = 0;

    // Read File
    std::string word, phrase;

    //Traverse File to collect input
    while (!fileInput.eof())
    {
        getline(fileInput, word);

        phrase += word;
    }

    //Use math to find index according to position in string
    // j , i
    // j + ( i * columns)

    for (int i = 0; i < phrase.length(); i++)
    {
        row = i / size;
        col = i % size;
        //If index is empty set location blank delimitter
        if (phrase[i] == ' ')
            newVector[row][col] = "-";
        else
            newVector[row][col] = phrase[i];
    }

    return newVector;
}

// Initializing temp board
std::vector<std::vector<std::string>> CreateInitialBoard()
{
    std::vector<std::vector<std::string>> initialBoard = {
      {"1", "2", "3", "-", "-", "-", "7", "8", "9"},
      {"4", "5", "6", "-", "-", "-", "1", "2", "3"},
      {"7", "8", "9", "-", "-", "-", "4", "5", "6"},
      {"-", "-", "-", "1", "2", "3", "-", "-", "-"},
      {"-", "-", "-", "4", "5", "6", "-", "-", "-"},
      {"-", "-", "-", "7", "8", "9", "-", "-", "-"},
      {"2", "3", "4", "-", "-", "-", "5", "6", "7"},
      {"5", "6", "7", "-", "-", "-", "8", "9", "1"},
      {"8", "9", "1", "-", "-", "-", "2", "3", "4"}};
    return initialBoard;
}

// Parsing CSV with Input File
std::vector<std::vector<std::string>> boardMatrix(std::ifstream &fileName)
{
    // Creating input string
    std::string line;

    std::vector<std::vector<std::string>> finalVec;
    while (getline(fileName, line))
    {
        std::stringstream ss(line);
        std::vector<std::string> myVec;
        std::string token;
        while (getline(ss, token, ','))
        {
            if (token.empty() || token == "0")
            {
                myVec.push_back("-");
            }
            else
            {
                myVec.push_back(token);
            }
        }
        finalVec.push_back(myVec);
    }
    fileName.close();
    return finalVec;
}

// Creating arrays based on CSV containing a puzzle per line
std::vector<std::vector<std::string>> testCSV(std::ifstream &file)
{

    std::vector<std::vector<std::string>> puzzle(9, std::vector<std::string>(9));
    std::string line;
    if (!getline(file, line))
    {
        std::cerr << "Error: Unable to read line from file" << std::endl;
        return {};
    }
    std::stringstream ss(line);
    std::string token;
    int row = 0, col = 0;
    while (getline(ss, token, ','))
    {
        if (token.empty() || token == "0")
        {
            puzzle[row][col] = "-";
        }
        else
        {
            puzzle[row][col] = token;
        }
        col++;
        if (col == 9)
        {
            col = 0;
            row++;
        }
    }
    return puzzle;
}

// Print 2D Vector
template <typename T>
void printVector(std::vector<std::vector<T>> vect)
{

    for (int i = 0; i < vect.size(); i++)
    {

        for (int j = 0; j < vect[i].size(); j++)
        {
            std::cout << vect[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Function to Check 3x3 Grid
bool gridCheck(std::vector<std::vector<std::string>> const vect, int row, int col, std::string shape)
{

    //return true;
    std::string num;

    //row multiples
    int n1, n2 = 0;

    if (vect[0].size() == 6)
    {
        n1 = 3;
        n2 = 2;
    }
    else if (vect[0].size() == 9)
    {
        n1 = 3;
        n2 = 3;
    }
    else if (vect[0].size() == 4)
    {
        n1 = 2;
        n2 = 2;
    }
    else if (vect[0].size() == 16)
    {
        n1 = 4;
        n2 = 4;
    }

    // Find the start of row
    int start_row = (row / n2) * n2;

    // Find the start of col
    int start_col = (col / n1) * n1;

    for (int i = start_row; i < start_row + n2; i++)
    {
        for (int j = start_col; j < start_col + n1; j++)
        {

            if (vect[i][j] == shape && i != row && j != col)
            {
                return false;
            }
        }
    }
    return true;
}

// Find Row Coordinate for Empty Cell
int FindEmptyX(std::vector<std::vector<std::string>> vect)
{
    for (int i = 0; i < vect[0].size(); i++)
    {
        for (int j = 0; j < vect[0].size(); j++)
        {
            if (vect[i][j] == "-")
            {
                return i;
            }
        }
    }
    return -1;
}

// Find Col Coordinate for Empty Cell
int FindEmptyY(std::vector<std::vector<std::string>> vect)
{
    //if(col  == vect[0].size() - 1 && vect[row][col] == "." ){col = 0;row++;}
    for (int i = 0; i < vect[0].size(); i++)
    {
        for (int j = 0; j < vect[0].size(); j++)
        {
            if (vect[i][j] == "-")
            {
                return j;
            }
        }
    }
    return -1;
}

// Function to check if a number is present vertically & horizontally
bool leftRight(std::vector<std::vector<std::string>> const vect, int row, int col, std::string shape)
{

    for (int i = 0; i < vect[0].size(); i++)
        if (vect[row][i] == shape && i != col || (vect[i][col] == shape && i != row))
        {
            return false;
        }

    if (vect[0].size() == 4 || vect[0].size() == 6 || vect[0].size() == 9 || vect[0].size() == 16)
        return gridCheck(vect, row, col, shape);

    return true;
}

// Recursive Sudoku Solver
bool SudukoSolves(std::vector<std::vector<std::string>> &vect, std::vector<std::string> arr)
{
    // Finding Empty Cell
    // Create Asynchronous Operation for Empty Row
    std::future<int> tRow = std::async(std::launch::async, FindEmptyX, vect);

    // Second Asynchronous Operation for Empty Column
    std::future<int> tCol = std::async(std::launch::async, FindEmptyY, vect);

    // Retrieving values
    int row = tRow.get();
    int col = tCol.get();

    // Keep track of values
    std::string num;

    // Check for All possible Positions
    if (row == -1 && col == -1)
        return true;

    // Traverse Possible Values in arr
    for (int i = 0; i < arr.size(); i++)
    {

        // Set Value of Num
        num = arr[i];

        // Check if value appears horizontally & vertically
        if (leftRight(vect, row, col, num))
        {

            // Set label in board
            vect[row][col] = num;

            // Recursive Call to function to check for values in that position
            // returns true if a possible solution is found
            if (SudukoSolves(vect, arr))
            {
                return true;
            }
            // BackTrack and reset Empty cell
            else
            {
                vect[row][col] = "-";
            }
        }
    }
    // Returns false if all values in array are traversed and do not create a solution
    return false;
}

//Recursive Utility Function
bool SudukoSolves(std::vector<std::vector<std::string>> &vect)
{
    std::vector<std::string> arr;

    for (int i = 1; i <= vect[0].size(); i++)
    {
        arr.push_back(std::to_string(i));
    }

    if (SudukoSolves(vect, arr) != 0)
    {
        std::cout << "Solved!" << std::endl;
        return true;
    }
    else
    {
        std::cout << "No Solution" << std::endl;
        return false;
    }
}
