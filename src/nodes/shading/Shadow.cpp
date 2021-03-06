/*
 * Shadow.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Shadow.hpp"

/** Initializes attributes.
 * 
 * @throw NodeException if cannot open subscene.
 */
Shadow::Shadow(const Tag &tag) : Texture(tag) {
	
	// Retrieve from tag
	tag.get("of", of, true, false);
	tag.get("from", from, true, false);
	
	// Check name
	if (!hasName()) {
		NodeException e(getTag());
		e << "[Shadow] Must have name.";
		throw e;
	}
	
	// Subscene
	try {
		openSubscene();
	} catch (exception &e) {
		glog << e.what();
		NodeException ex(getTag());
		ex << "[Shadow] Could not open subscene.";
		throw ex;
	}
}

/** Finds the group, light, and transforms. */
void Shadow::associate() {
	
	Texture::associate();
	
	findGroup();
	findLight();
	findTransforms();
}

/** Prepares the subscene and performs an initial render. */
void Shadow::finalize() {
	
	Texture::finalize();
	
	// Subscene
	try {
		prepareSubscene();
	} catch (exception &e) {
		glog << e.what() << endl;
		NodeException ex(getTag());
		ex << "[Shadow] Could not prepare subscene.";
		throw ex;
	}
	
	// Render
	render();
}

/** Finds the group named by @e of. 
 * 
 * @throw NodeException if group not found.
 */
void Shadow::findGroup() {
	
	group = Scout<Group>::search(findRoot(this), of);
	if (group == NULL) {
		NodeException e(tag);
		e << "[Shadow] Could not find group named '" << of << "'.";
		throw e;
	}
}

/** Finds the light named by @e from.
 * 
 * @throw NodeException if light not found.
 */
void Shadow::findLight() {
	
	// Find the node
	light = Light::search(Node::findRoot(this), from);
	if (light == NULL) {
		NodeException e(tag);
		e << "[Shadow] Light named '" << from << "' not found.";
		throw e;
	}
}

/** Finds the transforms above the light and group and adds listeners. */
void Shadow::findTransforms() {
	
	list<Transform*> transforms;
	list<Transform*>::iterator it;
	
	// Get all the transforms
	Transform::search(group, transforms);
	Transform::findAll(light, transforms);
	
	// Add listeners
	for (it=transforms.begin(); it!=transforms.end(); ++it) {
		(*it)->addListener(this, NodeEvent::MODIFY);
	}
}

/** Opens the subscene required by shadow. */
void Shadow::openSubscene() {
	
	Target *target;
	Clone *clone;
	
	// Open
	SubsceneUser::openSubscene(SHADOW_SUBSCENE);
	
	// Replace attributes of some nodes
	target = Scout<Target>::search(getSubsceneRoot());
	target->setLink(getName());
	clone = Scout<Clone>::search(getSubsceneRoot());
	clone->setOf(of);
}

/** Prepares the subscene required by shadow. */
void Shadow::prepareSubscene() {
	
	// Prepare
	addChild(getSubsceneRoot());
	SubsceneUser::prepareSubscene();
	removeChild(getSubsceneRoot());
}

/** Renders the group into the shadow map. */
void Shadow::render() {
	
	Matrix matrix;
	
	// Check subscene
	if (!isSubsceneOpened())
		return;
	
	// Set up view from light
	matrix = light->getTransformationInverse();
	State::setMode(MODEL_MODE);
	State::push();
	State::apply(matrix);
	
	// Run the scene
	traverseSubscene();
	
	// Remove view from light
	State::pop();
}

/** @return String comprised of the node's attributes. */
string Shadow::toString() const {
	
	ostringstream stream;
	
	stream << Texture::toString();
	stream << " of='" << of << "'"
	       << " from='" << from << "'";
	return stream.str();
}
