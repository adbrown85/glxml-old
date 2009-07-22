/*
 * Translation.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Translation.hpp"



Translation::Translation() {
	
}



Translation::Translation(float x,
                         float y,
                         float z) : 
                         Vector(x, y, z) {
	
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
 * Restores transformation that was in effect before Translation was applied.
 */
void Translation::remove() {
	
	// Restore
	glPopMatrix();
}