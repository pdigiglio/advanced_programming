/**
 *
 *
 *           @name  mm_mult.cpp
 *
 *          @brief  Program to play around with matrix multiplications.
 *
 *          @attention Make sure you compile it with the `-std=c++11` option!
 *
 *
 *        @version  1.0
 *           @date  01/08/2015 (09:23:07 PM)
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
#include <cmath>
#include <cstdlib>

// memcpy
#include <string.h>

// NOTE: this requires C++11 support
#include <chrono>

/**
 * @brief Definition for the block-matrix multiplication function pointer.
 *
 * Define a new type for passing functions pointer to functions as parameter
 * without having to copy the complete prototype (e.g. see `testFunctionBlock()` prototype)
 */
typedef void (*mm_mult_block_ptr)(size_t rows, size_t columns, size_t k, double *A, double *B, double *C, size_t blocksize);
/**
 * @brief Definition for the (normal) matrix multiplication function pointer.
 */
typedef void (*mm_mult_ptr)(size_t rows, size_t columns, size_t k, double *A, double *B, double *C);

// TODO: ASSIGNMENT 1: compute expected performance in GFLOP/s

/**
 * @brief Compute expected performance in GFLOP/s
 *
 * @param memory_bandwidth
 * @param rows rows of the first matrix
 * @param columns columns of the second matrix
 * @param k columns of the first matrix = rows of the second matrix
 */
	void
estimate_mm_mult_performance(
  /* machine properties */
    double memory_bandwidth,

    /* matrix properties */
    size_t rows,
    size_t columns,
    size_t k
) {
    // TODO: replace this value with the main clock frequency of your system.
    double CLOCK_FREQUENCY_IN_GHZ = 2.53;

    // count the number of memory accesses for matrix multiplication
    // TODO: Explain how this value was derived.
	
	/**
	 * For the first matrix I have a continuous row access so I load only \f$r\times k\f$
	 * variables. For the second one I have a summation over column: for each element of
	 * the column I load the row i.e. I load \f$k\times c\f$ variables for each raw of the
	 * first matrix so at the end there are \f$k\times c \times r\f$ accesses. Also I need
	 * to write the values into a \f$r\times c\f$ matrix. At the end I perform
	 * \f$ rk + rkc + rc\f$ accesses.
	 */
    size_t total_number_of_memory_accesses = columns * k * rows + rows * k + columns * rows;

    // TODO: count the number of flops in matrix multiplication
	
	/**
	 * For each element of the resulting matrix I perform \f$k\f$ multiplications and \f$k-1\f$
	 * summations: at the end there are \f$rc(2k - 1)\f$ operations.
	 */
	double flops = rows * columns * ( 2 * k - 1 );

    // TODO: compute computational intensity
	
	/**
	 * The _computational intensity_ is just the number of operations that I perform for
	 * each memory access.
	 */
	double computational_intensity = flops / total_number_of_memory_accesses;
    std::cout << "computational intensity: " << computational_intensity << std::endl;

    for (unsigned int vector_size = 1; vector_size <= 8; vector_size*=2) {
        // TODO: compute maximum achievable performance using different vector sizes

		/**
		 * The maximum achievable performance is the _processor clock_ times the _vector size_
		 * (i.e. number of variables which I can load for each cycle) times the _numbers of
		 * cores_ (only one) times the _FLOPs_.
		 */
        double maximum_performance_in_gflops = CLOCK_FREQUENCY_IN_GHZ * vector_size * flops;

        // TODO: compute the memory bandwidth in terms of doubles
        double double_memory_bandwidth = memory_bandwidth / sizeof( double );

        // TODO: compute expected performance according to the roofline model in the lecture

		/**
		 * The expected performance is the _maximum performance_ times the _memory
		 * bandwidth_ (in this case referred to `double` since the `vector_size` is the
		 * number of `double` that one can load per cycle).
		 */
		// XXX XXX XXX XXX XXX This seems not to be correct
        double expected_performance = maximum_performance_in_gflops * double_memory_bandwidth;

        std::cout << "expected performance for " << CLOCK_FREQUENCY_IN_GHZ
                  << " GHZ and vectorsize " << vector_size
                  << ": " << expected_performance
                  << " GFLOPS"
                  << std::endl;
    }
}

// TODO: ASSIGNMENT 2
// base version - row - column - k
// C[rows,columns] = A [rows,k] * B [k,columns]

/**
 * @brief Multiplication between matrix: base version (row-col-k)
 *
 * @param rows rows of the first matrix
 * @param columns columns of the second matrix
 * @param k columns of the first matrix = rows of the second matrix
 * @param A first matrix pointer
 * @param B second matrix pointer
 * @param C resulting matrix pointer
 *
 */
	void
mm_mult_rck( size_t rows, size_t columns, size_t k, double *A, double *B, double *C ) {
	
    for ( unsigned int row = 0; row < rows; ++ row ) {
        for ( unsigned int col = 0; col < columns; ++ col ) {
//            for (int i=0; i < k; ++i) {
//                if (i==0) {
//                    C[row*columns+col] = A[row*k + i] * B[i*columns + col];
//                } else {
//	                C[row*columns+col] += A[row*k + i] * B[i*columns + col];
//                }
//				}

			/**
			 * `if`-statement are _bad_ into `for` loop. In most of the cases I would be in
			 * the second case so branching is stupid.
			 */

			// initialize the value with the first element of the sum
            C[ row * columns + col ] = A[ row * k ] * B[ col ];
			for ( unsigned int i = 1; i < k; ++ i ) {
				/**
				 * I am writing a matrix \f$A\f$ in a vector to have a continuous memory access
				 * (as well as for \f$C\f$) but I _will not_ have a continuous memory access for \f$B\f$
				 * (since `columns` is not 1).
				 */
	            C[ row * columns + col] += A[ row * k + i] * B[ i * columns + col ];
            }

        }
    }
}

// TODO: ASSIGNMENT 2
// TODO: loop reordering and loop splitting - col - k - row

/**
 * @brief Multiplication between matrix: loop reordering and splitting (col-k-row).
 *
 * @param rows rows of the first matrix
 * @param columns columns of the second matrix
 * @param k columns of the first matrix = rows of the second matrix
 * @param A first matrix pointer
 * @param B second matrix pointer
 * @param C resulting matrix pointer
 *
 */
	void
mm_mult_ckr(size_t rows, size_t columns, size_t k, double *A, double *B, double *C) {

	for ( unsigned int col = 0; col < columns; ++ col ) {
		
//		for ( unsigned int i = 0; i < k; ++ i ) {

			/** First assign initial values to the `C` matrix. */
			for ( unsigned int row = 0; row < rows; ++ row ) {
	            C[ row * columns + col ] = A[ row * k ] * B[ col ];
			}
//		}

		/** Then perform the rest of the matrix multiplication */
		for ( unsigned int i = 1; i < k; ++ i ) {
			for ( unsigned int row = 0; row < rows; ++ row ) {
				/**
				 * With this loop reordering \f$B\f$ is continuously accessed but \f$A\f$
				 * and \f$C\f$ are no more (since `columns` and `k` are different from 1).
				 */
	            C[ row * columns + col ] += A[ row * k + i ] * B[ i * columns + col ];
			}
		}
	}

}

// TODO: ASSIGNMENT 2
// TODO: loop splitting and loop reordering - k - row - col

/**
 * @brief Multiplication between matrix: loop reordering and splitting (k-row-col).
 *
 * @param rows rows of the first matrix
 * @param columns columns of the second matrix
 * @param k columns of the first matrix = rows of the second matrix
 * @param A first matrix pointer
 * @param B second matrix pointer
 * @param C resulting matrix pointer
 *
 */
void mm_mult_krc(size_t rows, size_t columns, size_t k, double *A, double *B, double *C) {

	/**
	 * Assign the initial values to \f$c\f$
	 */
	for ( unsigned int row = 0; row < rows; ++ row ) {

		for ( unsigned int col = 0; col < columns; ++ col ) {
			C[ row * columns + col] += A[ row * k] * B[ col ];
		}
	}

	/**
	 * Then perform the remaining part of the matrix multiplication
	 */
	for ( unsigned int i = 1; i < k; ++ i ) {

		for ( unsigned int row = 0; row < rows; ++ row ) {

			for ( unsigned int col = 0; col < columns; ++ col ) {
				/**
				 * In this loop both \f$B\f$ and \f$C\f$ are continuously accessed and
				 * \f$A\f$ remains constant in the inner loop.
				 */
	            C[ row * columns + col] += A[ row * k + i] * B[ i * columns + col ];
			}
		}
	}
}

// TODO: ASSIGNMENT 2: optional
// TODO: loop reordering - column - row - k
void mm_mult_crk(size_t rows, size_t columns, size_t k, double *A, double *B, double *C) {

}

// TODO: ASSIGNMENT 2: optional
// TODO: loop reordering and loop - k - col - row
void mm_mult_kcr(size_t rows, size_t columns, size_t k, double *A, double *B, double *C) {

}

// TODO: ASSIGNMENT 2: optional
// TODO: loop reordering and loop splitting - row - k - col
void mm_mult_rkc(size_t rows, size_t columns, size_t k, double *A, double *B, double *C) {

}

// TODO: ASSIGNMENT 3: cache blocking of standard combination - row - column - k
void mm_mult_rck_block(size_t rows, size_t columns, size_t k, double *A, double *B, double *C, size_t blocksize) {

}

/**
 * @brief Testing the matrix-multiplication functions.
 *
 * It's just a `for` loop which calls the `mm_mult` function `samples` time and prints the
 * elapsed time to the `stdout`.
 *
 * @param mm_mult function pointer to one of the matrix-multiplication functions previously
 * implemented
 * @param rows rows of the first matrix
 * @param columns columns of the second matrix
 * @param k columns of the first matrix = rows of the second matrix
 * @param samples number of times `mm_mult` is called
 * @param A first matrix pointer
 * @param B second matrix pointer
 * @param C resulting matrix pointer
 */
	void
testFunction( mm_mult_ptr mm_mult, size_t rows, size_t columns, size_t k, size_t samples, double *A, double *B, double *C) {
    
	for ( unsigned int sample = 0; sample < samples; ++ sample ) {

        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;

        start = std::chrono::system_clock::now();

        mm_mult(rows, columns, k, A, B, C);

        end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end - start;
        
        const double total_flops = ( 2 * k - 1 ) * rows * columns;
        const double flops_per_second = total_flops / elapsed_seconds.count();
        const double gflops_per_second = flops_per_second / 1000000000.0;

        std::cout << "sample " << sample 
                  << " elapsed time: " << elapsed_seconds.count() << "s"
                  << " GFLOP/s: " << gflops_per_second
                  << std::endl;
    }
}

	void
testFunctionBlock(mm_mult_block_ptr mm_mult_block, size_t rows, size_t columns, size_t k, size_t samples, size_t blocksize, double *A, double *B, double *C) {
    for ( unsigned int sample = 0; sample < samples; ++ sample ) {
        std::chrono::time_point<std::chrono::system_clock> start;
        std::chrono::time_point<std::chrono::system_clock> end;

        start = std::chrono::system_clock::now();

        mm_mult_block(rows, columns, k, A, B, C, blocksize);

        end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end-start;
        
        const double total_flops = ( 2 * k - 1) * rows * columns;
        const double flops_per_second = total_flops / elapsed_seconds.count();
        const double mflops_per_second = flops_per_second / 1000000.0;

        std::cout << "sample " << sample 
                  << " elapsed time: " << elapsed_seconds.count() << "s"
                  << " MFLOP/s: " << mflops_per_second
                  << std::endl;
    }

}

/**
 * @brief
 *
 * @return an estimate for the memory bandwidth
 */
	double
memory_bandwidth_check( size_t rows, size_t columns, double *src, double *dest ) {

    const size_t mem_size = rows * columns * sizeof( double );
    char *mem_src = reinterpret_cast<char*>(src);
    char *mem_dest = reinterpret_cast<char*>(dest);

    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> end;

    // There are two cases:
    // a) memory size is too big for cache, than there will be almost no difference
    // b) memory size fits into cache, than all further calls will be a lot faster
    // This allows us to approximate the speed of cache and memory using the same procedure.
    double memory_bandwidth = 0.0;
    for ( size_t sample = 0; sample < 5; ++ sample ) {
        start = std::chrono::system_clock::now();
        memcpy( mem_src, mem_dest, mem_size );
        end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end-start;

        memory_bandwidth = ( mem_size / elapsed_seconds.count() ) / (1.0e9);
        std::cout << "estimated read/write bandwidth: " 
                  << memory_bandwidth
                  << " GB/s"
                  << std::endl;
    }
    
    return memory_bandwidth;
}

 
int main(int argc, char **argv) {
    const size_t samples = 4;

    // NOTE: if you run into "out of memory" problems, reduce this number.
    // If you have a lot of memory, feel free to increase this number.
    size_t maximum_number_of_rows_and_columns = 1024;
 
	/**
	 * Define the matrices (which in this case are square).
	 */
    double *A = new double[maximum_number_of_rows_and_columns*maximum_number_of_rows_and_columns];
    double *B = new double[maximum_number_of_rows_and_columns*maximum_number_of_rows_and_columns];
    double *C = new double[maximum_number_of_rows_and_columns*maximum_number_of_rows_and_columns];

	/** Start looping from a certain `reference_size` till the size of the matrices */
    for ( size_t reference_size = 64; reference_size <= maximum_number_of_rows_and_columns; reference_size *= 2 ) {
        const size_t rows = reference_size;
        const size_t columns = reference_size;
        const size_t k = reference_size;

        std::cout << " ================== " << reference_size << " ================ " << std::endl;
 
        std::cout << "== estimates for loop order: row - column - k ==" << std::endl;
        double memory_bandwidth = memory_bandwidth_check( rows, columns, A, C );
        estimate_mm_mult_performance( memory_bandwidth, rows, columns, k );

        std::cout << "== loop order: row - column - k ==" << std::endl;
        testFunction( mm_mult_rck, rows,columns, k, samples, A, B, C);

        std::cout << "== loop order: column - row - k ==" << std::endl;
        testFunction(mm_mult_crk, rows,columns,k, samples,A,B,C);
     
        std::cout << "== loop order: k - row - column ==" << std::endl;
        testFunction(mm_mult_krc, rows,columns,k, samples,A,B,C);
 
        std::cout << "== loop order: k - column - row ==" << std::endl;
        testFunction(mm_mult_kcr, rows,columns,k, samples,A,B,C);

        std::cout << "== loop order: row - k - column ==" << std::endl;
        testFunction(mm_mult_rkc, rows,columns,k, samples,A,B,C);

        std::cout << "== loop order: column - k - row ==" << std::endl;
        testFunction(mm_mult_ckr, rows,columns,k, samples,A,B,C);


    }
 
    /* ----------------------------- */
 
    std::cout << std::endl << std::endl;

	/**
	 * Now split matrices into blocks.
	 */
    const size_t reference_size = maximum_number_of_rows_and_columns;
    for (size_t blocksize = 4; blocksize <= 128; blocksize *= 2 ) {
        std::cout << " ================== " << reference_size << "(" << blocksize << ") ================ " << std::endl;

        const size_t rows = reference_size;
        const size_t columns = reference_size;
        const size_t k = reference_size;

        std::cout << "== blocked loop order: row - column - k ==" << std::endl;
        testFunctionBlock(mm_mult_rck_block,rows,columns,k,samples,blocksize,A,B,C);
    }
  
    /* ----------------------------- */

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}
