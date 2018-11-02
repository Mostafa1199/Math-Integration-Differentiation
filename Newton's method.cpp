#include <iostream>
#include <math.h>
#include <queue>
#include <fstream>
#include <windows.h>
#include <iomanip>
using namespace std;

/*Equation & it's derivatives */
#define f(x) pow(x,2)+(10*cos(x));
#define fd(x) (2*x)-(10*sin(x));
#define fdd(x) 2-(10*cos(x));

queue<double> points, As, Bs;


void welcomeScreen();

int startPoint();

void setValue(double &);

void estimate(double &);

bool assureValue(double);

void endingPoint(double &);

void getNextPoint(int, double &);

void stopDecimal(double, double &);

void show();

int main() {

	double startingPoint;

	welcomeScreen();

	if (startPoint() == 1) 
	{
		setValue(startingPoint);
	}
	else 
	{
		estimate(startingPoint);
	}

	system("cls");
	
	endingPoint(startingPoint);

	show();
	system("pause");
}

void welcomeScreen(){
	cout << "\t\t---------------------------" << endl;
	cout << "\t\t-----| Newton Solver |-----" << endl;
	cout << "\t\t---------------------------" << endl;

	cout << endl;
}

int startPoint() {
	int choice;

	cout << "1. Enter start point" << endl;
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
		welcomeScreen();
		startPoint();
	}
}

void setValue(double &point)
{
	system("cls");
	welcomeScreen();

	cout << "Enter a point: ";
	cin >> point;

	if(!assureValue(point))
	{
		cout << "The value you've entered can't be used in this system!" << endl;

		if (startPoint() == 1)
		{
			setValue(point);
		}
		else
		{
			estimate(point);
		}
	}
}

bool assureValue(double point)
{
	double A = f(point);
	double B = fd(point);
	double C = fdd(point);

	double assureVal = (A * C) / pow(B, 2);

	if (assureVal < 0)
		assureVal *= -1;

	if (assureVal < 1 && assureVal > 0)
	{
		points.push(point);
		return true;

	}
	else
		return false;
}

void estimate(double &point)
{
	double negativeDEC = 0;
	double positiveINC = 0;

	double step = 0.01;

	if (assureValue(0))
	{
		point = 0;
		return;
	}

	while (true)
	{
		positiveINC += step;

		if (assureValue(positiveINC))
		{
			point = positiveINC;
			return;
		}

		negativeDEC -= step;

		if (assureValue(negativeDEC))
		{
			point = negativeDEC;
			return;
		}
	}
}

void endingPoint(double &point)
{
	system("cls");
	welcomeScreen();
	cout << "\t\t Point = " << point << endl;


	cout << "How you want to continue?" << endl;

	int choice;
	cout << "1. Number of iteration" << endl;
	cout << "2. Decimal stop" << endl;

	cout << "Your choice: ";
	cin >> choice;

	switch(choice)
	{
	case 1:
		cout << "For how many iteration?" << endl;
		cout << "Your choice: ";
		cin >> choice;

		if (choice > 0)
			getNextPoint(choice, point);
		else
			endingPoint(point);

		break;

	case 2:
		cout << "After how many decimal points?" << endl;
		cout << "Your choice: ";
		cin >> choice;

		if (choice > 0)
			stopDecimal(choice, point);
		else
			endingPoint(point);

		break;

	default:
		endingPoint(point);
	}
}

void getNextPoint(int repeat, double &point)
{
	for (int i = 0; i < repeat; i++)
	{
		double A = f(point);
		As.push(A);

		double B = fd(point);
		Bs.push(B);

		point = point - (A/B);
		points.push(point);
	}
}

void stopDecimal(double tolerance, double &point)
{
	tolerance = 1 / pow(10, ++tolerance);

	int counter = 0;
	double temp = point;

	do
	{
		counter++;
		temp = point;

		double A = f(point);
		As.push(A);

		double B = fd(point);
		Bs.push(B);

		point = point - (A / B);
		points.push(point);

		cout << point - temp << endl;
	} 
	while (abs(point - temp) >= tolerance);
}

void show()
{
	if (remove("saved_data.csv") != 0)
		perror("Error deleting file");

	cout << "Opening Excel file....";

	ofstream outdata;
	outdata.open("saved_data.csv", ios::app);

	outdata << "iteration,Point,A,B," << endl;
	int i = 0;
	while (!Bs.empty())
	{
		outdata << i << "," << points.front() << "," << As.front() << "," << Bs.front() << endl;

		points.pop();
		As.pop();
		Bs.pop();
		i++;
	}
	ShellExecute(NULL, "open", "saved_data.csv", NULL, NULL, SW_SHOWDEFAULT);
}