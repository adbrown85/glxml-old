/*
 * Translate.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Translate.hpp"

/** Creates a new %Translate from an XML tag.
 * 
 * @param tag XML tag with "value", "x", "y", or "z" attributes.
 */
Translate::Translate(const Tag &tag) : Transform(tag) {
	
	float arr[4];
	
	if (tag.get("value", arr, false)) {
		value.x = arr[0];
		value.y = arr[1];
		value.z = arr[2];
	} else {
		tag.get("x", value.x, false);
		tag.get("y", value.y, false);
		tag.get("z", value.z, false);
	}
	value.w = 1.0;
}

/** Adds a vector to this translation. */
void Translate::add(const Vec4 &B) {
	
	value.x += B.x;
	value.y += B.y;
	value.z += B.z;
	fireEvent(NodeEvent(this, NodeEvent::MODIFY));
}

/** Performs the translation. */
void Translate::apply() {
	
	State::push();
	State::apply(getMatrix());
}

/** Add the translate to the matrix before sorting. */
void Translate::applyTo(Matrix &matrix) {
	
	Matrix T(1.0, 0.0, 0.0,  +value.x,
	         0.0, 1.0, 0.0,  +value.y,
	         0.0, 0.0, 1.0,  +value.z,
	         0.0, 0.0, 0.0, 1.0);
	
	// Add in translation
	matrix = matrix * T;
}

/** Restores transformation that was in effect before translate was applied. */
void Translate::remove() {
	
	State::pop();
}

/** Sets "x", "y", or "z" in value. */
bool Translate::setAttribute(pair<string,string> attribute) {
	
	bool changed=false;
	string key=Text::toLower(attribute.first);
	
	if (key == "x") {
		value.x = atof(attribute.second.c_str());
		changed = true;
	} else if (key == "y") {
		value.y = atof(attribute.second.c_str());
		changed = true;
	} else if (key == "z") {
		value.z = atof(attribute.second.c_str());
		changed = true;
	}
	
	if (changed) {
		fireEvent(NodeEvent(this, NodeEvent::MODIFY));
		return true;
	} else {
		return false;
	}
}

/** Forms a string from the object's attributes. */
string Translate::toString() const {
	
	ostringstream stream;
	
	// Build string
	stream << Node::toString();
	stream << " x='" << value.x << "'"
	       << " y='" << value.y << "'"
	       << " z='" << value.z << "'";
	return stream.str();
}
