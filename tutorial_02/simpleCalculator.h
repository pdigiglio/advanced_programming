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

