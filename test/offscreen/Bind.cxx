/*
 * Bind.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "glxml_common.h"
#include "Bind.hpp"
#include "Tester.hpp"
#include "AdvancedFactory.hpp"


int main(int argc, char *argv[]) {
	
	Toolkit toolkit(argc, argv);
	Tester tester;
	
	AdvancedFactory::install();
	
	tester.open("test/basic/Bind.xml");
	tester.start();
	
	return 0;
}

