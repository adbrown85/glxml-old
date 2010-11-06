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
#include <glawt/GLAWTFactory.hpp>
#include "Node.hpp"
#include "Scene.hpp"
#include "Traverser.hpp"
using namespace std;


/** @brief Utility for testing nodes.
 * @ingroup scene
 */
class Tester : public CanvasListener {
public:
	string getFilename();
	Scene* getScene();
	void onCanvasEvent(const CanvasEvent &event);
	void onCanvasEventDisplay(const CanvasEvent &event);
	void onCanvasEventKey(const CanvasEvent &event);
	void open(const string &filename);
	void start();
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
