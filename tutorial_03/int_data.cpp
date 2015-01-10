/**
 *
 *
 *           @name  int_data.cpp
 *          @brief  
 *
 *          Example usage:
 *          @code
 *          @endcode
 *
 *        @version  1.0
 *           @date  12/23/2014 (09:33:37 PM)
 *       @revision  none
 *       @compiler  gcc
 *
 *
 *         @author  P. Di Giglio (github.com/pdigiglio), <p.digiglio91@gmail.com>
 *        @company  
 *
 */


#include <iostream>
#include <limits>

using namespace std;

int
main ( void ) {

	/// For `unsigned` integers the minimum value is _always_ 0. To get the maximum
	/// value one can just initialize a variable to 0 and subtract 1 to get an underflow.
	unsigned char uc = 0;
	cout << "unsigned char:\t\t" << (int) uc;
	cout << " to " << (int) ( -- uc )  << endl; 
	cout << "From limits.h:\t\t" << (int) numeric_limits<unsigned char>::min();
	cout << " to " << (int) numeric_limits<unsigned char>::max() << endl << endl; 

	unsigned short int usi = 0;
	cout << "unsigned short int:\t" << usi;
	cout << " to " << -- usi << endl; 
	cout << "From limits.h:\t\t" << (int) numeric_limits<unsigned short>::min();
	cout << " to " << (int) numeric_limits<unsigned short>::max() << endl << endl; 

	unsigned int ui = 0;
	cout << "unsigned int:\t\t" << ui;
	cout << " to " << -- ui << endl; 
	cout << "From limits.h:\t\t" << numeric_limits<unsigned int>::min();
	cout << " to " << numeric_limits<unsigned int>::max() << endl << endl; 

	unsigned long int uli = 0;
	cout << "unsigned long int:\t" << uli;
	cout << " to " << -- uli << endl; 
	cout << "From limits.h:\t\t" << (unsigned long) numeric_limits<unsigned long>::min();
	cout << " to " << (unsigned long) numeric_limits<unsigned long>::max() << endl << endl; 

	size_t ust = 0;
	cout << "(unsigned) size_t:\t" << ust;
	cout << " to " << -- ust << endl; 
	cout << "From limits.h:\t\t" << numeric_limits<size_t>::min();
	cout << " to " << numeric_limits<size_t>::max() << endl << endl; 

	/// For signed variables, the minimum value is represented by `10...0` and the maximum
	/// by `01...1`.

	char c = 1;
	cout << endl << "char:\t\t" << (int) ( (char) ( c << ( 8 * sizeof(char) - 1 ) ) ) ;
	cout << " to " << (int) ( (char) ( ~ ( c << ( 8 * sizeof(char) - 1 ) ) ) ) << endl; 
	cout << "From limits.h:\t" << (int) numeric_limits<char>::min();
	cout << " to " << (int) numeric_limits<char>::max() << endl << endl; 

	// @attention this _need_ to be casted, otherwise it will print out wrong values!
	short s = 1;
	cout << "short:\t\t" << (short) ( s << ( 8 * sizeof(short) - 1 ) ) ;
	cout << " to " << (short) ( ~ ( s << ( 8 * sizeof(short) - 1 ) ) ) << endl; 
	cout << "From limits.h:\t" << (int) numeric_limits<short>::min();
	cout << " to " << (int) numeric_limits<short>::max() << endl << endl; 

	int i = 1;
	cout << "int:\t\t" << ( i << ( 8 * sizeof(int) - 1 ) ) ;
	cout << " to " << ~ ( i << ( 8 * sizeof(int) - 1 ) ) << endl; 
	cout << "From limits.h:\t" << (int) numeric_limits<int>::min();
	cout << " to " << (int) numeric_limits<int>::max() << endl << endl; 

	long int li = 1;
	cout << "long int:\t" << (long) ( li << ( 8 * sizeof(long int) - 1 ) ) ;
	cout << " to " << (long) ( ~ ( li << ( 8 * sizeof(long int) - 1 ) ) ) << endl; 
	cout << "From limits.h:\t" << (long) numeric_limits<long>::min();
	cout << " to " << (long) numeric_limits<long>::max() << endl; 

	return 0;
}
