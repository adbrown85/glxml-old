/*
 * Sort.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "AdvancedFactory.hpp"
#include "Tester.hpp"


int main(int argc, char *argv[]) {

	Toolkit toolkit(argc, argv);
	Tester tester;
	
	AdvancedFactory::install();
	
	tester.open("test/advanced/Sort.xml");
	tester.start();
	
	return 0;
}

