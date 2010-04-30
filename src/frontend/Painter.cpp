/*
 * Painter.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Painter.hpp"
Node* Painter::outline=NULL;


Painter::Painter(Scene *scene,
                 GLenum mode) {
	
	this->scene = scene;
	this->mode = mode;
	
	if (outline == NULL) {
		AdvancedFactory::install();
		BasicFactory::install();
		outline = Factory::open("${GANDER}/glsl/outline.xml");
		outline->prepare();
	}
}


/**
 * Paints all the items in a scene.
 */
void Painter::paint() {
	
/*
	if (renderMode != GL_SELECT)
		scene.sortByDepth();
*/
	
	// Draw
	Window::applyView();
	paintNode(scene->getRoot());
}


/**
 * Recursively paints the children of a node.
 * 
 * This functionality is implemented as a separate function, as opposed to 
 * incorporating it directly into <i>paint</i>, because some nodes need to 
 * paint their children at different times.
 * 
 * @param node Pointer to the parent node.
 */
void Painter::paintChildren(Node *node) {
	
	int numberOfChildren;
	vector<Node*> children;
	
	// Paint each child
	children = node->getChildren();
	numberOfChildren = children.size();
	for (int i=0; i<numberOfChildren; ++i) {
		paintNode(children[i]);
	}
}


/**
 * Recursively paints a node.
 * 
 * Automatically takes care of performing different actions depending on what 
 * type of interfaces the node supports.
 * 
 * @param node Pointer to the Node to paint.
 */
void Painter::paintNode(Node *node) {
	
	Applicable *applicable;
	Drawable *drawable;
	Selectable *selectable;
	
	// Node is drawable and visible
	if ((drawable = dynamic_cast<Drawable*>(node))
	      && drawable->isVisible()) {
		
		// Draw the node
		if (mode == GL_SELECT)
			glLoadName(drawable->getID());
		drawable->draw();
		
		// Paint UI elements for selected nodes
		if ((selectable = dynamic_cast<Selectable*>(node))
		      && selectable->isSelected()
		      && !Framebuffer::isActive())
			paintUIElements(selectable);
		
		// Paint children
		paintChildren(node);
	}
	
	// Node is applicable
	else if ((applicable = dynamic_cast<Applicable*>(node))) {
		applicable->apply();
		if (!(mode == GL_SELECT && Framebuffer::isActive())) {
			paintChildren(node);
		}
		applicable->remove();
	}
	
	// Regular node
	else
		paintChildren(node);
}


/**
 * Paints manipulators and an outline for a selected shape.
 */
void Painter::paintUIElements(Selectable *selectable) {
	
	Program *program;
	vector<Manipulator*>::iterator mi;
	
	// Disable shading and texture
	program = Program::getCurrent();
	if (program != NULL)
		program->remove();
	Texture::pause();
	
	// Draw outline
	paintNode(outline);
	
	// Draw manipulators
	glPushAttrib(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glPushAttrib(GL_POLYGON_BIT);
			glPolygonMode(GL_FRONT, GL_FILL);
			for (mi=manipulators.begin(); mi!=manipulators.end(); ++mi) {
				if (mode == GL_SELECT)
					glPushName((*mi)->getID());
				(*mi)->copySizeOf(*selectable);
				(*mi)->draw();
			}
		glPopAttrib();
	glPopAttrib();
	
	// Restore shading and texturing
	if (program != NULL)
		program->apply();
	Texture::restart();
}

