/*
 * SubsceneUser.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_SUBSCENEUSER_HPP
#define GLXML_SUBSCENEUSER_HPP
#include "glxml_common.h"
#include "Scene.hpp"
#include "Traverser.hpp"
#include "Resources.hpp"
using namespace std;

/** @brief Base class for an object that opens and runs a separate scene.
 * 
 * %SubsceneUser is great when a node requires already-existing functionality 
 * in other nodes to complete some action.  The developer can write an XML 
 * scene file with those nodes and load it at runtime, then simply traverse it 
 * to perform those actions.
 * 
 * Because the subscene should always be available to the program, 
 * %SubsceneUser automatically looks for the subscene in the resources 
 * directory using the Resources class.
 * 
 * @ingroup core
 */
class SubsceneUser {
public:
	SubsceneUser();
	virtual ~SubsceneUser();
// Getters and setters
	virtual bool isSubsceneOpened() const;
	virtual Node* getSubsceneRoot() const;
protected:
	virtual void openSubscene(const string &filename);
	virtual void prepareSubscene();
	virtual void traverseSubscene() const;
private:
	bool opened;
	Scene subscene;
	Traverser *traverser;
};

/** @return Root node of the subscene. */
inline Node* SubsceneUser::getSubsceneRoot() const {return subscene.getRoot();}

/** @return True if the subscene was successfully opened. */
inline bool SubsceneUser::isSubsceneOpened() const {return opened;}

/** Prepares the subscene. */
inline void SubsceneUser::prepareSubscene() {subscene.prepare();}

/** Traverse the subscene. */
inline void SubsceneUser::traverseSubscene() const {traverser->start();}

#endif
