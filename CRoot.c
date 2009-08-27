/*      @ file:            @ last modified:                    @ author:
 *      CRoot.c            08-07-2009 01:16                    Zborowski
 *
 *      @ Description:
 *      Root class implementation
 */

#include "CRoot.h"
#include "common.h"
#include "Vector3d.h"
#include <GL/gl.h>
#include <math.h>
#include "TextureMgr.h"
#include "Scene.h"

CRoot::CRoot()
{
}

CRoot::~CRoot()
{
}

void CRoot::GenerateList( void )
{
#define vertx( number ) glVertex3f( number.x, number.y, number.z )
    if( scene->IsTexturing() )
    {
        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, TextureMgr::GetInstance().m_Textures[ 1 ].texID );

        glBegin( GL_TRIANGLE_STRIP );
            glColor3f( 0.6f, 0.4f, 0.0f );
            glTexCoord2d(0.0,0.0); vertx( bottom_p.p0 );
            glTexCoord2d(1.0,0.0); vertx( top_p.p0 );
            glTexCoord2d(1.0,1.0); vertx( bottom_p.p1 );
            glTexCoord2d(0.0,1.0); vertx( top_p.p1 );
            glTexCoord2d(0.0,0.0); vertx( bottom_p.p2 );
            glTexCoord2d(1.0,0.0); vertx( top_p.p2 );
            glTexCoord2d(1.0,1.0); vertx( bottom_p.p3 );
            glTexCoord2d(0.0,1.0); vertx( top_p.p3 );
            glTexCoord2d(0.0,0.0); vertx( bottom_p.p4 );
            glTexCoord2d(1.0,0.0); vertx( top_p.p4 );
            glTexCoord2d(1.0,1.0); vertx( bottom_p.p5 );
            glTexCoord2d(0.0,1.0); vertx( top_p.p5 );
            glTexCoord2d(0.0,0.0); vertx( bottom_p.p6 );
            glTexCoord2d(1.0,0.0); vertx( top_p.p6 );
            glTexCoord2d(1.0,1.0); vertx( bottom_p.p7 );
            glTexCoord2d(0.0,1.0); vertx( top_p.p7 );
            glTexCoord2d(0.0,0.0); vertx( bottom_p.p0 );
            glTexCoord2d(1.0,0.0); vertx( top_p.p0 );
        glEnd();

        glDisable( GL_TEXTURE_2D );
    }
    else
    {
        glBegin( GL_TRIANGLE_STRIP );
            glColor3f( 0.6f, 0.4f, 0.0f );
            vertx( bottom_p.p0 );
            vertx( top_p.p0 );
            vertx( bottom_p.p1 );
            vertx( top_p.p1 );
            vertx( bottom_p.p2 );
            vertx( top_p.p2 );
            vertx( bottom_p.p3 );
            vertx( top_p.p3 );
            vertx( bottom_p.p4 );
            vertx( top_p.p4 );
            vertx( bottom_p.p5 );
            vertx( top_p.p5 );
            vertx( bottom_p.p6 );
            vertx( top_p.p6 );
            vertx( bottom_p.p7 );
            vertx( top_p.p7 );
            vertx( bottom_p.p0 );
            vertx( top_p.p0 );
        glEnd();
    }
#undef vertx
}

void CRoot::DrawTris( void )
{
#define vertx( number ) glVertex3f( number.x, number.y, number.z )
    glBegin( GL_LINE_STRIP );
    glColor3f( 1.0f, 1.0f, 1.0f );
        vertx( bottom_p.p0 );
        vertx( top_p.p0 );
        vertx( bottom_p.p1 );
        vertx( top_p.p1 );
        vertx( bottom_p.p2 );
        vertx( top_p.p2 );
        vertx( bottom_p.p3 );
        vertx( top_p.p3 );
        vertx( bottom_p.p4 );
        vertx( top_p.p4 );
        vertx( bottom_p.p5 );
        vertx( top_p.p5 );
        vertx( bottom_p.p6 );
        vertx( top_p.p6 );
        vertx( bottom_p.p7 );
        vertx( top_p.p7 );
        vertx( bottom_p.p0 );
        vertx( top_p.p0 );
    glEnd();
#undef vertx
}

void CRoot::GenerateRoot( Vector3d start, Vector3d stop, number w0, number w1, bool tris )
{
    this->w0 = w0;
    this->w1 = w1;
    this->start = start;
    this->stop = stop;

    number x0 = start.x;
    number y0 = start.y;
    number z0 = start.z;

    number x1 = stop.x;
    number y1 = stop.y;
    number z1 = stop.z;

    number ax = w0 * sqrt( 2.0f );
    number ax2= w1 * sqrt( 2.0f );
    Vector3d s0( x0 - w0, y0, z0 + w0 + ax );
    Vector3d s1( x1 - w1, y1, z1 + w1 + ax2 );
    Vector3d s2( x0 + w0, y0, z0 + w0 + ax );
    Vector3d s3( x1 + w1, y1, z1 + w1 + ax2 );
    Vector3d s4( x0 + w0 + ax, y0, z0 + w0 );
    Vector3d s5( x1 + w1 + ax2, y1, z1 + w1 );
    Vector3d s6( x0 + w0 + ax, y0, z0 - w0 );
    Vector3d s7( x1 + w1 + ax2, y1, z1 - w1 );
    Vector3d s8( x0 + w0, y0, z0 - w0 - ax );
    Vector3d s9( x1 + w1, y1, z1 - w1 - ax2 );
    Vector3d s10( x0 - w0, y0, z0 - w0 - ax );
    Vector3d s11( x1 - w1, y1, z1 - w1 - ax2 );
    Vector3d s12( x0 - w0 - ax, y0, z0 - w0 );
    Vector3d s13( x1 - w1 - ax2, y1, z1 - w1 );
    Vector3d s14( x0 - w0 - ax, y0, z0 + w0 );
    Vector3d s15( x1 - w1 - ax2, y1, z1 + w1 );


    //
    bottom_p.p0 = s0;
    bottom_p.p1 = s2;
    bottom_p.p2 = s4;
    bottom_p.p3 = s6;
    bottom_p.p4 = s8;
    bottom_p.p5 = s10;
    bottom_p.p6 = s12;
    bottom_p.p7 = s14;

    top_p.p0 = s1;
    top_p.p1 = s3;
    top_p.p2 = s5;
    top_p.p3 = s7;
    top_p.p4 = s9;
    top_p.p5 = s11;
    top_p.p6 = s13;
    top_p.p7 = s15;
    //
/*
    m_Vertices.push_back( s0 );
    m_Vertices.push_back( s1 );
    m_Vertices.push_back( s2 );
    m_Vertices.push_back( s3 );
    m_Vertices.push_back( s4 );
    m_Vertices.push_back( s5 );
    m_Vertices.push_back( s6 );
    m_Vertices.push_back( s7 );
    m_Vertices.push_back( s8 );
    m_Vertices.push_back( s9 );
    m_Vertices.push_back( s10 );
    m_Vertices.push_back( s11 );
    m_Vertices.push_back( s12 );
    m_Vertices.push_back( s13 );
    m_Vertices.push_back( s14 );
    m_Vertices.push_back( s15 );*/
/*
#define vertx( number ) glVertex3f( number.x, number.y, number.z )

    if( scene->IsTexturing() )
    {
        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, TextureMgr::GetInstance().m_Textures[ 1 ].texID );

        glBegin( GL_TRIANGLE_STRIP );
            glColor3f( 0.6f, 0.4f, 0.0f );
            glTexCoord2d(0.0,0.0); vertx( s0 );
            glTexCoord2d(1.0,0.0); vertx( s1 );
            glTexCoord2d(1.0,1.0); vertx( s2 );
            glTexCoord2d(0.0,1.0); vertx( s3 );
            glTexCoord2d(0.0,0.0); vertx( s4 );
            glTexCoord2d(1.0,0.0); vertx( s5 );
            glTexCoord2d(1.0,1.0); vertx( s6 );
            glTexCoord2d(0.0,1.0); vertx( s7 );
            glTexCoord2d(0.0,0.0); vertx( s8 );
            glTexCoord2d(1.0,0.0); vertx( s9 );
            glTexCoord2d(1.0,1.0); vertx( s10 );
            glTexCoord2d(0.0,1.0); vertx( s11 );
            glTexCoord2d(0.0,0.0); vertx( s12 );
            glTexCoord2d(1.0,0.0); vertx( s13 );
            glTexCoord2d(1.0,1.0); vertx( s14 );
            glTexCoord2d(0.0,1.0); vertx( s15 );
            glTexCoord2d(0.0,0.0); vertx( s0 );
            glTexCoord2d(1.0,0.0); vertx( s1 );
        glEnd();

        glDisable( GL_TEXTURE_2D );
    }
    else
    {
        glBegin( GL_TRIANGLE_STRIP );
            glColor3f( 0.6f, 0.4f, 0.0f );
            vertx( s0 );
            vertx( s1 );
            vertx( s2 );
            vertx( s3 );
            vertx( s4 );
            vertx( s5 );
            vertx( s6 );
            vertx( s7 );
            vertx( s8 );
            vertx( s9 );
            vertx( s10 );
            vertx( s11 );
            vertx( s12 );
            vertx( s13 );
            vertx( s14 );
            vertx( s15 );
            vertx( s0 );
            vertx( s1 );
        glEnd();
    }



    if( tris )
    {
        glBegin( GL_LINE_STRIP );
        glColor3f( 1.0f, 1.0f, 1.0f );
            vertx( s0 );
            vertx( s1 );
            vertx( s2 );
            vertx( s3 );
            vertx( s4 );
            vertx( s5 );
            vertx( s6 );
            vertx( s7 );
            vertx( s8 );
            vertx( s9 );
            vertx( s10 );
            vertx( s11 );
            vertx( s12 );
            vertx( s13 );
            vertx( s14 );
            vertx( s15 );
            vertx( s0 );
            vertx( s1 );
        glEnd();
    }

#undef vertx
*/
}


Vector3d CRoot::bottomPoint( void )
{
    return start;
}

Vector3d CRoot::topPoint( void )
{
    return stop;
}

