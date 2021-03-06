/*
 * Shadow.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_SHADOW_HPP
#define GLXML_SHADOW_HPP
#include "glxml_common.h"
#include <gloop/State.hpp>
#include "Texture.hpp"
#include "SubsceneUser.hpp"
#include "Group.hpp"
#include "Light.hpp"
#include "Resources.hpp"
#include "Target.hpp"
#include "Clone.hpp"
#include "Scout.hpp"
#define SHADOW_SUBSCENE "ui/shadow-cast.xml"
using namespace std;

/** @brief Shadow map generated from a light and a group.
 * 
 * @ingroup shading
 */
class Shadow : public Texture, public SubsceneUser,
               public NodeListener {
public:
	Shadow(const Tag &tag);
	virtual string toString() const;
// Preparation
	virtual void associate();
	virtual void finalize();
// Event handling
	virtual void onNodeEvent(NodeEvent &event);
protected:
	void findGroup();
	void findLight();
	void findTransforms();
	virtual void openSubscene();
	virtual void prepareSubscene();
	void render();
private:
	string of, from;
	Group *group;
	Light *light;
};

/** Renders the scene from the light's point of view into the shadow map. */
inline void Shadow::onNodeEvent(NodeEvent &event) {render();}

#endif
