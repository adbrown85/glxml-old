/*
 * Light.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_LIGHT_HPP
#define GLXML_LIGHT_HPP
#include "glxml_common.h"
#include "SimpleDrawable.hpp"
#include "Scene.hpp"
#include "Resources.hpp"
#include "Traverser.hpp"
#define LIGHT_DEFAULT_AMBIENT  0.2
#define LIGHT_DEFAULT_DIFFUSE  0.4
#define LIGHT_DEFAULT_SPECULAR 1.0
using namespace std;

/** @brief %Light that has intensities and can be transformed.
 * 
 * @ingroup shading
 */
class Light : public SimpleDrawable, public Nameable {
public:
	Light(const Tag &tag);
	virtual ~Light();
	virtual string toString() const;
// Traversal
	virtual void draw() const;
// Getters and setters
	virtual Vec4 getPosition();
	virtual Matrix getLightMatrix();
	virtual void getLightMatrix(GLfloat array[16]);
// Utilities
	static Light* search(Node *node, const string &name);
private:
	float ambient, diffuse, specular;
	Traverser *traverser;
	static Scene *widget;
	static bool tried;
};

#endif
