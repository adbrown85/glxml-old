/*
 * BasicFactory.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "glxml_common.h"
#include <cassert>
#include <edo/Parser.hpp>
#include <edo/Text.hpp>
#include "BasicFactory.hpp"


void testCreate(const string &text) {
	
	Node *node;
	Tag tag;
	
	tag = Parser::create(text);
	node = Factory::create(tag);
	cout << "  " << node << endl;
}


int main(int argc, char *argv[]) {
	
	// Test
	try {
		BasicFactory::install();
		testCreate("cube");
		testCreate("program");
		testCreate("scale");
		testCreate("shader file='../../glsl/basic.frag'");
		testCreate("square");
		testCreate("texture name='crate' file='../../textures/crate.jpg'");
		testCreate("texture file='../../textures/chunk.vlb'");
		testCreate("translate");
		testCreate("uniform type='int' name='bar'");
	} catch (exception &e) {
		cerr << e.what() << endl;
	}
	return 0;
}

