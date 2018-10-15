/* Scheduling Processes and Avoiding Deadlocks
 * Jake Allport
 * Jeremy Gouveia
 *
 * Started: 5/12/2018
 * Last Modified: 5/24/2018 
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "List.h"

using namespace std;

List::List() {

    head=NULL;
    curr=NULL;
    temp=NULL;
}

void List::AddNode(Jobs addJob){

    nodePtr n=new node;
    n->next=NULL;
    n->aJob= addJob;

    if(head !=NULL){
        curr =head;
        while(curr->next !=NULL){
            curr=curr->next;
        }

        curr->next=n;
    }
    else{
        head=n;
    }
}


void List::DeleteNode(int jobNum){
    nodePtr delPtr=NULL;
    temp=head;
    curr=head;
    while(curr!= NULL && stoi(curr->aJob.Job_Number)!=jobNum){
        temp=curr;
        curr=curr->next;
    }
    if(curr==NULL){
        cout<<jobNum<<"Was not in the list\n";
    }
    else{
        delPtr=curr;
        curr=curr->next;
        temp->next=curr;
        delete delPtr;
        cout<<"The value "<<jobNum<<" was deleted\n";
    }
}

Jobs List::FindNode(int findJob) {

    nodePtr delPtr = NULL;
    temp = head;
    curr = head;

    while (curr != NULL && stoi(curr->aJob.Job_Number) != (findJob)) {
        temp = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        cout << findJob << " Was not in the list\n";
    }
    
    cout<<"Found "<< temp->aJob.Job_Number<<'\n';
    return temp->aJob;

}


void List::PrintList(){

    curr=head;
    while(curr!=NULL){
        cout<<curr->aJob.Job_Number<<" Is in Queue"<<endl;
        curr=curr->next;
    }
}

Jobs List::pop() {

    if(head != NULL) {
        nodePtr aVal = head;
        head = head->next;
        return aVal->aJob;
    }
}

void List::swap(nodePtr a, nodePtr b) {

    Jobs temp = a->aJob;
    a->aJob = b->aJob;
    b->aJob = temp;
}


void List::sort() {
    //Ensure Hold1 is able to run for SJF
    cout << "Sorting List" << endl;
    nodePtr currtmp;
    nodePtr prevtmp = NULL;
    int swapped = 1;
    
    if (head == NULL) {
        return;
    }
    
    while(swapped) {
         swapped = 0;
        currtmp = head;
 
        while (currtmp->next != prevtmp)
        {
            if (currtmp->aJob.Job_Runtime > currtmp->next->aJob.Job_Runtime)
            { 
                cout << "Job A runtime: " << currtmp->aJob.Job_Runtime << endl;
                cout << "Job B runtime: " << currtmp->next->aJob.Job_Runtime << endl;
                swap(currtmp, currtmp->next);
                swapped = 1;
            }
            currtmp = currtmp->next;
        }
        prevtmp = currtmp;
    }
    while (swapped);
    PrintList();
}

