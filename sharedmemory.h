#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H
#include <vector>
#include <iostream>

class SharedMemory
{
public:
    SharedMemory();
    virtual ~SharedMemory();
    bool readyForWrite();
    void setRootToSelf();
    void setRoot(SharedMemory *newRoot);
    virtual void copyData(SharedMemory *destination) = 0;
    virtual void shareData(SharedMemory *destination) = 0;
    void decouple();


    std::vector<SharedMemory*> objects;

protected:
    void removeFromObjectsList(SharedMemory* object);
    static const bool DEBUG = false;

private:

    SharedMemory *root;
};

#endif // SHAREDMEMORY_H
