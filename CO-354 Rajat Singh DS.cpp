/******************************************************************************
                             PHONEBOOK
                    
                    
                            NAME1 : REUBEN           NAME2 : RAJAT
                            ROLL NO : 2K20/CO/358    ROLL NO : 2K20/CO/354
                            BATCH : A5               BATCH : A5
THIS DEMONSTRATES THE PHONEBOOK OF MOBILE PHONES WITH DOUBLY LINKED LISTS SO THAT TRAVERSING CAN BE EASY.....
*******************************************************************************/
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class dnode
{
    public:
    char number[50];
    char gmail[40];
    char name[30];
    dnode *prev,*next;
    dnode(char n[],char r[],char g[])
    {
        strcpy(name,n);
        strcpy(number,r);
        strcpy(gmail,g);
        next=NULL;
        prev=NULL;
    }
    // friend class dlist;
};

char* to_upper(char* str)
{
    int i = 0;
    while(str[i] != '\0')
    {
        if(str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] += 'A' - 'a';
        }
        i++;
    }
    return str;
}

string to_upper(string s)
{
    int i = 0;
    while(s[i] != '\0')
    {
        if(s[i] >= 'a' && s[i] <= 'z')
        {
            s[i] += 'A' - 'a';
        }
        i++;
    }
    return s;
}

dnode* split(dnode *head);

dnode *merge(dnode *first, dnode *second)
{
    // If first linked list is empty
    if (!first)
        return second;
 
    // If second linked list is empty
    if (!second)
        return first;
 
    // Pick the smaller value
    if (strcmp(first->name, second->name) < 0)
    {
        first->next = merge(first->next,second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        second->next = merge(first,second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

dnode *split(dnode *head)
{
    dnode *fast = head,*slow = head;
    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    dnode *temp = slow->next;
    slow->next = NULL;
    return temp;
}

dnode* mergeSort(dnode *head)
{
    if (!head || !head->next)
        return head;
    dnode *second = split(head);
 
    // Recur for left and right halves
    head = mergeSort(head);
    second = mergeSort(second);
 
    // Merge the two sorted halves
    return merge(head,second);
}

class dlist
{
    dnode *head,*temp,*ptr;
    
    dnode *ptr1, *ptr2, *dup;
    public:
    dnode *prevn;
        
    void insert();
    void sort();
    void deletecontact(char n[20]);
    void deletesamename();
    void searchbyname(char p[20]);
    void searchbynumber(char no[30]);
    void searchbygmail(char g[20]);

        // dnode *head,*temp,*ptr;
        // friend class apply;
    void accept();
    void display();
    void update(char ch[10]);
    dlist()
    {
        head=NULL;
        temp=NULL;
        ptr=NULL;
        ptr1=NULL;
        ptr2=NULL;
        dup=NULL;
    }
};
// class apply()
// {
    
// }
void dlist::accept()
{
    char number[50];
    char gmail[40];
    char name[30];
    char ans;
    do
    {
        cout<<"ENTER NAME      :";
        cin>>name;
        char* finalname = to_upper(name);
        // cin.getline (name,30);
        cout<<"ENTER NUMBER    :";
        cin>>number;
        while(strlen(number)!=10)
        {
            cout<<"ENTER VALID NUMBER  :";
            cin>>number;
        }
        cout<<"ENTER G-MAIL    :";
        cin>>gmail;
        temp=new dnode(finalname,number,gmail);
        if(head==NULL)
        {
            head=temp;
        }
        else
        {
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
        cout<<"\nDO YOU WANT TO CONTINUE?????????";
        cin>>ans;
    } while(ans=='y');

}
void dlist::display()
{
    ptr=head;//start the node
    while(ptr!=NULL)//traverse till last
    {
        cout<<"\n\nNAME  ::\t"<<ptr->name;
        cout<<"\nNUMBER  ::\t+91-"<<ptr->number;
        cout<<"\nG-MAIL  ::\t"<<ptr->gmail;
        ptr=ptr->next;
    }
}

    void dlist::insert()
    {
        accept();
    }
    void dlist::sort()
    {
        head = mergeSort(head);
    }
    void dlist::deletecontact(char s[20])
    {
        vector<dnode*> v;
        char* finalname = to_upper(s);
        ptr=head;
        while(ptr!=NULL)
        {
            if(strcmp(finalname,ptr->name)==0)
            {
                v.push_back(ptr);  
            }
            ptr=ptr->next;
        }
        if(v.size() == 0)
        {
            cout << "\nYOUR ENTERED NAME IS NOT IN THE LIST...\n";
        }
        else if(v.size() == 1)
        {
            if(v[0]==head && v[0]->next!=NULL)
            {
                head=head->next;
                head->prev=NULL;
                delete(v[0]);
                cout<<"YOUR CONTACT IS SUCCESSFULLY DELETED\n\n";
            }
            else if(v[0]!=head && v[0]->next!=NULL)
            {
                v[0]->prev->next=v[0]->next;
                v[0]->next->prev=v[0]->prev;
                delete(v[0]);
                cout<<"YOUR CONTACT IS SUCCESSFULLY DELETED\n\n";
            }
            else if(v[0]==head && v[0]->next == NULL)
            {
                delete(v[0]); 
                head = NULL; 
                cout<<"YOUR CONTACT IS SUCCESSFULLY DELETED\n\n";
                cout << "PHONEBOOK IS EMPTY\nENTER ATLEAST ONE CONTACT\n\n";
                accept();
                
            }
            else if(v[0]->next==NULL)
            {
                v[0]->prev->next=NULL;
                delete(v[0]);
                cout<<"YOUR CONTACT IS SUCCESSFULLY DELETED\n\n";
            }
        }
        else
        {
            for(int j = 0; j < v.size(); j++)
            {
                cout << j + 1 << ".\t";
                cout<<"CONTACT DETAILS ARE BELOW:\n"<<endl;
                cout<<"\n\nNAME  ::\t"<<v[j]->name;
                cout<<"\nNUMBER::\t+91-"<<v[j]->number;
                cout<<"\nG-MAIL::\t"<<v[j]->gmail << endl << endl;
            }
            cout << "WHICH ONE DO YOU WANT TO DELETE??????";
            int k;
            cin >> k;
            while(k < 1 || k > v.size())
            {
                cout << "GIVE A VALID CHOICE!!!!!!";
                cin >> k;
            }
            k--;
            if(v[k]!=head && v[k]->next!=NULL)
            {
                v[k]->prev->next=v[k]->next;
                v[k]->next->prev=v[k]->prev;
                delete(v[k]);
                cout<<"YOUR CONTACT IS SUCCESSFULLY DELETED\n\n";
            }
            if(v[k]==head && v[k]->next == NULL)
            {
                char* todelete = head ->name;
                cout<<"YOUR CONTACT IS SUCCESSFULLY DELETED\n\n";
                cout << "PHONEBOOK IS EMPTY\nENTER ATLEAST ONE CONTACT\n\n";
                accept();
                deletecontact(todelete);
            }
            else if(v[k]->next==NULL)
            {
                v[k]->prev->next=NULL;
                delete(v[k]);
                cout<<"YOUR CONTACT IS SUCCESSFULLY DELETED\n\n";
            }
        }
    }
    void dlist::deletesamename()
    {
        ptr1=head;
        while (ptr1 != NULL && ptr1->next != NULL) 
        { 
            ptr2 = ptr1; 
            while (ptr2->next != NULL) 
            { 
                if (strcmp(ptr1->name,ptr2->next->name)==0)
                { 
                    dup = ptr2->next; 
                    ptr2->next = ptr2->next->next; 
                    cout << "CONTACT WITH NAME " <<dup ->name << " AND NUMBER " << dup ->number << "HAS BEEN DELETED!!!!!!!!!!!" << endl;
                    delete(dup); 
                } 
                else
                {
                    ptr2 = ptr2->next; 
                }
            }
            ptr1 = ptr1->next; 
        } 
    }
    
    void dlist::searchbyname(char na[10])
    {
        int flag = 1;
        ptr=head;
        char* finalname = to_upper(na);
        while(ptr!=NULL)
        {
            if(strcmp(finalname,ptr->name)==0)
            {
                flag = 0;
                cout<<"NAME FOUND"<<endl;
                cout<<"CONTACT DETAILS ARE BELOW:\n"<<endl;
                cout<<"\n\nNAME  ::\t"<<ptr->name;
                cout<<"\nNUMBER::\t+91-"<<ptr->number;
                cout<<"\nG-MAIL::\t"<<ptr->gmail;
            }
            ptr=ptr->next;
        }
        if(flag)
        {
            cout << "CONTACT NOT FOUND!!!!!!!!!!!" << endl;
        }
    }
    void dlist::searchbynumber(char num[20])
    {
        int flag = 1;
        ptr=head;
        while(ptr!=NULL)
        {
            if(strcmp(num,ptr->number)==0)
            {
                flag = 0;
                cout<<"NUMBER FOUND\n"<<endl;
                cout<<"CONTACT DETAILS ARE BELOW:\n"<<endl;
                cout<<"\n\nNAME  ::\t"<<ptr->name;
                cout<<"\nNUMBER::\t+91-"<<ptr->number;
                cout<<"\nG-MAIL::\t"<<ptr->gmail;
            }
            ptr=ptr->next;
        } 
        if(flag)
        {
            cout << "CONTACT NOT FOUND!!!!!!!!!!!" << endl;
        }
    }
    void dlist::searchbygmail(char gm[20])
    {
        int flag = 1;
        ptr=head;
        while(ptr!=NULL)
        {
            if(strcmp(gm,ptr->gmail)==0)
            {
                flag = 0;
                cout<<"G-MAIL FOUND\n"<<endl;
                cout<<"CONTACT DETAILS ARE BELOW:\n"<<endl;
                cout<<"\n\nNAME  ::\t"<<ptr->name;
                cout<<"\nNUMBER::\t+91-"<<ptr->number;
                cout<<"\nG-MAIL::\t"<<ptr->gmail;
                
            }
            ptr=ptr->next;
        }
        if(flag)
        {
            cout << "CONTACT NOT FOUND!!!!!!!!!!!" << endl;
        }
    }
    void dlist::update(char n[20])
    {
        vector<dnode*> v;
        char ans;
        int c;
        ptr=head;
        char* finalname = to_upper(n);
        int x = 0;
        string finalname2;
        string tempo;
        while(ptr!=NULL)
        {
            if(strcmp(finalname,ptr->name)==0)
            {
                v.push_back(ptr);  
            }
            ptr=ptr->next;
        }
        if(v.size() == 0)
        {
            cout << "CONTACT NOT FOUND!!!!!!!!\n\n";
        }
        else if(v.size() == 1)
        {
            do
            {
                cout<<"\nWHAT DO YOU WANT TO UPDATE?\n1.NAME\n2.PHONE NUMBER\n3.G-MAIL\n";
                cin>>c;
                switch(c)
                {
                    case 1:
                    cout<<"ENTER NEW NAME  : ";
                    cin >> tempo;
                    finalname2 = to_upper(tempo);
                    while(x < finalname2.size())
                    {
                        v[0] ->name[x] = finalname2[x];
                        x++;
                    }
                    v[0] ->name[x] = '\0';
                    break;
                    case 2:
                    cout<<"ENTER NEW PHONE-NUMBER  :";
                    cin>>v[0]->number;
                    while(strlen(v[0]->number)!=10)
                    {
                        cout<<"ENTER VALID NUMBER  :";
                        cin>>v[0]->number;
                    }
                    break;
                    case 3:
                    cout<<"ENTER NEW G-MAIL  :";
                    cin>>v[0]->gmail;
                    break;
                }
                cout<<"\nDO YOU WANT TO CONTINUE UPDATING?";
                cin>>ans;
            } while(ans=='y');
        }
        else
        {
            for(int j = 0; j < v.size(); j++)
            {
                cout << j + 1 << ".\t";
                cout<<"CONTACT DETAILS ARE BELOW:\n"<<endl;
                cout<<"\n\nNAME  ::\t"<<v[j]->name;
                cout<<"\nNUMBER::\t+91-"<<v[j]->number;
                cout<<"\nG-MAIL::\t"<<v[j]->gmail << endl << endl;
            }
            cout << "WHICH ONE DO YOU WANT TO UPDATE??????";
            int k;
            cin >> k;
            while(k < 1 || k > v.size())
            {
                cout << "GIVE A VALID CHOICE!!!!!!";
                cin >> k;
            }
            k--;
            do
            {
                cout<<"\nWHAT DO YOU WANT TO UPDATE?\n1.NAME\n2.PHONE NUMBER\n3.G-MAIL\n";
                cin>>c;
                switch(c)
                {
                    case 1:
                    cout<<"ENTER NEW NAME  : ";
                    cin >> tempo;
                    finalname2 = to_upper(tempo);
                    while(x < finalname2.size())
                    {
                        v[k] ->name[x] = finalname2[x];
                        x++;
                    }
                    v[k] ->name[x] = '\0';
                    break;
                    case 2:
                    cout<<"ENTER NEW PHONE-NUMBER  :";
                    cin>>v[k] ->number;
                    while(strlen(v[k]->number)!=10)
                    {
                        cout<<"ENTER VALID NUMBER  :";
                        cin>>v[k]->number;
                    }
                    break;
                    case 3:
                    cout<<"ENTER NEW G-MAIL  :";
                    cin>>v[k]->gmail;
                    break;
                }
                cout<<"\nDO YOU WANT TO CONTINUE UPDATING?";
                cin>>ans;
            } while(ans=='y');  
        }
    }
int main()
{
    char n[20];
    char nam[20];
    char name[10];
    char number[10];
    char gmail[20];
    dlist d1;
    // apply d;
    char ans;
    int ch,a;
    cout<<"**************                                PHONE BOOK                          ********************";
    cout<<"\n\nWHAT IS YOUR NAME?\n";
    cin.getline(name,20);
    char* finalname = to_upper(name) ; 
    cout<<"\n\n!!!!!!!!!!!!!!!!!!!!!!!   WELCOME "<<finalname<<"   !!!!!!!!!!!!!!!!!!!!!";
    cout<<"\n\n\nLET'S CREATE OUR PHONEBOOK "<<finalname<<"  \n\n";
    d1.accept();
    d1.sort();
    do
    {
        cout<<"\n\n\n\n1) DISPLAY YOUR PHONE BOOK\n2) INSERT NEW CONTACT\n3) UPDATE DETAILS ON EXISTING CONTACT\n4) DELETE CONTACT\n5) DELETE SAME NAME IN PHONEBOOK\n6) SEARCH\n7) EXIT\n";
        cin>>ch;
        switch(ch)
        {
            case 2:
            d1.insert();
            d1.sort();
            break;
            
            case 1:
            // d1.sort();
            d1.display();
            break;

            case 3:
            cout<<"\n\nENTER THE NAME OF PERSON WHOSE DETAILS YOU WANT TO UPDATE...\n";
            cin>>n;
            d1.update(n);
            d1.sort();
            break;

            case 4:
            cout<<"\nENTER THE NAME YOU WANT TO DELETE FROM PHONEBOOK\n";
            cin>>name;
            d1.deletecontact(name);
            d1.sort();
            break;

            case 5:
            d1.deletesamename();
            break;

            case 6:
            do
            {
                cout<<"\n1.SEARCH BY NAME\n2.SEARCH BY NUMBER\n3.SEARCH BY GMAIL\n";
                cin>>a;
                switch(a)
                {
                    case 1:
                    cout<<"ENTER THE NAME TO BE SEARCHED\n";
                    cin>>name;
                    d1.searchbyname(name);
                    break;
                    case 2:
                    cout<<"ENTER THE NUMBER TO BE SEARCHED\n";
                    cin>>number;
                    d1.searchbynumber(number);
                    break;
                    case 3:
                    cout<<"ENTER THE GMAIL ID TO BE SEARCHED\n";
                    cin>>gmail;
                    d1.searchbygmail(gmail);
                    cout << endl;
                    break;
                    default:cout<<"\nNO PROPER INPUT GIVEN.....\n";
                }
                cout<<"\nDO YOU WANT TO CONTINUE SEARCHING?????????";
                cin>>ans;
            } while(ans=='y');
            break;
            
            case 7:
            goto label ;
            break;
            
            default:cout<<"\nNO PROPER INPUT GIVEN..\n";
        }
        cout<<"\n\nDO YOU WANT TO CONTINUE OPERATIONS?????????";
        cin>>ans;
    } while(ans=='y');
    
    label:
    cout << "~~~~~~~~~~~~~THANK YOU FOR USING OUR PHONEBOOK~~~~~~~~~~~~~\n\n";
}
