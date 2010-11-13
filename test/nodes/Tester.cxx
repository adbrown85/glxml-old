/*
 * Tester.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "glxml_common.h"
#include <edo/Path.hpp>
#include <glawt/Toolkit.hpp>
#include <glawt/Canvas.hpp>
#include <glawt/GLAWTFactory.hpp>
#include <gloop/Camera.hpp>
#include "Node.hpp"
#include "Scene.hpp"
#include "Traverser.hpp"
#include "BasicFactory.hpp"
#include "GeometryFactory.hpp"
#include "OffscreenFactory.hpp"
#include "OrganizeFactory.hpp"
#include "ShadingFactory.hpp"
#include "TransformFactory.hpp"
using namespace std;


/** @brief Utility for testing nodes.
 * @ingroup scene
 */
class Tester : public CanvasListener {
public:
	Tester();
	void open(const string &filename);
// Event handlers
	virtual void onCanvasInitEvent(Canvas &canvas) { }
	virtual void onCanvasDisplayEvent(Canvas &canvas);
	virtual void onCanvasKeyEvent(Canvas &canvas);
	virtual void onCanvasButtonEvent(Canvas &canvas) { }
	virtual void onCanvasDragEvent(Canvas &canvas) { }
// Getters and setters
	Canvas* getCanvas() const {return canvas;}
	Camera* getCamera() const {return camera;}
	string getFilename() const {return scene->getFilename();}
	Scene* getScene() const {return scene;}
protected:
	void select(int id);
	void move(const Vec4 &movement);
private:
	Traverser *traverser;
	Scene *scene;
	Canvas *canvas;
	Camera *camera;
	Window *window;
	Shape *shape;
	Translate *translate;
};

/** Initializes all the pointers. */
Tester::Tester() {
	
	traverser = NULL;
	scene = NULL;
	canvas = NULL;
	camera = NULL;
	window = NULL;
	shape = NULL;
	translate = NULL;
}

/** Draws the scene. */
void Tester::onCanvasDisplayEvent(Canvas &canvas) {
	
	// Clear
	glClearColor(0, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Draw
	camera->apply();
	traverser->start();
	canvas.write(scene->getFilename());
}

/** Key was pressed. */
void Tester::onCanvasKeyEvent(Canvas &canvas) {
	
	int trigger;
	
	trigger = canvas.getState().combo.trigger; 
	switch (trigger) {
	case TOOLKIT_KEY_UP:
		camera->rotate(-CAMERA_ROTATE_AMOUNT, Vec4(1.0,0.0,0.0));
		break;
	case TOOLKIT_KEY_RIGHT:
		camera->rotate(+CAMERA_ROTATE_AMOUNT, Vec4(0.0,1.0,0.0));
		break;
	case TOOLKIT_KEY_DOWN:
		camera->rotate(+CAMERA_ROTATE_AMOUNT, Vec4(1.0,0.0,0.0));
		break;
	case TOOLKIT_KEY_LEFT:
		camera->rotate(-CAMERA_ROTATE_AMOUNT, Vec4(0.0,1.0,0.0));
		break;
	case 'r':
	case 'R':
		camera->reset();
		break;
	case TOOLKIT_MINUS:
		camera->move(Vec4(0,0,-1));
		break;
	case TOOLKIT_PLUS:
	case TOOLKIT_EQUALS:
		camera->move(Vec4(0,0,+1));
		break;
	case TOOLKIT_ESCAPE:
	case 'Q':
	case 'q':
		exit(0);
		break;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		select(trigger - 48);
		break;
	case 'a':
	case 'A':
		move(Vec4(-0.1, 0, 0, 0));
		break;
	case 'd':
	case 'D':
		move(Vec4(+0.1, 0, 0, 0));
		break;
	case 'W':
	case 'w':
		move(Vec4(0, +0.1, 0, 0));
		break;
	case 'S':
	case 's':
		move(Vec4(0, -0.1, 0, 0));
		break;
	}
	canvas.refresh();
}

/** Moves the currently selected shape. */
void Tester::move(const Vec4 &movement) {
	
	if (translate != NULL) {
		translate->add(movement);
	} else {
		cerr << "Translate is NULL!" << endl;
	}
}

/** Selects a shape. */
void Tester::select(int id) {
	
	shape = dynamic_cast<Shape*>(Identifiable::findByID(id));
	if (shape != NULL) {
		cout << "Selected " << id << endl;
		translate = Scout<Translate>::locate(shape);
	}
}

/** Creates a window, opens the scene, prepares it, and runs it. */
void Tester::open(const string &filename) {
	
	// Print
	cout << endl;
	cout << "****************************************" << endl;
	cout << Path::getBasename(filename) << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Create the canvas
	canvas = GLAWTFactory::createCanvas();
	canvas->addListener(this);
	
	// Pack window
	window = GLAWTFactory::createWindow();
	window->setTitle("Tester");
	window->add(canvas);
	window->show();
	
	// Start setup
	canvas->primeStart();
	
	// Set up camera
	camera = new Camera();
	camera->load(canvas->getWidth(), canvas->getHeight());
	
	// Open and prepare scene
	scene = new Scene();
	scene->open(filename);
	scene->prepare();
	scene->print();
	traverser = new Traverser(scene);
	traverser->setCamera(camera);
	
	// End setup
	canvas->primeFinish();
	window->run();
}

/* Runs the test with a file from the command line. */
int main(int argc, char *argv[]) {
	
	Toolkit kit(argc, argv);
	Tester tester;
	string filename;
	
	if (argc == 2) {
		filename = argv[1];
	} else {
		cout << "Usage: " << argv[0] << " <filename>" << endl;
		exit(1);
	}
	
	BasicFactory::install();
	GeometryFactory::install();
	OffscreenFactory::install();
	OrganizeFactory::install();
	ShadingFactory::install();
	TransformFactory::install();

	try {
		tester.open(filename);
	} catch (exception &e) {
		cerr << e.what() << endl;
		exit(1);
	}
	
	return 0;
}

