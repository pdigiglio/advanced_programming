/**
 *
 *
 *           @name  end_of_scope_dtor.cpp
 *          @brief  Program to see if a reference destructed in a scope calls the class
 *          destructor.
 *
 *          Example usage:
 *          @code
 *          @endcode
 *
 *        @version  1.0
 *           @date  12/31/2014 (07:36:59 PM)
 *       @revision  none
 *       @compiler  gcc
 *
 *
 *         @author  P. Di Giglio (github.com/pdigiglio), <p.digiglio91@gmail.com>
 *        @company  
 *
 *
 */

#include <iostream>

class A {
	public:

		A () {};
		~A () {
			std::cout << "destructor" << std::endl;
		};
	
		void
		alive( void ) {
			std::cout << "I'm alive!" << std::endl;
		}
	protected:

	private:

}; /* -----  end of class A  ----- */

int
main ( int argc, char *argv[] ) {
	A a;

	/// The reference inside the scope doesn't destroy the class!
	{
		A &a_ref = a;
	}

	a.alive();

	return 0;
}				/* ----------  end of function main  ---------- */
