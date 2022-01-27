#include "linearSystemClass.h"
#include "matrixClass.h"
#include <iostream>
#include <conio.h>

int main()
{
	std::cout << "Linear system solver: This program solves equations of the form Ax=b" << std::endl << std::endl;
	matrix A;
	matrix x;
	matrix b;
	matrix residual;

	std::cout << "Enter details for the matrix A:" << std::endl;
	A.getMatrix();

	std::cout << "Enter details for the matrix b:" << std::endl;
	b.getMatrix();

	matrix ACopy;
	matrix bCopy;

	ACopy.copyMatrix(A);
	bCopy.copyMatrix(b);

	std::cout << std::endl << "----------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << "Equation to be solved:" << std::endl << std::endl;

	ACopy.displayMatrix();
	std::cout << "********************************************" << std::endl << std::endl << "x" << std::endl << std::endl << "============================================" << std::endl << std::endl;
	bCopy.displayMatrix();

	std::cout << std::endl << "----------------------------------------------------------------------------------------------------------" << std::endl;


	linearSystem mySystem(A, b);
	mySystem.GESolver();
	x = mySystem.returnSolution();


	std::cout << std::endl << "Solution:" << std::endl << std::endl;
	x.displayMatrix();

	std::cout << std::endl << std::endl << "----------------------------------------------------------------------------------------------------------" << std::endl;
	
	std::cout << std::endl << "Residual vector (b - A*solution): " << std::endl << std::endl;
	matrix Ax = ACopy * x;
	residual = bCopy - Ax;
	residual.displayMatrix();
	std::cout << std::endl;



	std::cout << "press anything to exit" << std::endl;
	_getch();
	return 0;
}