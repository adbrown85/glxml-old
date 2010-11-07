/*
 * Framebuffer.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Framebuffer.hpp"
#include "Tester.hpp"
#include "AdvancedFactory.hpp"


int main(int argc, char *argv[]) {
	
	Toolkit toolkit(argc, argv);
	Tester tester;
	
	AdvancedFactory::install();
	
	tester.open("test/advanced/Framebuffer.xml");
	tester.start();
	
	return 0;
}

