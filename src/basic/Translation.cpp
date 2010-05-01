/*
 * Translation.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Translation.hpp"


/**
 * Creates a new %Translation from an XML tag.
 * 
 * @param tag XML tag with "x", "y", and "z" values.
 */
Translation::Translation(const Tag &tag) {
	
	// Initialize
	tag.get("x", x, false);
	tag.get("y", y, false);
	tag.get("z", z, false);
}


/**
 * Adds a vector to this translation.
 */
void Translation::add(const Vector &B) {
	
	// Add components
	x += B.x;
	y += B.y;
	z += B.z;
}


/**
 * Performs the translation.
 */
void Translation::apply() {
	
	// Translate
	glPushMatrix();
	glTranslatef(x, y, z);
}


/**
 * Add the translation to the matrix before sorting.
 */
void Translation::sortByDepthBeg(Matrix &matrix) {
	
	Matrix transMatrix(1.0, 0.0, 0.0,  +x,
	                   0.0, 1.0, 0.0,  +y,
	                   0.0, 0.0, 1.0,  +z,
	                   0.0, 0.0, 0.0, 1.0);
	
	// Add in translation
	matrix = matrix * transMatrix;
}


/**
 * Remove the translation from the matrix after sorting.
 */
void Translation::sortByDepthEnd(Matrix &matrix) {
	
	Matrix transMatrix(1.0, 0.0, 0.0,  -x,
	                   0.0, 1.0, 0.0,  -y,
	                   0.0, 0.0, 1.0,  -z,
	                   0.0, 0.0, 0.0, 1.0);
	
	// Remove translation
	matrix = matrix * transMatrix;
}


/**
 * Restores transformation that was in effect before Translation was applied.
 */
void Translation::remove() {
	
	// Restore
	glPopMatrix();
}


/**
 * Forms a string from the object's attributes.
 */
string Translation::toString() const {
	
	ostringstream stream;
	
	// Build string
	stream << Node::toString();
	stream << " x='" << x << "'"
	       << " y='" << y << "'"
	       << " z='" << z << "'";
	return stream.str();
}
