#ifndef SUDOKO_H
#define SUDOKO_H



//Create 2D Vector Function
std::vector<std::vector<std::string> > CreateVect(int size);
//Char to String Function
char* toChar(std::string const str);

//
std::vector<std::vector<std::string> >CreateInitialBoard();


//Read Text File & return 2D Matrix
std::vector<std::vector<std::string> > readIn(std::ifstream& fileInput, int size);


//Parsing CSV with Input File
std::vector<std::vector<std::string>> boardMatrix(std::ifstream& fileName);



//Creating arrays based on CSV containing a puzzle per line
std::vector<std::vector<std::string>> testCSV(std::ifstream& file);


//Print 2D Vector
template<typename T>
void printVector( std::vector<std::vector<T> >  vect );

//Function to Check 3x3 Grid
bool gridCheck(std::vector<std::vector<std::string> > const vect, int row, int col, std::string shape);

//Find Row Coordinate for Empty Cell
int FindEmptyX(std::vector<std::vector<std::string> > vect);


//Find Col Coordinate for Empty Cell
int FindEmptyY(std::vector<std::vector<std::string> > vect);


//Function to check if a number is present vertically & horizontally
bool leftRight(std::vector<std::vector<std::string> > const vect, int row, int col, std::string shape);

//Recursive Sudoku Solver
bool SudukoSolves(std::vector<std::vector<std::string> >&vect, std::vector<std::string> arr);


//Recursive Utility Function
bool SudukoSolves(std::vector<std::vector<std::string> >& vect);


#endif // SUDOKO_H
