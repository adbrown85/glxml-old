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
	Canvas* getCanvas() const {return canvas;}
	Camera* getCamera() const {return camera;}
	string getFilename() const {return scene->getFilename();}
	Scene* getScene() const {return scene;}
private:
	Traverser *traverser;
	Scene *scene;
	Canvas *canvas;
	Camera *camera;
	Window *window;
};

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
	
	switch (canvas.getState().combo.trigger) {
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
	}
	canvas.refresh();
}

/** Creates a window, opens the scene, and prepares it. */
void Tester::open(const string &filename) {
	
	// Print
	cout << endl;
	cout << "****************************************" << endl;
	cout << Path::getBasename(filename) << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Create the canvas and get camera
	canvas = GLAWTFactory::createCanvas();
	canvas->addListener(this);
	camera = new Camera();
	
	// Pack window
	window = GLAWTFactory::createWindow();
	window->setTitle("Tester");
	window->add(canvas);
	window->show();
	
	// Start setup
	canvas->primeStart();
	
	// Open and prepare scene
	scene = new Scene();
	scene->open(filename);
	scene->prepare();
	scene->print();
	traverser = new Traverser(scene);
	
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
		tester.start();
	} catch (exception &e) {
		cerr << e.what() << endl;
		exit(1);
	}
	
	return 0;
}

