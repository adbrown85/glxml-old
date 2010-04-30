/*
 * Octree.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Octree.hpp"
#include "Tester.hpp"
#include "BasicFactory.hpp"
#include "AdvancedFactory.hpp"


int main(int argc,
         char *argv[]) {
	
	try {
		BasicFactory::install();
		AdvancedFactory::install();
		Window::init(argc, argv);
		Tester::open("Octree.xml");
		Tester::start();
	} catch (const char *e) {
		cerr << e << endl;
	}
	return 0;
}

