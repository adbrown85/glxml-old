/*
 * Wireframe.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "BasicFactory.hpp"
#include "Tester.hpp"


int main(int argc, char *argv[]) {

	Toolkit toolkit(argc, argv);
	Tester tester;
	
	BasicFactory::install();
	
	tester.open("test/basic/Wireframe.xml");
	tester.start();
	
	return 0;
}

