/*
 * Texture.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_TEXTURE_HPP
#define GLXML_TEXTURE_HPP
#include "glxml_common.h"
#include <gloop/TextureFactory.hpp>
#include "Node.hpp"                     // Base class
#include "NodeInterfaces.hpp"
#include "Scout.hpp"
using namespace std;

/** @brief OpenGL texture node.
 * 
 * Provides basic texture capability, including finding an open texture unit 
 * and binding the texture to that unit.
 * 
 * @ingroup shading
 */
class Texture : public Node,
                public Applicable, public Nameable, public Fileable {
public:
	Texture(const Tag &tag);
	virtual string toString() const;
// Preparation
	virtual void verify();
	virtual void associate();
	virtual void finalize();
// Traversal
	virtual void apply();
	virtual void remove() {}
// Getters and setters
	virtual GLuint getFootprint() const;
	virtual GLuint getHandle() const;
	virtual GLint getSize() const;
	virtual GLenum getType() const;
	virtual GLuint getUnit() const;
protected:
	void activate() const;
	void bind() const;
	TextureOrder makeOrder() const;
private:
	GLenum type;
	GLuint handle, unit, footprint, precision;
	string format;
	int size;
	bool compress;
};

/** Activates the correct texture unit. */
inline void Texture::activate() const {glActiveTexture(GL_TEXTURE0 + unit);}

/** Binds the texture to the active texture unit. */
inline void Texture::bind() const {glBindTexture(type, handle);}

/** @return OpenGL's unique identifier for this texture. */
inline GLuint Texture::getHandle() const {return handle;}

/** @return Width of the texture. */
inline GLint Texture::getSize() const {return size;}

/** @return Number of bytes used to store the texture. */
inline GLuint Texture::getFootprint() const {return footprint;}

/** @return GL_TEXTURE_1D, GL_TEXTURE_2D, or GL_TEXTURE_3D. */
inline GLenum Texture::getType() const {return type;}

/** @return %Texture unit holding the data. */
inline GLuint Texture::getUnit() const {return unit;}

#endif
