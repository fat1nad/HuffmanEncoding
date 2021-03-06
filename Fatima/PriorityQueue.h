///Fatima Nadeem - fn03768 - L1

#pragma once

#include "Node.h"

using namespace std;

class PriorityQueue
{
    int n;
    Node* sentinal;
    Node* head;
    Node* tail;

public:
    PriorityQueue();
    ~PriorityQueue();

    void Enqueue(Node*);
    Node* DeleteMin();
    void Pop();

    int Size();
//    void SetSize(int);
    Node* GetHead();
//    Node* GetTail();
//    void SetHead(Node*);
//    void SetTail(Node*);
};
