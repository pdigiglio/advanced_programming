/**
 *
 *
 *           @name  expression_template.cpp
 *
 *        @version  1.0
 *           @date  01/22/2015 (10:45:40 PM)
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

// TODO: Assignment 1: Task 1: Implement add / multiply

/**
 * @brief Sum two generic `Data` args.
 *
 * I declare the function to be `static` because I will use the function only
 * in the scope of this file: the compiler may activate more optimizations.
 */
template<typename Data>
	static inline Data
add ( const Data &a, const Data &b ) {
	return a + b;
}

/**
 * @brief Multiply two generic `Data` args.
 *
 * I declare the function to be `static` because I will use the function only
 * in the scope of this file: the compiler may activate more optimizations.
 */
template<typename Data>
	static inline Data
multiply ( const Data &a, const Data &b ) {
	return a * b;
}

// TODO: Assignment 1: Task 2: Implement power

// XXX This is right but it doesn't fullfil the requirements of the assignment
//template<typename Data>
//Data powerFor ( const Data &a, unsigned int N ) {
//	Data b = static_cast<Data>(1);
//	for ( unsigned int n = 0; n < N; ++ n ) {
//		b *= a;
//	}
//
//	return b;
//}


/**
 * @brief Template class to evaluate the \f$N\f$-power of a value.
 *
 * This will recursively call itself till the specialized class with \f$0\f$-power.
 */
template<typename Data, unsigned int N>
class power {
	public:
		/**
		 * The keyword `static` allows you to use the method without constructing the 
		 * object!
		 */
		static Data Eval ( const Data &a ) {
			return multiply( a, power<Data,N-1>::Eval(a) );
		}
};

/**
 * @brief Specialization of `power` class
 *
 * In the case `N == 0` the recursion must stop. That's what I am doing here: I just return
 * the 0-power of a number, i.e. return 1.
 *
 */
template<typename Data>
class power<Data,0> {
	public:
		static Data Eval ( const Data &a ) {
			/**
			 * This will give _unused argument_ warning at compile time.
			 */
			return (Data) 1;
		}
};

// TODO: Assignment 1: Task 3: Implement PolynomialTerm
template<typename Data, unsigned int N>
	inline static Data
PolynomialTerm ( const Data &c, const Data &x ) {
	return multiply( c, power<Data,N>::Eval( x ) );
}

// TODO: Assignment 1: Task 4: Implement Polynomial
template <typename Data, unsigned int N>
class Polynomial {
	public:
		static Data evaluate( const double *coeffs, const Data& value ) {
			return add( PolynomialTerm<Data,N>( coeffs[N], value ),
					Polynomial<Data,N-1>::evaluate( coeffs, value) );
		}
};

template <typename Data>
class Polynomial<Data,0> {
	public:
		static Data evaluate( const double *coeffs, const Data& value ) {
//			return coeffs[0];

			/**
			 * Explicitly call the `Polynomial::evaluate()` method to avoid warnigs at 
			 * compile-time.
			 */
			return PolynomialTerm<Data,0>( coeffs[0], value );
		}
};

int main(int argc, char **argv) {
	// create our polynomial object with fixed order
	const size_t order = 10;
	const size_t n_coefficients = order+1;
	Polynomial<double,order> polynomial;

	// setup the coefficients with random values
	double coefficients[n_coefficients];
	for ( size_t i=0; i < n_coefficients; ++ i ) {
		coefficients[i] = static_cast<double>(rand()) / RAND_MAX;
	}

	// evaluate our polynomial
	double value = 0.0;
	std::cout << "enter value: ";
	std::cin >> value;
	double result = polynomial.evaluate(coefficients, value);
	std::cout << "f(" << value << ") = " << coefficients[0] << "*(" << value << ")**0";
	for (size_t i=1; i < n_coefficients; ++i) {
		std::cout << " + " << coefficients[i] << "*(" << value << ")**" << i;
	}
	std::cout << " = " << result << std::endl;
	return  0;
}
