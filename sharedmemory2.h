#ifndef SHAREDMEMORY2_H
#define SHAREDMEMORY2_H
#include <vector>
#include <iostream>
#include "sharedmemorycontroller.h"

class SharedMemory2;

/**
 * @brief The SharedMemory2 class
 * Allows objects to copy eachother with shared memory.
 * Implement copyData & shareData.
 * Call copyFromRoot when copying objects.
 * Call writeData when writing to objects.
 * Check if canDeleteData is true before deleting shareable data.
 */
class SharedMemory2
{
public:
    SharedMemory2();
    virtual ~SharedMemory2();
    void setRoot(SharedMemory2 *newRoot);
    inline void copyFromRoot(SharedMemory2 *newRoot) { setRoot(newRoot); }
    void newRoot();
    virtual void copyData(SharedMemory2 *destination) = 0;  /** Copies shared data to destination - implementation is specific to child object. **/
    virtual void shareData(SharedMemory2 *destination) = 0; /** Shares shared data with destination - implementation is specific to child object. **/
    void decouple();
    void writeData() { decouple(); }
    void detachMemoryController();
    inline SharedMemoryController<SharedMemory2> *getRootMemoryController() { return rootMemoryController; } /** Returns memory controller. **/
    bool canDeleteData();


    std::vector<SharedMemory2*> objects;

protected:
    static const bool DEBUG = false;

private:
    SharedMemoryController<SharedMemory2> *rootMemoryController;
};

#endif // SHAREDMEMORY2_H
