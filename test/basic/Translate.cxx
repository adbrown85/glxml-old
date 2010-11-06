/*
 * Translate.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <ctime>
#include "Translate.hpp"
#include "BasicFactory.hpp"
#include "Tester.hpp"


/** Unit test for Translate. */
int main(int argc, char *argv[]) {

	Toolkit toolkit(argc, argv);
	Tester tester;
	
	BasicFactory::install();
	
	tester.open("test/basic/Translate.xml");
	tester.start();
	
	return 0;
}

