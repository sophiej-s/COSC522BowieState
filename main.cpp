//  Project in COSC 522. Bowie State University
//
//  This program accepts as the user input case sensitive alphabetic letters, A-Z and a-z, to populate sets A and B.
//  Inputs can be the Universal set, denoted by (U) (A-Z and a-z), or the empty set, denoted by (E).
//  The program performs the following calculations: cardinality, difference and a determination if the sets are disjoined.
//  The user is notified of errors, results, selections; menus are used throughout the process.
//  The input is parsed to ensure only alphabetic characters, (U) or (E), and appropriate menu selections is accepted.

#include <string>
#include <iostream>
using namespace std;


struct NodeType //node in a linked list
    {   char data;
        NodeType *next;
    };


NodeType* addNode2ENDLinkList(NodeType *head, int key) //add a node at the end of the linked list
    {   NodeType *newnode, *p=NULL;
        
        newnode = new NodeType;
        
        if (head==NULL) //adding a node if it is the first node
        {
            head=newnode;
            newnode->next=NULL;
            newnode->data=key;
            p= head;
        }
        
        else if (head !=NULL) //adding a node after the 1st node
        {   p=head;
            while (p->next!=NULL) {p=p->next;}  //traverse to the end
            newnode->next=NULL;//
            p->next=newnode;//
            newnode->data=key; //
            p=head;
        }
        return p;
    }


int sizeSet(NodeType *head) //find the size of the list

{   int sizeList=0;
    NodeType *p;

    if (head==NULL) {return 0;} //list is empty, return 0
    else if (head->next==NULL) {return 1;} //size=1
    
    p=head;
    sizeList=1; //starting with the first node; size=1
    while (p->next!=NULL)
    {
        sizeList++; //traverse the list, incr. the size
        p=p->next;
    }

    return sizeList;
}

NodeType* makeSetUniqueValues(NodeType* head)//eliminate duplicates in the list; in a set duplicates are ignored
{
    if (head==NULL) return NULL;
    int sizeS=sizeSet(head);
    char temp[sizeS]; //there are up to "sizeS" unique/non-repeating elements in the set
    int arraySize=0;
    int flag=0; // flag=0, letter is not a diplicate
    
    NodeType *p=head;
    while (p->next!=NULL)
    {
        for (int j=0; j<arraySize;j++)
            { if (p->data==temp[j]) flag=1; } //flag=1, letter is a diplicate
       
        if (flag==0)
            {temp[arraySize]=p->data; arraySize++;} //if not a diplicate, insert it into temp
        flag=0; p=p->next;
    }
    
    //last note in the list
    for (int j=0; j<arraySize;j++)
        { if (p->data==temp[j]) flag=1; }
   
    if (flag==0)
        {temp[arraySize]=p->data; arraySize++;}
    
    p=NULL;
    for (int j=0; j<arraySize;j++) // build a set based on temp which contains non-duplicative elements
    {
        p=addNode2ENDLinkList(p, temp[j]);
    }
        
    
    return p;
}



int cardinality(NodeType *head) //counts the number of elements in the a list (input list has no duplicates)
{
    NodeType*p=head;
    return sizeSet(p);
}


void printSet(NodeType* head)//print the list
    {
        NodeType  *p;
        p=head;
        int index=0;

        if (p==NULL) cout << "Empty set!" << '\n';
        else{ cout<<"{"; //use the braces for printing the elements in the set
            while (p->next!=NULL)
                  {
                      cout <<p->data<< ",";//use comma to separate the elements in the set
                      p=p->next; index++;
                  }
            cout <<p->data<<"}\n";//use the braces for printing the elements in the set
        }
    }




int menu() //Main Menu
    {
        int menuKey;
        cout <<'\n'<<"----------------------------------------------------------------------";
        cout <<'\n'<<"----------------------------------------------------------------------"<<'\n';
        cout << "MAIN MENU:"
        << '\n' << "-1:  Exit"
        << '\n' << " 1:  Input elements into sets A and B (default: A and B are empty sets)"
        << '\n' << " 2:  Compute the difference between the sets"
        << '\n' << " 3:  Compute the cardinality"
        << '\n' << " 4:  Compute if the sets are disjoint"
        <<'\n'<<"----------------------------------------------------------------------"<<'\n'
        << "Enter your selection and press ENTER here:   ";
        cout<<'\n';
        cin>> menuKey;
        
        while(cin.fail()) //if the user input is bad, ask for it again
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"\nPlease enter a valid selection from the Main Menu:   ";
            cin>>menuKey;
        }
        return menuKey;
    }





NodeType* makeUniversalSet(NodeType* head)// create a Universal set
{
    NodeType  *p=head;
    char alphabet[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
                    'r','s','t','u','v','w','x','y','z',
                    'A', 'B', 'C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q',
                    'R','S','T','U','V', 'W','X','Y','Z'};
    for (int i=0; i<26*2; i++) //make a list containing characters A-Z and a-z
    {
        p=addNode2ENDLinkList( p, alphabet[i]);
    }
    return p;
}



NodeType* getUserInput(NodeType* head) //get and parse user input
{   NodeType  *p=NULL;
    char key=' ';
    string inputString= " ";
    cin.ignore();
    cout <<'\n'<<"----------------------------------------------------------------------------------------------";
    cout << '\n' <<"Input alphabetic characters (A-Z and a-z) as one line and then press ENTER";
    cout << '\n' <<"Type (U) for the Universal set {𝑎,𝑏,𝑐,...,𝑧,𝐴,𝐵,𝐶,...𝑍}";
    cout << '\n' <<"Type (E) for the Empty set {}";
    cout << '\n' <<"For example:  (E) followed by ENTER produces the Emtpy set={} ";
    cout << '\n' <<"For example:  (U) followed by ENTER produces the Universal set={a,b,c...z,A,B,C..Z}";
    cout << '\n' <<"              ab c ;,&&E followed by ENTER produces {a,b,c,E} ";
    cout << '\n' <<"              abc D (U) followed by ENTER produces (U)";
    cout << '\n' <<"              abc D (E) followed by ENTER produces (E)";
    cout << '\n' <<"              (E) followed by (U) followed by ENTER produces (E)";
    cout << '\n' <<"              (U) followed by (E) followed by ENTER produces (U)";
    cout << '\n' <<"              $%@ 3, -45 D followed by ENTER produces {D}";
    cout << '\n' <<"              123456789 followed by ENTER produces the empty set {0}";
    cout<< '\n' << "Input is case sensitive (i.e., c and C are distinc). Duplicates will be removed from the set.";
    cout <<'\n'<<"----------------------------------------------------------------------------------------------";
    cout << '\n' <<"Input your set and press ENTER here:  ";

    cin.clear();
    getline(cin,inputString);
    p=NULL;
    
    for (int i=0; i<inputString.length(); i++) //parse user input
    {
        key=inputString[i];
    
       if(key=='(' && inputString.length()>=i+2 && inputString[i+1]=='U' &&inputString[i+2]==')')
       {   i=i+2;
           p=NULL; p=makeUniversalSet(p); return p; //if (U) is found, create the Universal set
       }
        
       else if(key=='(' && inputString.length()>=i+2 && inputString[i+1]=='E' &&inputString[i+2]==')')
       { i=i+2; p=NULL; return p;} //if (E) is found, create the Empty set
        
       else if  (isalpha (key))//if a letter found, insert into the list
        { p= addNode2ENDLinkList(p,  key); }
    }
    return p;
}



NodeType*  difference(NodeType* firstHead, NodeType* secondHead) //compute a set difference (first set -second set)
{
    int match=0;
    NodeType  * pA=firstHead, *pB=secondHead, *result=NULL;

    if (firstHead==NULL) return firstHead; //Empty Set - X  = X
    if (secondHead==NULL) return firstHead;//X-Empty Set=X
    // Method: traverse A and compare each character to all in set B. If it is a match (match=1), skip to the next char of A.
    // If B is fully traversed and there is no match (match=0), add the character from A into the result.
    
    while (pA->next!=NULL)
    {   match=0;
        
        pB=secondHead; //reset the pointer to point to the head of the second list
        while (pB->next!=NULL)
        {  if (pA->data==pB->data){match=1; }
            pB=pB->next;
        }
        if (pA->data==pB->data){match=1; } //last node of B

        if (match==0) //B is fully traversed, if the character in A is not in B, add it to result
        {result=addNode2ENDLinkList(result, pA->data); }

        pA=pA->next;//go to the next node in A
    }
    
    match=0;
    pB=secondHead; //reset the pointer to point to the head of the second list
    while (pB->next!=NULL)   //take care of the last node in A
        {  if (pA->data==pB->data){match=1; }
            pB=pB->next;
        }
        if (pA->data==pB->data){match=1; } //last node of B

    if (match==0) // if the char in A is not in B, add it to result
    {result=addNode2ENDLinkList(result, pA->data); }
    
    return result;
}




NodeType*  disjoint(NodeType* firstHead, NodeType* secondHead) //determine if the two sets are disjoined (result=NULL)
{
    int match=0;
    NodeType  * pA=firstHead, *pB=secondHead, *result=NULL;

    if (firstHead==NULL || secondHead==NULL) {cout<<"\n\nThe set A and B (and equivalently B and A) are disjoined!" ; return NULL;} // {} intersection with X set = {}
    while (pA->next!=NULL)
    {   match=0;
        
        pB=secondHead; //reset the pointer to point to the head of the second list
        while (pB->next!=NULL)
        {  if (pA->data==pB->data){match=1; result=addNode2ENDLinkList(result, pA->data); }
            pB=pB->next;
        }
        if (pA->data==pB->data){match=1; result=addNode2ENDLinkList(result, pA->data); } //last node of B
        pA=pA->next;// go to the next node in list A
        
    }
    
    match=0;
    pB=secondHead; //reset the pointer to point to the head of the second list; last node in A
    while (pB->next!=NULL)
        {  if (pA->data==pB->data){match=1; result=addNode2ENDLinkList(result, pA->data); }
            pB=pB->next;
        }
    if (pA->data==pB->data){match=1; result=addNode2ENDLinkList(result, pA->data); } //last node of B
    //if result==NULL,then the sets are disjoined; otherwise, they intersect in elements contained in result
    
    
    //Print the result and return the set containing the intersection
    if (result==NULL){cout<<"\n\nThe set A and B (and equivalently B and A) are disjoined!" ; }
    else {cout<<"\n\nThe sets are NOT disjoined!" ; }
    
    
    return result;
}



int main(void)
    {
        NodeType  *head_B=NULL, *head_A=NULL;
        int menuKey=20; //initialize to anything except for -1
        
        while (menuKey!=-1) //quit when the user inputs -1
        {   menuKey=menu();
            
            switch (menuKey)
            {
                case 1: //" 1:  Input elements into sets A and B
                { int done=2;
                    
                cout <<'\n'<< "You Selected to input elements into the sets!"<<'\n';
                while (done!=-1)
                {
                    cout<<'\n'<<"----------------------------------------------------------------------"<<'\n';
                    cout << "SUB-MENU:"
                    << '\n' << "-1: Exit / Leave the sub-menu"
                    << '\n' << " 1: Enter input for set A"
                    << '\n' << " 2: Enter input for set B"<<'\n';
                    cout   << '\n' << "Input your sub-menu selection and press ENTER here:  ";
                    cin>>done;
                    
                    if(cin.fail()) //if the user is bad, ask for it again
                    {
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        cout<<"\nInvalid entry!  Please enter a valid selection from the sub-menu here:   ";
                        cin>>done;
                    }
                    
                    
                    switch(done)
                    {
                        case 1:
                        {   cout<<"Getting your input for Set A!";
                            head_A=NULL; //re-initialize in case the user wants to re-enter the sets
                            head_A=getUserInput(head_A);
                            head_A=makeSetUniqueValues(head_A); //eliminate duplicates in the set
                            cout<<"\nSet A (diplicates are removed if applicable) is:  ";
                            printSet(head_A); //print the user's set
                            break;
                        } //close case 1
                
                        case 2:
                        {   cout<<"Getting your input for Set B!";
                            head_B=NULL; //re-initialize in case the user wants to re-enter the sets
                            head_B=getUserInput(head_B);
                            head_B=makeSetUniqueValues(head_B);//eliminate duplicates
                            cout<<"\nSet B (diplicates are removed if applicable) is:  ";
                            printSet(head_B); //print the user's set
                            break;
                        } //close case 2
                            
                        case -1: {cout<<"Returning to the main menu. "<<'\n'; break;}
                        default:  {cout<< "Not in the sub-menu. Try again.";break;}
                    }// close the switch on done
                    
                 } //close the switch on the sub menu selection
                    
                    //print the sets before returning to the main menu
                    cout<<"Your set A: "; printSet(head_A); cout<<'\n';
                    cout<<"Your set B: "; printSet(head_B); cout<<'\n';
                    break;
                } //close the switch on option 1 in the main menu
                    
                    
                case 2: //Compute the difference on the sets
                {
                    NodeType  *result=NULL; //result point to the list containing the difference
                    int done=2; //initialize it to anything except for -1
                    cout <<'\n'<< "You Selected to compute the difference between the sets!"<<'\n';
                    while (done!=-1)
                    {
                        cout<<'\n'<<"----------------------------------------------------------------------"<<'\n';
                        cout << "SUB-MENU:"
                        << '\n' << "-1: Leave the sub-menu"
                        << '\n' << " 1: Compute A-B"
                        << '\n' << " 2: Compute B-A"
                        << '\n' << "Input your menu selection and press ENTER here:  ";
                        cin>>done;
                        
                        if(cin.fail()) //if the input is bad, ask for it again
                        {
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cout<<"\nInvalid entry!  Please enter a valid selection from the sub-menu here:   ";
                            cin>>done;
                        }
                        
                        
                        switch(done)
                        {
                            case 1: //Compute A-B
                            {   result=NULL;
                                result= difference(head_A, head_B);
                
                                cout<<"\nResult for A-B=\n";
                                printSet(head_A); cout<<" - "; printSet(head_B); cout<<"= "; printSet(result);
                                break;
                            }
                    
                            case 2:// 2: Compute B-A
                            {   result=NULL;
                                result= difference(head_B, head_A);
                
                                cout<<"\nResult for B-A=\n";
                                printSet(head_B); cout<<" - "; printSet(head_A); cout<<"= "; printSet(result);
                                break;
                            }
                                
                            case -1: {cout<<"Returning to the main menu"<<'\n'; break;}
                            default:  {cout<< "Not in the sub-menu. Try again.";break;}
                        }// close the switch on done
                     } //close the switch on the sub menu selection
                        break;
                } //Close the selection 2 from the main menu
                    
                case 3://Compute the cardinality
                {
                    int done=2;//initialize it to anything except for -1
                    cout <<'\n'<< "You Selected to compute the cardinality!"<<'\n';
                    while (done!=-1)
                    {
                        cout<<'\n'<<"----------------------------------------------------------------------"<<'\n';
                        cout << "SUB-MENU:"
                        << '\n' << "-1: Leave the sub-menu"
                        << '\n' << " 1: Compute |A|"
                        << '\n' << " 2: Compute |B|"
                        << '\n' << " 3: Compute |A-B|"
                        << '\n' << " 4: Compute |B-A|"
                        << '\n' << " 5: Compute |B intersection A|=|A intersection B|"
                        << '\n' << "Input your menu selection and press ENTER here:  ";
                        cin>>done;
                        
                        if(cin.fail()) //if the input is bad, ask for it again
                        {
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            cout<<"\nInvalid entry!  Please enter a valid selection from the sub-menu here:   ";
                            cin>>done;
                        }
                        
                        int setSize;
                        switch(done)
                        {
                            case 1: //1: Compute the cardinality of A
                            {
                                setSize= cardinality(head_A);
                                cout<<"\nCardinality of set A="; printSet(head_A); cout<<" is "<<setSize;
                                break;
                            }
                    
                            case 2:// 2: Compute the cardinality of B
                            {
                                setSize= cardinality(head_B);
                                cout<<"\nCardinality of set B="; printSet(head_B); cout<<" is "<<setSize;
                                break;
                            }
                                
                            case 3://Compute the carinality of the difference, A-B
                            {
                                
                                setSize= cardinality(difference(head_A, head_B));
                                cout<<"\nCardinality of A-B="; printSet(difference(head_A, head_B));
                                cout<<" is "<<setSize;
                                break;}
                                
                            case 4://Compute the carinality of the difference, B-A
                            {
                                setSize= cardinality(difference(head_B, head_A));
                                cout<<"\nCardinality of B-A="; printSet(difference(head_B, head_A));
                                cout<<" is "<<setSize;
                                break;}
                                
                            case 5://Compute the card. of B intersection A=A intersection B
                            {
                                setSize= cardinality(disjoint(head_B, head_A));
                                cout<<"\nCardinality of set B intersection A=A intersection B="; printSet(disjoint(head_B, head_A));
                                cout<<" is "<<setSize;
                                break;}
                                
                            case -1: {cout<<"Returning to the main menu"<<'\n'; break;}
                            default:  {cout<< "Not in the sub-menu. Try again.";break;}
                        }// close the switch on done

                     } //close the switch on the sub menu selection
    
                        break;
                }//Close the selection 3 from the main menu
            
        
                    
                case 4://Compute if the sets are disjoint
                {
                    NodeType*  resultD= disjoint(head_A, head_B);
                    cout<<"\nResult for the intersection of A and B=\n";
                    printSet(head_A);
                    cout<<"intersectis with ";
                    printSet(head_B);
                    cout<<"= ";
                    printSet(resultD);
    
              
                    
                    break;}
                    
                    
            case -1: {cout<<"BYE!"<<'\n'; break;} //exit from the main menu and exit the program
                            
            default://handle the case when user input is not in the main menu
                {cout<< "Not in the menu. Try again.";break;}
                    
            } //close the switch statement
            
        }// close the   while (MenuKey!=-1)

    
        return 0;
    }
