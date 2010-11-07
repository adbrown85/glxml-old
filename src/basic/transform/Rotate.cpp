/*
 * Rotate.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Rotate.hpp"


/** Creates a new %Rotate from an XML tag.
 * 
 * @param tag XML tag with "angle" and "axis" values.
 */
Rotate::Rotate(const Tag &tag) : Transform(tag) {
	
	float arr[4];
	
	tag.get("angle", angle, true);
	tag.get("axis", arr, true);
	axis.x = arr[0];
	axis.y = arr[1];
	axis.z = arr[2];
	axis.z = arr[3];
	axis = normalize(axis);
	quaternion.set(angle, axis);
}


/** Performs the transformation. */
void Rotate::apply() {
	
	State::push();
	State::apply(quaternion.getMatrix());
}


void Rotate::applyTo(Matrix &matrix) {
	
	matrix = matrix * quaternion.getMatrix();
}


/** Restores state before transformation was applied. */
void Rotate::remove() {
	
	State::pop();
}


/** Forms a string from the object's attributes. */
string Rotate::toString() const {
	
	ostringstream stream;
	
	stream << fixed << setprecision(2);
	
	stream << Node::toString();
	stream << " angle='" << angle << "'"
	       << " axis='" << axis.x << " " << axis.y << " " << axis.z << "'";
	return stream.str();
}

