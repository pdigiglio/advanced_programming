/**
 *
 *
 *			 @file	find_vtable.cpp
 *
 *			@brief  
 *
 *			Compile without optimization (otherwise the compiler will remove
 *			the interesting parts)
 *			@code
 *			     g++ -O0 -g -o find_vtable find_vtable.cpp
 *			@endcode
 *
 *		  @version	1.0
 *			 @date	11/30/2014 (02:10:59 PM)
 *		 @revision	none
 *		 @compiler	gcc
 *
 *
 *		   @author	P. Di Giglio (github.com/pdigiglio), <p.digiglio91@gmail.com>
 *		  @company	
 *
 *
 */

#include "colors.h"

#include <iostream>

using namespace std;

// ----------------------------------------------- //
// non virtual classes
// ----------------------------------------------- //
class EmptyClass {};

class SimpleClass {
	public:
		SimpleClass() { }
		~SimpleClass() { }
};

// ----------------------------------------------- //
// virtual classes
// ----------------------------------------------- //
class DummyClass {
	public:
		DummyClass() { }
		virtual ~DummyClass() { }
};

class BaseClass {
	public:
		BaseClass() { }
		virtual void challenge() { 
			cout << "base class calling back" << endl; 
		}
		virtual ~BaseClass() { }
};

class SubClass : public BaseClass {
	public:
		SubClass() { }
		virtual ~SubClass() { }
};

class OverloadingSubClass : public BaseClass {
	public:
		OverloadingSubClass() { }
		virtual void challenge() {
			cout << "overloading subclass calling back" << endl;
			BaseClass::challenge();
		}
		virtual ~OverloadingSubClass() { }
};

/// @brief Helper function to print the contents of the
/// hidden table (= fixed array with `size_t` blocks)
///
/// @param tableaddr specifies the location of the table in memory
/// @param tablesize specifies the size of this table in bytes
	void
print_hidden_table( size_t tableaddr, size_t tablesize ) {
	cout << "Table address (dec):\t" << ANSI_BLUE << tableaddr << ANSI_RESET << endl;
	/// @attention `hex << tableaddr` and `reinterpret_cast<size_t*> ( tableaddr )`
	/// will print out the same value (except for the `0x` address prefix)
	cout << "Table address (hex):\t"<< ANSI_BLUE 
		<< reinterpret_cast<size_t*>( tableaddr ) << ANSI_RESET << endl;
	cout << "Table size:\t\t" << ANSI_BLUE << tablesize << " byte(s)" << ANSI_RESET << endl;

	/// Divide `tablesize` by the size of `size_t` to?
	tablesize /= sizeof( size_t );
	cout << "Table size:\t\t" << ANSI_BLUE << tablesize << " size_t" << ANSI_RESET << endl;

	cout << ANSI_GREEN << "-------- table contents --------" << ANSI_RESET << endl;

	size_t *hiddentable = reinterpret_cast<size_t*>( tableaddr );
	for ( size_t element = 0; element < tablesize; ++ element ) {
		cout << "hidden[" << dec // decimal representation
			<< element << "] = " << hiddentable[ element ] << endl;
	}

	cout << endl;
}

	void
call_hidden_table_entry( size_t tableaddr, size_t tableentry ) {
	cout << "[CALL] function from table @ " << tableaddr
		<< " and entry " << tableentry <<  endl;
  
	// TODO: implement this helper function to call a method which is given by the hidden table
	// tableaddr: specifies the location of the table in memory
	// tableentry: specifies the entry in the 

	cout << "[CALL DONE] function from table" << endl;
}

int main(int argc, char **argv) {

	cout << "***************************************************************************" << endl;
	cout << " Task 1:" << endl;
	cout << " Analysis of class sizes, dep. on whether they are virtual or non-virtual" << endl;
	cout << "***************************************************************************" << endl;

	// TODO: Print size of each predefined class type and discuss the differences.

	/// For classes with a `virtual` method I will obtain as size, the size of the pointer to the `vtable`.
	/// No matter how man `virtual` function one has: only _one_ pointer to _one_ `vtable` will be stored. 
	cout << "EmptyClass size:\t\t" << sizeof( EmptyClass ) << " byte(s)" << endl;
	cout << "SimpleClass size:\t\t" << sizeof( SimpleClass ) << " byte(s)" << endl;
	cout << "DummyClass size:\t\t" << sizeof( DummyClass ) << " byte(s)" << endl;
	cout << "BaseClass size:\t\t\t" << sizeof( BaseClass ) << " byte(s)" << endl;
	cout << "SubClass size:\t\t\t" << sizeof( SubClass ) << " byte(s)" << endl;
	cout << "OverloadingSubClass size:\t" << sizeof( OverloadingSubClass ) << " byte(s)" << endl;

	cout << endl;
	cout << "***************************************************************************" << endl;
	cout << " Task 2:" << endl;
	cout << " Analysis of strides in memory between classes of different type and size," << endl;
	cout << " also dep. on whether they are virtual or non-virtual" << endl;
	cout << "***************************************************************************" << endl;

	// TODO: Print the values of the hidden members of each class type.
	// HINT: First, use an instance of each predefined class and interpret it as simple chunk of memory.
	//		 Then try to interpret this chunk of memory as a datatype which has the same size.
	
	{	// TODO: show hidden member of EmptyClass
		// ... this will probably print junk.

		EmptyClass empty;
		EmptyClass emptyLast;
		// I take something which matches with size
		size_t EmptyAddr = reinterpret_cast<size_t> (&empty);
		size_t EmptySize = reinterpret_cast<size_t> ( &empty ) - reinterpret_cast<size_t> ( &emptyLast );

		// check if `sizeof` and difference between addresses results match
		if ( EmptySize != sizeof( EmptyClass ) ) {
			cerr << ANSI_RED << "Not matching! &-& = " << EmptySize
				<< " sizeof() = " << sizeof( EmptyClass ) << ANSI_RESET << endl;
		}

		print_hidden_table( EmptyAddr, EmptySize );
	
	}
 
	{	// TODO: show hidden member of SimpleClass
		// ... this will probably print junk.

		SimpleClass simple;
		SimpleClass simpleLast;
		// I take something which matches with size
		size_t SimpleAddr = reinterpret_cast<size_t> (&simple);
		size_t SimpleSize = reinterpret_cast<size_t> ( &simple ) - reinterpret_cast<size_t> ( &simpleLast );

		// check if `sizeof` and difference between addresses results match
		if ( SimpleSize != sizeof( SimpleClass ) ) {
			cerr << ANSI_RED << "Not matching! &-& = " << SimpleSize
				<< " sizeof() = " << sizeof( SimpleClass ) << ANSI_RESET << endl;
		}

		print_hidden_table( SimpleAddr, SimpleSize );
	
	}
 
	{	// TODO: show hidden member of DummyClass
		// ... this should NOT print junk.
	
		DummyClass dummy;
		DummyClass dummyLast;
		// I take something which matches with size
		size_t DummyAddr = reinterpret_cast<size_t> (&dummy);
		size_t DummySize = reinterpret_cast<size_t> ( &dummy ) - reinterpret_cast<size_t> ( &dummyLast );

		// check if `sizeof` and difference between addresses results match
		if ( DummySize != sizeof( DummyClass ) ) {
			cerr << ANSI_RED << "Not matching! &-& = " << DummySize
				<< " sizeof() = " << sizeof( DummyClass ) << ANSI_RESET << endl;
		}

		print_hidden_table( DummyAddr, DummySize );
	}

	{	// TODO: show the hidden member of two BaseClass instances
		// ... this should NOT print junk. what is so special about this member? 
		BaseClass base;
		BaseClass baseLast;
		// I take something which matches with size
		size_t BaseAddr = reinterpret_cast<size_t> (&base);
		size_t BaseSize = reinterpret_cast<size_t> ( &base ) - reinterpret_cast<size_t> ( &baseLast );

		// check if `sizeof` and difference between addresses results match
		if ( BaseSize != sizeof( BaseClass ) ) {
			cerr << ANSI_RED << "Not matching! &-& = " << BaseSize
				<< " sizeof() = " << sizeof( BaseClass ) << ANSI_RESET << endl;
		}

		print_hidden_table( BaseAddr, BaseSize );
	
	}

	{	// TODO: show hidden member of SubClass
		// .... this should NOT print junk.
   
		SubClass sub;
		SubClass subLast;
		// I take something which matches with size
		size_t SubAddr = reinterpret_cast<size_t> (&sub);
		size_t SubSize = reinterpret_cast<size_t> ( &sub ) - reinterpret_cast<size_t> ( &subLast );

		// check if `sizeof` and difference between addresses results match
		if ( SubSize != sizeof( SubClass ) ) {
			cerr << ANSI_RED << "Not matching! &-& = " << SubSize
				<< " sizeof() = " << sizeof( SubClass ) << ANSI_RESET << endl;
		}

		print_hidden_table( SubAddr, SubSize );
	}

	{	// TODO: show hidden member of OverloadingSubClass
		// ... this should NOT print junk.
   
		OverloadingSubClass overloadingSub;
		OverloadingSubClass overloadingSubLast;
		// I take something which matches with size
		size_t SubAddr = reinterpret_cast<size_t> (&overloadingSub);
		size_t SubSize = reinterpret_cast<size_t> ( &overloadingSub ) - reinterpret_cast<size_t> ( &overloadingSubLast );

		// check if `sizeof` and difference between addresses results match
		if ( SubSize != sizeof( OverloadingSubClass ) ) {
			cerr << ANSI_RED << "Not matching! &-& = " << SubSize
				<< " sizeof() = " << sizeof( OverloadingSubClass ) << ANSI_RESET << endl;
		}

		print_hidden_table( SubAddr, SubSize );
	}


	cout << "***************************************************************************" << endl;
	cout << " Task 3:" << endl;
	cout << " Analysis of class contents, for both kinds of classes, virtual and non-virtual" << endl;
	cout << "***************************************************************************" << endl;

	// task 3: - what's behind the address? a function or something more complex? print the offset differences! (how does it change with the number of methods)
	//		   - what is the purpose of this special hidden member variable, what's behind it and what does the offset difference indiciate?
	// (also think about that these objects are created by the runtime, and the compiler still has to call the right functions)
	// The class types are arranged like a stack in "memory"
	{

		// TODO: - compute the difference of the hidden value of DummyClass and the hidden value of BaseClass.
		//		 - implement and use the print_hidden_table function to display the hidden table
 
		// TODO: - compute the difference of the hidden value of SubClass and the hidden value of BaseClass
		//		 - implement and use the print_hidden_table function to display the hidden table
 
		// TODO: - compute the difference of the hidden value of OverloadingSubClass and the hidden value of SubClass
		//		 - implement and use the print_hidden_table function to display the hidden table
	
	}

	cout << "***************************************************************************" << endl;
	cout << " Task 4: THE CHALLENGE" << endl;
	cout << " Low-level (and not recommended) way of calling virtual member functions	 " << endl;
	cout << "***************************************************************************" << endl;
 
	// --------------------------------------------------------------------------------------------
	// IMPORTANT: - Look for the entries of the hidden tables from task 3 in the output of:
	//				objdump -d <yourbinary>
	//			  - Use this information to determine the table entry for the "challenge()" method
	// --------------------------------------------------------------------------------------------

	{	// TODO: execute challenge() method of a BaseClass instance in a low-level way
	
	}

	{	// TODO: execute challenge() method of a SubClass instance in a low-level way
	
	}

	{	// TODO: execute challenge() method of a OverloadingSubClass instance in a low-level way
	
	}

	return 0;
}
