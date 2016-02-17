#pragma once
#include <string>
#include <vector>

typedef std::vector<std::vector<float>> Matrix;

static const int SIZE_ARRAY = 3;
static const int MAX_AMOUNT_ARGUMENTS = 2;
static const std::string NO_ARGUMENTS = "no required arguments";
static const std::string STRING_FORMAT = "EXAMPLE: invert.exe <matrixfile>";
static const std::string NOT_OPEN = " file can not be opened";
static const std::string INVALID_CHARACTER = "File contains an invalid character";
static const std::string NO_INVERT = "no inverse matrix";
static const int COUNT_AFTER_POINT = 2;

static const Matrix SIGNS = {{1, -1, 1},
							 {-1, 1, -1},
							 {1, -1, 1}};