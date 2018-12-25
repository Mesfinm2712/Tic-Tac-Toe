#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3

int isInputValid(int, int, int);
int isBoardFull(char [N][N]);
void createInitialBoard(char [N][N]);
void readUserMove(int *, int *);
void printCurrentBoard(char[N][N]);
int getComputerMove(char [N][N], int *, int *, int, int);
int gameWon(char [N][N], char);
int computerPlaysToWin(char [N][N], int * , int * );
void computerPlaysRandom(int * , int * , int , int );
void sumAllDimensions(char [N][N], int [N], int [N], int *, int *);
int memberOf(int , int [N]);
int computerPlaysToBlock(char [N][N], int * , int * );

int main(){

   int userRow, userCol, computerRow, computerCol;
   int taken;
   char board[N][N];
   char winner = 'N';

   srand(time(NULL));

   printf("This tic-tac-toe board is of size %d by %d\n", N, N);

   printf("Player symbol: X \n Computer symbol: O\n\n");

   printf("Here is the board - spaces are indicated by a ?\n");

   createInitialBoard(board);			// create a 3 X 3 board with '?' in each cell

   while ((winner != 'Y') && !(isBoardFull(board))) // while there is no winner and the board is not full
   {
	   taken = 0;

		while (!(taken))                  // loop used to accept valid row and col values from the user
		{
			readUserMove(&userRow, &userCol);                  //get user's move
			printf("You chose row %d and column %d \n", userRow, userCol);

			while (!isInputValid(userRow, 1, N) || !isInputValid(userCol, 1, N))     // validate user's move
			{
				printf("That's is an invalid row or column number - try again\n");
				readUserMove(&userRow, &userCol);
				printf("You chose row %d and column %d \n", userRow, userCol);
			}

			if (board[userRow-1][userCol-1] == '?')           // if cell is unoccupied
			{
				board[userRow-1][userCol-1] = 'X';			// store an X there
				taken = 1;
			}
			else
			{
				taken = 0;									// otherwise inform the user to enter values again
				printf("That spot is taken - please try another one\n");
			}

		} //end of while (!taken)

	   if (gameWon(board, 'X'))   // check if the user wins - game will end if the user does win
	   {
		   printf("Congrats - you won against the computer :)\n");
		   winner = 'Y';
	   }

	   else  if (!(isBoardFull(board)))            //check if the board is already full
	   {
		   taken = 0;

		   while (!(taken))
		   {
				getComputerMove(board, &computerRow, &computerCol, userRow-1, userCol-1); // get computer's row and col

				if (board[computerRow][computerCol] == '?')         // check if the cell is unoccupied
				{
					board[computerRow][computerCol] = 'O';
					taken = 1;
				}
				else
				{
					taken = 0;		//That spot is taken - computer - try another one
				}
		   }

		   printf("Computer chose row %d and column %d \n", computerRow+1, computerCol+1);

		   if (gameWon(board, 'O'))               // check if the computer wins - game must end if it does
		   {
			   printf("Oh the computer won this time :(( think hard next time\n");
			   winner = 'Y';
		   }
	   }
	printCurrentBoard(board);

	printf("\nPress enter to continue \n");
	getchar();

   } //end of while

   if (winner != 'Y')
			printf("Game was a tie - no winner!\n\n");

   return 0;
}
//checks to see if input is between minimum (1) and maximum (3)
int isInputValid(int entered, int minimum, int maximum)
{
  if (entered >= minimum  && entered <= maximum )
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
//checks too see if board full, returns 1 if it is full
int isBoardFull(char board[N][N])
{

  int boardFull;
  boardFull = 1;

  for (int i = 0; i < N; i ++)
  {
    for (int j = 0; j < N; j++)
    {
      if (board[i][j] == '?')
      {
        boardFull = 0;

      }

    }

  }

  return boardFull;
}
//creates the initial board for the user with '?' as each cell
void createInitialBoard(char board[N][N])
{
  board [0][0] = '?';
  board [0][1] = '?';
  board [0][2] = '?';
  board [1][0] = '?';
  board [1][1] = '?';
  board [1][2] = '?';
  board [2][0] = '?';
  board [2][1] = '?';
  board [2][2] = '?';


  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j ++)
    {

      if (j == 2)
      {
        printf("  %c ", board[i][j]);
      }
      else
      {
        printf("  %c |", board[i][j]);
      }
    }
      printf("\n--------------\n");
  }

}
//allows user to insert their move
void readUserMove(int *userRow, int *userCol)
{
  printf("Your move - enter numbers between 1 and 3\n");
  printf("Enter row number: ");
  scanf ("%d", userRow);
  printf("Enter column number: ");
  scanf("%d", userCol);

}
//prints the current board after every move
void printCurrentBoard(char board[N][N])
{
  printf("Current board now is: \n");
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j ++)
    {
      if (j == 2)
      {
        printf("  %c ", board[i][j]);
      }
      else
      {
        printf("  %c |", board[i][j]);
      }
    }
      printf("\n--------------\n");
  }

}
//checks to see if user or computer wins the game
int gameWon(char board[N][N], char symbol)
{
  int winner;
  int sumR[N], sumC[N];
  int sumLD, sumRD;

  winner = 0;

  symbol = ' ';

  sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD);

  for(int i = 0; i < N; i++)
  {
    if (sumR[i] == 12)
    {
      winner = 1;
      symbol = 'O';
    }
    else if(sumR[i] == 3)
    {
      winner = 1;
      symbol = 'X';
    }
    else if(sumC[i] == 12)
    {
    winner = 1;
    symbol = 'O';
    }
    else if(sumC[i] == 3)
    {
      winner = 1;
      symbol = 'X';
    }
  }

  if(sumLD == 12)
  {
    winner = 1;
    symbol = 'O';
  }
  else if(sumLD == 3)
  {
    winner = 1;
    symbol = 'X';
  }
  else if(sumRD == 12)
  {
    winner = 1;
    symbol = 'O';
  }
  else if(sumRD == 3)
  {
    winner = 1;
    symbol = 'X';
  }

  return winner;

}
//allows the computer to play to win the game if there are two 'O' in a row, column or diagonal
int computerPlaysToWin(char board[N][N], int *cRow , int *cCol )
{

  int sumR[N], sumC[N], computerWins;
  int sumLD, sumRD;


  computerWins = 0;

  sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD);

  //rows
  for(int i = 0; i < N; i++)
  {
    if (sumR[i] - 8 == 0)
    {

      if (board[i][0] != 'O')
      {
        *cRow = i;
        *cCol = 0;
        computerWins = 1;
      }
      else if (board [i][1] != 'O')
      {
        *cRow = i;
        *cCol = 1;
        computerWins = 1;
      }
      else if (board [i][2] != 'O')
      {
        *cRow = i;
        *cCol = 2;
        computerWins = 1;
      }
      else
      {
      computerWins = 0;
      }

    }
  }

  //columns
  for(int i = 0; i < N; i++)
  {
    if (sumC[i] - 8 == 0)
    {

      if (board[0][i] != 'O')
      {
        *cRow = 0;
        *cCol = i;
        computerWins = 1;
      }
      else if (board [1][i] != 'O')
      {
        *cRow = 1;
        *cCol = i;
        computerWins = 1;
      }
      else if (board [2][i] != 'O')
      {
        *cRow = 2;
        *cCol = i;
        computerWins = 1;
      }
      else
      {
        computerWins = 0;
      }

    }
  }

  //left diagonal
  if (sumLD - 8 == 0)
  {

    if (board[0][0] != 'O')
    {
      *cRow = 0;
      *cCol = 0;
      computerWins = 1;
    }
    else if (board [1][1] != 'O')
    {
      *cRow = 1;
      *cCol = 1;
      computerWins = 1;
    }
    else if (board [2][2] != 'O')
    {
      *cRow = 2;
      *cCol = 2;
      computerWins = 1;
    }
    else
    {
      computerWins = 0;
    }

  }

  //right diagonal
  if (sumRD - 8 == 0)
  {
    if (board [0][2] != 'O')
    {
      *cRow = 0;
      *cCol = 2;
      computerWins = 1;
    }
    else if (board[1][1] != 'O')
    {
      *cRow = 1;
      *cCol = 1;
      computerWins = 1;
    }
    else if (board [2][0] != 'O')
    {
      *cRow = 2;
      *cCol = 0;
      computerWins = 1;
    }
    else
    {
      computerWins = 0;
    }

  }

return computerWins;
return *cRow;
return *cCol;

}
//makes the computer play random if it cannot block or win
void computerPlaysRandom(int *cRow , int *cCol , int uRow , int uCol)
{
  int number, diagonal, noMoves;
  number = rand() %5;
  diagonal = rand() %2;
  noMoves = 1;

  char board[N][N];
  int sumR[N], sumC[N];
  int sumLD, sumRD;


  sumAllDimensions (board, sumR, sumC, &sumLD, &sumRD);

  if(noMoves == 1)
  {
    //same row
    if (number == 0)
    {
      *cRow = uRow;
      *cCol = rand() %3;
      noMoves = 0;
    }
    //same column
    if (number == 1)
    {
      *cCol = uCol;
      *cRow = rand() %3;
      noMoves = 0;
    }
    //left diagonal
    if (number == 2)
    {
      if (uRow == 0 && uCol == 0)
      {
        if (diagonal == 0)
        {
          *cRow = 1;
          *cCol = 1;
          noMoves = 0;
        }
        else if (diagonal == 1)
        {
          *cRow = 2;
          *cCol = 2;
          noMoves = 0;
        }
      }
      if (uRow == 1 && uCol == 1)
      {
        if (diagonal == 0)
        {
          *cRow = 0;
          *cCol = 0;
          noMoves = 0;
        }
        else if (diagonal == 1)
        {
          *cRow = 2;
          *cCol = 2;
          noMoves = 0;
        }
      }
      if (uRow == 2 && uCol == 2)
      {
        if (diagonal == 0)
        {
          *cRow = 1;
          *cCol = 1;
          noMoves = 0;
        }
        else if (diagonal == 1)
        {
          *cRow = 0;
          *cCol = 0;
          noMoves = 0;
        }
      }
    }
    //right diagonal
    if (number == 3)
    {
      if (uRow == 0 && uCol == 2)
      {
        if (diagonal == 0)
        {
          *cRow = 1;
          *cCol = 1;
          noMoves = 0;
        }
        else if (diagonal == 1)
        {
          *cRow = 2;
          *cCol = 0;
          noMoves = 0;
        }
      }
      if (uRow == 1 && uCol == 1)
      {
        if (diagonal == 0)
        {
          *cRow = 0;
          *cCol = 2;
          noMoves = 0;
        }
        else if (diagonal == 1)
        {
          *cRow = 2;
          *cCol = 0;
          noMoves = 0;
        }
      }
      if (uRow == 2 && uCol == 0)
      {
        if (diagonal == 0)
        {
          *cRow = 1;
          *cCol = 1;
          noMoves = 0;
        }
        else if (diagonal == 1)
        {
          *cRow = 0;
          *cCol = 2;
          noMoves = 0;
        }
      }
    }
    if(number == 4)
    {
      if(uRow ==  1 && uCol ==2)
      {
        if(diagonal == 0)
        {
        *cRow = 2;
        *cCol = 1;
        }
        else if (diagonal == 1)
        {
          *cRow = 0;
          *cCol = 1;
        }
      }
      else if(uRow ==  1 && uCol ==0)
      {
        if(diagonal == 0)
        {
        *cRow = 0;
        *cCol = 1;
        }
        else if (diagonal == 1)
        {
          *cRow = 2;
          *cCol = 1;
        }
      }
      else if(uRow ==  0 && uCol ==1)
      {
        if(diagonal == 0)
        {
        *cRow = 1;
        *cCol = 0;
        }
        else if (diagonal == 1)
        {
          *cRow = 1;
          *cCol = 2;
        }
      }
      else if(uRow ==  2 && uCol ==1)
      {
        if(diagonal == 0)
        {
        *cRow = 1;
        *cCol = 0;
        }
        else if (diagonal == 1)
        {
          *cRow = 1;
          *cCol = 2;
        }
      }
    }
  }

}
//adds up the sum of each row, column, and diagonal assigning ('X' to 1) and ('O' to 4)
void sumAllDimensions(char board[N][N], int sumR[N], int sumC[N], int * sumLD, int *sumRD)
{

  *sumLD = 0;
  *sumRD = 0;

  for (int i = 0; i < N; i++)
  {
    sumR[i] = 0;
    sumC[i] = 0;
  }

  //sum for left diagonal
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      if (i == j)
      {
        if (board[i][j] == 'O')
        {
          *sumLD = *sumLD + 4;
        }
        if (board[i][j] == 'X')
        {
          *sumLD = *sumLD + 1;
        }
        if (board[i][j] == '?')
        {
          *sumLD = *sumLD;
        }

      }

    }

  }

  //sum for right diagonal
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      if ((i == 0 && j == 2) ||(i == 1 && j ==1) || (i == 2 && j == 0))
      {
        if (board[i][j] == 'O')
        {
          *sumRD = *sumRD + 4;
        }
        if (board[i][j] == 'X')
        {
          *sumRD = *sumRD + 1;
        }
      }

      if (board[i][j] == '?')
      {
        *sumRD = *sumRD;
      }

    }

  }


//sum of rows
  for (int i = 0; i < N; i++)
  {

    for (int j = 0; j < N; j++)
    {
      if (board[i][j] == 'O') //assigning value in array to 4 and 1
      {
        sumR[i] = sumR[i] + 4;
      }
      if (board[i][j] == 'X')
      {
        sumR[i] = sumR[i] + 1;
      }
      if (board[i][j] == '?')
      {
        sumR[i] = sumR[i];
      }
    }
  }

  //sum of columns
  for (int j = 0; j < N; j++)
  {
    for (int i = 0; i < N; i++)
    {

      if (board[j][i] == 'O')//assigning value in array to 4 and 1
      {
        sumC[i] = sumC[i] + 4;
      }
      if (board[j][i] == 'X')
      {
        sumC[i] = sumC[i] + 1;
      }
      if (board[j][i] == '?')
      {
        sumC[i] = sumC[i];
      }

    }

  }

}
//returns 1 if value exists in array
int memberOf(int aNum, int someArray[N])
{
  int existArray;

  for (int i = 0; i < N; i++)
  {

    if(someArray[i] == aNum)
    {
      existArray = 1;
    }
    else
    {
      existArray = 0;
    }

  }

  return existArray;
}
//checks to see if computer can block player move, if so it does
int computerPlaysToBlock(char board[N][N], int *computerRow , int *computerCol )
{
  int blocked;
  blocked = 1;

  int sumR[N], sumC[N];
  int sumLD, sumRD;


  sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD);


  for (int i = 0; i < N; i++)
  {
    if (sumR[i] - 2 == 0 || sumC[i] - 2 == 0)
    {
      blocked = 1;
      break;
    }
    if (sumRD - 2 == 0 || sumLD - 2 == 0)
    {
      blocked = 1;
      break;
    }
    else
    {
      blocked = 0;
    }
  }

  //rows
  for(int i = 0; i < N; i++)
  {
    if (sumR[i] - 2 == 0)
    {
      *computerRow = i;
      for (int j = 0; j < N; j++)
      {
        if (board[i][j] == '?')
        {
          *computerCol = j;
        }
      }

    }

  }

//columns
  for(int i = 0; i < N; i++)
  {
    if (sumC[i] - 2 == 0)
    {
      *computerCol = i;
      for (int j = 0; j < N; j++)
      {
        if (board[j][i] == '?')
        {
          *computerRow = j;
        }
      }

    }
  }

  //left diagonal
  if (sumLD - 2 == 0)
  {
    if ((board[0][0] == 'X') && (board[1][1] == 'X'))
    {
      *computerRow = 2;
      *computerCol = 2;
    }
    else if ((board[1][1] == 'X') && (board[2][2] == 'X'))
    {
      *computerRow = 0;
      *computerCol = 0;
    }
    else if ((board[0][0] == 'X') && (board[2][2] == 'X'))
    {
      *computerRow = 1;
      *computerCol = 1;
    }

  }

  //right diagonal
  if (sumRD - 2 == 0)
  {
    if ((board [0][2] == 'X') && (board[1][1] == 'X'))
    {
      *computerRow = 2;
      *computerCol = 0;
    }
    else if ((board[1][1] == 'X') && (board[2][0] == 'X'))
    {
      *computerRow = 0;
      *computerCol = 2;
    }
    else if ((board[0][2] == 'X') && (board[2][0] == 'X'))
    {
      *computerRow = 1;
      *computerCol = 1;
    }

  }


  if (blocked == 0)
  {
    return blocked;
  }
  else
  {
    return blocked;
    return *computerRow;
    return *computerCol;
  }

}
//function calls all of computer moves based on priority of "winning", "blocking" and then "random"
int  getComputerMove(char board[N][N], int * computerRow, int * computerCol, int userRow, int userCol){
/*
  This function determines computer's move in terms of row (computerRow) and column (computerCol)
  and outputs them to main. The computer first tries to find a winning spot for itself; if it doesn't
  find one, then it calls function computerPlaysRandom in its attempt to place its symbol in
  the same row or column as the user (userRow, userCol)
*/

   int winningSpot = 0;
   int blocked = 1;     //       this declaration is required if you attempt the bonus part

   winningSpot = computerPlaysToWin(board, computerRow, computerCol);

   if (!winningSpot)            // if computer does find a winning spot, then it plays to block the user
   {
	   computerPlaysRandom(computerRow, computerCol, userRow, userCol);

	   blocked = computerPlaysToBlock(board, computerRow, computerCol);

	   if (blocked == 0)
		   {
		   computerPlaysRandom(computerRow, computerCol, userRow, userCol);
		   }
   }

   return winningSpot;
}




