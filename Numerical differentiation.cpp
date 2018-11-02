#include <iostream>
using namespace std;

#define f(xi) cos(xi)
#define ff(xi) -sin(xi)
#define pi  3.14159265358979323846

double point = pi / 3, // Required point
exact,	// Exact solution
h,		// Required h
ffForward, // Forward difference
ffBackward, // Backward difference
ffCentral, // Central difference
iMinOne,	// Fi-1
iPlusOne;	// Fi+1

			// Get the exact solution for the equation at the known point
void solveExact() {
	exact = ff(point);
	cout << "Exact solution = " << exact << endl;
}

// Get Fi+1 and Fi-1
void getStepValues() {
	iMinOne = f(point - h);
	iPlusOne = f(point + h);
	cout << "Fi+1 = " << iPlusOne << endl;
	cout << "Fi-1 = " << iMinOne << endl;
}

// Solve the Forward difference
void solveForward() {
	ffForward = (iPlusOne - f(point)) / h;
	cout << "Forward result = " << ffForward << endl;
}

void solveBackward() {
	ffBackward = (f(point) - iMinOne) / h;
	cout << "Backward result = " << ffBackward << endl;
}

// Solve the central difference
void solveCentral() {
	ffCentral = (iPlusOne - iMinOne) / (2 * h);
	cout << "Central result = " << ffCentral << endl;
}

// Calculate the errors of forward difference and central difference
void calculateErrors() {
	double forwardError, centralError, backwardError;
	forwardError = abs(exact - ffForward);
	backwardError = abs(exact - ffBackward);
	centralError = abs(exact - ffCentral);
	cout << "The error from forward = " << forwardError << endl;
	cout << "The error from backward = " << backwardError << endl;
	cout << "The error from central = " << centralError << endl;
}

int main() {
	system("cls");
	cout << "Numerical Difference for equation cos(xi) at point pi/3\n\n";
	cout << "Enter h: ";
	cin >> h;
	solveExact();
	getStepValues();
	solveForward();
	solveCentral();
	solveBackward();
	calculateErrors();
	cout << "Do you want to try again? (Y/Any Key for No): ";
	char choose;
	cin >> choose;
	if (choose == 'Y' || 'y')
		main();
	else
		return 0;
}