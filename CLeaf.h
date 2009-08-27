#ifndef CLEAF_H
#define CLEAF_H

#include "common.h"
#include "Vector3d.h"

#define NO_LEAF         0x00

#define LEAF_SOSNA      0x01
#define LEAF_DAB        0x02
#define LEAF_WIERZBA    0x03
#define LEAF_KLON       0x04

#define SP_LEAF         0xff

#include <vector>
#include "Vector3d.h"

class CLeaf
{
    public:
    CLeaf( void );
    CLeaf( u8 T );
    ~CLeaf();

    void GenerateLeaf( Vector3d pos, Vector3d end, number spec, number size );
    void DrawLeaf( void );
    u8 GetType( void );
    void GenerateList( void );
    //

    private:
    u8 m_Type;
    std::vector< Vector3d > m_Points;

};

#endif // CLEAF_H
