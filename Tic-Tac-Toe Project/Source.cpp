#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <Windows.h>

/*
* Tic-Tac-Toe:
* ------------
*1. Intro
*
*2. RNG flip (1d2) to determine who goes first.
*3. Display board
*4. Get response to mark board
*5. Update board
*6. Check to see if win condition met
*7. Check for stalemate.
*7. Next turn ask for decision
*8. Update Board
*9. Check if win condition met.
*10.Check for stalemate.
*11.Update score
*12.Ask to rematch
* 
* 
* To-Do:
* Program an AI to take user choice into consideration and block easy wins.....
*13.  END PROGRAM
*/
void intro(std::string&, int& , std::fstream&);
void displayBoard(char *space, char, int);
void markBoard(char, char *space);
void cpuDecision(char *space, char, char);
void checkWin(char [], int&, char, bool&, std::string&);
void defaultBoard(char *space, int);

int main()
{
	/************** DECLARING VARIABLES ***********/
	const int MAX = 10;
	char space[10];
	char retry;
	bool gameEnd;
	srand(time(0));

	//Player var
	int pcScore = 0;
	char pcMark;
	std::string name;

	//cpu var
	int cpuScore;
	char cpuMark;
	bool cpuFirst;
	std::string cpuName = "Computer";


	/*****  START OF PROGRAM   ****************/
	std::fstream file;
	intro(name, pcScore,file);

	//Retrieves user file to update score
/*	
	file.open(name, std::ios::in);
	if (file.fail())
	{
		std::cout << "Creating a new file for user..." << std::endl;
		file.open(name, std::ios::out);
		file.close();
	}
	else if (file)
	{
		std::cout << "Welcome back," << name << "." << std::endl;
		file >> pcScore;
		file.close();
	}
*/

	do
	{
		defaultBoard(space, MAX);
		retry = 'N';
		gameEnd = false;

//Determines who goes first
		std::cout << "Flipping coin...\n\n";
		cpuFirst = rand() % 2;

		if (cpuFirst == true)
		{
			std::cout << "Heads! You're going second.\n\n";
			cpuMark = 'X';
		}
		else
		{
			std::cout << "Tails! You go first\n\n";
			cpuMark = 'O';
		}
		pcMark = cpuFirst == true ? 'O' : 'X';
		system("pause");


		if (cpuFirst == true) //Used if cpu goes first
		{
			displayBoard(space, pcMark, pcScore);
			std::cout << "Computer's turn...\n";
			Sleep(1500);
			cpuDecision(space, cpuMark, pcMark);
			//Write code to make cpu move
		}

//Start of game loop
		do
		{	
			std::cout << pcMark << std::endl;
			//Player Turn
			displayBoard(space, pcMark, pcScore);
			std::cout << space[0] << std::endl;
			markBoard(pcMark, space);
			displayBoard(space, pcMark, pcScore);
			checkWin(space, pcScore, pcMark, gameEnd, name);
		
			if (gameEnd != true) {
				//CPU turn
				std::cout << "Computer's turn...\n";
				Sleep(1500);
				cpuDecision(space, cpuMark, pcMark);
				displayBoard(space, pcMark, pcScore);
				checkWin(space, cpuScore, cpuMark, gameEnd, cpuName);
			}
		} while (gameEnd != true);

		std::cout << "Wuould you like to play again?\n\n" <<
					 "Y/N" << std::endl;
		std::cin >> retry;
		std::cin.ignore();

	} while (toupper(retry) == 'Y');

	file.open(name, std::ios::out);
	file << pcScore;
	file.close();
}




/*******************************************************************
********************************************************************
*****************  FUNCTION DEFINITIONS ****************************
********************************************************************/


void intro(std::string& name, int& pcScore, std::fstream& file) //Gets name of player
{
	char choice;


	std::cout << "Welcome to my 2nd project, \"Tic-Tac-Toe\"\n\n";
	system("pause");

	std::cout << "We'll begin by asking for your name.\n\n";
	system("pause");


	do
	{
		std::cout << "Please enter your name: ";
		std::getline(std::cin, name);

		std::cout << "\n\nName:" << name <<
			"\n\nIs this correct? Y/N\n";

		std::cin >> choice;
		std::cout << std::endl;
		std::cin.ignore();
	} while (toupper(choice) == 'N');

//Gets user file
	file.open(name, std::ios::in);
	if (file.fail())				// Creates user file if it doesn't exist.
	{
		std::cout << "Creating a new file for user..." << std::endl;
		file.open(name, std::ios::out);
		file.close();
		system("pause");
	}
	else if (file)					// If exists, updates pcScore
	{
		std::cout << "Welcome back, " << name << "." << std::endl;
		file >> pcScore;
		file.close();
		system("pause");
	}

	std::cout << "Next we'll flip a coin to see who goes first. You'll be tails.\n\n";
	system("pause");
}



void displayBoard(char *square, char mark, int score)  //Updates and displays the board
{
	system("cls");

	std::cout << "     |     |     " << std::endl;
	std::cout << "  " << square[0] << "  |  " << square[1] << "  |  " << square[2] << std::endl;
	std::cout << "     |     |     " << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "     |     |     " << std::endl;
	std::cout << "  " << square[3] << "  |  " << square[4] << "  |  " << square[5] << std::endl;
	std::cout << "     |     |     " << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "     |     |     " << std::endl;
	std::cout << "  " << square[6] << "  |  " << square[7] << "  |  " << square[8] << std::endl;
	std::cout << "     |     |     " << std::endl;

	std::cout << "You are: " << mark << std::endl;
	std::cout << "Wins:" << score << std::endl;

}



void markBoard(char mark, char *square) //Marks board with X's and O's
{
	char choice; // Used to choose space on board
	int x;
	do
	{
		std::cout << "Choose a number to mark the space\n\n";
		std::cin >> choice;
		std::cin.ignore();

		for (x = 0; x < 10 && x != -1; x++) 
		{
			if (square[x] == choice) 
			{
				square[x] = mark;
				x = -2;  //Used to exit FOR LOOP and DO-WHILE LOOP
			}
			else if (square[x] == '!')
			{
				std::cout << "Invalid space. Please choose another number\n\n";
			}
		}
	} while (x != -1);	
}





void checkWin(char square[], int &score, char mark, bool &gameEnd, std::string &name) //Determines if win condition is met
{
//Straight Horizontal
	if (square[0] == square[1] && square[1] == square[2] && square[0] == mark) {
		score++;
		gameEnd = true;
		std::cout << name << " wins!\n\n";
	}
	if (square[3] == square[4] && square[4] == square[5]) {
		score++;
		gameEnd = true;
		std::cout << name << " wins!\n\n";
	}
	if (square[6] == square[7] && square[7] == square[8]) {
		score++;
		gameEnd = true;
		std::cout << name << " wins!\n\n";
	}

//Straight Vertical
	if (square[0] == square[3] && square[3] == square[6]) {
		score++;
		gameEnd = true;
		std::cout << name << " wins!\n\n";
	}
	if (square[1] == square[4] && square[4] == square[7]) {
		score++;
		gameEnd = true;
		std::cout << name << " wins!\n\n";
	}
	if (square[2] == square[5] && square[5] == square[8]) {
		score++;
		gameEnd = true;
		std::cout << name << " wins!\n\n";
	}

//Diagonal
	if (square[0] == square[4] && square[4] == square[8]) {
		score++;
		gameEnd = true;
		std::cout << name << " wins!\n\n";
	}
	if (square[2] == square[4] && square[4] == square[6]) {
		score++;
		gameEnd = true;
		
		std::cout << name << " wins!\n\n";
	}

//Tie
	if (square[0] != '1' && square[1] != '2' && square[2] != '3'
		&& square[3] != '4' && square[4] != '5' && square[5] != '6'
		&& square[6] != '7' && square[7] != '8' && square[8] != '9') 
	{
		std::cout << "TIE!" << std::endl;
		gameEnd = true;
	}
}

void defaultBoard(char *space, int MAX) 
{
	char y = '1';
	for (int x = 0; x < MAX; x++)
	{
		if (x < 9){
			space[x] = y;
				y++;
		}

		else if (x == 9){
			space[x] = '!';
		}
	}
}


void cpuDecision(char* ar, char cpuMark, char pcMark)
{
//1st priority - Winning move
	std::cout << "In function" << std::endl;
	Sleep(1000);

//2nd priority - Defend
	//Row: 1-1
		if(ar[0] == ar[1] && ar[2] == '3'){
			ar[2] = cpuMark;	}
	//Row: 1-2
		else if (ar[2] == ar[1] && ar[1] == '1') {
			ar[2] = cpuMark;	}
	//Row: 1-3
		else if (ar[0] == ar[2] && ar[1] == '2') {
			ar[1] = cpuMark;	}
	//Row: 2-1
		else if (ar[3] == ar[4] && ar[5] == '6') {
			ar[5] = cpuMark;	}
	//Row: 2-2
		else if (ar[5] == ar[4] && ar[3] == '4') {
			ar[3] = cpuMark;	}
	//Row: 2-3
		else if (ar[3] == ar[5] && ar[4] == '5') {
			ar[4] = cpuMark;	}
	//Row: 3-1
		else if (ar[6] == ar[7] && ar[8] == '9') {
			ar[8] = cpuMark;	}
	//Row: 3-2
		else if (ar[8] == ar[7] && ar[6] == '7') {
			ar[6] = cpuMark;	}
	//Row: 3-3
		else if (ar[6] == ar[8] && ar[7] == '8') {
			ar[7] = cpuMark;	}
	//Col: 1-1
		else if (ar[0] == ar[3] && ar[6] == '7') {
			ar[6] = cpuMark;	}
	//Col: 1-2
		else if (ar[6] == ar[3] && ar[0] == '1') {
			ar[0] = cpuMark;	}
	//Col:: 1-3
		else if (ar[0] == ar[6] && ar[3] == '4') {
			ar[3] = cpuMark;	}
	//Col: 2-1
		else if (ar[1] == ar[4] && ar[7] == '8') {
			ar[7] = cpuMark;	}
	//Col: 2-2
		else if (ar[7] == ar[4] && ar[1] == '2') {
			ar[1] = cpuMark;	}
	//Col: 2-3
		else if (ar[1] == ar[7] && ar[4] == '5') {
			ar[4] = cpuMark;	}
	//Col: 3-1
		else if (ar[2] == ar[5] && ar[8] == '9') {
			ar[8] = cpuMark;	}
	//Col: 3-2
		else if (ar[8] == ar[5] && ar[2] == '3') {
			ar[2] = cpuMark;	}
	//Col: 3-3
		else if (ar[8] == ar[2] && ar[5] == '6') {
			ar[5] = cpuMark;	}
	//Dia: 1-1
		else if (ar[0] == ar[4] && ar[8] == '9') {
			ar[8] = cpuMark;	}
	//Dia: 1-2
		else if (ar[8] == ar[4] && ar[0] == '1') {
			ar[0] = cpuMark;	}
	//Dia: 1-3
		else if (ar[0] == ar[8] && ar[4] == '5') {
			ar[4] = cpuMark;	}
	//Dia: 2-1
		else if (ar[2] == ar[4] && ar[6] == '7') {
			ar[6] = cpuMark;	}
	//Dia: 2-2
		else if (ar[6] == ar[4] && ar[2] == '3') {
			ar[2] = cpuMark;	}
	//Dia: 2-3
		else if (ar[2] == ar[6] && ar[4] == '5') {
			ar[4] = cpuMark;	}

		else //3rd priority - Random Space
		{
			std::cout << "Making random Move" << std::endl;
			Sleep(1500);
			bool endLoop = false; //Used to end loop
			do
			{
				int x = rand() % 9;
				if (ar[x] != 'X' && ar[x] != 'O')
				{
					ar[x] = cpuMark;
					endLoop = true;

				}	
			} while (endLoop != true);
			}		
}
