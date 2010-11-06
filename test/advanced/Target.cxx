/*
 * Target.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Target.hpp"
#include "Tester.hpp"
#include "AdvancedFactory.hpp"


int main(int argc, char *argv[]) {

	Toolkit toolkit(argc, argv);
	Tester tester;
	
	AdvancedFactory::install();
	
	tester.open("test/advanced/Target.xml");
	tester.start();
	
	return 0;
}

