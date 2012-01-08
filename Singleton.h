#ifndef _SINGLETON_H
#define	_SINGLETON_H
#include <stdlib.h>
#include <assert.h>

template <class T>
class	cSingleton
{
	protected:
					cSingleton() {};
					~cSingleton() {};

	private:
		static T	*_instance;

	public:
		static T	*GetInstance();
		static void	killInstance();
};

template <typename T>
T *cSingleton<T>::_instance = NULL;

template <typename T>
T *cSingleton<T>::GetInstance()
{
    if (_instance == NULL)
    {
        _instance = new T;
    }
    return _instance;
}

template <typename T>
void cSingleton<T>::killInstance()
{
	if (_instance != NULL)
	{
	    delete _instance;
		_instance = NULL;
	}
}

#endif	/* _SINGLETON_H */