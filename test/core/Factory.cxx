/*
 * Factory.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Factory.hpp"

Node* createShape(const Tag &tag) {
	
	cout << "createShape()" << endl;
	cout << tag << endl;
	return new Node(tag);
}

Node* createTexture(const Tag &tag) {
	
	cout << "createTexture()" << endl;
	cout << tag << endl;
	return new Node(tag);
}

Node* createTransform(const Tag &tag) {
	
	cout << "createTransform()" << endl;
	cout << tag << endl;
	return new Node(tag);
}

int main(int argc, char *argv[]) {
	
	Node *node;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Factory" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	try {
		Factory::install("shape", &createShape);
		Factory::install("texture", &createTexture);
		Factory::install("transform", &createTransform);
		node = Factory::create("shape");
		node = Factory::create("texture file='crate.jpg'");
		node = Factory::create("texture file='${GANDER}/textures/crate.jpg'");
		node = Factory::create("transform");
		node = Factory::create("transformation");
	} catch (exception &e) {
		cerr << e.what() << endl;
	}
	
	// End
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Factory" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

