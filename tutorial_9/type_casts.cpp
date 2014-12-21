/**
 *
 *
 *           @name  type_casts.cpp
 *
 *        @version  1.0
 *           @date  12/07/2014 (07:15:21 PM)
 *       @revision  none
 *       @compiler  gcc
 *
 *
 *         @author  P. Di Giglio (github.com/pdigiglio), <p.digiglio91@gmail.com>
 *        @company  
 *          @brief  
 *
 *          Example usage:
 *          @code
 *          @endcode
 *
 *
 */

#include <iostream>

class Base {
	public:
		void echo ( void ) {
			std::cout << "Base" << std::endl;
		};
};

class Derived: public Base {
	public:
		void echo ( void ) {
			std::cout << "Derived" << std::endl;
		};
};

	int
main ( void ) {

	Base* ptr = new Derived();
	/// This will call Derived::echo() if Base::echo() is declared to be `virtual`.
	///
	/// Also, if you rename `Base::echo()` into `Base::echo2()` then this will give an
	/// error at compile time because the compiler cannot resolve the function. It will
	/// try to call `Base::echo()` which doesn't exist.
	ptr->echo();

	/// If you use this `stack` allocation, Derived::echo() will be called even if
	/// the method is not virtual.
//	Derived *derived = new Derived();
//	Derived derived;
//	derived.echo();

	return 0;
}
