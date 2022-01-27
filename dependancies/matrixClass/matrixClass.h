#pragma once

class matrix
{
	int rows;
	int columns;
	float* elements; //ptr to an array of all the matrix elements

public:
	matrix();

	matrix(int r, int c); //creates rxc matrix initialized to zero

	matrix(int r, int c, float* e); //creates rxc matrix initialized to the values stored at e

	void copyMatrix(matrix A); /*the object which calls this function will become identical to matrix A except for the location it is stored in i.e.
							   everything is copied from A except for the elements pointer. The elements pointer might change after the use of this 
							   function since more memory might need be allocated for the contents of A*/

	void getMatrix();

	void displayMatrix() const;

	int returnrows() const; 

	int returncolumns() const; 

	float* returnElement(int i, int j) const;

	matrix operator*(matrix X) const;

	matrix operator+(matrix X) const;

	matrix operator-(matrix X) const;
};
