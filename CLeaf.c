/*      @ file:            @ last modified:                    @ author:
 *      CLeaf.c            08-07-2009 01:16                    Zborowski
 *
 *      @ Description:
 *      Leaf class implementation
 */

#include "common.h"
#include "CLeaf.h"
#include "Vector3d.h"
#include "GL/gl.h"
#include <math.h>
#include "TextureMgr.h"
#include "Scene.h"

CLeaf::CLeaf()
{
}

CLeaf::~CLeaf()
{
}


void CLeaf::GenerateLeaf( Vector3d pos, Vector3d end, number spec, number size )
{
    /*Vector3d v1( pos.x+0.1f, pos.y+0.1f, pos.z+0.1f );
    S.x0 = x0;
    S.y0 = y0;
    S.z0 = z0;

    S.x1 = x1;
    S.y1 = y1;
    S.z1 = z1;

    S.x2 = x1;
    S.y2 = y0;
    S.z2 = z1;

    S.x3 = x0 + eps;
    S.y3 = y1;
    S.z3 = z0;
    S.is_root = false;

    m_Strips.push_back( S );
    glBegin( GL_TRIANGLE_STRIP );
        glColor3f( 0.0f, 1.0f, 0.0f );
        glVertex3f( S.x0, S.y0, S.z0 );
        glVertex3f( S.x1, S.y1, S.z1 );
        glVertex3f( S.x2, S.y2, S.z2 );
        //glVertex3f( S.x3, S.y3, S.z3 );
    glEnd();*/

    //Vector3d start( pos.x, pos.y, pos.z );
    //Vector3d stop( end.x, end.y, end.z );
    m_Points.clear();
    m_Points.push_back( pos );
    m_Points.push_back( end );


}

void CLeaf::GenerateList()
{
    number size = 0.05f;
    Vector3d pos, pos2;//( 0.0f, 0.0f, 0.0f );
    pos = m_Points[ 0 ];
    pos2 = m_Points[ 1 ];


    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, TextureMgr::GetInstance().m_Textures[ 0 ].texID );
    glBegin( GL_QUADS );
        glColor3f( 0.0f, 1.0f, 0.1f );
        glTexCoord2f( 0.0f, 0.0f ); glVertex3f( pos.x - size, pos.y, pos.z );
        glTexCoord2f( 1.0f, 0.0f ); glVertex3f( pos.x + size, pos.y, pos.z );
        glTexCoord2f( 1.0f, 1.0f ); glVertex3f( pos.x + size, pos2.y, pos2.z );
        glTexCoord2f( 0.0f, 1.0f ); glVertex3f( pos.x - size, pos2.y, pos2.z );
    glEnd();
    glDisable( GL_TEXTURE_2D );
}

void CLeaf::DrawLeaf( void )
{
    number size = 0.35f;
    Vector3d pos, pos2;//( 0.0f, 0.0f, 0.0f );
    pos = m_Points[ 0 ];
    pos2 = m_Points[ 1 ];


    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, TextureMgr::GetInstance().m_Textures[ 0 ].texID );
    glBegin( GL_QUADS );
        glColor3f( 0.0f, 1.0f, 0.1f );
        glTexCoord2f( 0.0f, 0.0f ); glVertex3f( pos.x - size, pos.y, pos.z );
        glTexCoord2f( 1.0f, 0.0f ); glVertex3f( pos.x + size, pos.y, pos.z );
        glTexCoord2f( 1.0f, 1.0f ); glVertex3f( pos.x + size, pos2.y, pos2.z );
        glTexCoord2f( 0.0f, 1.0f ); glVertex3f( pos.x - size, pos2.y, pos2.z );
    glEnd();
    glDisable( GL_TEXTURE_2D );
    /*glBegin( GL_TRIANGLE_STRIP );
        glColor3f( 0.0f, 1.0f, 0.1f );
        glVertex3f( pos.x + 0.0f, pos.y + 0.0f, pos.z + 0.0f );
        glVertex3f( pos.x + 0.0f, pos.y + 1.0f * size, pos.z + 0.0f );
        glVertex3f( pos.x + 0.1f * size, pos.y + 0.05f * size, pos.z + 0.0f );
        glVertex3f( pos.x + 0.25f * size, pos.y + 0.15f * size, pos.z + 0.0f );
        glVertex3f( pos.x + 0.0f, pos.y + 1.0f * size, pos.z + 0.0f );
        glVertex3f( pos.x + 0.30f * size, pos.y + 0.2f * size, pos.z + 0.0f );
        glVertex3f( pos.x + 0.0f, pos.y + 1.0f * size, pos.z + 0.0f );
        glVertex3f( pos.x + 0.35f * size, pos.y + 0.35f * size, pos.z + 0.0f );
        glVertex3f( pos.x + 0.0f, pos.y + 0.0f, pos.z + 0.0f );
        glVertex3f( pos.x + 0.32f * size, pos.y + 0.39f * size, pos.z + 0.0f );
        glVertex3f( pos.x + 0.0f, pos.y + 0.0f, pos.z + 0.0f );
        glVertex3f( pos.x + 0.25f * size, pos.y + 0.57f * size, pos.z + 0.0f );
        glVertex3f( pos.x + 0.0f, pos.y + 0.0f, pos.z + 0.0f );
    glEnd();*/

    /*glBegin( GL_TRIANGLE_STRIP );
        glColor3f( 0.0f, 1.0f, 0.1f );
        glVertex3f( pos.x - size, pos.y, pos.z );
        glVertex3f( pos.x + size, pos.y, pos.z );
        glVertex3f( pos.x, pos2.y, pos2.z );
    glEnd();*/


    //glBegin( GL_LINES );
    //    glLineWidth( 14.0f );
    //    glColor3f( 0.0f, 0.8f, 0.0f );
    //    glVertex3f( 0.0f, 0.0f, 0.0f );
    //    glVertex3f( 0.0f, 1.0f * size , 0.0f );
    //    glLineWidth( 1.0f );
    //glEnd();


    /*glBegin( GL_LINE_STRIP );
        glColor3f( 0.0f, 0.9f, 0.1f );
        glVertex3f( m_Points[ 0 ].x, m_Points[ 0 ].y, m_Points[ 0 ].z );
        glVertex3f( ( m_Points[ 1 ].x + m_Points[ 0 ].x ) / 2.0f, ( m_Points[ 1 ].y + m_Points[ 0 ].y ) / 2.0f, ( m_Points[ 1 ].z + m_Points[ 0 ].z ) / 2.0f );
        //glVertex3f( m_Points[ 1 ].x, m_Points[ 1 ].y, m_Points[ 1 ].z );
    glEnd();*/

}
