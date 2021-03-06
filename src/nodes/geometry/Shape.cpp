/*
 * Shape.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Shape.hpp"
map<string,VertexBufferObject*> Shape::vbos;

/** Creates a shape from an XML tag.
 * 
 * @param tag XML tag with attributes for SimpleDrawable.
 * @param traits Structure of shape parameters.
 */
Shape::Shape(const Tag &tag, ShapeTraits traits) : SimpleDrawable(tag) {
	
	list<string>::iterator it;
	VertexAttribute va;
	
	// Copy traits
	this->count = traits.count;
	this->limit = traits.count;
	this->mode = traits.mode;
	this->usage = traits.usage;
	
	// Retrieve from tag
	tag.get("name", name, false, false);
	if (!tag.get("defaults", defaults, false)) {
		defaults = true;
	}
	
	// Other attributes
	this->generated = false;
	this->vbo = NULL;
	
	// Store vertex attributes
	for (it=traits.attributes.begin(); it!=traits.attributes.end(); ++it) {
		va.setName(*it);
		va.setNumber(distance(traits.attributes.begin(), it));
		va.setComponents(3);
		va.setOffset(0);
		attributes.push_back(va);
	}
}

/** Destroys the shape. */
Shape::~Shape() {
	
	if (vbo != NULL) {
		delete vbo;
	}
}

/** Finds a program to bind the shape's vertex attributes to.
 * 
 * @throw NodeException if a program cannot be found.
 */
void Shape::associate() {
	
	SimpleDrawable::associate();
	
	// Find program
	program = Scout<Program>::locate(parent);
	if (program == NULL) {
		NodeException e(tag);
		e << "[Shape] No shader program found to bind attributes to.";
		throw e;
	}
}

void Shape::checkForDefaultUniforms() {
	
	int tally;
	map<string,UniformInfo> uniforms;
	map<string,UniformInfo>::iterator it;
	ostringstream stream;
	Node *node;
	
	// Try to add missing default uniforms
	tally = 0;
	uniforms = ProgramAnalyzer::listUniforms(program->getHandle());
	for (it=uniforms.begin(); it!=uniforms.end(); ++it) {
		if (UniformMatrix::isDefault(it->first, it->second.type)) {
			if (!UniformMatrix::hasChild(this, it->first)) {
				stream.str("");
				stream << "uniform type='mat4' name='" << it->first << "'";
				node = Factory::create(stream.str());
				addChild(node);
				node->associate();
				++tally;
			}
		}
	}
	
	// Confirm
	if (tally > 0) {
		glog << tag.getLocation();
		glog << " [Shape] Added " << tally << " default uniforms." << endl;
	}
}

/** Renders the entire shape. */
void Shape::draw() const {
	
	draw(0, limit);
}

/** Renders part of the shape. */
void Shape::draw(int first, int number) const {
	
	list<VertexAttribute>::const_iterator it;
	int loc, off, com;
	int stride = vbo->getStride();
	int size = vbo->getSize();
	
	// Enable buffer and attributes
	vbo->bind();
	for (it=attributes.begin(); it!=attributes.end(); ++it) {
		com = it->getComponents();
		loc = it->getLocation();
		off = it->getOffset();
		glEnableVertexAttribArray(it->getLocation());
		glVertexAttribPointer(it->getLocation(),            // index
		                      it->getComponents(),          // size
		                      GL_FLOAT,                     // type
		                      false,                        // normalized
		                      vbo->getStride(),             // stride
		                      (void*)it->getOffset());      // pointer
	}
	
	// Draw
	glDrawArrays(mode, first, number);
	
	// Disable buffer and attributes
	for (it=attributes.begin(); it!=attributes.end(); ++it) {
		glDisableVertexAttribArray(it->getLocation());
	}
	vbo->unbind();
}

/** Loads the vertex data into the vertex buffer so it's ready to render. */
void Shape::finalize() {
	
	list<VertexAttribute>::iterator it;
	
	// Initialize buffer
	if (usage == GL_STATIC_DRAW && isBufferStored(getClassName())) {
		vbo = vbos.find(getClassName())->second;
	} else {
		generate();
	}
	
	// Get locations of attributes in program
	for (it=attributes.begin(); it!=attributes.end(); ) {
		it->setLocation(glGetAttribLocation(program->getHandle(),
		                                    it->getName().c_str()));
		if (it->getLocation() == -1)
			it = attributes.erase(it);
		else
			++it;
	}
	
	// Store offsets
	for (it=attributes.begin(); it!=attributes.end(); ++it) {
		it->setOffset(vbo->getOffset(it->getName()));
	}
	
	// Check for defaults
	if (defaults) {
		checkForDefaultUniforms();
	}
}

/** Generates the vertex buffer for the shape. */
void Shape::generate() {
	
	list<VertexAttribute>::iterator it;
	
	// Check if already generated
	if (generated)
		return;
	
	// Create and bind
	vbo = new VertexBufferObject();
	vbo->bind();
	
	// Allocate and fill
	for (it=attributes.begin(); it!=attributes.end(); ++it) {
		vbo->addAttribute(it->getName(), it->getComponents());
	}
	vbo->allocate(usage, count);
	updateBuffer();
	
	// Store for static shapes
	if (usage == GL_STATIC_DRAW) {
		vbos[getClassName()] = vbo;
	}
	
	// Unbind
	vbo->unbind();
	
	// Finish
	generated = true;
}

/** Checks if a buffer already exists for a concrete shape. */
bool Shape::isBufferStored(const string &className) {
	
	map<string,VertexBufferObject*>::iterator it;
	
	it = vbos.find(className);
	return it != vbos.end();
}

/** Sets data in the buffer according to its vertex attribute name.
 * 
 * @param name Name of the vertex attribute
 * @param data Array of values of length <i>count</i>
 */
void Shape::setBufferData(const string &name, GLfloat data[][3]) {
	
	vbo->bind();
	vbo->seek(name);
	vbo->enableAutoStriding();
	for (int i=0; i<count;  ++i) {
		vbo->put(data[i][0], data[i][1], data[i][2]);
	}
	vbo->flush();
	vbo->unbind();
}

/** @return String comprised of the object's attributes. */
string Shape::toString() const {
	
	ostringstream stream;
	
	stream << SimpleDrawable::toString();
	stream << " vbo='" << vbo->getHandle() << "'";
	if (!name.empty()) {
		stream << " name='" << name << "'";
	}
	return stream.str();
}

