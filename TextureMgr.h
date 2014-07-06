/*
 *
 *
 *
 */

#ifndef _TEXTUREMGR_H
#define _TEXTUREMGR_H

#include <GL/gl.h>
#include <vector>
#include <string>
#include "common.h"
#include "Singleton.h"
using namespace std;

typedef struct
{
	GLubyte     *imageData;
	GLuint      bpp;
	GLuint      width;
	GLuint      height;
	GLuint      texID;
    string      name;
} Texture_t;


class TextureMgr : public cSingleton< TextureMgr >
{
    public:
    TextureMgr();
    bool LoadTGA( string FName );
    void DrawTexture( uint TextureID, number x0, number y0, number z0, number x1, number y1, number z1, number x2, number y2, number z2, number x3, number y3, number z3 );

    void BindTexture( uint TextureID  );
    vector< Texture_t > m_Textures;
    private:

    vector< Texture_t >::iterator m_Iterator;
};

#endif /* _TEXTUREMGR_H */
