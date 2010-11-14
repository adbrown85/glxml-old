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
 * @ingroup organize
 */
class Replacement : public Node {
public:
	Replacement(const Tag &tag);
	virtual string toString() const;
// Traversal
	virtual bool areChildrenPreparable() const;
	virtual bool areChildrenTraversable() const;
// Getters and setters
	virtual string getOf() const;
private:
	string of;
};

/** @return Name of the placeholder to replace. */
inline string Replacement::getOf() const {return of;}

inline bool Replacement::areChildrenPreparable() const {return false;}
inline bool Replacement::areChildrenTraversable() const {return false;}


#endif
