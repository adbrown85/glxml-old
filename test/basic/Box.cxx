/*
 * Box.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Box.hpp"
#include "Tester.hpp"
#include "BasicFactory.hpp"


int main(int argc, char *argv[]) {

	Toolkit kit(argc, argv);
	Tester tester;
	
	BasicFactory::install();
	
	tester.open("test/basic/Box.xml");
	tester.start();
	
	return 0;
}

