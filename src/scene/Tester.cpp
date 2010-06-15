/*
 * Tester.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Tester.hpp"


void Tester::onCanvasEvent(const CanvasEvent &event) {
	
	switch (event.type) {
	case CanvasEvent::DISPLAY:
		onCanvasEventDisplay(event);
		break;
	case CanvasEvent::KEY:
		onCanvasEventKey(event);
		break;
	}
}


/** Draws the scene. */
void Tester::onCanvasEventDisplay(const CanvasEvent &event) {
	
	// Clear
	canvas->clear();
	
	// Draw
	camera->apply();
	traverser->start();
	//canvas->write(scene.getFilename());
	
	// Finish
	canvas->flush();
}


/** Key was pressed. */
void Tester::onCanvasEventKey(const CanvasEvent &event) {
	
	switch(event.state.combo.trigger) {
	case CANVAS_KEY_UP:
		camera->rotate(-CAMERA_ROTATE_AMOUNT, Vector(1.0,0.0,0.0));
		break;
	case CANVAS_KEY_RIGHT:
		camera->rotate(+CAMERA_ROTATE_AMOUNT, Vector(0.0,1.0,0.0));
		break;
	case CANVAS_KEY_DOWN:
		camera->rotate(+CAMERA_ROTATE_AMOUNT, Vector(1.0,0.0,0.0));
		break;
	case CANVAS_KEY_LEFT:
		camera->rotate(-CAMERA_ROTATE_AMOUNT, Vector(0.0,1.0,0.0));
		break;
	case 'r':
	case 'R':
		camera->reset();
		break;
	case CANVAS_MINUS:
		camera->move(Vector(0,0,-1));
		break;
	case CANVAS_PLUS:
	case CANVAS_EQUALS:
		camera->move(Vector(0,0,+1));
		break;
	case CANVAS_ESCAPE:
	case 'Q':
	case 'q':
		exit(0);
	}
	canvas->refresh();
}


/** Creates a window, opens the scene, and prepares it. */
void Tester::open(const string &filename) {
	
	GLenum err;
	
	// Print
	cout << endl;
	cout << "****************************************" << endl;
	cout << Path::getBasename(filename) << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Create the canvas and get camera
	canvas = new CanvasGTK();
	canvas->addListener(this, CanvasEvent::DISPLAY);
	canvas->addListener(this, CanvasEvent::KEY);
	camera = canvas->getCamera();
	
	try {
		
		// Pack window
		window = new Gtk::Window();
		window->set_title("Tester");
		window->add(*canvas);
		window->show_all();
		
		// Start setup
		canvas->primeStart();
		
		// Load GLEW
		err = glewInit();
		if (err != GLEW_OK) {
			throw Exception("[Tester] Could not initialize GLEW");
		}
		
		// Open and prepare scene
		scene = new Scene();
		scene->open(filename);
		scene->prepare();
		scene->print();
		traverser = new Traverser(scene);
		
		// End setup
		canvas->primeFinish();
	}
	catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
}


/** Starts the window's main loop, catching any exceptions. */
void Tester::start() {
	
	try {
		Gtk::Main::run(*window);
	} catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
}
