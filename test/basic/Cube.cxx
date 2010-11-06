/*
 * Cube.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Cube.hpp"
#include "Tester.hpp"
#include "BasicFactory.hpp"


int main(int argc, char *argv[]) {

	Toolkit toolkit(argc, argv);
	Tester tester;
	
	BasicFactory::install();
	
	tester.open("test/basic/Cube.xml");
	tester.start();
	
	return 0;
}

