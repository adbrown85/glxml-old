/*
 * AdvancedFactory.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <cassert>
#include "AdvancedFactory.hpp"
#include <edo/Parser.hpp>
#include <edo/Text.hpp>


void testCreate(const string &text) {
	
	Node *node;
	Tag tag;
	
	tag = Parser::create(text);
	node = Factory::create(tag);
	cout << node << endl;
	assert(tag.getName() == Text::toLower(node->getClassName()));
}


int main(int argc,
         char *argv[]) {
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "AdvancedFactory" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	try {
		AdvancedFactory::install();
		testCreate("blend");
		testCreate("cull faces='front'");
		testCreate("framebuffer");
		testCreate("fullscreen");
		testCreate("octree name='octree' link='volume'");
		testCreate("target link='buffer'");
		testCreate("wireframe");
	} catch (exception &e) {
		cerr << e.what() << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "AdvancedFactory" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

