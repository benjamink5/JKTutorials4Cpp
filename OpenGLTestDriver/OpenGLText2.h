#pragma once

#include <iostream>         // for string
#include <vector>           // for vector (u don't say? :D)

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <ft2build.h>       // freetype headers
#include FT_FREETYPE_H      // also freetype header   
 
#include "IShader.h"

// let's use std namespace so we don't need to write it every time
using namespace std;
 
// here we have some enums for align and font size settings
enum {
    ALIGN_LEFT, ALIGN_CENTER, ALIGN_RIGHT,
    FONT_SIZE
};
 
// this class contains all the glyph data that we use
class GlyphData {
public:
    char c;     // the character of this glyph
    int size;   // font size
     
    int bitmap_width;   // texture width
    int bitmap_rows;    // texture height
    unsigned char *bitmap_buffer;   // texture data
    FT_Vector advance;  // this variable contains the information of how much we need to move to the right from the last character
    int bitmap_left;    // width of the glyph in pixels
    int bitmap_top;     // height of the glyph in pixels
};

class OpenGLText2
{
public:
	OpenGLText2(void);
	~OpenGLText2(void);

	void init(IShader* prog, const char *fontname, int size, float screenWidth, float screenHeight); // init method
    //void write(string text, float x, float y, int align); // this method will be used for rendering text
    void write(const char* text, float x, float y, int align); // this method will be used for rendering text
    void fontOpt(int opt, int value); // font option method. i have included only font size option to this method but you can do more

private: 
    // our freetype objects
    FT_Library ft; // the library object
    FT_Face face;  // the face (font) object
    FT_GlyphSlot g;// the glyph
     
    int currentSize; // current size of text
     
    void getGlyph(char c); // get glyph for the 'c' char
     
    IShader* shaderProgram; // the shader program. this will be set in the init method
    GLuint vao; // vertex array object for the text
    GLuint vbo; // vertex buffer object for the text
    GLint fontCoords; // shader attribute for text coordinates
    GLuint textTex; // texture object for the text
     
    vector<GlyphData> glyphs; // vector of all loaded glyphs. with this we can reuse the glyphs that has already been loaded
    GlyphData currentG; // current glyph
     
    // these variables are used for getting screen size, if you're not developing for iOS you need to find out your screen size someway else
    //CGRect screenRect;      // the rect
    GLfloat screenWidth;    // width of the screen
    GLfloat screenHeight;   // height of the screen

	PFNGLGENBUFFERSARBPROC pglGenBuffersARB;                     // VBO Name Generation Procedure
	PFNGLBINDBUFFERARBPROC pglBindBufferARB;                     // VBO Bind Procedure
	PFNGLBUFFERDATAARBPROC pglBufferDataARB;                     // VBO Data Loading Procedure
	PFNGLBUFFERSUBDATAARBPROC pglBufferSubDataARB;               // VBO Sub Data Loading Procedure
	PFNGLDELETEBUFFERSARBPROC pglDeleteBuffersARB;               // VBO Deletion Procedure
	PFNGLGETBUFFERPARAMETERIVARBPROC pglGetBufferParameterivARB; // return various parameters of VBO
	PFNGLMAPBUFFERARBPROC pglMapBufferARB;                       // map VBO procedure
	PFNGLUNMAPBUFFERARBPROC pglUnmapBufferARB;                   // unmap VBO procedure

	PFNGLGENVERTEXARRAYSPROC pglGenVertexArraysARB;
	PFNGLDELETEVERTEXARRAYSPROC pglDeleteVertexArraysARB;
	PFNGLBINDVERTEXARRAYPROC pglBindVertexArrayARB;
	PFNGLACTIVETEXTUREPROC	pglActiveTextureARB;

	PFNGLGETATTRIBLOCATIONARBPROC pglGetAttribLocationARB;

	PFNGLENABLEVERTEXATTRIBARRAYPROC pglEnableVertexAttribArrayARB;
	PFNGLDISABLEVERTEXATTRIBARRAYPROC pglDisableVertexAttribArrayARB;
	PFNGLVERTEXATTRIBPOINTERPROC	pglVertexAttribPointerARB;

};

