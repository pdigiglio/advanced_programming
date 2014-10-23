#include "./simpleCalculator.h"

#include <cmath>

/*
 * ============================================================================
 *        Class: MoreSofisticatedCalculator
 *  Description: Based on Simplecalculator, extend metods with cos, sin, tg
 * ============================================================================
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

	protected:
	private:
}; /* -----  end of class MoreSofisticatedCalculator  ----- */

