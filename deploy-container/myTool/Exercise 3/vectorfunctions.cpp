#include <iostream>
#include <string>
#include <cmath>

namespace cie
{

void inputVectorElements( double vector[], int size, std::string name )
{
    for( int i = 0; i < size; ++i )
    {
        std::cout << name << "[" << i << "] = ";
        std::cin >> vector[i];
    }
}

void printVector( double vector[], int size, std::string name )
{
    std::cout << name << " = [";
        
    for( int i = 0; i < size - 1; ++i )
    {
        std::cout << vector[i] << ", ";
    }
    
    if( size != 0 )
    {
      std::cout << vector[size - 1];
    }
    
    std::cout << "]" << std::endl;
}

bool checkSize( int size )
{
    if( size == 0 )
    {
        std::cout << "Warning: Vector has size zero." << std::endl;
    }
    
    return size == 0;
}

double dotProduct( double vector1[], double vector2[], int size )
{
    if( checkSize( size ) )
    {
        return 0.0;
    }

    double result = 0.0;
    
    for( int i = 0; i < size; ++i )
    {
      result += vector1[i] * vector2[i];
    }
    
    return result;
}

double euclideanNorm( double vector[], int size )
{
    return std::sqrt( dotProduct( vector, vector, size ) );
}

double maximumNorm( double vector[], int size )
{
    if( checkSize( size ) )
    {
        return 0.0;
    }
    
    double maximumValue = std::abs( vector[0] );
    
    for( int i = 0; i < size; ++i )
    {
        int absValue = std::abs( vector[i] );
        
        if( absValue > maximumValue )
        {
            maximumValue = absValue;
        }
    }
    
    return maximumValue;
}

double* createArray( std::string name, int& size )
{
    std::cout << "Input vector " << name << std::endl;
    std::cout << "    size = ";
    
    std::cin >> size;
    
    double* target = new double[size];
    
    inputVectorElements( target, size, "    " + name );

    return target;
}

void deleteArray( double* array )
{
    delete[] array;
}

} // namespace cie

