#include<iostream>

int main( )
{
    int number;

    std::cout << "Input integer number: ";
    std::cin >> number;

    int sign = number < 0;

    std::cout << "Bitwise representation is ";

    while( number != 0 )
    {
        if( number % 2 )
        {
            std::cout << '1';
        }
        else
        {
            std::cout << '0';
        }

        number = number / 2;
    }

    std::cout << " " << sign << std::endl;
}
