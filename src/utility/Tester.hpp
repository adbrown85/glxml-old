/*
 * Tester.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TESTER_HPP
#define TESTER_HPP
#include "glxml_common.h"
#include <edo/Path.hpp>
#include <glawt/Toolkit.hpp>
#include <glawt/Canvas.hpp>
#include <glawt/GLAWTFactory.hpp>
#include <gloop/Camera.hpp>
#include "Node.hpp"
#include "Scene.hpp"
#include "Traverser.hpp"
using namespace std;


/** @brief Utility for testing nodes.
 * @ingroup scene
 */
class Tester : public CanvasListener {
public:
	void open(const string &filename);
	void start();
// Event handlers
	virtual void onCanvasInitEvent(Canvas &canvas) { }
	virtual void onCanvasDisplayEvent(Canvas &canvas);
	virtual void onCanvasKeyEvent(Canvas &canvas);
	virtual void onCanvasButtonEvent(Canvas &canvas) { }
	virtual void onCanvasDragEvent(Canvas &canvas) { }
// Getters and setters
	string getFilename();
	Scene* getScene();
private:
	Traverser *traverser;
	Scene *scene;
	Canvas *canvas;
	Camera *camera;
	Window *window;
};

inline Scene* Tester::getScene() {return scene;}
inline string Tester::getFilename() {return scene->getFilename();}


#endif
