#pragma once
#include "matrixClass.h"

class linearSystem
{
	matrix A;
	matrix x;
	matrix b;

public:
	linearSystem(matrix transformation, matrix output);

	void GESolver(); //gaussian elimination solver with partial pivoting

	void partialPivot(int c); //sets the pivot to the largest element below the diagonal in column c of the matrix A. Any transformation applied to A is also applied to b.

	void introduceZeros(int c); //introduces zeros below the diagonal in column c by applying a step of gaussian elimination. Any transformation applied to A is also applied to b.

	matrix returnSolution() const;
	
	void backSubstitution();

	
};
