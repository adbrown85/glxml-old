/*
 * Fullscreen.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Fullscreen.hpp"
#include "Tester.hpp"
#include "AdvancedFactory.hpp"


int main(int argc, char *argv[]) {

	Toolkit toolkit(argc, argv);
	Tester tester;
	
	AdvancedFactory::install();
	
	tester.open("test/advanced/Fullscreen.xml");
	tester.start();
	
	return 0;
}

