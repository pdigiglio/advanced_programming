/*
 * ==================================================================
 *
 *       Filename:  helloPerson.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  21/10/2014 21:33:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  P. Di Giglio (), p.digiglio91@gmail.com
 *   Organization:  
 *
 * ==================================================================
 */


#include <iostream>

class Person {
	public:

		Person() {
			// prompt for first name and set member variable
			std::cout << "Please insert your first name: ";

			// If you use std::cin you cannot insert multiple-words names
			// Moreover, if I don't use getline, the next instruction will take
			// the return '\n' as input

//			std::cin >> firstName;
			std::getline( std::cin, firstName );

			// prompt for last name and set member variable
			std::cout << "Please insert your last name: ";

			// If you use std::cin you cannot insert multiple-words names

//			std::cin >> lastName;
			std::getline( std::cin, lastName );

			// TODO suppress ' ', '\t', '\n' characters @ the end of strings
		}

		virtual ~Person() {}

		void sayHello() const {
			// write greeting line
			std::cout << "Hello " << firstName << " " << 
				lastName << "!" << std::endl;
		}

		/// member variables holding first and last name
		std::string firstName;
		std::string lastName;
};


int main(int argc, char *argv[]) {
	Person p;

	p.sayHello();

	return 0;
}
