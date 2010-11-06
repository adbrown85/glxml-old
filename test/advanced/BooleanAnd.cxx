/*
 * BooleanAnd.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "BooleanAnd.hpp"
#include "Tester.hpp"
#include "AdvancedFactory.hpp"


class BooleanAndTest : public CanvasListener {
public:
	BooleanAndTest();
	virtual void onCanvasInitEvent(Canvas &canvas) { }
	virtual void onCanvasDisplayEvent(Canvas &canvas) { }
	virtual void onCanvasKeyEvent(Canvas &canvas);
	virtual void onCanvasButtonEvent(Canvas &canvas) { }
	virtual void onCanvasDragEvent(Canvas &canvas) { }
	void setScene(Scene *scene) {this->scene = scene;}
protected:
	void move(const Vec4 &movement);
	void select(int id);
private:
	Scene *scene;
	Shape *shape;
};

BooleanAndTest::BooleanAndTest() {
	
	shape = NULL;
}

void BooleanAndTest::onCanvasKeyEvent(Canvas &canvas) {
	
	int trigger;
	
	trigger = canvas.getState().combo.trigger;
	
	switch (trigger) {
	case '1':
	case '2':
		select((trigger-48) - 1); break;
	case 'A':
		move(Vec4(-0.1,0,0,0)); break;
	case 'D':
		move(Vec4(+0.1,0,0,0)); break;
	case 'W':
		move(Vec4(0,+0.1,0,0)); break;
	case 'S':
		move(Vec4(0,-0.1,0,0)); break;
	case '<':
	case ',':
		move(Vec4(0,0,-0.1,0)); break;
	case '>':
	case '.':
		move(Vec4(0,0,+0.1,0)); break;
	case 'P':
		scene->print(); break;
	case '-':
	case '_':
		move(Vec4(0,0,-2,0)); break;
	case '+':
	case '=':
		move(Vec4(0,0,+2,0)); break;
	case TOOLKIT_ESCAPE:
		exit(0);
	}
	
	canvas.refresh();
}

void BooleanAndTest::move(const Vec4 &movement) {
	
	Translate *translate;
	
	// Nothing selected
	if (shape == NULL)
		return;
	
	// Alter translate
	translate = Scout<Translate>::locate(shape);
	if (translate != NULL) {
		translate->add(movement);
	}
}

void BooleanAndTest::select(int id) {
	
	int i;
	Node::iterator it;
	Node *node, *other;
	
	// Get the shape
	shape = dynamic_cast<Shape*>(Identifiable::findByID(id));
	
	// Add new color uniform and refresh
	node = Factory::create("uniform type='vec4' name='Color' value='1 1 0 1'");
	shape->addChild(node);
	node->associate();
	node->finalize();
	
	// Remove from other
	id = !id;
	other = dynamic_cast<Node*>(Identifiable::findByID(id));
	i = 0;
	for (it=other->begin(); it!=other->end(); ++it) {
		++i;
		if (i == 3) {
			delete *it;
			other->erase(it);
			break;
		}
	}
}

/* Run the test. */
int main(int argc, char *argv[]) {
	
	Toolkit toolkit(argc, argv);
	BooleanAndTest test;
	Tester tester;
	
	AdvancedFactory::install();
	tester.open("test/advanced/BooleanAnd.xml");
	
	test.setScene(tester.getScene());
	tester.getCanvas()->addListener(&test);
	tester.start();
	
	return 0;
}

