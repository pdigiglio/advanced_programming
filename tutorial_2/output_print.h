/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  output_print
 *  Description:  
 * =====================================================================================
 */
void
output_print ( double a, double b, char o, double result ) {
	std::cout << a << " " << o << " " << b <<
		" = " << result << std::endl;
}		/* -----  end of function output_print  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  output_print
 *  Description:  
 * =====================================================================================
 */
void
output_print ( double a, std::string op, double result ) {
	std::cout << op << "( pi * " << a << " ) = " << result << std::endl;
}		/* -----  end of function output_print  ----- */
