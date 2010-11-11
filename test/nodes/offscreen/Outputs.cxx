/*
 * Outputs.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Outputs.hpp"
#include "Tester.hpp"
#include "AdvancedFactory.hpp"


int main(int argc, char *argv[]) {

	Toolkit toolkit(argc, argv);
	Tester tester;
	
	AdvancedFactory::install();
	
	tester.open("test/advanced/Outputs.xml");
	tester.start();
	
	return 0;
}

