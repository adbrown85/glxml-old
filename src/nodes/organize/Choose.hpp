/*
 * Choose.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_CHOOSE_HPP
#define GLXML_CHOOSE_HPP
#include "glxml_common.h"
#include "Node.hpp"
#include "NodeInterfaces.hpp"
#include "NodeEvent.hpp"
#include "Branch.hpp"
using namespace std;

/** @brief Selects a branch to follow.
 * @ingroup advanced
 */
class Choose : public Node, public NodeNotifier {
public:
	Choose(const Tag &tag);
	virtual string toString() const;
// Preparation
	virtual void associate();
	virtual void finalize();
// Getters and setters
	virtual bool setAttribute(pair<string,string> attribute);
	virtual string getChoice() const;
	virtual bool hasChoice() const;
	virtual void setChoice(const string &choice);
private:
	string choice;
	map<string,Branch*> branches;
};

/** @return Name of the branch that was chosen. */
inline string Choose::getChoice() const {return choice;}

/** @return True if @e choice is not empty. */
inline bool Choose::hasChoice() const {return !choice.empty();}

#endif
