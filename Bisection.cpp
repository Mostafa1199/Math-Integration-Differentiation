#include <iostream>
#include <math.h>
#include <queue>
#include <fstream>
#include <windows.h>
#include <iomanip>
using namespace std;

#define F(x) x-cos(x)

/* A queue to hold all of our variables */
queue<double> As, Bs, Cs, FCs;

/* Prototypes */

/* Saying Hi */
void WelcomeScreen();

/* Let the user choose the way he want to
go with for starting poitns whether to
pick them or to let the program estimate them */
int startPoint();

/* Let the user enter 2 different points */
void setNumbers(double &, double &, double, double);
/* Checks the sign of the functino of numbers */
bool SignCheck(double, double);
/* Make the program think of 2 numbers that fits the equation */
void estimate(double &, double &, double);

/* Let the user choose how far is he going */
void endingPoint(double &, double &, double &);

/* The progress of choosing midpoint */
// case 1: certain number of iteration
void getNextPoint(int, double &, double &, double &);
// case 2: certain decimal stop
void stopDecimal(double, double &, double &, double &);

/* Opens the excel file */
void show();

/*Main body*/
void main()
{
	double point0 = 0, point1 = 0;

	// Negative starting point
	double A = -1000; // nega
	// Positive starting point
	double B = -1000; // pos

	// Temp point
	double C;

	WelcomeScreen();

	if (startPoint() == 1)
		setNumbers(A, B, point0, point1);
	else
		estimate(A, B, 0);

	system("cls");

	endingPoint(A, B, C);

	show();

	cin >> C;
}
/*Functions*/

/*Welcome Screen*/
void WelcomeScreen()
{
	cout << "\t\t--------------------------" << endl;
	cout << "\t\t---| BiSection Solver |---" << endl;
	cout << "\t\t--------------------------" << endl;

	cout << endl;
}

/*Choose whether to add certain points or let the program choose em*/
int startPoint()
{
	int choice;
	cout << "1. Enter starting points" << endl;
	cout << "2. Let the program estimate" << endl;
	cout << "Choice: ";
	cin >> choice;

	switch (choice)
	{
	case 1:
	case 2:

		return choice;
		break;

	default:

		system("cls");
		WelcomeScreen();
		startPoint();
	}
}

/* The user puts 2 numbers */
void setNumbers(double &negative, double &positive, double point0, double point1)
{
	cout << "Point 1: ";
	cin >> point0;

	cout << "Point 2: ";
	cin >> point1;

	if (SignCheck(point0, point1) == false)
		setNumbers(negative, positive, point0, point1);
	//////
	if (F(point0) < 0)
	{
		negative = point0;
		positive = point1;

	}
	else
	{
		positive = point0;
		negative = point1;
	}
}

/*Checks the sign of the functino of numbers*/
bool SignCheck(double num0, double num1)
{
	if (F(num0)*F(num1) < 0)
		return true;
	else
		return false;
}

/*The program estimates 2 numbers that correct the equation*/
void estimate(double &negative, double &positive, double start)
{
	if (negative != -1000 && positive != -1000)
	{
		if (!SignCheck(negative, positive))
			estimate(negative, positive, start);

		As.push(negative);
		Bs.push(positive);
		return;
	}

	if (F(start) < 0)
	{
		negative = start;
		estimate(negative, positive, ++start);
	}
	else
	{
		positive = start;
		estimate(negative, positive, --start);
	}
}

/*The user chooses how to continue with specific iteration or decimal stops*/
void endingPoint(double &negative, double &positive, double &midPoint)
{
	WelcomeScreen();

	cout << "How you want to continue?" << endl;

	int choice;
	cout << "1. Number of iteration" << endl;
	cout << "2. Decimal stop" << endl;

	cout << "Your choice: ";
	cin >> choice;

	if (choice == 1)
	{
		cout << "For how many iteration?" << endl;
		cout << "Your choice: ";
		cin >> choice;
		if (choice > 0)
			getNextPoint(choice, negative, positive, midPoint);
		else
			endingPoint(negative, positive, midPoint);
	}

	else if (choice == 2)
	{
		cout << "After how many decimal points?" << endl;
		cout << "Your choice: ";
		cin >> choice;

		if (choice > 0)
			stopDecimal(choice, negative, positive, midPoint);
		else
			endingPoint(negative, positive, midPoint);
	}
}

/*When the user choose to continue with specific iterations*/
void getNextPoint(int repeat, double &negative, double &positive, double &midPoint)
{
	for (int i = 0; i < repeat; i++)
	{
		As.push(negative);
		Bs.push(positive);

		midPoint = (negative + positive) / 2;

		if (F(midPoint) < 0)
			negative = midPoint;
		else
			positive = midPoint;

		FCs.push(F(midPoint));
		Cs.push(midPoint);
	}
}

/*When the user choose to continue with specific decimal stops*/
void stopDecimal(double tolerance, double &negative, double &positive, double &midPoint)
{
	tolerance = 1 / pow(10, ++tolerance);

	// 1 / (10^3) = 0.001

	int counter = 0;

	midPoint = -1000;

	double temp;

	do
	{
		temp = midPoint;  // -1000

		midPoint = (negative + positive) / 2;

		if (F(midPoint) < 0)
			negative = midPoint;
		else
			positive = midPoint;

		counter++;

		As.push(negative); 
		Bs.push(positive);
		Cs.push(midPoint);
		FCs.push(F(midPoint));
	}

	while (abs(midPoint - temp) >= tolerance);

	//1.5-1.49 = 0.01

	cout << "\nRepeat time: " << counter << endl;
	cout << "Min: " << tolerance << endl;
}

/*Creates Excel file and opens it*/
void show()
{
	if (remove("saved_data.csv") != 0)
		perror("Error deleting file");

	cout << "Opening Excel file....";

	ofstream outdata;
	outdata.open("saved_data.csv", ios::app);

	outdata << "iteration,A,B,C,F(C)" << endl;
	int i = 0;

	while (!Cs.empty())
	{
		outdata << i << "," << As.front() << "," << Bs.front() << "," << Cs.front() << "," << FCs.front() << endl;

		As.pop();
		Bs.pop();
		Cs.pop();
		FCs.pop();
		i++;
	}

	ShellExecute(NULL, "open", "saved_data.csv", NULL, NULL, SW_SHOWDEFAULT);
}