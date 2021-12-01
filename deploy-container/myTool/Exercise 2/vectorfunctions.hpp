#include <iostream>
#include <string>
#include <cmath>

namespace cie
{

void inputVectorElements( double vector[], int size, std::string name );

void printVector( double vector[], int size, std::string name );

bool checkSize( int size );

double dotProduct( double vector1[], double vector2[], int size );

double euclideanNorm( double vector[], int size );

double maximumNorm( double vector[], int size );

double* createArray( std::string name, int& size );

void deleteArray( double* array );

} // namespace cie

