/**
 *
 *
 *           @name  eta.h
 *
 *        @version  1.0
 *           @date  11/09/2014 (11:04:05 PM)
 *       @revision  none
 *       @compiler  gcc
 *
 *
 *         @author  P. Di Giglio (github.com/pdigiglio), <p.digiglio91@gmail.com>
 *        @company  
 *          @brief  Header for `ETA` function.
 *
 *          Example usage:
 *          @code
 *          @endcode
 *
 *
 */

#ifndef  eta_INC
#define  eta_INC

#include <stdio.h>

//!
//! \brief Simple funtion to get elapsed time (in seconds).
//!
//! Takes a `clock_t start` time as input and evaluates the difference
//! between `start` and the current value of `clock()` divided by the number of
//! clock per second (`CLOCK_PER_SEC` macro) to get the time in seconds.
//!
//!	\param start the time from which measure elapsed time
//!	\return elapsed time in seconds
//!
	double
getETA ( clock_t start ) {
	return (double) ( clock() - start ) / CLOCKS_PER_SEC;
}		/* -----  end of function getETA  ----- */

//!
//! \brief Simple funtion to print elapsed time to a stream.
//!
//! Calls `getETA()` and prints the result to a stream (default `stdout`).
//!
	void
printETA ( clock_t start, FILE *stream = stdout ) {
	fprintf( stream, "%lf\n",  (double) ( clock() - start ) / CLOCKS_PER_SEC );
}		/* -----  end of function ETA  ----- */

//!
//! \brief Simple funtion to inform user of the elapsed time.
//!
//! Calls `getETA()` and prints the result to a stream.
//! The default stream is `stderr` to avoid problem when redirecting output in text
//! file or `/dev/null`.
//!
	void
fancyPrintETA ( clock_t start, FILE *stream = stderr ) {
	fprintf( stream, "Esecution time: %lfs\n", 
		(double) ( clock() - start ) / CLOCKS_PER_SEC );
}		/* -----  end of function ETA  ----- */
#endif   /* ----- #ifndef eta_INC  ----- */
