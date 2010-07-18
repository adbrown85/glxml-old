/*
 * WindowGTK.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "WindowGTK.hpp"
#ifdef HAVE_GTK


/** Create a GTK window. */
WindowGTK::WindowGTK() {
	
	window = new Gdk::Window();
}


/** Destroys the GTK window. */
WindowGTK::~WindowGTK() {
	
	delete window;
}


/** Adds a GTK widget to the window. */
void WindowGTK::add(Gtk::Widget &widget) {
	
	window->add(widget);
}


/** Adds the canvas to the window. */
void WindowGTK::add(Canvas *canvas) {
	
	window->add(*(dynamic_cast<CanvasGTK*>(canvas)));
}


/** Starts processing the window. */
void WindowGTK::run() {
	
	Gtk::Main::run(*window);
}


/** Makes the window visible on screen. */
void WindowGTK::show() {
	
	window->set_title(getTitle());
	window->show_all();
}


#endif // HAVE_GTK