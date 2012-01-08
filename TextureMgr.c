#include "TextureMgr.h"
#include <stdlib.h>
#include <cstring>
#include <stdio.h>

TextureMgr::TextureMgr()
{
}

bool TextureMgr::LoadTGA( string FName )
{
    GLubyte		TGAheader[ 12 ] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	GLubyte		TGAcompare[ 12 ];
	GLubyte		header[6];
	GLuint		bytesPerPixel;
	GLuint		imageSize;
	GLuint		temp;
	GLuint		type = GL_RGBA;

    Texture_t *texture, tmp;
    m_Textures.push_back( tmp );
    //texture = &m_Textures[ m_Textures.back() ];
    texture = &m_Textures.back();

	FILE *fp = fopen( FName.c_str(), "rb" );

	if(	fp == NULL || fread(TGAcompare,1,sizeof(TGAcompare),fp)!=sizeof(TGAcompare) || memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0 || fread(header,1,sizeof(header),fp)!=sizeof(header))
	{
		if (fp == NULL)
			return false;
		else
		{
			fclose( fp );
			return false;
		}
	}

    texture->name = FName;
	texture->width  = header[ 1 ] * 256 + header[0];			// 	(highbyte*256+lowbyte)
	texture->height = header[ 3 ] * 256 + header[2];			// 	(highbyte*256+lowbyte)

 	if(	texture->width	<=0	|| texture->height	<=0	|| (header[ 4 ] != 24 && header[ 4 ] != 32))
	{
		fclose( fp );
		return false;
	}

	texture->bpp	= header[ 4 ];
	bytesPerPixel	= texture->bpp / 8;
	imageSize	= texture->width * texture->height * bytesPerPixel;

	texture->imageData = (GLubyte *)malloc(imageSize);

	if(	texture->imageData == NULL || fread( texture->imageData, 1, imageSize, fp ) != imageSize)
	{
		if( texture->imageData!=NULL )
			free( texture->imageData );

		fclose( fp );
		return false;
	}

	for( GLuint i=0; i<int(imageSize); i+=bytesPerPixel )
	{
		temp=texture->imageData[i];
		texture->imageData[i] = texture->imageData[i + 2];
		texture->imageData[i + 2] = temp;
	}

	fclose( fp );
	glGenTextures( 1, /*&texture[ */&m_Textures.back()/* ]*/.texID );

	glBindTexture( GL_TEXTURE_2D, /*texture[0].*/m_Textures.back().texID );
	glBindTexture( GL_TEXTURE_2D, /*texture[0].*/m_Textures.back().texID );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	if( texture[0].bpp==24 )
		type=GL_RGB;

	glTexImage2D( GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData );
	return true;
}

/*
void TextureMgr::DrawTexture( uint TextureID, number x, number y, number Scale, number Rotation )
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, m_Textures[ TextureID ].texID );
    glBegin(GL_QUADS);
        glTexCoord2d(0.0,0.0); glVertex3f( x, y, 0.0 );
        glTexCoord2d(1.0,0.0); glVertex3f( x+1.0, y, 0.0 );
        glTexCoord2d(1.0,1.0); glVertex3f( x+1.0, y+1.0, 0.0 );
        glTexCoord2d(0.0,1.0); glVertex3f( x, y+1.0, 0.0 );
    glEnd();
    glDisable(GL_TEXTURE_2D);
}*/

void TextureMgr::BindTexture( uint TextureID )
{
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, m_Textures[ TextureID ].texID );
}



