/**
 *
 *
 *           @name  alter_behaviour.cpp
 *
 *        @version  1.0
 *           @date  11/20/2014 (08:41:03 PM)
 *       @revision  none
 *       @compiler  gcc
 *
 *
 *         @author  P. Di Giglio (github.com/pdigiglio), <p.digiglio91@gmail.com>
 *        @company  
 *          @brief  Simple code to demostrate how dangerous can be an invalid array access.
 *
 *          Example usage:
 *          @code
 *          @endcode
 *
 *
 */

#include <iostream>
#include <cstring>

int main(int argc, char **argv) {
    // NOTE: on some systems the compiler might reorder the following variables.
    // Therefore, our intended behaviour might not work out as planned.
    // If so, feel free to reduce the size of the buffer array to something smaller,
    // e.g. 30. Please let us know in the tutorials if you have such a system.
    char buffer[73];
    std::cout << "DEBUG: buffer address: " << reinterpret_cast<void*>(&buffer) << std::endl;

    char secret_dataset[73] = {0x0,0x0,0x0,0x43,0x6F,0x6E,0x67,0x72,0x61,0x74,0x75,
                               0x6C,0x61,0x74,0x69,0x6F,0x6E,0x73,0x2C,0x20,0x79,0x6F,
                               0x75,0x20,0x68,0x61,0x76,0x65,0x20,0x73,0x75,0x63,0x63,
                               0x65,0x73,0x73,0x66,0x75,0x6C,0x6C,0x79,0x20,0x63,0x68,
                               0x61,0x6E,0x67,0x65,0x64,0x20,0x61,0x20,0x70,0x72,0x6F,
                               0x67,0x72,0x61,0x6D,0x27,0x73,0x20,0x62,0x65,0x68,0x61,
                               0x76,0x69,0x6F,0x75,0x72,0x2E,0x0A};
    std::cout << "DEBUG: buffer address: " << reinterpret_cast<void*>(&secret_dataset) << std::endl;

    std::cout << "DEBUG: secret dataset address: " << reinterpret_cast<void*>(&secret_dataset) << std::endl;
	std::cout << "DEBUG: difference of addresses: "
		<< -reinterpret_cast<size_t>(&buffer) + reinterpret_cast<size_t>(&secret_dataset) 
		<< std::endl;

    // TODO: Look for strlen in a C/C++ reference documentation and 
    // explain how it works. Further, does strlen always terminate?
    std::cout << "DEBUG: old size of secret dataset: " << strlen(secret_dataset) << std::endl;
    std::cout << "enter value to run out of bounds (suggested 83): ";
    int size;
    std::cin >> size;

	/// The assumptions is that `buffer[73]` and `secret_dataset[73]` are allocated close to each
	/// other. In my arch, `buffer` will take 73 bytes, then 7 will be left empty (they sum
	/// up to 80). When you enter 83 as out-of-bounds value you overwrite the first three
	/// terminators which appear at the beginning of `secret_dataset`. Also, `buffer` has
	/// no terminators (since it contains only 'A's) so `buffer` and `secret_dataset` will
	/// be considered only one string.

    // TODO: Prevent potential out of bounds access

    // ------------------------------

    for (int i=0; i < size; i++) {
        buffer[i] = 'A';
    }

    // ------------------------------

    std::cout << "DEBUG: buffer content: " << buffer << std::endl;

	/// Secret dataset doesn't end with a `\0` character so his length will depend on the
	/// position of the first zero outside the array.
    std::cout << "new size of secret dataset: " << strlen(secret_dataset) << std::endl;
    return 0;
}
