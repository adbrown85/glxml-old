/*
 * Boolean.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Boolean.hpp"
float Boolean::FLT_INF;

/** Creates a new %Boolean node.
 * 
 * @throw Exception if @e of attribute not present
 * @throw Exception if @e operation attribute not present
 * @throw NodeException if float is not signed
 */
Boolean::Boolean(const Tag &tag, ShapeTraits traits) : Hexahedron(tag,traits) {
	
	// Get tag attributes
	tag.get("of", of);
	tag.get("operation", operation);
	selectable = false;
	
	// Check operations will work correctly
	if (numeric_limits<float>::is_signed) {
		if (numeric_limits<float>::has_infinity) {
			FLT_INF = numeric_limits<float>::infinity();
		} else {
			FLT_INF = numeric_limits<float>::max();
		}
	} else {
		NodeException e(tag);
		e << "[Boolean] Cannot perform boolean without signed float.";
		throw e;
	}
}

/** Deletes all the uniforms stored. */
Boolean::~Boolean() {
	
	list<Uniform*>::iterator it;
	
	// Delete each uniform
	for (int i=0; i<2; ++i) {
		for (it=uniforms[i].begin(); it!=uniforms[i].end(); ++it) {
			delete (*it);
		}
	}
}

/** Applies all the uniforms for all of the shapes. */
void Boolean::applyUniforms() const {
	
	list<Uniform*>::const_iterator it;
	
	// Apply each uniform for each shape
	for (int i=0; i<2; ++i) {
		for (it=uniforms[i].begin(); it!=uniforms[i].end(); ++it) {
			(*it)->apply();
		}
	}
}

/** Applies all the uniforms for one of the shapes. */
void Boolean::applyUniforms(int i) const {
	
	list<Uniform*>::const_iterator it;
	
	// Apply each uniform for shape
	for (it=uniforms[i].begin(); it!=uniforms[i].end(); ++it) {
		(*it)->apply();
	}
}

/** Finds the group, shapes, transforms, and uniforms needed by the operation.
 * 
 * @throw NodeException from Shape::associate()
 */
void Boolean::associate() {
	
	Hexahedron::associate();
	
	// Find nodes
	findGroup();
	findShapes();
	findTransforms();
	findUniforms();
	
	// Associate
	associateUniforms();
}

/** Associates all the uniforms. */
void Boolean::associateUniforms() {
	
	list<Uniform*>::iterator it;
	
	// Associate each uniform
	for (int i=0; i<2; ++i) {
		for (it=uniforms[i].begin(); it!=uniforms[i].end(); ++it) {
			(*it)->setParent(this);
			(*it)->associate();
		}
	}
}

/** Boolean shape is not correct and must be recalculated. */
void Boolean::calculate() {
	
	calculateExtents();
	calculateOverlap();
	calculateTangible();
}

/** Traverse the group and calculate extents for each shape. */
void Boolean::calculateExtents() {
	
	// Load identity matrix
	State::setMode(MODEL_MODE);
	State::push();
	State::loadIdentity();
	
	// Collect all the extents in the group
	extents.clear();
	calculateExtents(group);
	
	// Restore original matrix
	State::pop();
}

/** Traverse a subtree and calculate extents for each shape. */
void Boolean::calculateExtents(Node *node) {
	
	Node::iterator it;
	Transform *transform;
	Shape *shape;
	
	// Apply and remove transform nodes
	if ((transform = dynamic_cast<Transform*>(node))) {
		transform->apply();
		for (it=transform->begin(); it!=transform->end(); ++it)
			calculateExtents(*it);
		transform->remove();
	}
	
	// Store extents of shapes
	else if ((shape = dynamic_cast<Shape*>(node))) {
		Extent extent;
		modelMatrix = State::getModelMatrix();
		extent.upper = modelMatrix * Vec4(+0.5,+0.5,+0.5,1.0);
		extent.lower = modelMatrix * Vec4(-0.5,-0.5,-0.5,1.0);
		extent.diagonal = extent.upper - extent.lower;
		extent.label = shape->getID();
		extent.index = extents.size();
		extents.push_back(extent);
	}
	
	// Otherwise just do children
	else {
		for (it=node->begin(); it!=node->end(); ++it) {
			calculateExtents(*it);
		}
	}
}

/** Find where the shapes overlap. */
void Boolean::calculateOverlap() {
	
	vector<Extent>::iterator it;
	
	// Form shape
	overlap.upper = Vec4(+FLT_INF);
	overlap.lower = Vec4(-FLT_INF);
	for (it=extents.begin(); it!=extents.end(); ++it) {
		overlap.upper = min(overlap.upper, it->upper);
		overlap.lower = max(overlap.lower, it->lower);
	}
	overlap.diagonal = overlap.upper - overlap.lower;
}

/** Only draw the boolean operation if its output is tangible. */
void Boolean::draw() const {
	
	// Only draw if tangible
	if (tangible) {
		Hexahedron::draw();
	}
}

/** Creates the shape and finalizes all the uniforms. */
void Boolean::finalize() {
	
	calculate();
	Hexahedron::finalize();
	finalizeUniforms();
}

/** Suppresses then finalizes all the stored uniforms. */
void Boolean::finalizeUniforms() {
	
	list<Uniform*>::iterator it;
	
	// Suppress
	suppressor.start();
	
	// Finalize
	for (int i=0; i<2; ++i) {
		for (it=uniforms[i].begin(); it!=uniforms[i].end(); ++it) {
			(*it)->finalize();
		}
	}
	
	// Check
	if (suppressor.check() > 0) {
		suppressor.print(getTag());
	}
}

/** Finds the group the Boolean should look for shapes in. 
 * 
 * @throw NodeException if the group named by @e of cannot be found.
 */
void Boolean::findGroup() {
	
	group = Scout<Group>::search(findRoot(this), of);
	if (group == NULL) {
		NodeException e(tag);
		e << "[Boolean] Could not find group named '" << of << "'.";
		throw e;
	}
}

/** @throw NodeException if no shapes are in group. */
void Boolean::findShapes() {
	
	Node *node;
	Node::iterator it;
	queue<Node*> q;
	Shape *shape;
	
	// Search subtree under group for shapes
	q.push(group);
	while (!q.empty()) {
		node = q.front();
		shape = dynamic_cast<Shape*>(node);
		if (shape != NULL) {
			shapes.push_back(shape);
		}
		for (it=node->begin(); it!=node->end(); ++it)
			q.push(*it);
		q.pop();
	}
	
	// Check
	if (shapes.size() != 2) {
		NodeException e(tag);
		e << "[Boolean] Must use two shapes for boolean.";
		throw e;
	}
}

/** Finds transforms in the group and listens for changes from them. */
void Boolean::findTransforms() {
	
	Node *node;
	Node::iterator it;
	queue<Node*> q;
	Transform *transform;
	
	// Add listener to each transform
	q.push(group);
	while (!q.empty()) {
		node = q.front();
		transform = dynamic_cast<Transform*>(node);
		if (transform != NULL)
			transform->addListener(this, NodeEvent::MODIFY);
		for (it=node->begin(); it!=node->end(); ++it)
			q.push(*it);
		q.pop();
	}
}

/** Finds uniforms of the shapes, then copies and stores them. */
void Boolean::findUniforms() {
	
	Node::iterator it;
	Shape *shape;
	Uniform *uniform;
	
	// Copy and store uniforms for each shape
	for (int i=0; i<2; ++i) {
		shape = shapes[i];
		for (it=shape->begin(); it!=shape->end(); ++it) {
			uniform = dynamic_cast<Uniform*>(*it);
			if (uniform != NULL) {
				uniform = (Uniform*)Factory::copy(uniform, tag.getLine());
				uniforms[i].push_back(uniform);
				suppressor.add(uniform);
			}
		}
	}
}

/** Determines if the shapes intersect each other using overlap attribute. */
bool Boolean::isOverlapped() const {
	
	return min(overlap.upper,overlap.lower) == overlap.lower
	         && isSubstantial(overlap);
}

/** Determines if an extent is three dimensional. */
bool Boolean::isSubstantial(const Extent &extent) {
	
	return fabs(extent.diagonal.x) > 0.01
	         && fabs(extent.diagonal.y) > 0.01
	         && fabs(extent.diagonal.z) > 0.01;
}

/** Redo the operation when a transform has changed. */
void Boolean::onNodeEvent(NodeEvent &event) {
	
	calculate();
	updateBuffer();
}

/** @return string representing the node. */
string Boolean::toString() const {
	
	ostringstream stream;
	
	stream << getClassName();
	stream << " operation='" << operation << "'"
	       << " of='" << of << "'";
	return stream.str();
}

/** Only initialize all the attributes if the boolean output is tangible. */
void Boolean::updateBuffer() {
	
	if (tangible) {
		Hexahedron::updateBuffer();
	}
}
