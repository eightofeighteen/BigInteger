#include "sharedmemory.h"

SharedMemory::SharedMemory()
{
    if (DEBUG)  std::cout << "Init SharedMemory." << std::endl;
    root = this;
}

SharedMemory::~SharedMemory()
{
    if (DEBUG)  std::cout << "Destruct SharedMemory." << std::endl;
}

void SharedMemory::setRoot(SharedMemory *newRoot)
{
    //if (root == this && (!objects.size()))
    if (newRoot->root == newRoot)
    {
        root = newRoot;
    }
    else
    {
        root = newRoot->root;
    }
    root->objects.push_back(this);
    root->shareData(this);
}

void SharedMemory::decouple()
{
    if (root != this && objects.empty())
    {
        root->copyData(this);
        root->removeFromObjectsList(this);
        root = this;
    }
    else if (root == this && !objects.empty())
    {
        SharedMemory *newRoot = objects[0];
        newRoot->decouple();
        while (!objects.empty())
        {
            objects[0]->setRoot(newRoot);
            objects.pop_back();
        }
        /*while (!objects.empty())
        {
            objects[0]->decouple();
        }*/
    }
}

void SharedMemory::removeFromObjectsList(SharedMemory *object)
{
    for (std::vector<SharedMemory*>::iterator i = objects.begin(); i < objects.end(); i++)
    {
        if (*i == object)
        {
            objects.erase(i);
            break;
        }
    }
}
