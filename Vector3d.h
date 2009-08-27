/*      @ file:            @ last modified:                    @ author:
 *      Vector3d.h         08-07-2009 01:16                    Zborowski
 *
 *      @ Description:
 *      three-dimensional Vector class.
 */

#ifndef _VECTOR3D_H
#define	_VECTOR3D_H


#include "common.h"

class Vector3d
{
    public:
    number x, y, z;

    Vector3d( void )
    {
        x = 0;
        y = 0;
        z = 0;
    }

    Vector3d( number x, number y, number z )
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }


    /// Operators:

    Vector3d operator+( const Vector3d& other ) const;

    Vector3d& operator+=( Vector3d& other );

    Vector3d operator-( const Vector3d& other ) const;

    Vector3d& operator-=( Vector3d& other );

    Vector3d operator-() const;

    Vector3d operator/( number Scalar ) const;

    friend Vector3d operator*( number Scalar, const Vector3d& v );

    friend Vector3d operator*( const Vector3d& v, number Scalar );

    bool operator==( const Vector3d& other ) const;

    bool operator!=( const Vector3d& other ) const;

    bool operator<( const Vector3d& other );

    bool operator>( const Vector3d& other );

    Vector3d& operator=( const Vector3d& other );
    //FIXME: WTF with #include <iostream> doesn't work
    //friend std::ostream& operator<<( std::ostream&, const Vector2d& v );
            //friend std::istream& operator>>( std::istream&, const Vector2d& v );


    /// Vector-like functions:

    Vector3d Normalize() const;

    number Lenght() const;

    static number Dot( const Vector3d& v1, const Vector3d& v2 );

    static Vector3d Cross( const Vector3d& v1, const Vector3d& v2 );

            static number Angle( const Vector3d& v1, const Vector3d& v2 );

            void Project( const Vector3d& other );

            void Reflect( const Vector3d& n );

    Vector3d abs( Vector3d& v ) const;


    /// Common vectors:

    static const Vector3d Zero;
    static const Vector3d UnitX;
    static const Vector3d UnitY;
    static const Vector3d UnitZ;

};


#endif	/* _VECTOR3D_H */
