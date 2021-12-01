#include <iostream>

#include "vectorfunctions.hpp"

int main( )
{
    int option;

    do
    {   
        std::cout << "------ Menu ------\n"
                     "[1] dot product   \n"
                     "[2] euclidean norm\n"
                     "[3] maximum norm  \n"
                     "[4] exit          \n\n";
                    
        std::cout << "Input: ";
        std::cin >> option; 
        std::cout << std::endl;
        
        if( option == 1 )
        {
            int n1, n2;
            
            double* v1 = cie::createArray( "v1", n1 );
            double* v2 = cie::createArray( "v2", n2 );

            if( n1 != n2 )
            {
                std::cout << "\nError: vectors sizes don't match." << "\n" << std::endl;

                continue;
            }
            
            std::cout << "\nDot product is " << cie::dotProduct( v1, v2, n1 ) << "\n" << std::endl;
            
            cie::deleteArray( v1 );
            cie::deleteArray( v2 );
        }
        else if( option == 2 )
        {
            int n1;
            double* v1 = cie::createArray( "v1", n1 );
               
            std::cout << "\nEuclidean norm is " << cie::euclideanNorm( v1, n1 ) << "\n" << std::endl;
            
            cie::deleteArray( v1 );
        }
        else if( option == 3 )
        {
            int n1;
            double* v1 = cie::createArray( "v1", n1 );
               
            std::cout << "\nMaximum norm is " << cie:: maximumNorm( v1, n1 ) << "\n" << std::endl;
            
            cie::deleteArray( v1 );
        }
    } 
    while( option != 4 );
    
    return 0;
}
