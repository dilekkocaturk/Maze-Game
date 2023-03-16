#include<iostream>
#include<stdlib.h>
#include<time.h>
#include <Windows.h>
#include <conio.h>
#define MAXSIZE 100
#include <string>
#include <fstream>

using namespace std;

int maze[MAXSIZE][MAXSIZE];
char giris;

void generateMaze(int maze[][MAXSIZE], int size);
void instructions();
void charyaz();
void gotoXY(int x, int y);
void move(int size, ofstream& outtext);
void monsterYaz();
void goldYaz();

int main() {

	int size, a, b;

	srand(time(NULL));

	ofstream outFile;
	outFile.open("outputs.txt");
	if (!outFile) {
		cout << "Output file could not be opened! Terminating!" << endl;
		return 1;
	}

	cout << "\t\t\t\t\t\tWelcome to Maze Game!" << endl;
	cout << "Enter number of labyrinth size(at least 10 and at most 100): ";
	cin >> size;

	if (size < 10 || size > 100)
	{
		system("pause");
		exit(0);
	}

	instructions();

	generateMaze(maze, size);

	for (int i = 0; i < size; i++) {

		for (int j = 0; j < size; j++) {

			if (maze[i][j] == 'm')
			{
				monsterYaz();
			}
			else if (maze[i][j] == 'g')
			{
				goldYaz();
			}
			else {
				cout << maze[i][j] << " ";
			}
		}
		cout << endl;
	}

	move(size, outFile);

	cout << endl << endl << endl << endl << endl;
	outFile.close();
	system("pause");
	return 0;
}

void generateMaze(int maze[][MAXSIZE], int size) {

	int a, b;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j || j == i + 1)
			{
				maze[i][j] = 0;
			}
			else
			{
				maze[i][j] = rand() % 2;
			}
		}
	}

	for (int i = 0; i < size; i++) {

		a = (rand() % size);
		b = (rand() % size);
		if (maze[a][b] != 0)
		{
			maze[a][b] = 'm';
		}
	}

	for (int i = 0; i < size / 2; i++) {

		a = (rand() % size);
		b = (rand() % size);

		maze[a][b] = 'g';
	}
}
void gotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void move(int size, ofstream& outtext)
{
	int x = 0;
	int y = 15;
	int xCln = 0;
	int yCln = 15;
	int goldNum = 0;

	outtext << "The Way Out of the Labyrinth" << endl << endl;
	outtext << " x\ty" << endl;

	while (true)
	{
		gotoXY(xCln, yCln);
		cout << " ";

		outtext << " " << y - 15 << "\t" << x / 2 << endl;

		gotoXY(x, y);
		charyaz();
		giris = _getch();
		xCln = x;
		yCln = y;

		if (giris == 'w')
		{
			if (y != 15)
			{
				y -= 1;
			}
		}
		else if (giris == 's')
		{
			if (y != 15 + size - 1)
			{
				y += 1;
			}
		}
		else if (giris == 'a')
		{
			if (x != 0)
			{
				x -= 2;
			}
		}
		else if (giris == 'd')
		{
			if (x < 2 * (size - 1))
			{
				x += 2;
			}
		}
		if (maze[y - 15][x / 2] == 1)
		{
			x = xCln;
			y = yCln;
		}
		else if (maze[y - 15][x / 2] == 'g' && y == 15 + size - 1)
		{
			goldNum++;
			cout << endl << endl << endl;
			cout << "\t\t\t\t\tCongratulations! You won!\n";
			cout << "The number of gold you collect is: " << goldNum;

			gotoXY(xCln, yCln);
			cout << " ";
			outtext << " " << y - 15 << "\t" << x / 2 << endl;

			gotoXY(x, y);
			charyaz();
			break;
		}
		else if (maze[y - 15][x / 2] == 'g')
		{
			goldNum++;
		}
		else if (maze[y - 15][x / 2] == 'm')
		{
			system("CLS");
			cout << "\t\t\t\t\t\tWelcome to Maze Game!" << endl;
			cout << "Enter number of labyrinth size: " << size;

			instructions();

			cout << "You reached the monster. Game started again. Try again.." << endl;

			for (int i = 0; i < size; i++) {

				for (int j = 0; j < size; j++) {

					if (maze[i][j] == 'm')
					{
						monsterYaz();
					}
					else if (maze[i][j] == 'g')
					{
						goldYaz();
					}
					else {
						cout << maze[i][j] << " ";
					}
				}
				cout << endl;
			}

			goldNum = 0;
			x = 0;
			y = 15;
			xCln = 0;
			yCln = 15;
			gotoXY(x, y);
			charyaz();

			int d = outtext.tellp();
			outtext.seekp(38, ios::beg);
			for (int i = 0; i < d; i++)
			{
				outtext.write(" ", ios::cur);
			}
			outtext.seekp(38, ios::beg);
		}
		else if (maze[y - 15][x / 2] == 0 && y == 15 + size - 1)
		{
			cout << endl << endl << endl;
			cout << "\t\t\t\t\tCongratulations! You won!\n";
			cout << "The number of gold you collect is: " << goldNum;

			gotoXY(xCln, yCln);
			cout << " ";

			outtext << " " << y - 15 << "\t" << x / 2 << endl;

			gotoXY(x, y);
			charyaz();
			break;
		}
	}
}
void charyaz()
{
	cout << char(175);
}
void monsterYaz()
{
	cout << "M ";
}
void goldYaz()
{
	cout << "G ";
}
void instructions() {
	cout << endl << "G -> represents the golds.\tM -> represents the monsters." << endl << endl;
	cout << "1s are walls.\t\t\t0s are roads." << endl << endl;
	cout << "You will start at the point (0,0) of the maze. Your exit point is '0' on the last line of the maze,"
		<< " which you can reach without getting stuck.(You can also have a gold at your exit point instead of 0)\n\n";
	cout << "Press 'd' to move right (Enter lower case!)"
		<< "\nPress 'a' to move left  (Enter lower case!)"
		<< "\nPress 'w' to move up    (Enter lower case!)"
		<< "\nPress 's' to move down  (Enter lower case!)" << endl << endl;
}