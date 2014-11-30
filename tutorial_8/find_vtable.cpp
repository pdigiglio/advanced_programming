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

#include <iostream>

// ----------------------------------------------- //
// non virtual classes
// ----------------------------------------------- //

/// @brief Empty class
class EmptyClass {};

/// @brief A Simple class with two implemented methods and no data members.
///
/// Since C++ automatically implements a default constructor, default
/// destructor, copy constructor and assignment operator, this class should have
/// the same size as EmptyClass.
class SimpleClass {
	public:
		SimpleClass() { }
		~SimpleClass() { }
};

// ----------------------------------------------- //
// virtual classes
// ----------------------------------------------- //

/// @brief Class with two implemented methods and no data members.
///
/// Since one method is virtual, a `vtable` is "appended" with the class. Thus, although
/// DummyClass has the same number of methods as SimpleClass and EmptyClass, it will need
/// a larger memory chunk to be allocated.
class DummyClass {
	public:
		DummyClass() { }
		virtual ~DummyClass() { }
};

class BaseClass {
	public:
		BaseClass() { }
		virtual void challenge() { 
			std::cout << "base class calling back" << std::endl; 
		}
		virtual ~BaseClass() { }
};

class Subclass : public BaseClass {
	public:
		Subclass() { }
		virtual ~Subclass() { }
};

class OverloadingSubclass : public BaseClass {
	public:
		OverloadingSubclass() { }
		virtual void challenge() {
			std::cout << "overloading subclass calling back" << std::endl;
			BaseClass::challenge();
		}
		virtual ~OverloadingSubclass() { }
};

/// @brief helper function to print the contents of the
/// hidden table (= fixed array with `size_t` blocks)
///
/// @param tableaddr specifies the location of the table in memory
/// @param tablesize specifies the size of this table in bytes
	void
print_hidden_table( size_t tableaddr, size_t tablesize ) {
	std::cout << "-------- table contents --------" << std::endl;
	// TODO: implement this helper function to print the contents of the
	// hidden table (= fixed array with size_t blocks)
	// tableaddr: specifies the location of the table in memory
	// tablesize: specifies the size of this table in bytes
}

	void
call_hidden_table_entry( size_t tableaddr, size_t tableentry ) {
	std::cout << "[CALL] function from table @ " << tableaddr
		<< " and entry " << tableentry <<  std::endl;
  
	// TODO: implement this helper function to call a method which is given by the hidden table
	// tableaddr: specifies the location of the table in memory
	// tableentry: specifies the entry in the 

	std::cout << "[CALL DONE] function from table" << std::endl;
}

int main(int argc, char **argv) {

	std::cout << "***************************************************************************" << std::endl;
	std::cout << " Task 1:" << std::endl;
	std::cout << " Analysis of class sizes, dep. on whether they are virtual or non-virtual" << std::endl;
	std::cout << "***************************************************************************" << std::endl;

	// TODO: Print size of each predefined class type and discuss the differences.

	std::cout << "EmptyClass size: " << sizeof( EmptyClass ) << " byte(s)" << std::endl;
	std::cout << "SimpleClass size: " << sizeof( SimpleClass ) << " byte(s)" << std::endl;
	std::cout << "DummyClass size: " << sizeof( DummyClass ) << " byte(s)" << std::endl;
	std::cout << "BaseClass size: " << sizeof( BaseClass ) << " byte(s)" << std::endl;
	std::cout << "Subclass size: " << sizeof( Subclass ) << " byte(s)" << std::endl;
	std::cout << "OverloadingSubclass size: " << sizeof( OverloadingSubclass ) << " byte(s)" << std::endl;

	std::cout << "***************************************************************************" << std::endl;
	std::cout << " Task 2:" << std::endl;
	std::cout << " Analysis of strides in memory between classes of different type and size," << std::endl;
	std::cout << " also dep. on whether they are virtual or non-virtual" << std::endl;
	std::cout << "***************************************************************************" << std::endl;

	/// Instance an object for each declared class
	EmptyClass empty();
	SimpleClass simple();
	DummyClass dummy();
	BaseClass base();
	Subclass sub();
	OverloadingSubclass overloadingsub();

	// TODO: Print the values of the hidden members of each class type.
	// HINT: First, use an instance of each predefined class and interpret it as simple chunk of memory.
	//		 Then try to interpret this chunk of memory as a datatype which has the same size.
	
	{	// TODO: show hidden member of EmptyClass
		// ... this will probably print junk.
	
	}
 
	{	// TODO: show hidden member of SimpleClass
		// ... this will probably print junk.
	
	}
 
	{	// TODO: show hidden member of DummyClass
		// ... this should NOT print junk.
	
	}

	{	// TODO: show the hidden member of two BaseClass instances
		// ... this should NOT print junk. what is so special about this member? 
	
	}

	{	// TODO: show hidden member of Subclass
		// .... this should NOT print junk.
   
	}

	{	// TODO: show hidden member of OverloadingSubclass
		// ... this should NOT print junk.
   
	}


	std::cout << "***************************************************************************" << std::endl;
	std::cout << " Task 3:" << std::endl;
	std::cout << " Analysis of class contents, for both kinds of classes, virtual and non-virtual" << std::endl;
	std::cout << "***************************************************************************" << std::endl;

	// task 3: - what's behind the address? a function or something more complex? print the offset differences! (how does it change with the number of methods)
	//		   - what is the purpose of this special hidden member variable, what's behind it and what does the offset difference indiciate?
	// (also think about that these objects are created by the runtime, and the compiler still has to call the right functions)
	// The class types are arranged like a stack in "memory"
	{

		// TODO: - compute the difference of the hidden value of DummyClass and the hidden value of BaseClass.
		//		 - implement and use the print_hidden_table function to display the hidden table
 
		// TODO: - compute the difference of the hidden value of Subclass and the hidden value of BaseClass
		//		 - implement and use the print_hidden_table function to display the hidden table
 
		// TODO: - compute the difference of the hidden value of OverloadingSubclass and the hidden value of Subclass
		//		 - implement and use the print_hidden_table function to display the hidden table
	
	}

	std::cout << "***************************************************************************" << std::endl;
	std::cout << " Task 4: THE CHALLENGE" << std::endl;
	std::cout << " Low-level (and not recommended) way of calling virtual member functions	 " << std::endl;
	std::cout << "***************************************************************************" << std::endl;
 
	// --------------------------------------------------------------------------------------------
	// IMPORTANT: - Look for the entries of the hidden tables from task 3 in the output of:
	//				objdump -d <yourbinary>
	//			  - Use this information to determine the table entry for the "challenge()" method
	// --------------------------------------------------------------------------------------------

	{	// TODO: execute challenge() method of a BaseClass instance in a low-level way
	
	}

	{	// TODO: execute challenge() method of a Subclass instance in a low-level way
	
	}

	{	// TODO: execute challenge() method of a OverloadingSubclass instance in a low-level way
	
	}

	return 0;
}
