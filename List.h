/* Scheduling Processes and Avoiding Deadlocks
 * Jake Allport
 * Jeremy Gouveia
 *
 * Started: 5/12/2018
 * Last Modified: 5/24/2018 
 */
#include "Jobs.h"


#ifndef OSPROJ_LIST_H
#define OSPROJ_LIST_H


class List{

private:

    typedef struct node{
        Jobs aJob;
        node* next;
    }*nodePtr;

    
    nodePtr curr;
    nodePtr temp;

public:
    nodePtr head;
    List();
    void sort();
    void AddNode(Jobs addJob);
    void DeleteNode(int jobNum);
    Jobs FindNode(int findNode);
    void PrintList();
    Jobs pop();
    void swap(nodePtr a, nodePtr b);

};



#endif //OSPROJ_LIST_H

