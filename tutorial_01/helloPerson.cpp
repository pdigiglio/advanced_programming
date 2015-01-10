/**
 *
 *
 *           @file  helloPerson.cpp
 *          @brief  Evoluted version of `Hello world` program.
 *
 *          It takes a name and surname as input and prints `Hello <name> <surname>!`.
 *
 *         @author  P. Di Giglio (), p.digiglio91@gmail.com
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  21/10/2014 21:33:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *   Organization:  
 *
 *
 */


#include <iostream>

class Person {
	public:

		Person() {
			/// Prompt for first name and set member variable.
			std::cout << "Please insert your first name: ";

			/// If you use `std::cin` you cannot insert multiple-words names.
			/// Moreover, if you don't use `std::getline`, the next instruction will take
			/// the return '\\n' as input.

//			std::cin >> firstName;
			std::getline( std::cin, firstName );

			/// Prompt for last name and set member variable
			std::cout << "Please insert your last name: ";

			// If you use std::cin you cannot insert multiple-words names

//			std::cin >> lastName;
			std::getline( std::cin, lastName );

			/// @todo suppress ' ', '\\t', '\\n' characters @ end of strings.
		}

		virtual ~Person() {}

		/// @brief Write a greeting line.
		void sayHello() const {
			// write greeting line
			std::cout << "Hello " << firstName << " " << 
				lastName << "!" << std::endl;
		}

		// member variables holding first and last name
		std::string firstName; //!< Member variable for the first name.
		std::string lastName; //!< Member variable for the second name.
};


int main(int argc, char *argv[]) {
	Person p;

	p.sayHello();

	return 0;
}
