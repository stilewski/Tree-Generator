#include "Vector3d.h"
#include <math.h>

Vector3d Vector3d::operator+( const Vector3d& other ) const
{
    return Vector3d( x + other.x, y + other.y, z + other.z );
}

Vector3d& Vector3d::operator+=( Vector3d& other )
{
    x += other.x;
    y += other.y;
    z += other.z;
    return ( *this );
}

Vector3d Vector3d::operator-( const Vector3d& other ) const
{
    return Vector3d( x - other.x, y - other.y, z - other.z );
}

Vector3d& Vector3d::operator-=( Vector3d& other )
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return ( *this );
}

Vector3d Vector3d::operator-() const
{
    return Vector3d( -x, -y, -z );
}

Vector3d Vector3d::operator/( number Scalar ) const
{
    return Vector3d( x / Scalar, y / Scalar, z / Scalar );
}

Vector3d operator*( number Scalar, const Vector3d& v )
{
    return Vector3d( Scalar * v.x, Scalar * v.y, Scalar * v.z );
}

Vector3d operator*( const Vector3d& v, number Scalar )
{
    return Vector3d( Scalar * v.x, Scalar * v.y, Scalar * v.z );
}

bool Vector3d::operator==( const Vector3d& other ) const
{
    return ( x == other.x && y == other.y && z == other.z );
}

bool Vector3d::operator!=( const Vector3d& other ) const
{
    return ( x != other.x || y != other.y || z != other.z );
}

bool Vector3d::operator<( const Vector3d& other )
{
    return ( x < other.x && y < other.y && z < other.z );
}

bool Vector3d::operator>( const Vector3d& other )
{
    return ( x > other.x && y > other.y && z > other.z );
}

Vector3d& Vector3d::operator=( const Vector3d& other )
{
    x = other.x;
    y = other.y;
    z = other.z;
    return ( *this );
}

Vector3d Vector3d::Normalize() const
{
    return ( (*this) / Lenght() );
}

number Vector3d::Lenght() const
{
    return (number)( sqrt( x*x + y*y + z*z ) );
}

number Dot( const Vector3d& v1, const Vector3d& v2 )
{
    return ( v1.x * v2.x + v1.y * v2.y + v1.z * v2.z );
}

Vector3d Cross( const Vector3d& v1, const Vector3d& v2 )
{
    return Vector3d( 0, 0, 0 );
}

void Vector3d::Project( const Vector3d& other )
{
    //( *this ) = other * ( ( *this ) * other )/( other * other );
}
