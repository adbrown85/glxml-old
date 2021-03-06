/*
 * Shape.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <ctime>
#include <iostream>
#include "Shape.hpp"
#include "Translate.hpp"
#define NUMBER_OF_ITEMS 4
using namespace std;


class FakeShape : public Shape {
public:
	FakeShape(const Tag &tag) : Shape(tag,getTraits()) {}
	static ShapeTraits getTraits();
	virtual void draw() const {};
	virtual void updateBuffer() {};
};

ShapeTraits FakeShape::getTraits() {
	
	ShapeTraits traits;
	
	traits.count = 24;
	traits.mode = GL_QUADS;
	traits.usage = GL_STATIC_DRAW;
	traits.attributes.push_back("MCVertex");
	traits.attributes.push_back("MCNormal");
	traits.attributes.push_back("TexCoord0");
	return traits;
}


int main() {
	
	FakeShape *shape;
	Tag tag;
	
	// Tag
	try {
		cout << "Testing tag..." << endl;
		tag["size"] = "5.5";
		tag["style"] = "3D";
		shape = new FakeShape(tag);
		cout << "  " << *shape << endl;
	} catch (exception &e) {
		cerr << e.what() << endl;
		exit(1);
	}
}

