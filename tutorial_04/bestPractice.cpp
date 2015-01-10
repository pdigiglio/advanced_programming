//
/// bestPractice2.cpp
//
///     by Paul Sarbu
//
/// Advanced Programming tutorial
//


// => a must read article for optimizing your code:
///    http://www.tantalon.com/pete/cppopt/asyougo.htm
// main article: http://www.tantalon.com/pete/cppopt/main.htm

// => a good read on floating-point problems
// (although specific to Intel compilers, most problems are still valid in general)
///    https://software.intel.com/sites/default/files/comment/1673734/fp-consistency-102511.pdf


/************************************************
*
*   Casting values
*
******************************************/

// usually most numerical casting problems come with division:
double x = 1 / 3;  // => x = 0

// bad way to fix it:
double x = (double)(1 / 3);   // => x = 0

// right way to fix:
double x = (double)(1) / 3; // or: double x = 1. / 3;

// when casting is required, do it from the inside out and preferably
// only once per operation:
double x = (double)(1) / (double)(3);   // too much casting (not necessary)

// when one of the values in the operation is a numeric constant, it's
// easier and better to specify directly if you want it as a floating point
int y = 20;
double x = 5. / y; // wrong way to do it would be: double x = 5 / y;

// of course, in some cases (e.g. transforming a number from one base to another)
// we really want the automatic casting of the division operator:
int r = 5 % 2;
int d = 5 / 2;
if ( 5 == (2 * d + r) )
    std::cout << "Of course it is! :)";

/************************************************
*
*   Overflows & truncation
*
******************************************/


// this will never end
for (char i = 0; i < 128; i++) {}

// remember to always set the type of the index
// to fit the loop limits and the step !!!

// this is not good either: overkill
for (double i = -1; i <= 1; i++) {}

// and this is just wrong... (it works, just not as planned)
for (int i = 0; i < 300; i += 1.5) {}


/************************************************
*
*   Variable re-usage & scope
*
******************************************/


// version 1
int i;
for (i = 0; i < 100; i++)
    int x = i * i;

// version 2
int i, x;
for (i = 0; i < 100; i++)
    x = i * i;

// version 3
for (int i = 0; i < 100; i++)
    int x = i * i;

// version 4
int x;
for (int i = 0; i < 100; i++)
    x = i * i;

// when working with built in standard types,
// there is little to no difference in performance;
// still, I recommend to not stick to a single option
// and think about each context to see which one makes
// more sense in a particular case

/************************************************

// please refer to the given article for more

/************************************************
    Happy coding!
