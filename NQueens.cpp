/* Authors: Zachary Gay             Date: 11/25/19
AI Final Term Project #4 - (N-Queens)
This program will take input a single integer from the user setting the N value for the NxN Array & Number of queens to place.
*/
#include <iostream>

using namespace std;


/* The welcome() function greets the player and receives their input for N as an integer. It returns N. */
int welcome () {
int n = 0;
cout << "\nWelcome to the N-Queens puzzle solving program.\n\n" << "Please enter the number for N you wish the program to solve:";
cin >> n;
 while(cin.fail()) {
        cout << "\nError: Please input a positive integer != 0,2,3: ";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> n;
    }
cout << "\n\n Processing Solution... \n\n";
return n; 
}


int main()
{
  //greet and receive input from user
  int n = welcome();

  //create a 2d array. (An array or arrays)
  int** board = new int*[n];
    for(int i = 0; i < n; ++i)
    { board[i] = new int[n]; }

  // These two for loops initiliaze all the values in the 2d array structure to 0
  for (int row = 0; row < n; row++)
  {
    for (int col = 0; col < n; col++)
    {
      board[row][col] = 0;
    } 
  }
  
  // These two for loops print out the 2d array data structure
  for (int r = 0; r < n; r++)
  {
    cout << "{ ";
    for (int c = 0; c < n; c++)
    {
      cout << board[r][c] << ", ";
    } 
    cout << "}\n";
  }
}