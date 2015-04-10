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
		/// @todo negative numbers [DONE]
		void base( int number, int base ) {

			/// First check if `base` is positive: if not so, returns.
			if( base < 0 ) {
				std::cerr << ANSI_RED << "Negative base!"
					<< ANSI_RESET << std::endl;
				return;
			} else if ( base == 0 ) {
				std::cerr << ANSI_RED << "Null base!"
					<< ANSI_RESET << std::endl;
				return;
			}
			
			// character for the sign of the number
			char sign = '\0';
			/// Check if `number` is negative: if so, returns.
			if ( number < 0 ) {
				std::cerr << ANSI_BLUE << "Negative number"
					<< ANSI_RESET << std::endl;
					
				number *= -1;
				sign = '-';
			}

			std::cout << number << " is represented in base " << base << " by ";
			std::cout << sign;
			
			/**
			 * Find the maximum power of `base` which is lower than `number`. The
			 * test is `<=` instead than `<` so that in case `number == 0` it works
			 * properly.
			 */
			unsigned int exponent = 0;
			int counter = 1;
			while ( counter <= number ) {
				counter *= base;
				++ exponent;
			}

			/**
			 * Go back of one step. In fact if, for example, `base` is 2 and `number`
			 * is 4, at the end of the loop `counter` is 8 and `exponent` is 3. This
			 * is because of the previous `<=` (which I need for the case `number == 0`).
			 */
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

