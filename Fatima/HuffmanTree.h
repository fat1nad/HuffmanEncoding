///Fatima Nadeem - fn03768 - L1

#pragma once

#include "PriorityQueue.h"

using namespace std;

class HuffmanTree
{
private:
    Node* root;

public:
    HuffmanTree();
    HuffmanTree(PriorityQueue*);
    ~HuffmanTree;

    char* GenCode(T);
};

