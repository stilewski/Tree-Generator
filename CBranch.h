#ifndef CBRANCH_H
#define CBRANCH_H

#include <vector>
#include "CRoot.h"
#include "CLeaf.h"

class CBranch
{
    public:
    CBranch();
    ~CBranch();

    void PushSegment( CRoot s );
    void PushLeaf( CLeaf l );

    void Simplify( void );
    void GenerateList( void );
    void DrawTris( void );

    private:
    std::vector< CRoot > m_Segments;
    //std::vector< CRoot > m_Segments2;
    std::vector< CLeaf > m_Leafs;
};

#endif // CBRANCH_H
