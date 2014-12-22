#include "./simpleCalculator.h"

#include <cmath>

/**
 *
 *        @class MoreSofisticatedCalculator
 *
 *        @brief Based on Simplecalculator, extend metods with cos, sin, tg
 *
 */
class MoreSofisticatedCalculator: public SimpleCalculator {
	public:	
		MoreSofisticatedCalculator (void) {}; /* ctor */
		virtual ~MoreSofisticatedCalculator (void) {}; /* dtor */

		double mySin ( const double &x ) {
			return sin( M_PI * x );
		}

		double myCos ( const double &x ) {
			return cos( M_PI * x );
		}

		double myTan( const double &x ) {
			return tan( M_PI * x );
		}

		/// @brief Convert number from base 10 to base `base`.
		/// @todo From any base to any base
		/// @todo negative numbers
		void base( int number, int base ) {

			/// First check if `base` is positive: if not so, returns.
			if( !( base > 0 ) ) {
				std::cerr << ANSI_RED << "Negative or null base"
					<< ANSI_RESET << std::endl;
				return;
			}
			
			/// Check if `number` is negative: if so, returns.
			if ( number < 0 ) {
				std::cerr << ANSI_RED << "Negative number"
					<< ANSI_RESET << std::endl;
				return;
			}

			std::cout << number << " is represented in base " << base << " by ";

			/// Find the maximum power of `base` which is lower than `number`.
			unsigned int exponent = 0;
			int counter = 1;
			while ( counter <= number ) {
				counter *= base;
				++ exponent;
			}

			// go back of one step
			counter /= base;
			-- exponent;

			/// Convert number from base 10 to base `base`.
			do {
				std::cout << parse( number / counter );
				number %= counter;
				counter /= base;
			} while ( counter > 0 );

			std::cout << std::endl;
		}

		/// @brief Converts number > 9 into A,B,\dots{} chars
		char parse ( int number ) {

			if ( number > 9 ) {
//				return (char) ( (int) 'A' + number - 10 );
				// 'A' -> 65
				return (char) ( 55 + number );
			}

			// returns the char corresponding to the digit
			// '0' -> 48
			return (char) ( 48 + number);
		}

	protected:
	private:
}; /* -----  end of class MoreSofisticatedCalculator  ----- */

