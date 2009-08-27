/*      @ file:            @ last modified:                    @ author:
 *      CPlant.c             31-07-2009 21:20                    Zborowski S.
 *
 *      @ Description:
 *      Implementation of L-system trees.
 */

#include <GL/gl.h>
#include <math.h>
#include "CPlant.h"
#include "common.h"
#include "CRand.h"
#include <sstream>
#include <string>
#include "TextureMgr.h"
#include "Vector3d.h"
#include "CRoot.h"
#include "CLeaf.h"
#include "CBranch.h"

//to remove
#include <iostream>
using namespace std;

double getRandom()
{
    double random = 0;
    MTRand drand;
    for( int i = 0; i < 10; ++i )
    {
        random = drand();
    }

    random -= 0.5f;
    random *= 40.0f;
    //cout << "random: " << random << endl;
    return random;
}
float Bangle = 40.0f;


CPlant::CPlant()
{
    m_currpos = 0;m_currpos2 = 0;m_currpos3d=0,m_currpos3dm=0,m_formula_pos=0;
    m_root_r = "P";
    m_leaf_r = "L";
    m_lbracket_r = "[";
    m_rbracket_r = "]";

    m_formula.str( "" );
    displayList = glGenLists( 1 );

    m_Tris = false;
    m_Random = true;
    m_Gravity = false;
}

CPlant::CPlant( std::string formula )
{
    CPlant();
    m_formula.str( formula );
}

CPlant::CPlant( std::string formula, std::string root_r, std::string leaf_r, std::string lbracket_r, std::string rbracket_r )
{
    m_currpos = 0;m_currpos2 = 0;m_currpos3d=0,m_currpos3dm=0,m_formula_pos=0;
    m_root_r = root_r;
    m_leaf_r = leaf_r;
    m_lbracket_r = lbracket_r;
    m_rbracket_r = rbracket_r;

    m_formula.str( formula );
    displayList = glGenLists( 1 );

    m_Tris = false;
    m_Random = true;
    m_Gravity = false;
}

void CPlant::set( std::string formula, std::string root_r, std::string leaf_r, std::string lbracket_r, std::string rbracket_r )
{
    m_currpos = 0;m_currpos2 = 0;m_currpos3d=0;
    m_root_r = root_r;
    m_leaf_r = leaf_r;
    m_lbracket_r = lbracket_r;
    m_rbracket_r = rbracket_r;

    m_formula.str( formula );
}

bool CPlant::CheckFormula()
{
    uint opened = 0, closed = 0;
    u8 s;

    for( uint i = 0; i < m_formula.str().length(); i++ )
    {
        s = m_formula.str().c_str()[ i ];
        if( s == '[' )
            opened++;
        else if( s == ']' )
            closed++;
    }

    return ( opened == closed );
}


void CPlant::ExpandFormula( uint N )
{
    std::stringstream newFormula;

    for( uint n = 0; n < N; n++ )
    {
        for( uint i = 0; i < m_formula.str().size(); i++ )
        {
            switch( m_formula.str().c_str()[ i ] )
            {
                case 'P':
                    newFormula << m_root_r;
                break;

                case 'L':
                    newFormula << m_leaf_r;
                break;

                case '[':
                    newFormula << m_lbracket_r;
                break;

                case ']':
                    newFormula << m_rbracket_r;
                break;

                case '+':
                    // increment angle
                break;

                case '-':
                    // decrement angle
                break;

                default:
                break;
            }
        }

        m_formula.str( newFormula.str() );
        newFormula.str( "" );
    }
}

void CPlant::Simplify( void )
{
    for( m_Branches_Iter = m_Branches.begin(); m_Branches_Iter != m_Branches.end(); ++m_Branches_Iter )
    {
        (*m_Branches_Iter).Simplify();
    }
}

/*
void CPlant::DrawPlant( float x0, float y0, double angle, double len )
{
    while( m_currpos < m_formula.str().length() )
    {
        len = len * 0.995;
        char sign = m_formula.str().c_str()[ m_currpos ];
        m_currpos++;

        if( sign == 'L' || sign == 'P' )
        {
            float x1 = x0 + len * cos( angle * M_PI / 180.0 );
            float y1 = y0 + len * sin( angle * M_PI / 180.0 );
            //if( x1 > MAX_RIGHT )
              //  MAX_RIGHT = x1;
            //if( x1 < MAX_LEFT )
              //  MAX_LEFT = x1;

            //if( y1 > MAX_UP )
              //  MAX_UP = y1;


            if( sign == 'L' )
                glColor3f( 0.1, 1.0, 0.1 );
            else
                glColor3f( 1.0, 0.2, 0.4 );

            glBegin( GL_LINES );
                glVertex3f( x0, y0, 0.0f );
                glVertex3f( x1, y1, 0.0f );
            glEnd();

            x0 = x1;
            y0 = y1;
        }

        if( sign == '[' )
        {
            Bangle = -Bangle;
            DrawPlant( x0, y0, angle + Bangle + getRandom(), len );
        }

        if( sign == ']' )
            return;
    }
    m_currpos = 0;
}

void CPlant::GeneratePlant( float x0, float y0, float z0, double angle, double Zangle, double len )
{
    if( m_currpos2 == 0 )
        m_Lines.clear();


    while( m_currpos2 < m_formula.str().length() )
    {
        len = len * 0.995;
        char sign = m_formula.str().c_str()[ m_currpos2 ];
        m_currpos2++;

        if( sign == 'L' || sign == 'P' )
        {
            if( sign == 'L' )
                len /= 6.0f;

            float x1 = x0 + len * cos( angle * M_PI / 180.0f );
            float y1 = y0 + len * sin( angle * M_PI / 180.0f );
            float z1 = z0 + len * sin( Zangle * M_PI / 180.0f );

            if( sign == 'L' )
                len *= 6.0f;

            /// NOW IT'S TIME TO
            /// GENERATE VECTOR!!
            line3 LINE;
            if( sign == 'L' )
            {
                LINE.cr = 0.1f;
                LINE.cg = 1.0f;
                LINE.cb = 0.1f;
                LINE.is_root = false;
            }
            else
            {
                LINE.cr = 1.0f;
                LINE.cg = 0.2f;
                LINE.cb = 0.4f;
                LINE.is_root = true;
            }

            LINE.x0 = x0;
            LINE.y0 = y0;
            LINE.z0 = z0;//0.0f;
            LINE.x1 = x1;
            LINE.y1 = y1;
            LINE.z1 = z1;//0.0f;

            m_Lines.push_back( LINE );

            x0 = x1;
            y0 = y1;
            z0 = z1;
        }

        if( sign == '[' )
        {
            Bangle = -Bangle;
            GeneratePlant( x0, y0, z0, angle + Bangle + getRandom(), Zangle+getRandom(), len );
        }

        if( sign == ']' )
        {
            return;
        }
    }
    m_currpos2 = 0;
}

void CPlant::GeneratePlant3d( float x0, float y0, float z0, float width, double angle, double Zangle, double len )
{
    if( m_currpos3d == 0 )
        m_Squares.clear();


    float width_d = 0.95f;

    while( m_currpos3d < m_formula.str().length() )
    {
        len = len * 0.995f;
        char sign = m_formula.str().c_str()[ m_currpos3d ];
        m_currpos3d++;

        if( sign == 'L' || sign == 'P' )
        {
            if( sign == 'L' )
                len /= 6.0f;

            float x1 = x0 + len * cos( angle * M_PI / 180.0f );
            float y1 = y0 + len * sin( angle * M_PI / 180.0f );
            float z1 = z0 + len * sin( Zangle * M_PI / 180.0f );

            if( sign == 'L' )
                len *= 6.0f;

            /// NOW IT'S TIME TO
            /// GENERATE VECTOR!!
            //line3 LINE;
            square3 SQUARE;
            if( sign == 'L' )
            {
                SQUARE.x0 = x1 - width;
                SQUARE.y0 = y1;
                SQUARE.z0 = z1 + width;

                SQUARE.x1 = x1 + width;
                SQUARE.y1 = y1;
                SQUARE.z1 = z1 + width;

                SQUARE.x2 = x0 + width;
                SQUARE.y2 = y0;
                SQUARE.z2 = z0 + width;

                SQUARE.x3 = x0 - width;
                SQUARE.y3 = y0;
                SQUARE.z3 = z0 + width;

                //glVertex3f( x1 - eps, y1, z1 + eps );
                //glVertex3f( x1 + eps, y1, z1 + eps );
                //glVertex3f( x0 + eps, y0, z0 + eps );
                //glVertex3f( x0 - eps, y0, z0 + eps );
                SQUARE.is_root = false;
                m_Squares.push_back( SQUARE );
            }
            else
            {
                /// front face
                SQUARE.x0 = x1 - width;
                SQUARE.y0 = y1;
                SQUARE.z0 = z1 + width*width_d;

                SQUARE.x1 = x1 + width;
                SQUARE.y1 = y1;
                SQUARE.z1 = z1 + width*width_d;

                SQUARE.x2 = x0 + width;
                SQUARE.y2 = y0;
                SQUARE.z2 = z0 + width;

                SQUARE.x3 = x0 - width;
                SQUARE.y3 = y0;
                SQUARE.z3 = z0 + width;

                SQUARE.is_root = true;
                m_Squares.push_back( SQUARE );

                /// back face
                SQUARE.x0 = x1 - width;
                SQUARE.y0 = y1;
                SQUARE.z0 = z1 - width*width_d;

                SQUARE.x1 = x1 + width;
                SQUARE.y1 = y1;
                SQUARE.z1 = z1 - width*width_d;

                SQUARE.x2 = x0 + width;
                SQUARE.y2 = y0;
                SQUARE.z2 = z0 - width;

                SQUARE.x3 = x0 - width;
                SQUARE.y3 = y0;
                SQUARE.z3 = z0 - width;

                SQUARE.is_root = true;
                m_Squares.push_back( SQUARE );

                /// left face
                SQUARE.x0 = x1 - width;
                SQUARE.y0 = y1;
                SQUARE.z0 = z1 + width*width_d;

                SQUARE.x1 = x1 - width;
                SQUARE.y1 = y1;
                SQUARE.z1 = z1 - width*width_d;

                SQUARE.x2 = x0 - width;
                SQUARE.y2 = y0;
                SQUARE.z2 = z0 - width;

                SQUARE.x3 = x0 - width;
                SQUARE.y3 = y0;
                SQUARE.z3 = z0 + width;

                SQUARE.is_root = true;
                m_Squares.push_back( SQUARE );

                /// right face
                SQUARE.x0 = x1 + width;
                SQUARE.y0 = y1;
                SQUARE.z0 = z1 + width*width_d;

                SQUARE.x1 = x1 + width;
                SQUARE.y1 = y1;
                SQUARE.z1 = z1 - width*width_d;

                SQUARE.x2 = x0 + width;
                SQUARE.y2 = y0;
                SQUARE.z2 = z0 - width;

                SQUARE.x3 = x0 + width;
                SQUARE.y3 = y0;
                SQUARE.z3 = z0 + width;

                SQUARE.is_root = true;
                m_Squares.push_back( SQUARE );
            }




            x0 = x1;
            y0 = y1;
            z0 = z1;
            width *= width_d;
        }

        if( sign == '[' )
        {
            Bangle = -Bangle;
            GeneratePlant3d( x0, y0, z0, width*width_d, angle + Bangle + getRandom(), Zangle+getRandom()*10.0f, len );
        }

        if( sign == ']' )
        {
            return;
        }
    }
    m_currpos3d = 0;
}

void CPlant::DrawPlantFromBuffer3d( void )
{
    for( m_Iterator_s = m_Squares.begin(); m_Iterator_s != m_Squares.end(); ++m_Iterator_s )
    {
        float x0 = (*m_Iterator_s).x0;
        float y0 = (*m_Iterator_s).y0;
        float z0 = (*m_Iterator_s).z0;
        float x1 = (*m_Iterator_s).x1;
        float y1 = (*m_Iterator_s).y1;
        float z1 = (*m_Iterator_s).z1;
        float x2 = (*m_Iterator_s).x2;
        float y2 = (*m_Iterator_s).y2;
        float z2 = (*m_Iterator_s).z2;
        float x3 = (*m_Iterator_s).x3;
        float y3 = (*m_Iterator_s).y3;
        float z3 = (*m_Iterator_s).z3;

        if( (*m_Iterator_s).is_root )
        {
            TextureMgr::GetInstance().DrawTexture( 1, x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3 );
        }
        else
        {
            TextureMgr::GetInstance().DrawTexture( 0, x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3 );
        }

            glColor3f( 1.0, 1.0, 1.0 );
            glBegin( GL_LINES );
                glVertex3f( x0, y0, z0 );
                glVertex3f( x1, y1, z1 );
                glVertex3f( x2, y2, z2 );
                glVertex3f( x3, y3, z3 );
            glEnd();
    }
}
*/


CPlant::~CPlant()
{
}



/// ACTUAL

void CPlant::GeneratePlantB( Vector3d v, number len, number width, number angle, number zangle )
{
    number width_decrement = 0.975f;
    number length_decrement = 0.995f;
    Vector3d v1;

    bool catch_ = true;
    uint opened = 0;
    uint nRoots = 0;

    if( m_formula_pos == 0 )
    {
        while( m_formula_pos < m_formula.str().length() )
        {
            u8 sign = m_formula.str().c_str()[ m_formula_pos ];
            if( sign == 'P' && opened == 0 )
                nRoots++;
            else if( sign == '[' )
                opened++;
            else if( sign == ']' )
                opened--;

            m_formula_pos++;
        }

        m_formula_pos = 0;
        width_decrement = 1.0f - 1.0f / (number)nRoots;
    }
    else
    {
        uint tmp = m_formula_pos;
        opened = 1;
        while( opened > 0 )
        {
            u8 sign = m_formula.str().c_str()[ tmp ];
            if( sign == 'P' && opened == 1 )
                nRoots++;
            else if( sign == '[' )
                opened++;
            else if( sign == ']' )
                opened--;

            tmp++;
        }
        width_decrement = 1.0f - 1.0f / (number)nRoots +0.05f;
    }

    if( m_formula_pos == 0 )
    {
        m_Roots.clear();
        m_Leafs.clear();
        m_Branches.clear();
    }


    CBranch branch;
    uint numLeafs = 0, numSegments = 0;
    while( m_formula_pos < m_formula.str().length() )
    {
        len *= length_decrement;
        u8 sign = m_formula.str().c_str()[ m_formula_pos ];
        m_formula_pos++;

        switch( sign )
        {
            case '+':
                angle += 10.0f;
            case '-':
                angle -= 10.0f;
            case 'P':
            case 'L':

                v1 = Vector3d( v.x + len*cos( angle * M_PI / 180.0f ), v.y + len*sin( angle * M_PI / 180.0f ), v.z + len*sin( zangle * M_PI / 180.0f ) );

                if( sign == 'L' )
                {
                    CLeaf l;
                    l.GenerateLeaf( v, v1, 0, 0 );
                    m_Leafs.push_back( l );
                    branch.PushLeaf( l );
                    numLeafs++;
                }
                else
                {
                    CRoot r;
                    r.GenerateRoot( v, v1, width, width*width_decrement, m_Tris );
                    //m_Roots.push_back( r );
                    branch.PushSegment( r );
                    numSegments++;

                    v = v1;
                    if( width > 0.025f )
                        width *= width_decrement;
                }
            break;

            case '[':
                Bangle = -Bangle;
                GeneratePlantB( v, len, width, m_Random ? angle + Bangle + getRandom() : angle + Bangle, m_Random ? zangle+getRandom()*10.0f : zangle );
            break;

            case ']':
                if( numSegments > 0 )
                    m_Branches.push_back( branch );
                return;
            break;

            default: break;
        }
    }

    m_formula_pos = 0;
    if( numSegments > 0 )
        m_Branches.push_back( branch );
}


void CPlant::GenerateDisplayList( void )
{
    glDeleteLists( displayList, 1 );
    displayList = glGenLists( 1 );
    glNewList( displayList, GL_COMPILE );

    glColor3f( 1.0f, 1.0f, 1.0f );
    for( m_Branches_Iter = m_Branches.begin(); m_Branches_Iter != m_Branches.end(); ++m_Branches_Iter )
    {
        (*m_Branches_Iter).GenerateList();
    }

    glEndList();
}

void CPlant::GeneratePlant( Vector3d v, number len, number width, number angle, number zangle )
{
    number width_decrement = 0.975f;
    number length_decrement = 0.995f;
    Vector3d v1;

    bool catch_ = true;
    uint opened = 0;
    uint nRoots = 0;

    if( m_formula_pos == 0 )
    {
        while( m_formula_pos < m_formula.str().length() )
        {
            u8 sign = m_formula.str().c_str()[ m_formula_pos ];
            if( sign == 'P' && opened == 0 )
                nRoots++;
            else if( sign == '[' )
                opened++;
            else if( sign == ']' )
                opened--;

            m_formula_pos++;
        }

        m_formula_pos = 0;
        width_decrement = 1.0f - 1.0f / (number)nRoots;
    }
    else
    {
        uint tmp = m_formula_pos;
        opened = 1;
        while( opened > 0 )
        {
            u8 sign = m_formula.str().c_str()[ tmp ];
            if( sign == 'P' && opened == 1 )
                nRoots++;
            else if( sign == '[' )
                opened++;
            else if( sign == ']' )
                opened--;

            tmp++;
        }
        width_decrement = 1.0f - 1.0f / (number)nRoots;
    }


    glDeleteLists( displayList, 1 );
    displayList = glGenLists( 1 );
    glNewList( displayList, GL_COMPILE );
    glColor3f( 1.0f, 1.0f, 1.0f );

    if( m_formula_pos == 0 )
    {
        m_Roots.clear();
        m_Leafs.clear();
    }

    while( m_formula_pos < m_formula.str().length() )
    {
        len *= length_decrement;
        u8 sign = m_formula.str().c_str()[ m_formula_pos ];
        m_formula_pos++;

        switch( sign )
        {
            case '+':
                angle += 10.0f;
            case '-':
                angle -= 10.0f;
            case 'P':
            case 'L':

                v1 = Vector3d( v.x + len*cos( angle * M_PI / 180.0f ), v.y + len*sin( angle * M_PI / 180.0f ), v.z + len*sin( zangle * M_PI / 180.0f ) );

                if( sign == 'L' )
                {
                    CLeaf l;
                    l.GenerateLeaf( v, v1, 0, 0 );
                    m_Leafs.push_back( l );
                }
                else
                {
                    CRoot r;
                    r.GenerateRoot( v, v1, width, width*width_decrement, m_Tris );
                    m_Roots.push_back( r );

                    v = v1;
                    width *= width_decrement;
                }
            break;

            case '[':
                Bangle = -Bangle;
                GeneratePlant( v, len, width, m_Random ? angle + Bangle + getRandom() : angle + Bangle, m_Random ? zangle+getRandom()*10.0f : zangle );
            break;

            case ']':
                return;
            break;

            default: break;
        }
    }

    m_formula_pos = 0;
    glEndList();
}





void CPlant::GeneratePlant3dStrips( float x0, float y0, float z0, float len, float width, double angle, double Zangle )
{
    if( m_currpos3dm == 0 )
        m_Strips.clear();

    glDeleteLists( displayList, 1 );
    displayList = glGenLists( 1 );
    glNewList( displayList, GL_COMPILE );
    glColor3f( 1.0f, 1.0f, 1.0f );

    float width_d = 0.975f;
    /**
    uint nRoots = 0;
    bool catch_ = true;
    for( uint i = 0; i < m_formula.str().length(); ++i )
    {
        if( m_formula.str().c_str()[ i ] == 'P' )
            nRoots++;
        else if( m_formula.str().c_str()[ i ] == '[' )
            catch_ = false;
        else if( m_formula.str().c_str()[ i ] == ']' )
            catch_ = true;
    }
    printf( "Number of roots in this branch is: %d.   ", nRoots );**/

    while( m_currpos3dm < m_formula.str().length() )
    {
        len = len * 0.995f;
        char sign = m_formula.str().c_str()[ m_currpos3dm ];
        m_currpos3dm++;

        if( sign == 'L' || sign == 'P' )
        {
            if( sign == 'L' )
                len /= 2.0f;

            float x1 = x0 + len * cos( angle * M_PI / 180.0f );
            float y1 = y0 + len * sin( angle * M_PI / 180.0f );
            float z1 = z0 + len * sin( Zangle * M_PI / 180.0f );

            if( sign == 'L' )
                len *= 2.0f;

            /// NOW IT'S TIME TO
            /// GENERATE VECTOR!!
            square_strip S;

            if( sign == 'L' )
            {
                /*//SQUARE.x0 = x1 - width;
                //SQUARE.y0 = y1;
                //SQUARE.z0 = z1 + width;
                P.M.data[ 0 ][ 0 ] = x1 - width;
                P.M.data[ 0 ][ 1 ] = y1;
                P.M.data[ 0 ][ 2 ] = z1 + width;
                P1.M.data[ 0 ][ 0 ] = x1 - width;
                P1.M.data[ 0 ][ 1 ] = y1;
                P1.M.data[ 0 ][ 2 ] = z1 + width;

                //SQUARE.x1 = x1 + width;
                //SQUARE.y1 = y1;
                //SQUARE.z1 = z1 + width;
                P1.M.data[ 1 ][ 0 ] = x1 + width;
                P1.M.data[ 1 ][ 1 ] = y1;
                P1.M.data[ 1 ][ 2 ] = z1 + width;

                //SQUARE.x2 = x0 + width;
                //SQUARE.y2 = y0;
                //SQUARE.z2 = z0 + width;
                P.M.data[ 1 ][ 0 ] = x0 + width;
                P.M.data[ 1 ][ 1 ] = y0;
                P.M.data[ 1 ][ 2 ] = z0 + width;

                //SQUARE.x3 = x0 - width;
                //SQUARE.y3 = y0;
                //SQUARE.z3 = z0 + width;
                P.M.data[ 2 ][ 0 ] = x0 - width;
                P.M.data[ 2 ][ 1 ] = y0;
                P.M.data[ 2 ][ 2 ] = z0 + width;
                P1.M.data[ 2 ][ 0 ] = x0 - width;
                P1.M.data[ 2 ][ 1 ] = y0;
                P1.M.data[ 2 ][ 2 ] = z0 + width;

                //glVertex3f( x1 - eps, y1, z1 + eps );
                //glVertex3f( x1 + eps, y1, z1 + eps );
                //glVertex3f( x0 + eps, y0, z0 + eps );
                //glVertex3f( x0 - eps, y0, z0 + eps );
                //SQUARE.is_root = false;
                P.is_root = false;
                P1.is_root = false;
                m_Matrices.push_back( P );
                m_Matrices.push_back( P1 );
                //m_Squares.push_back( SQUARE );*/
                float eps = 0.2f;
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
                glEnd();
            }
            else
            {
                // strip
                //
                S.x0 = x0 - width;
                S.y0 = y0;
                S.z0 = z0 + width;

                S.x1 = x1 - width;
                S.y1 = y1;
                S.z1 = z1 + width*width_d;

                S.x2 = x0 + width;
                S.y2 = y0;
                S.z2 = z0 + width;

                S.x3 = x1 + width;
                S.y3 = y1;
                S.z3 = z1 + width*width_d;

                S.x4 = x0 + width;
                S.y4 = y0;
                S.z4 = z0 - width;

                S.x5 = x1 + width;
                S.y5 = y1;
                S.z5 = z1 - width*width_d;

                S.x6 = x0 - width;
                S.y6 = y0;
                S.z6 = z0 - width;

                S.x7 = x1 - width;
                S.y7 = y1;
                S.z7 = z1 - width*width_d;

                S.is_root = true;
                m_Strips.push_back( S );


                glBegin( GL_TRIANGLE_STRIP );
                    glColor3f( 0.6f, 0.4f, 0.0f );
                    glVertex3f( S.x0, S.y0, S.z0 );
                    glVertex3f( S.x1, S.y1, S.z1 );
                    glVertex3f( S.x2, S.y2, S.z2 );
                    glVertex3f( S.x3, S.y3, S.z3 );
                    glVertex3f( S.x4, S.y4, S.z4 );
                    glVertex3f( S.x5, S.y5, S.z5 );
                    glVertex3f( S.x6, S.y6, S.z6 );
                    glVertex3f( S.x7, S.y7, S.z7 );
                    glVertex3f( S.x0, S.y0, S.z0 );
                    glVertex3f( S.x1, S.y1, S.z1 );
                glEnd();
                /*/// front face
                SQUARE.x0 = x1 - width;
                SQUARE.y0 = y1;
                SQUARE.z0 = z1 + width*width_d;

                SQUARE.x1 = x1 + width;
                SQUARE.y1 = y1;
                SQUARE.z1 = z1 + width*width_d;

                SQUARE.x2 = x0 + width;
                SQUARE.y2 = y0;
                SQUARE.z2 = z0 + width;

                SQUARE.x3 = x0 - width;
                SQUARE.y3 = y0;
                SQUARE.z3 = z0 + width;

                SQUARE.is_root = true;
                m_Squares.push_back( SQUARE );

                /// back face
                SQUARE.x0 = x1 - width;
                SQUARE.y0 = y1;
                SQUARE.z0 = z1 - width*width_d;

                SQUARE.x1 = x1 + width;
                SQUARE.y1 = y1;
                SQUARE.z1 = z1 - width*width_d;

                SQUARE.x2 = x0 + width;
                SQUARE.y2 = y0;
                SQUARE.z2 = z0 - width;

                SQUARE.x3 = x0 - width;
                SQUARE.y3 = y0;
                SQUARE.z3 = z0 - width;

                SQUARE.is_root = true;
                m_Squares.push_back( SQUARE );

                /// left face
                SQUARE.x0 = x1 - width;
                SQUARE.y0 = y1;
                SQUARE.z0 = z1 + width*width_d;

                SQUARE.x1 = x1 - width;
                SQUARE.y1 = y1;
                SQUARE.z1 = z1 - width*width_d;

                SQUARE.x2 = x0 - width;
                SQUARE.y2 = y0;
                SQUARE.z2 = z0 - width;

                SQUARE.x3 = x0 - width;
                SQUARE.y3 = y0;
                SQUARE.z3 = z0 + width;

                SQUARE.is_root = true;
                m_Squares.push_back( SQUARE );

                /// right face
                SQUARE.x0 = x1 + width;
                SQUARE.y0 = y1;
                SQUARE.z0 = z1 + width*width_d;

                SQUARE.x1 = x1 + width;
                SQUARE.y1 = y1;
                SQUARE.z1 = z1 - width*width_d;

                SQUARE.x2 = x0 + width;
                SQUARE.y2 = y0;
                SQUARE.z2 = z0 - width;

                SQUARE.x3 = x0 + width;
                SQUARE.y3 = y0;
                SQUARE.z3 = z0 + width;

                //SQUARE.is_root = true;
                //m_Squares.push_back( SQUARE );*/
            }

            x0 = x1;
            y0 = y1;
            z0 = z1;
            width *= width_d;
        }

        if( sign == '[' )
        {
            Bangle = -Bangle;
            GeneratePlant3dStrips( x0, y0, z0, len, width/**width_d*/, angle + Bangle + getRandom(), Zangle+getRandom()*10.0f );
        }

        if( sign == ']' )
        {
            return;
        }
    }
    m_currpos3dm = 0;

    glEndList();

}



void CPlant::DrawPlantFromBuffer3dStrips( void )
{
    glCallList( displayList );
    if( m_Tris )
        for( m_Branches_Iter = m_Branches.begin(); m_Branches_Iter != m_Branches.end(); ++m_Branches_Iter )
        {
            (*m_Branches_Iter).DrawTris();
        }

    for( m_Leafs_Iter = m_Leafs.begin(); m_Leafs_Iter != m_Leafs.end(); ++m_Leafs_Iter )
    {
        (*m_Leafs_Iter).DrawLeaf();
    }
}



uint CPlant::GetLeafsNumber( void )
{
    return m_Leafs.size();
}

uint CPlant::GetRootsNumber( void )
{
    return m_Roots.size();
}

void CPlant::SetOptions( u8 o )
{
    if( o == PLANT_SHOW_TRIS )
    {
        m_Tris = !m_Tris;
    }
    else if( o == PLANT_RANDOM_ANGLES )
        m_Random = !m_Random;
}



