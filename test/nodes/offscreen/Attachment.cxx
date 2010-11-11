/*
 * Attachment.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "glxml_common.h"
#include <glawt/Toolkit.hpp>
#include <glawt/GLAWTFactory.hpp>
#include "Attachment.hpp"


class AttachmentTest {
public:
	void setUp();
	void tearDown();
	void testColorAttachments();
	void testMaxColorAttachments();
	void testMaxDrawBuffers();
private:
	Window *window;
	Canvas *canvas;
};

void AttachmentTest::setUp() {
	
	window = GLAWTFactory::createWindow();
	canvas = GLAWTFactory::createCanvas();
	
	window->setTitle("AttachmentTest");
	window->add(canvas);
	window->show();
}

void AttachmentTest::tearDown() {
	
	delete window;
	delete canvas;
}

void AttachmentTest::testMaxDrawBuffers() {
	
	GLint value;
	
	cout << "Max draw buffers: " << endl;
	glGetIntegerv(GL_MAX_DRAW_BUFFERS, &value);
	cout << value << endl;
}

void AttachmentTest::testMaxColorAttachments() {
	
	GLint value;
	
	cout << "\nMax color attachments: " << endl;
	glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &value);
	cout << value << endl;
}

void AttachmentTest::testColorAttachments() {
	
	cout << "\nColor attachments..." << endl;
	cout << GL_COLOR_ATTACHMENT0 << endl;
	cout << GL_COLOR_ATTACHMENT1 << endl;
	cout << GL_COLOR_ATTACHMENT2 << endl;
	cout << GL_COLOR_ATTACHMENT3 << endl;
	cout << GL_COLOR_ATTACHMENT4 << endl;
	cout << GL_COLOR_ATTACHMENT5 << endl;
	cout << GL_COLOR_ATTACHMENT6 << endl;
}

/* Run the test. */
int main(int argc, char *argv[]) {
	
	Toolkit toolkit(argc, argv);
	AttachmentTest test;
	
	test.setUp();
	test.testMaxDrawBuffers();
	test.testMaxColorAttachments();
	test.testColorAttachments();
	test.tearDown();
	
	return 0;
}

