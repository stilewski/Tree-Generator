/*
 * File:   Singleton.h
 * Author: stilewski
 *
 * Created on 30 czerwiec 2009, 01:01
 */

#ifndef _SINGLETON_H
#define	_SINGLETON_H

#include <assert.h>

template< typename T >
class Singleton
{
    static T* Instance;

    public:
    Singleton( void )
    {
        assert( !Instance );
        int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
        Instance = (T*)((int)this + offset);
    }

    static T& GetInstance( void )
    {
        assert( Instance );
        return ( *Instance );
    }

    static T* GetInstancePtr( void )
    {
        return ( Instance );
    }

    ~Singleton( void )
    {
        assert( Instance );
        Instance = 0;
    }
};

template <typename T> T* Singleton<T>::Instance = 0;

#endif	/* _SINGLETON_H */

