#ifndef CROOT_H
#define CROOT_H

#include "common.h"
#include <vector>
#include "Vector3d.h"

typedef struct
{
    Vector3d p0;
    Vector3d p1;
    Vector3d p2;
    Vector3d p3;
} Square_t;

typedef struct
{
    Vector3d p0;
    Vector3d p1;
    Vector3d p2;
    Vector3d p3;
    Vector3d p4;
    Vector3d p5;
    Vector3d p6;
    Vector3d p7;
} Polygon_t;

class CRoot
{
    public:
    CRoot( void );
    CRoot( u8 T );
    ~CRoot();

    void Set(  );

    void GenerateRoot( Vector3d start, Vector3d stop, number w0, number w1, bool tris );
    void GenerateList( void );
    void DrawTris( void );

    Polygon_t bottom_p;
    Polygon_t top_p;

    Vector3d bottomPoint( void );
    Vector3d topPoint( void );

    number                                      w0, w1;
    private:
    Vector3d                                    start;
    Vector3d                                    stop;
    number                                      len;


    std::vector< Vector3d >                     m_Vertices;
    std::vector< Vector3d >::iterator           m_Vertices_Iter;

};

#endif // CROOT_H
