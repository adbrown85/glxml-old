/*
 * Traverser.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_TRAVERSER_HPP
#define GLXML_TRAVERSER_HPP
#include "glxml_common.h"
#include <edo/BasicException.hpp>
#include "Node.hpp"
#include "NodeInterfaces.hpp"
#include "Scene.hpp"
using namespace std;


/** @brief Utility to walk through nodes.
 * @ingroup scene
 */
class Traverser {
public:
	Traverser(Scene *scene);
	virtual ~Traverser() {}
	virtual void start();
// Getters and setters
	Camera* getCamera() const;
	void setCamera(Camera *camera);
protected:
	void findCameraUsers();
	virtual void onApplicable(Node *node, Applicable *applicable);
	virtual void onDrawable(Node *node, Drawable *drawable);
	void traverseChildren(Node *node);
	void traverseNode(Node *node);
private:
	list<CameraUser*> cameraUsers;
	Scene *scene;
	Camera *camera;
};

/** Sets the camera that will be passed to CameraUser nodes. */
inline void Traverser::setCamera(Camera *c) {camera = c;}

/** @return %Camera used for CameraUser nodes. */
inline Camera* Traverser::getCamera() const {return camera;}


#endif
