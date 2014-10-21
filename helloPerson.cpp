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
			std::cin >> firstName;

			// prompt for last name and set member variable
			std::cout << "Please insert your last name: ";
			std::cin >> lastName;
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
