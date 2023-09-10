#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

struct node{
    int data;
    node*next;
    node*previous;
};

void add(node**head,node**last,int num){
    if (num<=0)                                      // if data is less or equal to zero, node will not add in the list
    {
        cout<<"number should be greater than zero, cannot perform operation"<<endl;
        return;
    }
    
    node*newnode=new node();                          // we will create a new node
    newnode->data=num;
    newnode->next=NULL;
    newnode->previous=NULL;
    if ((*head)==NULL)                               // if head is null,means list is empty
    {
        (*head)=newnode;                             // we will make it head of list 
        (*last)=newnode;                             // also we will make it last of list
        return;
    }
    (*last)->next=newnode;                           // otherwise add new node to the last of list
    newnode->previous=(*last);
    (*last)=newnode;                                // and make this new node last node of list
}
void ThirdLast(node**last){                      // function to print 3rd last node's data
    node*currentnode=(*last);                    // we will traverse from the end of list
    int i=1;                                     
    while (i!=3)                                 // traverse to 3rd last node
    {
        if (currentnode==NULL)
        {
            break;
        }
        
        currentnode=currentnode->previous;
        i+=1;
    }
    if (currentnode==NULL)                       // if list has node's less than 3
    {
        cout<<-1<<endl;
    }
    else{                                        // otherwise
        cout<<currentnode->data<<endl;           // print 3rd last node's data
    }
    
}
int main(){
    node*head=NULL;
    node*last=NULL;

    string file_name;
    cout<<"enter file name: ";cin>>file_name;       // taking file name from user

    // same as the previous 
    ifstream file(file_name);                     
    string command;

    while (getline(file,command))
    {
        string word;
        istringstream ss(command);     
        while(ss>>word){               // here another loop to read all the word in each line
            int num;
            istringstream is(word);

            is>>num;
            add(&head,&last,num);               // function to add node
        }
        
    }
    ThirdLast(&last);                          // function to print 3rd last node's data
}