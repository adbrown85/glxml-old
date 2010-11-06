/*
 * Tester.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Tester.hpp"

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
	
	try {
		
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
	}
	catch (exception &e) {
		cerr << e.what() << endl;
		exit(1);
	}
}

/** Starts the window's main loop, catching any exceptions. */
void Tester::start() {
	
	try {
		window->run();
	} catch (exception &e) {
		cerr << e.what() << endl;
		exit(1);
	}
}

