#include <algorithm>
#include "minheap.h"
#include <iostream>

using namespace std;

struct sCharacter;

cMinHeap::cMinHeap(int theCapacity = 10)
{
    heapsize = 0;
    heap = new sNode[256];

    heapcopy = new sNode[256];
    copyindex = 0;
}

cMinHeap::~cMinHeap()
{
    //delete[] heap;
}

bool compare(sNode& a, sNode& b)
{
    if(a.frequency > b.frequency)
        return true;
    else if(a.frequency == b.frequency)
    {
        if(a.asciivalue > b.asciivalue)
            return true;
        else
            return false;
    }
    else
        return false;
}
void cMinHeap::Push(sNode& e)
{
    int currentNode = ++heapsize;
    //while(currentNode != 1 && heap[currentNode/2].frequency > e.frequency)
    while(currentNode != 1 && compare(heap[currentNode/2], e))
    {
        heap[currentNode] = heap[currentNode/2];
        currentNode/=2;
    }
    heap[currentNode] = e;
}



sNode* cMinHeap::Pop()
{
    if(heapsize == 0) throw "Heap is empty. Cannot delete.";
    //heap[1] = NULL;
    //sNode top = heap[1];

    sNode lastE = heap[heapsize];
    //heap[heapsize+1] = heap[1];
    heapcopy[copyindex] = heap[1];
    copyindex++;
    heapsize--;

    int currentNode = 1; //root
    int child = 2;
    while(child <= heapsize)
    {
        if(child < heapsize && heap[child].frequency > heap[child + 1].frequency) child++;
        if(child < heapsize && heap[child].frequency == heap[child + 1].frequency && heap[child].asciivalue > heap[child +1].asciivalue) child++;

        if(lastE.frequency < heap[child].frequency)
            break;
        else if(lastE.frequency == heap[child].frequency && lastE.asciivalue < heap[child].asciivalue )
            break;

        heap[currentNode] = heap[child];
        currentNode = child; child *= 2;
    }
    heap[currentNode] = lastE;
    //return &heap[heapsize + 2];
    return &heapcopy[copyindex -1];
}


void cMinHeap::append(sNode N, sCharacter* C, int arraysize, int& index, int& counter)
{
    if(N.left == NULL)
    {
        C[index].ascii = N.asciivalue;
        index++;
    }
    else
    {
        C[index].binary.insert(C[index].binary.end(), '0');
        ++counter;
        append(*N.left, C, arraysize, index, counter);
        --counter;
        C[index].binary.insert(0, C[index-1].binary,0,counter);
        C[index].binary.insert(C[index].binary.end(), '1');
        ++counter;
        append(*N.right, C, arraysize, index, counter);
        --counter;
    }




   /*
    while(N.left != NULL && N.right != NULL)
    {
        N = *N.left;
        cout << N.asciivalue << endl;
        cout << N.frequency << endl;
        C[0].binary.insert(C[0].binary.end(), '0');
        cout << "insert 0" << endl;
    }
    C[0].ascii = N.asciivalue;
    */
}
