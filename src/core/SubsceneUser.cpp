/*
 * SubsceneUser.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "SubsceneUser.hpp"

/** Initializes attributes. */
SubsceneUser::SubsceneUser() {
	
	traverser = NULL;
	opened = false;
}

/** Destroys the traverser. */
SubsceneUser::~SubsceneUser() {
	
	if (traverser != NULL) {
		delete traverser;
		traverser = NULL;
	}
}

/** Opens the subscene using @e filename from resources directory.
 * 
 * @throw BasicException if already opened.
 */
void SubsceneUser::openSubscene(const string &filename) {
	
	// Check if already opened
	if (opened) {
		throw BasicException("[SubsceneUser] Subscene already opened.");
	}
	
	// Open
	subscene.open(Resources::get(filename));
	traverser = new Traverser(&subscene);
	opened = true;
}

