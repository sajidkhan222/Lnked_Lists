#include<iostream>
#include<fstream>
#include<sstream>
#include<list>
#include<algorithm>
using namespace std;

struct editor{                                                   // double linked list
    int data;
    editor*next;
    editor*previous;
};
// for undo
list<string>l1;                                                 
list<int>l2;
list<int>l3;

void printAll(editor*curr_number){                              // print function to print all elements
    cout<<"List: [";
    while (curr_number!=NULL)
    {
        cout<<curr_number->data;
        curr_number=curr_number->next;
        if(curr_number!=NULL){
            cout<<", ";
        }
    }
    cout<<"]"<<endl;
}

void ADD(editor**head,editor**last,editor**cursor,int num,string per){
    editor*new_number=new editor();
    new_number->data=num;
    new_number->next=NULL;
    new_number->previous=NULL;

    if ((*head)==NULL)
    {
        (*head)=new_number;
        (*last)=new_number;
        (*cursor)=new_number;
    }
    
    else{
        (*last)->next=new_number;
        new_number->previous=(*last);
        (*last)=new_number;
        
    }
    if(per=="yes"){
        l1.push_back("Add");
        l2.push_back(-1000000000);
        l3.push_back(-1000000000);
    }
}

void DELETE(editor**head,editor**last,editor**cursor,string per){
    if ((*head)==NULL)
    {
        cout<<"NO number to delete, empty List"<<endl;
        return;
    }
    else if ((*head)==(*last))
    {
        if(per=="yes"){
            l1.push_back("Delete");
            l2.push_back((*head)->data);
            l3.push_back(-1000000000);
        }
        delete(*head);
        (*head)=NULL;
        (*last)=NULL;
        (*cursor)=NULL;
        
    }
    
    else{
        editor*curr_number=(*last);
        (*last)=(*last)->previous;
        (*last)->next=NULL;
        if ((*cursor)==curr_number)
        {
            (*cursor)=(*last);
            
        }
        if(per=="yes"){
            l1.push_back("Delete");
            l2.push_back(curr_number->data);
            l3.push_back(-1000000000);
        }
        delete(curr_number);
    }
    
}

void AddIndex(editor**head,editor**last,editor**cursor,int index,int num,string per){
    editor*new_number=new editor();
    new_number->data=num;
    new_number->next=NULL;
    new_number->previous=NULL;

    editor*curr_number=(*head);
    int i=0;
    if (i<0)
    {
        cout<<"negative index,cannot perform operation"<<endl;
        return;
    }
    
    while (i!=index)
    {
        if (curr_number==NULL)
        {
            cout<<"index is out of length, cannot perform operation"<<endl;
            return;
        }
        i+=1;
        curr_number=curr_number->next;
    }
    
    if (curr_number==NULL)
    {
        curr_number=(*last);
        cout<<curr_number->data<<endl;
        curr_number->next=new_number;
        new_number->previous=curr_number;
        new_number->next=NULL;
        (*last)=new_number;
        if(per=="yes"){
            l1.push_back("Addi");
            l2.push_back(index);
            l3.push_back(-1000000000);
        }
    }
    
    else if ((*head)==curr_number)
    {
        
        new_number->next=curr_number;
        curr_number->previous=new_number;
        (*head)=new_number;
        (*cursor)=(*cursor)->previous;
        if(per=="yes"){
            l1.push_back("Addi");
            l2.push_back(index);
            l3.push_back(-1000000000);
        }
    }
    
    else if ((*last)==curr_number)
    {
        editor*prev=curr_number->previous;
        new_number->next=curr_number;
        curr_number->previous=new_number;
        new_number->previous=prev;
        prev->next=new_number;
        if (curr_number==(*cursor))
        {
            (*cursor)=new_number;
        }
        if(per=="yes"){
            l1.push_back("Addi");
            l2.push_back(index);
            l3.push_back(-1000000000);
        } 
    }
    
    else
    {
        editor*prev=curr_number->previous;
        prev->next=new_number;
        new_number->previous=prev;
        new_number->next=curr_number;
        curr_number->previous=new_number;
        if(per=="yes"){
            l1.push_back("Addi");
            l2.push_back(index);
            l3.push_back(-1000000000);
        }
        //this process is for moving cursor backward
        while (curr_number!=(*cursor))           // if the new number add before cursor or at cursor,then we have to move cursor one step backward 
        {
            if (curr_number==NULL)
            {
                break;
            } 
            curr_number=curr_number->next;
        }
        if (curr_number==(*cursor))
        {
            
            (*cursor)=(*cursor)->previous;
        }
        
        
    }
    
}

void DeleteIndex(editor**head,editor**last,editor**cursor,int index,string per){
    int i=0;
    if (i<0)
    {
        cout<<"negative index,cannot perform operation"<<endl;
        return;
    }
    editor*curr_number(*head);
    while (i!=index)
    {   
        i+=1;
        curr_number=curr_number->next;
    }
    if (curr_number==NULL)
    {
        cout<<"index is out of length, cannot perform operation"<<endl;
        return;
    }
    else if ((*head)==curr_number)
    {
        (*head)=curr_number->next;
        if (curr_number==(*last))
        {
            (*last)=(*head);
        }
        (*cursor)=(*cursor)->previous;        //moving cursor one step backward

        if(per=="yes"){
            l1.push_back("Deletei");
            l2.push_back(index);                   // holding index for Undo
            l2.push_back(curr_number->data);       // holding number for Undo
        }

        delete(curr_number);
    }
    
    else if ((*last)==curr_number)
    {
        (*last)=(*last)->previous;
        (*last)->next=NULL;
        if ((*cursor)==curr_number)
        {
            (*cursor)=(*last);
        }
        if(per=="yes"){
            l1.push_back("Deletei");
            l2.push_back(index);                   // holding index for Undo
            l2.push_back(curr_number->data);       // holding number for Undo
        }
        delete(curr_number);
    }
    
    else{
        editor*prev=curr_number->previous;
        prev->next=curr_number->next;
        curr_number->next->previous=prev;
        
        editor*cr=curr_number;
        //this process is for moving cursor backward
        while (cr!=(*cursor))           // if the node deleted before cursor or at cursor,then we have to move cursor one step forwardward 
        {
            if (cr==NULL)
            {
                break;
            } 
            cr=cr->next;
        }
        if (cr==(*cursor))
        {
            
            (*cursor)=(*cursor)->next;
        }
        if(per=="yes"){
            l1.push_back("Deletei");
            l2.push_back(index);                   // holding index for Undo
            l2.push_back(curr_number->data);       // holding number for Undo
        }

        delete(curr_number);
    }
}

void MoveForward(editor**head,editor**last,editor**cursor,int steps,string per){
    int i=0;
    if (steps<0)
    {
        cout<<"negative steps,cannot perform operation"<<endl;
        return;
    }
    editor*curr_number=(*cursor);
    while (i!=steps)
    { 
        if(curr_number==NULL){
            break;
        }  
        i+=1;
        curr_number=curr_number->next;
    }
    
    if (curr_number==NULL)
    {
        cout<<"steps out of length, cannot perform operation"<<endl;
        return;
    }
    if (i==steps)
    {
        (*cursor)=curr_number;
        cout<<"cursor moved forward "<<steps<<" steps(s)"<<endl;
        if(per=="yes"){
        l1.push_back("MoveForward");
        l2.push_back(steps);
        l3.push_back(-1000000000);
        }
    }
    
}

void MoveBackward(editor**head,editor**last,editor**cursor,int steps,string per){
    int i=0;
    if (steps<0)
    {
        cout<<"negative steps,cannot perform operation"<<endl;
        return;
    }
    editor*curr_number=(*cursor);
    while (i!=steps)
    { 
        if(curr_number==NULL){
            break;
        }  
        i+=1;
        curr_number=curr_number->previous;
        
    }
    
    if (curr_number==NULL)
    {
        cout<<"steps out of length, cannot perform operation"<<endl;
        return;
    }
    if(i==steps){
        (*cursor)=curr_number;
        cout<<"cursor moved backward "<<steps<<" steps(s)"<<endl;
        if(per=="yes"){
            l1.push_back("MoveBackward");
            l2.push_back(steps);
            l3.push_back(-1000000000);
        }
        
    }
}

void AddImmediate(editor**head,editor**cursor,editor**last,int num,string per){
    editor*new_number=new editor();
    new_number->data=num;
    new_number->next=NULL;
    new_number->previous=NULL;
    if ((*head)==NULL)
    {
        cout<<"cursor is not defined"<<endl;
        return;
    }
    else if ((*head)==(*last))
    {
        (*cursor)->next=new_number;
        new_number->previous=(*cursor);
        (*last)=new_number;
    }
    
    else if ((*cursor)==(*last))
    {
        (*cursor)->next=new_number;
        new_number->previous=(*cursor);
        (*last)=new_number;
    }
    else{
        
        editor*nx=(*cursor)->next;
        (*cursor)->next=new_number;
        new_number->previous=(*cursor);
        new_number->next=nx;
        nx->previous=new_number;

    }
    int i=0;
    editor*curr_num=(*head);
    while(curr_num!=(*cursor)){
        curr_num=curr_num->next;
        i+=1;
    }
    i+=1;
    if(per=="yes"){
        l1.push_back("AddImmediate");
        l2.push_back(i);
        l3.push_back(-1000000000);
    }
}

void DeleteImmediate(editor**head,editor**cursor,editor**last,string per){
    if ((*head)==NULL)
    {
        cout<<"list is empty, cannot perform operation"<<endl;
        return;
    }
    int cr=(*cursor)->data;
    if((*head)==(*last)){
        editor*curr_number=(*cursor);
        (*head)=NULL;
        (*last)=NULL;
        (*cursor)=NULL;
        delete(curr_number);
    }
    else if ((*cursor)==(*head))
    {
        editor*curr_number=(*head);
        (*head)=curr_number->next;
        (*cursor)=(*head);
        (*cursor)->previous=NULL;
        delete(curr_number);
    }
    
    else if((*cursor)==(*last)){
        editor*curr_number=(*last);
        (*cursor)=(*cursor)->previous;
        (*last)=(*last)->previous;
        (*last)->next=NULL;
        delete(curr_number);
    }
    else{
        
        editor*curr_number=(*cursor);
        editor*prev=curr_number->previous;
        prev->next=curr_number->next;
        curr_number->next->previous=prev;
        (*cursor)=curr_number->next;
        delete(curr_number);
    }
    int i=0;
    editor*curr_num=(*head);
    while (curr_num!=(*cursor))
    {
        i+=1;
        curr_num=curr_num->next;
    }
    if(per=="yes"){
        l1.push_back("DeleteImmediate");
        l2.push_back(i);
        l3.push_back(cr);
    }
}

void print(editor**cursor){
    if ((*cursor)==NULL)
    {
        cout<<"list is empty, cannot perform operation"<<endl;
        return;
    }
    cout<<(*cursor)->data<<endl;
}

void UpdateIndexNumber(editor**head,int index,int num,string per){
    if ((*head)==NULL)
    {
        cout<<"list is empty, cannot perform operation"<<endl;
        return;
    }
    if (index<0)
    {
        cout<<"negative index, cannot perform operation"<<endl;
        return;
    }
    
    int i=0;
    editor*curr_number=(*head);
    while (i!=index)
    {
        if (curr_number==NULL)
        {
            break;
        }
        curr_number=curr_number->next;
        i+=1;
    }
    if (curr_number==NULL)
    {
        cout<<"index out of length, cannot perform operation"<<endl;
        return;
    }
    else{
        if(per=="yes"){
            l1.push_back("Updatei");
            l2.push_back(index);
            l3.push_back(curr_number->data);
        }
        curr_number->data=num;
    }
}

void UpdateImmediate(editor**cursor,int num,string per){
    if ((*cursor)==NULL)
    {
        cout<<"list is empty, cannot perform operation"<<endl;
        return;
    }
    if(per=="yes"){
        l1.push_back("UpdateImmediate");
        l2.push_back((*cursor)->data);
        l3.push_back(-1000000000);
    }
    (*cursor)->data=num;
}

void ShiftIndex(editor**head,editor**cursor,int index,string per){
    if ((*head)==NULL)
    {
        cout<<"list is empty, cannot perform operation"<<endl;
        return;
    }
    if (index<0)
    {
        cout<<"negative index, cannot perform operation"<<endl;
        return;
    }
    
    int i=0;
    editor*curr_number=(*head);
    while (i!=index)
    {
        if (curr_number==NULL)
        {
            break;
        }
        curr_number=curr_number->next;
        i+=1;
    }
    if (curr_number==NULL)
    {
        cout<<"index out of length, cannot perform operation"<<endl;
        return;
    }
    else{
        if(per=="yes"){
            l1.push_back("ShiftIndex");
            l2.push_back(index);
            l3.push_back(-1000000000);
        }
        swap((*cursor)->data,curr_number->data);
    }
}

int main(){

    editor*head=NULL;
    editor*last=NULL;
    editor*cursor=NULL;
    int cr;

//==========================================================================\\.

    string file_name;
    cout<<"enter file name: ";cin>>file_name;                // taking file name from user

    ifstream file(file_name);
    string command;

    while (getline(file,command))
    {
        string word;
        istringstream ss(command);
        int num1=-1000000000,num2=-1000000000;
        if(ss>>word>>num1){
            if(ss>>num2){
                ss>>word>>num1>>num2;
                
            }
        
            else
            {
                ss>>word>>num1;
                
            }
        }

        else{
            ss>>word;
            
        }
    
        if (word=="Add"&&num1!=-1000000000&&num2==-1000000000)     // if we are adding at the last on list then its undo is to delete last value 
        {
            ADD(&head,&last,&cursor,num1,"yes");
            if(l1.size()>5){
                l1.pop_front();
                l2.pop_front();
                l3.pop_front();
            }
            printAll(head);
        }
        else if(word=="Delete"&&num1==-1000000000&&num2==-1000000000){    // if we are deleting last number then its undo is to add that number at last so we have to hold the value in Undo stack
            DELETE(&head,&last,&cursor,"yes");
            if(l1.size()>5){
                l1.pop_front();
                l2.pop_front();
                l3.pop_front();
            }
            printAll(head);
        }
        else if (word =="Add" && num1 !=-1000000000 && num2!=-1000000000)     // if we are adding number at any index then its undo is to delete that number from that index,so we have to hold index of number in Undo stack
        {
            AddIndex(&head,&last,&cursor,num1,num2,"yes");
            if(l1.size()>5){
                l1.pop_front();
                l2.pop_front();
                l3.pop_front();
            }
            printAll(head);
        }
        else if(word=="Delete" && num1 !=-1000000000 && num2==-1000000000){  // if we are deleting number from any index then its undo is to add that number at same index,so i have to hold index and number in Undo stack
            DeleteIndex(&head,&last,&cursor,num1,"yes");
            if(l1.size()>5){
                l1.pop_front();
                l2.pop_front();
                l3.pop_front();
            }
            printAll(head);
        }
        else if(word=="MoveForward" && num1!=-1000000000 && num2==-1000000000){   // if we are moving cursor forward then it usdo is to move backward equal step, so we hold steps  
            MoveForward(&head,&last,&cursor,num1,"yes");
            if(l1.size()>5){
                l1.pop_front();
                l2.pop_front();
                l3.pop_front();
            }
            
        }
        else if(word=="MoveBackward" && num1!=-1000000000 && num2==-1000000000){    // if we are moving cursor backward then it usdo is to move forward equal step, so we hold steps
            MoveBackward(&head,&last,&cursor,num1,"yes");
            if(l1.size()>5){
                l1.pop_front();
                l2.pop_front();
                l3.pop_front();
            }
            
        }
        else if(word=="AddImmediate" && num1!=-1000000000 && num2==-1000000000){    // if we are adding number after cursor then its undo is to delete that number, so we apply delete index function and hold index
            AddImmediate(&head,&cursor,&last,num1,"yes");
            if(l1.size()>5){
                l1.pop_front();
                l2.pop_front();
                l3.pop_front();
            }
            printAll(head);
        }
        else if(word=="DeleteImmediate" && num1==-1000000000 && num2==-1000000000){     // if we are deleting cursor then its undo is to add number at cursor's position, so we hold cursor index
            DeleteImmediate(&head,&cursor,&last,"yes");
            if(l1.size()>5){
                l1.pop_front();
                l2.pop_front();
                l3.pop_front();
            }
            printAll(head);
        }
        else if(word=="Print"){
            print(&cursor);
            if(l1.size()>5){
                l1.pop_front();
                l2.pop_front();
                l3.pop_front();
            }
            
        }
        else if(word=="Update" && num1!=-1000000000 && num2!=-1000000000){       // if we are updating number at specific index hen its undo is to update again with previous value os same index, so we have hold previous number and index
            UpdateIndexNumber(&head,num1,num2,"yes");
            if(l1.size()>5){
                l1.pop_front();
                l2.pop_front();
                l3.pop_front();
            }
            printAll(head);
        }
        else if(word=="UpdateImmediate" && num1!=-1000000000 && num2==-1000000000){     // if we are updating cursor's number then its undo is to update again cursor's number with previous number, so we have to hold index
            UpdateImmediate(&cursor,num1,"yes");
            if(l1.size()>5){
                l1.pop_front();
                l2.pop_front();
                l3.pop_front();
            }
            printAll(head);
        }
        else if(word=="Shift" && num1!=-1000000000 && num2==-1000000000){      // if we are sifting curor's value with the index value then its undo is to reshift , so we hold index and cursor's number 
            ShiftIndex(&head,&cursor,num1,"yes");
            if(l1.size()>5){
                l1.pop_front();
                l2.pop_front();
                l3.pop_front();
            }
            printAll(head);
        }
        
        //======================== undo process ===========================
        else if(word=="Undo" && num1==-1000000000 && num2==-1000000000){
            
            if (l1.size()==0)
            {
                cout<<"Undo stack is empty"<<endl;
            }
            else{
                list<string>::iterator it1=l1.end();
                list<int>::iterator it2=l2.end();
                list<int>::iterator it3=l3.end();
                *it1--;
                *it2--;
                *it3--;
                /*
                for (it1=it1; it1!=l1.begin() ; it1--)
                {
                    cout<<*it1<<endl;
                }
                cout<<*it1<<endl;
                */
                if (*it1=="Add")
                {
                    DELETE(&head,&last,&cursor,"no");
                    printAll(head);
                }
                else if(*it1=="Delete"){
                    ADD(&head,&last,&cursor,*it2,"no");
                    printAll(head);
                }
                else if(*it1=="Addi"){
                    DeleteIndex(&head,&last,&cursor,*it2,"no");
                    printAll(head);
                }
                else if(*it1=="Deletei"){
                    AddIndex(&head,&last,&cursor,*it2,*it3,"no");
                    printAll(head);
                }
                else if(*it1=="MoveForward"){
                    MoveBackward(&head,&last,&cursor,*it2,"no");
                }
                else if(*it1=="MoveBackward"){
                    MoveForward(&head,&last,&cursor,*it2,"no");
                }
                else if(*it1=="AddImmediate"){
                    DeleteIndex(&head,&last,&cursor,*it2,"no");
                    printAll(head);
                }
                else if(*it1=="DeleteImmediate"){
                    AddIndex(&head,&last,&cursor,*it2,*it3,"no");
                    printAll(head);
                }
                else if(*it1=="Updatei"){
                    UpdateIndexNumber(&head,*it2,*it3,"no");
                    printAll(head);
                }
                else if(*it1=="UpdateImmediate"){
                    UpdateImmediate(&cursor,*it2,"no");
                    printAll(head);
                }
                else if(*it1=="ShiftIndex"){
                    ShiftIndex(&head,&cursor,*it2,"no");
                    printAll(head);
                }
                
                l1.pop_back();
                l2.pop_back();
                l3.pop_back();
            }
        }
        else{
            cout<<word<<" is not define as a right command"<<endl;
        }
    } 

//===========================================================================\\.
    
}