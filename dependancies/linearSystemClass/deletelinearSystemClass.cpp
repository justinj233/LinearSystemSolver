#include "linearSystemClass.h"
#include <iostream>

linearSystem::linearSystem(matrix transformation, matrix output) : A(transformation), x(matrix::matrix(transformation.returncolumns(), 1)), b(output)
{ }

void linearSystem::GESolver()
{
	if (A.returnrows() == A.returncolumns())
	{
		int n = A.returnrows();
		for (int i = 1; i <= (n - 1); i++)
		{
			partialPivot(i); 
			if (*A.returnElement(i, i) == 0) //check for a zeros on the diagonal to avoid division by zero.
			{
				std::cout << "Pivot is zero Gaussian Elimination failed." << std::endl;
				return;
			}
			introduceZeros(i); 
			//A.displayMatrix();  uncomment these lines to output matricies after each transformation
			//b.displayMatrix(); 
		}
		backSubstitution();
	}
}

void linearSystem::partialPivot(int c)
{
	if (A.returnrows() == A.returncolumns())
	{
		int i= c;
		int j = 1;

		while ((i + j) <= A.returnrows())
		{
			if (*A.returnElement(i, c) >= *A.returnElement(i + j, c))
			{
				j++;
			}
			else
			{
				i += j;
				j = 1;
			}
		}

		//switch rows c and i of A
		if (i != c)
		{
			float* temprow = new float[A.returncolumns() - (c - 1)]();

			for (int n = c; n <= A.returncolumns(); n++)  //copy row c to temp
			{
				*(temprow + (n - c)) = *A.returnElement(c, n);
			}
			for (int n = c; n <= A.returncolumns(); n++) //copy row i to row c
			{
				*A.returnElement(c, n) = *A.returnElement(i, n);
			}
			for (int n = c; n <= A.returncolumns(); n++) //copy temp to row i
			{
				*A.returnElement(i, n) = *(temprow + (n - c));
			}

			delete[] temprow;

			//switch rows c and i of b
			float temp = *b.returnElement(c, 1);
			*b.returnElement(c, 1) = *b.returnElement(i, 1);
			*b.returnElement(i, 1) = temp;
		}
	}
}


void linearSystem::introduceZeros(int c)
{
	float* temp = new float[A.returnrows() - c](); //stores the lower diagonal elements in column c before the introduction of zeros

	for (int i = (c + 1); i <= A.returnrows(); i++) //copy lower diagonal elements of column c to temp
	{
		*(temp + (i - (c + 1))) = *A.returnElement(i, c);
	}

	for (int i = (c + 1); i <= A.returnrows(); i++) //introduce zero into column c row i
	{
		for (int j = c; j <= A.returncolumns(); j++) //add -(*A.returnElement(i, c))/(*A.returnElement(c, c)) times row c to row i.
		{
			*A.returnElement(i, j) += (-(*(temp + (i - (c + 1)))) / (*A.returnElement(c, c))) * (*A.returnElement(c, j));
		}
		*b.returnElement(i, 1) += (-(*(temp + (i - (c + 1)))) / (*A.returnElement(c, c))) * (*b.returnElement(c, 1)); // Apply the same to matrix b transformation to b.
	}
	delete[] temp;
}

matrix linearSystem::returnSolution() const
{
	return matrix(x.returnrows(), 1, x.returnElement(1, 1));
}

void linearSystem::backSubstitution()
{
	for (int i = x.returnrows(); i >= 1; i--)
	{
		float sum = 0;
		for (int j = (i + 1); j <= x.returnrows(); j++)
		{
			sum += (*x.returnElement(j, 1)) * (*A.returnElement(i, j));
		}
		*(x.returnElement(i, 1)) = (*(b.returnElement(i, 1)) - sum) / *(A.returnElement(i, i));
	}
}
