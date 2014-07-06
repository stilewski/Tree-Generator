#include <iostream>
#include <stdio.h>
#include "CBranch.h"
#include "CRoot.h"
#include "CLeaf.h"
#include <vector>

CBranch::CBranch()
{

}

CBranch::~CBranch()
{

}


void CBranch::PushSegment( CRoot s )
{
    m_Segments.push_back( s );
}

void CBranch::PushLeaf( CLeaf l )
{
    m_Leafs.push_back( l );
}



void CBranch::GenerateList( void )
{
    std::vector< CRoot >::iterator it;
    for( it = m_Segments.begin(); it != m_Segments.end(); ++it )
    {
        (*it).GenerateList();
    }

    std::vector< CLeaf >::iterator i;
    for( i = m_Leafs.begin(); i != m_Leafs.end(); ++i )
    {
        (*i).GenerateList();
    }
}

void CBranch::DrawTris( void )
{
    std::vector< CRoot >::iterator it;
    for( it = m_Segments.begin(); it != m_Segments.end(); ++it )
    {
        (*it).DrawTris();
    }
}

void CBranch::Simplify( void )
{
    std::cout <<  "There was " << m_Segments.size() << " wooden segments. Now there are";
    if( m_Segments.size() > 1 )
    {
        std::vector< CRoot > tmp;
        Vector3d tmp_bottom( 0.0f, 0.0f, 0.0f );
        Vector3d tmp_top( 0.0f, 0.0f, 0.0f );
        number tmp_w0, tmp_w1;

        std::vector< CRoot >::iterator it;
        it = m_Segments.begin();
        int i = 1;
        CRoot R;
        tmp_bottom = (*it).bottomPoint();
        tmp_w0 = (*it).w0;

        //printf( "first segment (%lf,%lf,%lf)...\n", (*it).topPoint().x, (*it).topPoint().y, (*it).topPoint().z );

        for( it = m_Segments.begin(); it != m_Segments.end(); ++it )
        {

            if( it+1 != m_Segments.end() && (*it).topPoint() == (*(it+1)).bottomPoint() )
            {
                //m_Segments.erase( it );
                i++;
            }
            else
                break;
        }

        //printf( "last segment (%lf,%lf,%lf)...\n", (*it).topPoint().x, (*it).topPoint().y, (*it).topPoint().z );

        tmp_top = (*it).topPoint();
        tmp_w1 = (*it).w1;

        R.GenerateRoot( tmp_bottom, tmp_top, tmp_w0, tmp_w1, false );
        //printf( "%d segments as one, w0: %lf, w1: %lf \n", i, tmp_w0, tmp_w1 );
        //m_Segments.clear();
        //m_Segments2.push_back( R );


        //m_Segments.insert( m_Segments.begin(), R );
    }
    std::cout <<  m_Segments.size() << std::endl;
}



