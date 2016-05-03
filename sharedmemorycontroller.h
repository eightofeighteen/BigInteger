#ifndef SHAREDMEMORYCONTROLLER_H
#define SHAREDMEMORYCONTROLLER_H
#include <iostream>
#include <vector>

template <class T>
class SharedMemoryController
{
public:
    SharedMemoryController();
    virtual ~SharedMemoryController();
    std::vector<T*> objects; /** List of objects which use this memory object. **/
    T* getData(T *notThis = 0);
    void addObject(T *object);
    void removeObject(T *object);
    int size();
};

template <class T>
SharedMemoryController<T>::SharedMemoryController()
{
}

template<class T>
SharedMemoryController<T>::~SharedMemoryController()
{

}

template<class T>
/**
 * @brief SharedMemoryController<T>::getData
 * Returns an object which uses this memory controller.
 * Any object, except the object specified will be returned.
 * TODO: Change this collection to something lighter.
 * @param notThis
 * Does not return this object.
 * @return
 */
T* SharedMemoryController<T>::getData(T* notThis)
{
    if (objects.size() > 0)
        for (typename std::vector<T*>::iterator i = objects.begin(); i < objects.end(); i++)
            if (*i != notThis)
                return *i;
    return 0;
}

template<class T>
/**
 * @brief SharedMemoryController<T>::addObject
 * Adds an object to this memory controller.
 * @param object
 */
void SharedMemoryController<T>::addObject(T *object)
{
    objects.push_back(object);
}

template<class T>
/**
 * @brief SharedMemoryController<T>::removeObject
 * Removes an object from this memory controller.
 * @param object
 */
void SharedMemoryController<T>::removeObject(T *object)
{
    for (typename std::vector<T*>::iterator i = objects.begin(); i < objects.end(); i++)
    {
        if (*i == object)
        {
            objects.erase(i);
            break;
        }
    }
}

template<class T>
/**
 * @brief SharedMemoryController<T>::size
 * Returns number of objects which use this memory controller.
 * @return
 */
int SharedMemoryController<T>::size()
{
    return objects.size();
}


#endif // SHAREDMEMORYCONTROLLER_H
