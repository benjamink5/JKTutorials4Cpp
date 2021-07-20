#pragma once

//FreeType Headers
#include <ft2build.h>
//#include <freetype/config/ftheader.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

//OpenGL Headers 
//#include <windows.h>		//(the GL headers need it)
#include <GL/gl.h>
#include <GL/glu.h>

//Some STL headers
#include <vector>
#include <string>

//Using the STL exception library increases the
//chances that someone else using our code will corretly
//catch any exceptions that we throw.
#include <stdexcept>

class OpenGLText
{
private:
	float h;			///< Holds the height of the font.
	GLuint * textures;	///< Holds the texture id's 
	GLuint list_base;	///< Holds the first display list id

	int	 next_p2( int a );
	void makeDisplayList( FT_Face face, char ch, GLuint list_base, GLuint * tex_base );
	void pushScreenCoordinateMatrix();
	void popProjectionMatrix();
public:
	OpenGLText(void);
	~OpenGLText(void);

	void init(const char *fontname, unsigned int h);

	void clean();

	void write(GLfloat x, GLfloat y, const char *message);
};

