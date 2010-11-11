/*
 * Uniform.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Uniform.hpp"
#include "Tester.hpp"
#include "BasicFactory.hpp"


int main(int argc, char *argv[]) {
	
	Toolkit toolkit(argc, argv);
	Tester tester;
	
	BasicFactory::install();
	
	tester.open("test/basic/UniformMatrix.xml");
	tester.start();
	
	return 0;
}

