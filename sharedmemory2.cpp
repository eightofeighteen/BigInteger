#include "sharedmemory2.h"

SharedMemory2::SharedMemory2()
{
    if (DEBUG)  std::cout << "Init SharedMemory2." << std::endl;
    //root = 0;
    rootMemoryController = 0;
}

SharedMemory2::~SharedMemory2()
{
    if (DEBUG)  std::cout << "Destruct SharedMemory2 - " << this << std::endl;
    detachMemoryController();
    //if (rootMemoryController->size() == 1)

}

/**
 * @brief SharedMemory2::detachMemoryController
 * Detaches the memory controller from this object, deleting it if this object is the only object attached to it.
 */
void SharedMemory2::detachMemoryController()
{
    if (rootMemoryController != 0)
    {
        if (rootMemoryController->size() <= 1)
        {
            if (DEBUG) std::cout << "Deleting memory controller." << std::endl;
            delete rootMemoryController;
        }
        else
        {
            rootMemoryController->removeObject(this);
            rootMemoryController = 0;
        }
    }
}

/**
 * @brief SharedMemory2::newRoot
 * Creates new memory controller for this object.
 */
void SharedMemory2::newRoot()
{
    rootMemoryController = new SharedMemoryController<SharedMemory2>();
    rootMemoryController->addObject(this);
}

/**
 * @brief SharedMemory2::setRoot
 * Creates new memory controller for newRoot, set it as this object's memory conroller and shares newRoot's data.
 * @param newRoot
 * Source object to share data from.
 */
void SharedMemory2::setRoot(SharedMemory2 *newRoot)
{
    detachMemoryController();
    if (newRoot->getRootMemoryController() == 0)
        newRoot->newRoot();
    rootMemoryController = newRoot->getRootMemoryController();
    rootMemoryController->addObject(this);
    newRoot->shareData(this);
}

/**
 * @brief SharedMemory2::decouple
 * Decouples this object from any shared data, copying it, if needed.
 */
void SharedMemory2::decouple()
{
    if (rootMemoryController != 0)
    {
        if (rootMemoryController->size() > 1)
        {
            rootMemoryController->getData(this)->copyData(this);
            rootMemoryController->removeObject(this);
            rootMemoryController = 0;
        }
        else
        {
            delete rootMemoryController;
            rootMemoryController = 0;
        }
    }
}

/**
 * @brief SharedMemory2::canDeleteData
 * Checks if the data is owned and can be deleted.
 * @return
 */
bool SharedMemory2::canDeleteData()
{
    if (rootMemoryController == 0)
    {
        return true;
    }
    else
    {
        return (rootMemoryController->size() <= 1);
    }
}
