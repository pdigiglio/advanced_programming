/*
 * ==================================================================
 *
 *       Filename:  simpleCalculator.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22/10/2014 12:59:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  P. Di Giglio (), p.digiglio91@gmail.com
 *   Organization:  
 *
 * ==================================================================
 */

#include <iostream>
#include <cmath>

#include "colors.h"

/*
 * ==================================================================
 *        Class: SimpleCalculator
 *  Description: 
 * ==================================================================
 */
class SimpleCalculator {
	public:	
		SimpleCalculator ( void ) {}; /* ctor */
		
		virtual ~SimpleCalculator ( void ) {}; /* dtor */
	
		// return the sum of two numbers
		double sum ( const double &a, const double &b ) {
			return a + b;
		}

		// return difference between numbers (a - b)
		double subtract ( const double &a, const double &b ) {
			return a - b;
		}

		// return multiplication between numbers
		double multiply ( const double &a, const double &b ) {
			return a * b;
		}

		// return division between numbers
		double divide ( const double &a, const double &b ) {
			if ( !b ) { /* if b == 0 */
				std::cerr << ANSI_RED << 
					"Cannot divide by zero!!" 
					<< ANSI_RESET << std::endl;
				return NAN;
			}
			return a / b;
		}

		// mean between numbers
		double mean ( const double &a, const double &b ) {
			return ( a + b ) / 2.;
		}

	protected:
	private:
}; /* -----  end of class SimpleCalculator  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  output_print
 *  Description:  
 * =====================================================================================
 */
void
output_print ( double a, double b, char o, double result ) {
	std::cout << a << " " << o << " " << b <<
		" = " << result << std::endl;
}		/* -----  end of function output_print  ----- */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int
main ( int argc, char *argv[] ) {
	
	SimpleCalculator instance;
	double a, b;
	char operation;

	// create a prompt
	std::cout << "Please insert two numbers and select one of the following operations" << std::endl;
	std::cout << " > Sum ( insert + )" << std::endl;
	std::cout << " > Difference ( insert - )" << std::endl;
	std::cout << " > Multiplication ( insert * )" << std::endl;
	std::cout << " > Division ( insert / )" << std::endl;
	std::cout << " > Mean ( insert m )" << std::endl << std::endl;

	std::cout << "Numbers >> ";
	// read numbers
	std::cin >> a >> b;

	std::cout << "Operation >> ";
	// read operation
	std::cin >> operation;

	if ( operation == '+' )
		output_print( a, b, operation, instance.sum( a, b ) );
	else if ( operation == '-' )
		output_print( a, b, operation, instance.subtract( a, b ) );
	else if ( operation == '*' )
		output_print( a, b, operation, instance.multiply( a, b ) );
	else if ( operation == '/' )
		output_print( a, b, operation, instance.divide( a, b ) );
	else if ( operation == 'm' )
		std::cout << "mean( " << a << ", " << b <<
			") = " << instance.mean( a, b ) << std::endl;

	return 0;
}				/* ----------  end of function main  ---------- */

