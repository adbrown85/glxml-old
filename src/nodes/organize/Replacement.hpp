/*
 * Replacement.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_REPLACEMENT_HPP
#define GLXML_REPLACEMENT_HPP
#include "glxml_common.h"
#include "Node.hpp"
using namespace std;


/** @brief Substitute for a placeholder in a group instance.
 * 
 * @see Replica
 * @ingroup advanced
 */
class Replacement : public Node {
public:
	Replacement(const Tag &tag);
	virtual bool areChildrenPreparable() const;
	virtual bool areChildrenTraversable() const;
	virtual string getOf() const;
	virtual string toString() const;
private:
	string of;
};

/** @return Name of the placeholder to replace. */
inline string Replacement::getOf() const {return of;}

inline bool Replacement::areChildrenPreparable() const {return false;}
inline bool Replacement::areChildrenTraversable() const {return false;}


#endif