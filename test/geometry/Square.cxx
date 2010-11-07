/*
 * Square.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Square.hpp"
#include "Tester.hpp"
#include "BasicFactory.hpp"


int main(int argc, char *argv[]) {

	Toolkit kit(argc, argv);
	Tester tester;
	
	BasicFactory::install();
	
	tester.open("test/basic/Square.xml");
	tester.start();
	
	return 0;
}

