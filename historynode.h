#ifndef HISTORYNODE_H
#define HISTORYNODE_H 1

#include <iostream>
#include "account.h"
using namespace std;

class HistoryNode
{
private:
    string time;
    HistoryNode *next;

public:
    HistoryNode();
    HistoryNode(string time);
    ~HistoryNode();
    friend class Customer;
};

#endif