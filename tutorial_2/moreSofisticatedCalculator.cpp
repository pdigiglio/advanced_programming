/*
 * ==================================================================
 *
 *       Filename:  moreSofisticatedCalculator.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22/10/2014 13:42:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  P. Di Giglio (), p.digiglio91@gmail.com
 *   Organization:  
 *
 * ==================================================================
 */

#include <iostream>
#include <map>
#include <cmath>

#define LONG	1
#define NEXISTS	2

#include "./moreSofisticatedCalculator.h"
#include "./output_print.h"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int
main ( int argc, char *argv[] ) {
	// declare a new calculator
	MoreSofisticatedCalculator instance;

	// conversion map between literals operators and actual operators
	std::map<char,std::string> conv;
	conv['m'] = "mean";
	conv['s'] = "sin";
	conv['c'] = "cos";
	conv['t'] = "tan";

	char bin_op[] = {'+', '-', '*', '/', 'm'};
	char un_op[] = {'t', 'c', 's'};

	double a, b;
	char operation;

	// create a prompt
	std::cout << "Please insert one of the following operations" << std::endl;
	std::cout << " > Sum ( insert + )" << std::endl;
	std::cout << " > Difference ( insert - )" << std::endl;
	std::cout << " > Multiplication ( insert * )" << std::endl;
	std::cout << " > Division ( insert / )" << std::endl;
	std::cout << " > Mean ( insert m )" << std::endl;
	std::cout << " > Sine ( insert s )" << std::endl;
	std::cout << " > Cosine ( insert c )" << std::endl;
	std::cout << " > Tangent ( insert t )" << std::endl << std::endl;

	std::cout << "Operation >> ";

	// read operation
	std::string input;
	std::getline( std::cin, input );

	// all operators have length = 1
	if ( input.length() - 1 ) {
		std::cerr << ANSI_RED << "[" << LONG << 
			"] Operation not valid" << ANSI_RESET << std::endl;
		return LONG;
	}

	operation = input.at(0);

	// decides if operation is unary or binary
	bool unary = true;
	for ( unsigned short int i = 0; i < 5 ; ++ i )
		if( operation == *( bin_op + i ) ) {
			unary = !unary;
			break;
		}

	// if 'unary' has not been changed, check if the operation is valid
	if ( unary ) {
		bool valid = false;

		for ( unsigned short int i = 0; i < 3 ; ++ i ) {
			if( operation == *( un_op + i ) ) {
				valid = true;
				break;
			}
		}
			
		if( !( valid ) ) {
			std::cerr << ANSI_RED << "[" << NEXISTS <<
				"] Operation not valid" << ANSI_RESET << std::endl;
			return NEXISTS;
		}
	}


	
	// decide wether the input is one or two numbers
	if ( unary ) {
		std::cout << "Number (only one!) >> ";
		// read numbers
		std::cin >> a;
	} else { // if operator is binary
		std::cout << "Numbers >> ";
		// read numbers
		std::cin >> a >> b;
	}

	// output
	switch ( operation ) {
		case '+':	
			output_print( a, b, operation, instance.sum( a, b ) );
			break;

		case '-':	
			output_print( a, b, operation, instance.subtract( a, b ) );
			break;

		case '*':	
			output_print( a, b, operation, instance.multiply( a, b ) );
			break;

		case '/':	
			output_print( a, b, operation, instance.divide( a, b ) );
			break;

		case 'm':	
			std::cout << "mean( " << a << ", " << b <<
				" ) = " << instance.mean( a, b ) << std::endl;
			break;

		case 'c':
			output_print( a, conv['c'], instance.myCos(a) );
			break;

		case 's':
			output_print( a, conv['s'], instance.mySin(a) );
			break;

		case 't':
			output_print( a, conv['t'], instance.myTan(a) );
			break;
	}				/* -----  end switch  ----- */

	return 0;
}				/* ----------  end of function main  ---------- */
