/*
 * Instance.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Instance.hpp"


/** Initializes the <i>of</i> attribute. */
Instance::Instance(const Tag &tag) : Applicable(tag) {
	
	tag.get("of", of);
}


/** Resets all the uniforms to be under this instance. */
void Instance::apply() {
	
	restoreShapes();
	restoreUniforms();
}


/** Makes sure the instance's children point to it. */
void Instance::assignParents() {
	
	Node::iterator ni;
	
	// Make sure children's parents point to this instance
	for (ni=begin(); ni!=end(); ++ni) {
		(*ni)->setParent(this);
	}
}


/** Finds the group, its children, and all the uniforms in it. */
void Instance::associate() {
	
	findGroup();
	findChildren();
	findShapes();
	findUniforms();
}


/** Stores the programs of the uniforms so they can be reset later. */
void Instance::associateAfter() {
	
	storeShapes();
	storeUniforms();
}


/** Resets all the uniforms to be under this instance. */
void Instance::finalize() {
	
	assignParents();
	restoreShapes();
	restoreUniforms();
}


/** Stores the locations of the uniforms so they can be reset later. */
void Instance::finalizeAfter() {
	
	storeShapes();
	storeUniforms();
}


/** Adds the group's children to the instance's children. */
void Instance::findChildren() {
	
	Node::iterator it;
	
	// Get children from group
	for (it=group->begin(); it!=group->end(); ++it) {
		addChild(*it);
	}
}


/** Finds the group named by <i>of</i>.
 * 
 * @throws NodeException if the group cannot be found.
 */
void Instance::findGroup() {
	
	// Find the group
	group = Group::find(this, of);
	if (group == NULL) {
		NodeException e(tag);
		e << "[Instance] Could not find group with name '" << of << "'";
		throw e;
	}
}


/** Finds all the shapes in the group. */
void Instance::findShapes() {
	
	Node::iterator it;
	Node *node;
	queue<Node*> q;
	Shape *shape;
	
	// Search subtree for uniforms
	q.push(this);
	while (!q.empty()) {
		node = q.front();
		shape = dynamic_cast<Shape*>(node);
		if (shape != NULL)
			shapes[shape] = ShapeSnapshot();
		for (it=node->begin(); it!=node->end(); ++it)
			q.push(*it);
		q.pop();
	}
}


/** Finds all the uniforms in the group. */
void Instance::findUniforms() {
	
	Node::iterator it;
	Node *node;
	queue<Node*> q;
	Uniform *uniform;
	
	// Search subtree for uniforms
	q.push(this);
	while (!q.empty()) {
		node = q.front();
		uniform = dynamic_cast<Uniform*>(node);
		if (uniform != NULL)
			uniforms[uniform] = UniformSnapshot();
		for (it=node->begin(); it!=node->end(); ++it)
			q.push(*it);
		q.pop();
	}
}


/** Resets the shapes to their stored snapshots. */
void Instance::restoreShapes() {
	
	map<Shape*,ShapeSnapshot>::iterator it;
	
	for (it=shapes.begin(); it!=shapes.end(); ++it) {
		(it->first)->setProgram((it->second).program);
		(it->first)->setAttributes((it->second).attributes);
	}
}


/** Resets the uniforms to their stored snapshots. */
void Instance::restoreUniforms() {
	
	map<Uniform*,UniformSnapshot>::iterator it;
	
	for (it=uniforms.begin(); it!=uniforms.end(); ++it) {
		(it->first)->setProgram((it->second).program);
		(it->first)->setLocation((it->second).location);
	}
}


/** Saves snapshots of the shapes. */
void Instance::storeShapes() {
	
	map<Shape*,ShapeSnapshot>::iterator it;
	
	for (it=shapes.begin(); it!=shapes.end(); ++it) {
		(it->second).program = (it->first)->getProgram();
		(it->second).attributes = (it->first)->getAttributes();
	}
}


/** Saves snapshots of the uniforms. */
void Instance::storeUniforms() {
	
	map<Uniform*,UniformSnapshot>::iterator it;
	
	for (it=uniforms.begin(); it!=uniforms.end(); ++it) {
		(it->second).program = (it->first)->getProgram();
		(it->second).location = (it->first)->getLocation();
	}
}


/** @return String comprised of the object's attributes. */
string Instance::toString() const {
	
	ostringstream stream;
	
	stream << Applicable::toString();
	stream << " of='" << of << "'";
	return stream.str();
}

