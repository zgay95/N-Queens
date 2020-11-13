/* Authors: Zachary Gay, Jialin Wang            Date: 12/02/19
AI Final Term Project #4 (N-Queens)

Project Desciprtion: N-Queens is a puzzle-solving problem involving the placement of N chess queens on an N by N grid so that no two queens threaten each other. 
Solutions exist for all natural numbers n with the exception of n = 2 or n = 3. While there are many different ways to represent and solve this problem, 
the most efficient method is to model it as a constraint satisfaction problem (CSP) using a minimum-conflict heuristic.

This program will take input from a user of a single integer; setting the N value for either algorithm the user selects. If the backtracking Algorithm is selected, 
the program will then create an array the size of MAX x MAX and begin to iterate through the 2D array(board) until a solution is found. If the Heuristic Algortihm 
is selected,the program will use a 1d array to keep track fo queen placements for each row and use a minimum conflict heuristic to calculate a solution. A solution 
should be found for every postive integer that != 0,2,3. The solution will be printing out into a visual chess board for the terminal with 'Q' being in place of where 
the queens are. This way we can check the solution visually to ensure it is valid. 
*/
//Includes
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
//Namespaces
using namespace std;
//Constants
#define MAX 1000 //set MAX constant for space management. 
//The calcConflicts() fucntion calculates the number of conflicts left in the puzzle
int calcConflicts(int a[], int n)
{
	int temp = 0;
	for (int i = 0; i < n; i++) 
	{
		for (int j = i + 1; j < n; j++) // ofr every element
		{
			if ((a[i] == a[j]) || (abs(i - j) == abs(a[i] - a[j])))	//calculate number of conflicts
				temp++;
		}
	}
	return temp; // return number of conflcits
}
// the function solveHeurtic() solves the given N-queens puzzle using a minimum conflict heuristic
bool solveHeurstic(int Queens[], int n)
{	
  srand(time(NULL)); //set time for random number generates
	bool Solved; //boolean to keep track of when a solution is found
	int tempConflicts, curConflict, bestConflict, curRow, bestCol, bestRow, restart; // all neede variables ot calculate a solution							

	while (!Solved)//while puzzle is not solved 
	{
    restart = 1000; //max number of elements to explore per attempt
    if (Solved) // check fi a solution ahs eben found
    {
      return Solved;
    }
		for (int i = 0; i < n; i++)// for every queen to be place, ranodmly place them in each row
    {
		  Queens[i] = (rand() % n);
    }
		curConflict = calcConflicts(Queens,n); //calculate current number of conflicts
		while (curConflict > 0)							//while conflicts exists, must be no solution yet
		{
			bestConflict = curConflict;
			curRow = rand() % n; //assign a random row
			for (int j = 0; j < n; j++)
			{
				Queens[curRow] = j; //check conflicts at every column
				tempConflicts = calcConflicts(Queens,n); //calculate conflicts if queen was placed
				if (tempConflicts <= bestConflict) //if new conflicts si better than the bnest we know swap them
				{							
					bestConflict = tempConflicts;
					bestRow = j;
					bestCol = curRow;
				}
			}
			if (restart == 0) //Solution was not found within # of iterations. Restart search
			{
				break;							
			}
			else								//Store values for each iteration
			{
				Queens[bestCol] = bestRow;
				curConflict = bestConflict;
				restart--;
			}
			if (bestConflict == 0)//if there are 0 conflcits then a solution be found
			{
				return Solved = true; //exit fucntion and return true for solution found
			}
		}
	}
}
// The welcome() function greets the player and receives their input for N as an integer. It returns N. 
int welcome () 
{
  int n = 0;
  cout << "\nWelcome to the N-Queens puzzle solving program.\n\n" << "Please enter the number for N you wish the program to solve: ";
  cin >> n;
  while(cin.fail() || n > MAX || n == 0 || n == 2 || n == 3) //check input is valid for a solution and is a number
  {
    cout << "\nError: Please input a positive integer != 0,2,3: ";
    cin.clear();
    cin.ignore(256,'\n'); //clear input buffer
    cin >> n;
  }
  return n; 
}
// The select() function recieve input fromt he user on which algorithm they wish to solve the problem
int select () 
{
  int s = 0;
  cout << "Please enter how you wish the program to solve the N queens puzzle:\n 1.Backtracking Algorithm\n 2.Heuristic Algorithm\n\n Enter: ";
  cin >> s;
  while(cin.fail() || s < 1 || s > 2 ) //check input is valid for a solution and is a number
  {
    cout << "\nError: Please input a 1 or 2 depending on how you wish the program to solve the puzzle. ";
    cin.clear();
    cin.ignore(256,'\n'); //clear input buffer
    cin >> s;
  }
  return s; 
}
// The checkMove() function checks if a given placement is a valid mvoe to palce a queen.
// Due to the way we are traverseing the 2D array data structure, We only need to check the upper& lower left diagonal and the same row to the left side
bool checkMove(int board[MAX/10][MAX/10], int col, int row) 
{ 
  //These two for loop checks the upper left diagonal
  for (int r = row, c = col; c >= 0 && r >= 0; r--,c--) 
  {
    if (board[r][c] == 1) //if a queen is placed there
    {
      return false; 
    }
  }
  //These two loop checks the lower left diagonal
  for (int x = row, y = col; y >= 0 && x < MAX; x++, y--) 
  {
    if (board[x][y] == 1) //if a queen is placed there
    {
      return false; 
    }
  }
  //This for loop checks the row to the left
  for (int z = 0; z < col; z++) 
  {
    if (board[row][z] == 1) //if a queen is placed there
    {
      return false; 
    }
  }
  return true; //valid move
} 
//The solve() function recursively calls itself to search each column for any avaiable moves and backtracks if no move is avaiable in that column
bool solve(int board[MAX/10][MAX/10], int column, int size) 
{ 
  //Return true if all columns traversed, then a solution must be found 
  if (column >= size) 
  {
    return true; 
  }
  //for every row in this column
  for (int row = 0; row < size; row++) 
  { 
    //check if any moves are available
    if (checkMove(board, column, row)) 
    { 
      //Place queen if move avaialable
      board[row][column] = 1; 
  
      //after move is place, recursively move to the next column. 
      //If false is returned then backtracking will occur
      if (solve(board, column + 1, size)) 
      {
        return true; 
      }  
      //Ensure the queen that was palce is reste to 0
      board[row][column] = 0;
    } 
  } 
  //no move is available in this column. Backtrack.
  return false; 
} 
//The printboard() functions prints out the board past to it in a visual way for the terminal
void printboard(int board[MAX/10][MAX/10], int n)
{
  for (int row = 0; row < n; row++)
    {
      for (int i = 0; i < n; i++) //print top dashed bar for every col
      {
        cout << "--";
      }
      cout << "\n";
      cout << "|";
      for (int col = 0; col < n; col++)
      {
        if (board[row][col] == 1) // if there is a queen print 'Q' , otherwise print space
        {
          cout << "Q|";
        }
        else
        {
          cout << " |";
        }
      } 
      cout << "\n";
    }
    for (int j = 0; j < n; j++) // print last dash row to finish board display
      {
        cout<<"--";
      }
      cout << "\n\n\n";
}
void printboard(int Queens[], int n)
{
  for (int i = 0; i < n; i++) //print top dashed bar for every col
  {
    cout << "--";
  }
  for (int i = 0; i < n; i++)
	{
      cout << "\n";
      cout << "|";
		for (int j = 0; j < n; j++)
		{
			if (j == Queens[i])
      {
        cout << "Q|";
      }
      else
      {
        cout << " |";
      }
		}
    cout << endl;
    for (int j = 0; j < n; j++) // print last dash row to finish board display
      {
        cout<<"--";
      }
  }
  cout << "\n\n\n";
}
//The main() function is the driver for the program
int main()
{
  //create a 2d array with constants, just easier this way rather than variable length, use in backtracking solution.
  int board[MAX/10][MAX/10];									
  //create 1d array to store solution in heuristic solution, will be assigned random values later
  int Queens[MAX];	
  //greet and receive input from user
  int n = welcome(), s = select();
  bool solved;
  // print out to show we accept the input and are ready to calculate a solution
  cout << "\n\n Processing Solution... \n\n"; 
  //select which algorithm to run based on user input
  switch (s)
  {
  case 1:
  // These two for loops initiliaze all the values in the 2d array structure to 0
    for (int row = 0; row < MAX/10; row++)
    {
      for (int col = 0; col < MAX/10; col++)
      {
        board[row][col] = 0;
      } 
    }
    //call recursive backtracking function to solve the puzzle based on size from user input
    solved = solve(board,0,n);
    break;
  case 2:
    //call heuristic function to solve the puzzle based on size from user input
    solved = solveHeurstic(Queens, n);
    break;
  default:
    break;
  }
  // If statemant checks if a solution was found. If so we display the array in a visual format. Otherwise display a no solution message
  if (solved == true)
  {
    cout << "Solution Found!\n\n"; // Solution Found
    if (s == 1)
    {
      printboard(board,n); //print backtracking solution
    }
    else
    {
      printboard(Queens,n); //print Heuristic solution
    }
  }
  else // No solution found
  {
    cout << "No solution Found. Please Try again.\n\n ";
  }
  return 0; //end program
}