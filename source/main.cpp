/* NAME          : main.cpp
 * PURPOSE       : Main program file.
 * CREATION DATE : 06.08.2021
 * LAST UPDATE   : 11.08.2021
 */

#include "parser\parser.h"

// Single tone declaration
acrtx::raytracer acrtx::raytracer::Instance;

/* Main program function.
 * ARGUMENTS: 
 *   - Number of console arguments:
 *       INT ArgC;
 *   - String console arguments:
 *       CHAR *ArgV[].
 * RETURNS: None.
 */
INT main( INT ArgC, CHAR *ArgV[] )
{
  acrtx::parser Read;

  // double X = strtod("12 3 mas cdcdmk", nullptr);
  // if (ArgC > 1)
  Read.ParseFile("scene_2.txt");
} /* End of 'main' function */

/* END OF 'main.cpp' FILE */