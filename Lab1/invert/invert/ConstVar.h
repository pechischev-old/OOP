#pragma once
#include <string>
#include <vector>

typedef std::vector<std::vector<float>> Matrix;

static const int SIZE_ARRAY = 3;
static const int NECESSARY_AMOUNT_ARGUMENTS = 2;
static const std::string NO_ARGUMENTS = "no required arguments";
static const std::string STRING_FORMAT = "EXAMPLE: invert.exe <matrixfile>";
static const std::string CANNOT_OPEN = " file can not be opened";
static const std::string INVALID_CHARACTER = "File contains an invalid character";
static const std::string CANNOT_INVERT = "no inverse matrix";
static const std::string SIZE_EXCEED = "the number of lines does not meet the conditions of the problem";
static const int FLOAT_PRECISION = 3;

static const Matrix SIGNS_REPLACE_MATRIX = {{1, -1, 1},
							 {-1, 1, -1},
							 {1, -1, 1}};