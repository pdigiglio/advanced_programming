/**
 * @file   pointer_arithmetic.cpp
 * @brief  play around with pointer and `size_t` aritmetic
 * @author Roland Wittmann <roland.wittmann@mytum.de> 
 */

#include <iostream>

int main(int argc, char **argv) {  
    int a[2] = { 10, 11 };

	// the same as
	// int a_ptr = a;
    int *a_ptr = &a[0];

	/**
	 * Convert the address of the first entry of the array `a` into a `size_t` and put the
	 * result into a variable `b`.
	 * Then increment `a_ptr` by 1 (this will go to the next entry of the array so it won't
	 * actually increment the address by one byte).
	 * Increment also `b` by `sizeof(typeof(a[0])) = sizeof(int)`.
	 */
    size_t b = reinterpret_cast<size_t>(a_ptr);
	a_ptr += 1;
    b += sizeof(int);
    
	/**
	 * Define a new pointer `c_ptr` which points to the (new) value of `b` casted into a
	 * pointer (i.e. it will point to `a[1]`)
	 */
	int *c_ptr = reinterpret_cast<int*>(b);
    int c = *c_ptr; 

    std::cout << "value of a[1]: " << a[1] << std::endl;
    std::cout << "value of *a_ptr: " << *a_ptr << std::endl;
    std::cout << "value of c: " << c << std::endl;
}
