// invert.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm> 

#include "ConstVar.h"

using namespace std;

void OutputArray(const Matrix & matrix)
{
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		for (size_t j = 0; j < matrix[i].size(); ++j)
		{
			printf("%.3f ", matrix[i][j]);
		}
		cout << endl;
	}
}

float GetDeterminateFromArray_2x2(const Matrix & matrix_2x2)
{
	return matrix_2x2[0][0] * matrix_2x2[1][1] - matrix_2x2[0][1] * matrix_2x2[1][0];
}

float GetMinor(const Matrix & matrix, const size_t & column, const size_t & row)
{
	Matrix matrix_2x2;
	matrix_2x2.resize(2);
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		int k = 0;
		for (size_t j = 0; j < matrix[i].size(); ++j)
		{
			if (column != j && row != i)
			{
				matrix_2x2[k].push_back(matrix[i][j]);
				++k;
			}
		}
	}
	return GetDeterminateFromArray_2x2(matrix_2x2);
}

float GetDeterminate(const Matrix & matrix)
{
	float determinate = 0;
	for (size_t column = 0; column < matrix.size(); ++column)
	{
		int row = 0;
		determinate += matrix[row][column] * GetMinor(matrix, column, row) * static_cast<float>(pow(-1, column));
	}
	return determinate;
}

Matrix GetMinorArray(const Matrix & matrix)
{
	Matrix arrayMinor;
	arrayMinor.resize(matrix.size());
	for (size_t column = 0; column < matrix.size(); ++column) 
		for (size_t row = 0; row < matrix[column].size(); ++row) 
			arrayMinor[column].push_back(GetMinor(matrix, column, row));
	return arrayMinor;
}

void InvertMatrix(Matrix & arrayMinor, float & determinate)
{
	for (size_t i = 0; i < arrayMinor.size(); ++i)
		for (size_t j = 0; j < arrayMinor[i].size(); ++j) 
			arrayMinor[i][j] = (1 / determinate) * SIGNS_REPLACE_MATRIX[i][j] * arrayMinor[i][j];
}

void Run(Matrix & matrix)
{
	float determinate = GetDeterminate(matrix);
	if (determinate != 0) 
	{
		matrix = GetMinorArray(matrix);
		InvertMatrix(matrix, determinate);
		OutputArray(matrix);
	}
	else
	{
		cout << CANNOT_INVERT << endl;
	}
}

Matrix GetArrayFromFile(const string & inputFileStr) 
{
	ifstream fin(inputFileStr);
	Matrix arr(SIZE_ARRAY);
	
	for (size_t i = 0; i < SIZE_ARRAY; ++i)
	{
		for (size_t j = 0; j < SIZE_ARRAY; ++j) 
		{
			float number = 0;
			fin >> number;
			arr[i].push_back(number);
		}
	}
	return arr;
}

bool IsCorrectSymbol(const char & symbol)
{
	return (isdigit(static_cast<int>(symbol)) || symbol == '-' || symbol == ' ' || symbol == '.' || symbol == '\t' || symbol == ',');
}

bool CheckFileContent(const string & inputPath) 
{
	ifstream fin(inputPath);
	if (!fin.is_open())
	{
		cout << inputPath + CANNOT_OPEN << endl;
		return false;
	}
	string inputStr;
	int lineCount = 0;
	while (getline(fin, inputStr))
	{
		if (!inputStr.empty()) 
		{
			if (any_of(inputStr.begin(), inputStr.end(), [](const char & symbol) {return !IsCorrectSymbol(symbol); }))
			{
				cout << INVALID_CHARACTER << endl;
				return false;
			}
		}
		++lineCount;
	}
	if (lineCount != SIZE_ARRAY)
	{
		cout << SIZE_EXCEED << endl;
		return false;
	}
	return true;
}

bool InitProgram(int argc, char* argv[], Matrix & arr)
{
	if (argc == NECESSARY_AMOUNT_ARGUMENTS) 
	{
		if (!CheckFileContent(argv[1])) 
		{
			return false;
		}
		arr = GetArrayFromFile(argv[1]);
	}
	else
	{
		cout << NO_ARGUMENTS << endl;
		cout << STRING_FORMAT << endl;
		return false;
	}
	return true;
}

int main(int argc, char* argv[])
{
	Matrix matrix;
	if (InitProgram(argc, argv, matrix))
	{
		Run(matrix);
	}
	else 
	{
		return 1;
	}
    return 0;
}

