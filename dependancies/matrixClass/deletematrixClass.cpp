#include "matrixClass.h"
#include <iomanip>
#include <iostream>

//------------------------------------------------------------------------------------------------------------------------------------
// CONSTRUCTORS

matrix::matrix() : rows(0), columns(0), elements(NULL)
{ }


matrix::matrix(int r, int c) : rows(r), columns(c)
{ 
	int totalElements = r * c;
	elements = new float[totalElements]();
}

matrix::matrix(int r, int c, float* e) : rows(r), columns(c), elements(e)
{ }



//------------------------------------------------------------------------------------------------------------------------------------
// MEMBER FUNCTIONS

void matrix::copyMatrix(matrix A)
{
	int totalElements = rows * columns;
	int totalElementsA = A.returnrows() * A.returncolumns();

	rows = A.returnrows();
	columns = A.returncolumns();

	if (totalElements >= totalElementsA)
	{
		for (int i = 1; i <= rows; i++)
		{
			for (int j = 1; j <= columns; j++)
			{
				//std::cout << "CASE 1 iteration: i = " << i << "   j = " << j << std::endl;   //uncomment to output details about the copying
				*returnElement(i, j) = *A.returnElement(i, j);
			}
		}
		
	}
	else
	{
		elements = new float[totalElementsA];
		for (int i = 1; i <= rows; i++)
		{
			for (int j = 1; j <= columns; j++)
			{
				//std::cout << "CASE 2 iteration: i = " << i << "   j = " << j << std::endl;   //uncomment to output details about the copying
				*returnElement(i, j) = *A.returnElement(i, j);
			}
		}
	}
}



void matrix::getMatrix()
{
	std::cout << "Enter number of rows:" << std::endl;
	std::cin >> rows;
	std::cout << "Enter number of columns:" << std::endl;
	std::cin >> columns;
	std::cout << std::endl;

	int totalElements = rows * columns;
	elements = new float[totalElements];

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			std::cout << "Enter element " << (i + 1) << "," << (j + 1) << ":" << std::endl;
			std::cin >> *(elements + (i * columns + j));
		}
	}
	std::cout << std::endl;
}



void matrix::displayMatrix() const 
{
	for (int i = 1; i <= rows; i++)
	{
		for (int j = 1; j <= columns; j++)
		{
			std::cout << std::setw(10) << std::left << *returnElement(i, j) << " ";
			if (j == (columns))
			{
				std::cout << std::endl << std::endl;
			}
		}
	}
	std::cout << std::endl;
}



int matrix::returnrows() const
{
	return rows;
}

int matrix::returncolumns() const
{
	return columns;
}

float* matrix::returnElement(int i, int j) const
{
	if ((i > rows) || (j > columns))
	{
		std::cout << "Attempting to access element " << i << "," << j << " which not in this matrix. Returning a pointer to element 1,1 instead." << std::endl;
		return elements;
	}
	return (elements + ((i - 1) * columns + (j - 1)));
}


//------------------------------------------------------------------------------------------------------------------------------------
//OPERATOR OVERLOADS

matrix matrix::operator*(matrix X) const
{
	if (columns == X.returnrows())
	{
		int totalElements = rows * X.returncolumns();
		float* temp = new float[totalElements]();

		for (int j = 1; j <= X.returncolumns(); j++)
		{
			for (int i = 1; i <= rows; i++)
			{
				for (int k = 1; k <= columns; k++)
				{
					*(temp + ((i - 1) * X.returncolumns() + (j - 1))) += (*returnElement(i, k)) * (*X.returnElement(k, j));
				}
			}
		}
		return matrix(rows, X.returncolumns(), temp);
	}
	else
	{
		std::cout << "Matricies are not compatible, cannot perform multiplication." << std::endl;
		return matrix();
	}
}

matrix matrix::operator+(matrix X) const
{
	if ( (rows == X.returnrows()) && (columns == X.returncolumns()) )
	{
		int totalElements = rows * columns;
		float* tempStorage = new float[totalElements];
		matrix temp(rows, columns, tempStorage);

		for (int i = 1; i <= rows; i++)
		{
			for (int j = 1; j <= columns; j++)
			{
				*temp.returnElement(i, j) = *returnElement(i, j) + *X.returnElement(i, j);
			}
		}
		return temp;
	}
	else
	{
		std::cout << "Matricies are not the same size, cannot perform addition." << std::endl;
		return matrix();
	}
}

matrix matrix::operator-(matrix X) const
{
	if ((rows == X.returnrows()) && (columns == X.returncolumns()))
	{
		int totalElements = rows * columns;
		float* tempStorage = new float[totalElements];
		matrix temp(rows, columns, tempStorage);

		for (int i = 1; i <= rows; i++)
		{
			for (int j = 1; j <= columns; j++)
			{
				*temp.returnElement(i, j) = *returnElement(i, j) - *X.returnElement(i, j);
			}
		}
		return temp;
	}
	else
	{
		std::cout << "Matricies are not the same size, cannot perform subtraction." << std::endl;
		return matrix();
	}
}



//------------------------------------------------------------------------------------------------------------------------------------
