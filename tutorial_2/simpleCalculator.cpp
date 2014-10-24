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

#include <math.h>
#include <stdio.h>

#include "./simpleCalculator.h"
#include "./output_print.h"



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
			" ) = " << instance.mean( a, b ) << std::endl;
	else {
		std::cerr << ANSI_RED << "Operation not defined!" << ANSI_RESET << std::endl;
		return 1;
	}

	return 0;
}				/* ----------  end of function main  ---------- */

