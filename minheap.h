#ifndef minheap_h
#define minheap_h
#include <string>

using namespace std;

struct sCharacter
{
    int ascii;
    string binary;
};


struct sNode
{
    sNode()
    {
        left = NULL;
        right = NULL;
        frequency = 0;
    }

    int asciivalue;
    int frequency;
    sNode *left ;
    sNode *right ;
};

class cMinHeap
{
public:
    cMinHeap(int theCapacity);
    ~cMinHeap();
    void Push(sNode& e);
    void append(sNode N, sCharacter* C, int arraysize, int &index, int& counter);
    sNode* Pop();
    sNode *heap;
    int heapsize;


    sNode* heapcopy;
    int copyindex;

private:
    //sNode *heap;
    //int heapsize;
    int capacity;
};


#endif
