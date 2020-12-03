#include<iostream>
using namespace std;

class Doc_Info {
private:
    string docName; //stores the name of the document
    int termFreq; //stores the term frequency
    Doc_Info* next;  //points to the next Doc_Info object
public:
    Doc_Info();
    Doc_Info(string, int);
    void SetDocName(string);
    void SetTermFrequency(int);
    void SetNextPtr(Doc_Info*);
    string GetDocName();
    int GetTermFrequency();
    Doc_Info* GetNextPtr();
    ~Doc_Info() {
        this->docName.~basic_string();
        this->termFreq = -99;
        delete this->next;
        this->next = nullptr;
    }
};

Doc_Info::Doc_Info() {
    docName = " ";
    termFreq = -99;
    next = nullptr;
}

Doc_Info::Doc_Info(string docName, int termFreq) {
    this->docName = docName;
    this->termFreq = termFreq;
    next = nullptr;
}

void Doc_Info::SetDocName(string docName) {
    this->docName = docName;
}

void Doc_Info::SetTermFrequency(int termFreq) {
    this->termFreq = termFreq;
}

void Doc_Info::SetNextPtr(Doc_Info* next) {
    this->next = next;
}

string Doc_Info::GetDocName() {
    return docName;
}

int Doc_Info::GetTermFrequency() {
    return termFreq;
}

Doc_Info* Doc_Info::GetNextPtr() {
    return next;
}


class LinkedList {
private:
    Doc_Info* head;
    Doc_Info* tail;
public:
    LinkedList();
    LinkedList(const LinkedList&); //Copy Constructor
    void Insert(string, int); //The parameters for this Insert are the name of the document and the term frequency
    void Display(); //Displays the items stored inside the linkedList of head and tail.
   /* ~LinkedList() {
        if (head && tail) {
            delete head, tail;
            head = tail = nullptr;
        }
    }*/
};

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

LinkedList::LinkedList(const LinkedList& obj) {
    this->head = nullptr;
    this->tail = nullptr;
    Doc_Info* ptr = obj.head;

    while (ptr != nullptr) {
        this->Insert(ptr->GetDocName(), ptr->GetTermFrequency());
        ptr = ptr->GetNextPtr();
    }
}


void LinkedList::Insert(string docName, int termFreq) {
    Doc_Info* temp = new Doc_Info(docName, termFreq);

    if (head == nullptr) {
        head = temp;
        tail = temp;
    }
    else {
        tail->SetNextPtr(temp);
        tail = temp;
    }
}

void LinkedList::Display() {
    Doc_Info* ptr = head;

    while (ptr != nullptr) {
        cout << ptr->GetDocName() << " " << ptr->GetTermFrequency() << " ";
        ptr = ptr->GetNextPtr();
    }
    cout << endl;

}

class Term_Info {
private:
    string termName;
    LinkedList DocList; //associated list of Doc_Info 
public:
    Term_Info();
    Term_Info(string);
    Term_Info(const Term_Info&);
    void SetTermName(string);
    void AddToDocList(string, int); //Wrapped that lets Addition Of Document to be done by Term_Info class. It basically calls on the DocList and then adds to the document list that already exists.
    string GetTermName();
    LinkedList GetDocList();
    void Display() {
        cout << "TERM: " << termName << "\n";
        this->DocList.Display();
    }
    /* ~Term_Info() {
         termName.~basic_string();
         DocList.~LinkedList();
     }*/
};

Term_Info::Term_Info() {
    termName = string();
    DocList = LinkedList();
}

Term_Info::Term_Info(string termName) {
    this->termName = termName;
    DocList = LinkedList();
}

Term_Info::Term_Info(const Term_Info& obj) {
    this->termName = obj.termName;
    DocList = LinkedList(obj.DocList);
}

void Term_Info::SetTermName(string termName) {
    this->termName = termName;
}

void Term_Info::AddToDocList(string docName, int termFreq) {
    this->DocList.Insert(docName, termFreq);
}

string Term_Info::GetTermName() {
    return termName;
}

LinkedList Term_Info::GetDocList() {
    return DocList;
}

class Anode {
private:
    Anode* left;
    Anode* right;
    int height;
    Term_Info term; //this is the 'data' part of the anode.

public:
    Anode(int);
    Anode(const Anode*&);
    Anode(Term_Info term);
    void SetHeight(int); //sets the height
    void SetLeftPtr(Anode* left);
    void SetRightPtr(Anode* right);
    Anode* GetRightPtr();
    Anode* GetLeftPtr(); //returns the left PTR
    int GetHeight(); //gives the height
    string GetTermName(); //returns the name of the term that is used to sort
    void AddDocToTerm(string, int); //Wrapper for Anode class to add a new document with name and term frequency. It calls on term which itself calls the LinkedList class
    Term_Info GetTerm(); //returns the term_Info object pointed to
   /* ~Anode() {
        delete left, right;
        left = right = nullptr;
        height = -99;
        term = Term_Info();
    }*/
};

Anode::Anode(int data) {
    left = nullptr;
    right = nullptr;
    height = 0;
    term = Term_Info();
}

Anode::Anode(const Anode*& obj) {
    this->left = obj->left;
    this->right = obj->right;
    this->height = obj->height;
    this->term = Term_Info(obj->term); //CC for this
}

Anode::Anode(Term_Info term) {
    this->height = 0;
    left = nullptr;
    right = nullptr;
    this->term = Term_Info(term); //cc
}

Anode* Anode::GetRightPtr() { return right; }
Anode* Anode::GetLeftPtr() { return left; }
int Anode::GetHeight() { return height; }
string Anode::GetTermName() { return this->term.GetTermName(); }
Term_Info Anode::GetTerm() { return this->term; }



void Anode::SetHeight(int height) {
    this->height = height;
}

void Anode::SetLeftPtr(Anode* left) {
    this->left = left;
}

void Anode::SetRightPtr(Anode* right) {
    this->right = right;
}

void Anode::AddDocToTerm(string docName, int termFreq) {
    term.AddToDocList(docName, termFreq);
}


class AVLTree
{
private:
    Anode* root;
public:
    AVLTree();
    Anode* Insert(Anode*, string, Term_Info);
    Anode* SingleRightRotate(Anode*&);
    Anode* SingleLeftRotate(Anode*&);
    Anode* DoubleLeftRotate(Anode*&);
    Anode* DoubleRightRotate(Anode*&);
    Anode* FindMin(Anode*);
    Anode* FindMax(Anode*);
    int getBalance(Anode*); //returns the balance factor
    int height(Anode*); //returns the height of the Anode* sent to it
    int GetMax(int, int); //returns the greater of the two number passed to it.
    bool SearchTree(Anode*, string, string, int, bool); //this is used in the case of insert. It searches for a value and sees if it's pre-existing. If it is, it adds to the DocList of the Term_Info rather than adding that term to the tree.
    void Search(string, string, int); //Basically the search Handler for incoming enteries. It calls on SearchTree and relies on the value returned by it. If searchTree returns false, it adds a new term by calling Insert.
    void SearchTerm(string term); //Wrapper function which cals RSearchTree
    bool RSearchTerm(Anode* ptr, string termName, bool); //Used to locate and search for a already existing node. Displays the info of the term after.

    void InorderTrasversal(Anode* ptr) //traverses through the AVL tree in order
    {
        if (ptr == nullptr) return;

        InorderTrasversal(ptr->GetLeftPtr());
        ptr->GetTerm().Display();
        InorderTrasversal(ptr->GetRightPtr());
    }

    void Insert(string termName) { //Wrapper function to insert.
        Term_Info rookie_term(termName);
        root = Insert(root, termName, rookie_term);
    }

    void Display() // Wrapper function for InorderTraversal
    {
        InorderTrasversal(root);
    }
    void RecursiveDestroy(Anode* ptr) {
        if (ptr != nullptr) {
            RecursiveDestroy(ptr->GetLeftPtr());
            RecursiveDestroy(ptr->GetRightPtr());
            delete ptr;
            ptr = nullptr;
        }
    }
    /*~AVLTree() {
         RecursiveDestroy(root);
    }*/
};

AVLTree::AVLTree() { root = nullptr; }
Anode* AVLTree::Insert(Anode* ptr, string termName, Term_Info term)
{
    if (ptr == nullptr)
    {
        ptr = new Anode(term);
    }

    else if (termName > ptr->GetTermName()) //sorts by the termname itself
    {
        ptr->SetRightPtr(Insert(ptr->GetRightPtr(), termName, term));
        if (height(ptr->GetRightPtr()) - height(ptr->GetLeftPtr()) == 2) //height is used to get the height of the object pointed to by the pointer
        {
            if (termName < ptr->GetRightPtr()->GetTermName()) {
                ptr = SingleLeftRotate(ptr);
            }
            else {
                ptr = DoubleLeftRotate(ptr);
            }
        }
    }

    else if (termName < ptr->GetTermName())
    {
        ptr->SetLeftPtr(Insert(ptr->GetLeftPtr(), termName, term));
        if (height(ptr->GetLeftPtr()) - height(ptr->GetRightPtr()) == 2)
        {
            if (termName < ptr->GetLeftPtr()->GetTermName()) {
                ptr = SingleRightRotate(ptr);
            }
            else {
                ptr = DoubleRightRotate(ptr);
            }
        }
    }

    ptr->SetHeight(GetMax(height(ptr->GetLeftPtr()), height(ptr->GetRightPtr())) + 1);
    return ptr;
}
Anode* AVLTree::SingleRightRotate(Anode*& ptr)
{
    if (ptr->GetLeftPtr() != nullptr) {
        Anode* tempPtr(ptr->GetLeftPtr());
        ptr->SetLeftPtr(tempPtr->GetRightPtr());
        tempPtr->SetRightPtr(ptr);
        ptr->SetHeight(GetMax(height(ptr->GetLeftPtr()), height(ptr->GetRightPtr())) + 1);
        tempPtr->SetHeight(GetMax(height(tempPtr->GetLeftPtr()), ptr->GetHeight()) + 1);
        return tempPtr;
    }
    return ptr;
}
Anode* AVLTree::SingleLeftRotate(Anode*& ptr)
{
    if (ptr->GetRightPtr() != nullptr) {
        Anode* tempPtr(ptr->GetRightPtr());
        ptr->SetRightPtr(tempPtr->GetLeftPtr());
        tempPtr->SetLeftPtr(ptr);
        ptr->SetHeight(GetMax(height(ptr->GetLeftPtr()), height(ptr->GetRightPtr())) + 1);
        tempPtr->SetHeight(GetMax(height(ptr->GetRightPtr()), ptr->GetHeight()) + 1);
        return tempPtr;
    }
    return ptr;
}

Anode* AVLTree::DoubleLeftRotate(Anode*& ptr)
{
    Anode* temp = ptr->GetRightPtr();
    ptr->SetRightPtr(SingleRightRotate(temp));
    return SingleLeftRotate(ptr);
}

Anode* AVLTree::DoubleRightRotate(Anode*& ptr)
{
    Anode* temp = ptr->GetLeftPtr();
    ptr->SetLeftPtr(SingleLeftRotate(temp));
    return SingleRightRotate(ptr);
}

Anode* AVLTree::FindMin(Anode* ptr)
{
    if (ptr == nullptr) {
        return nullptr;
    }
    else if (ptr->GetLeftPtr() == nullptr) {
        return ptr;
    }
    else {
        return FindMin(ptr->GetLeftPtr());
    }
}

Anode* AVLTree::FindMax(Anode* ptr)
{
    if (ptr == nullptr) {
        return nullptr;
    }
    else if (ptr->GetRightPtr() == nullptr) {
        return ptr;
    }
    else {
        return FindMax(ptr->GetRightPtr());
    }
}

int AVLTree::height(Anode* ptr)
{
    return (ptr == nullptr ? -1 : ptr->GetHeight());
}
int AVLTree::getBalance(Anode* ptr)
{
    if (ptr == nullptr) return 0;

    return (height(ptr->GetLeftPtr()) - height(ptr->GetRightPtr()));
}
int AVLTree::GetMax(int x, int y) {
    return (x > y ? x : y);
}

//Used when adding new enteries to see if they pre-exist or not.
bool AVLTree::SearchTree(Anode* ptr, string termName, string docName, int termFreq, bool found) {
    if (ptr == nullptr) return found;

    found = SearchTree(ptr->GetLeftPtr(), termName, docName, termFreq, found);
    found = SearchTree(ptr->GetRightPtr(), termName, docName, termFreq, found);

    if (ptr->GetTermName() == termName) {
        found = true;
        ptr->AddDocToTerm(docName, termFreq); //if the termName being passed already exists. This line will add the doc to the docList of the Term_Info rather than creating a new node inside the tree itself.
        return true;
    }

    return found;
}

void AVLTree::Search(string termName, string docName, int termFreq) {
    bool found = SearchTree(root, termName, docName, termFreq, false);
    //if found == false, then the term does not pre-exist and hence you need to add the new term to the AVL Tree. 
    if (!found) {
        //cout << "new term added\n";
        Term_Info newTerm(termName);
        newTerm.AddToDocList(docName, termFreq);
        root = this->Insert(root, termName, newTerm);
    }
}
//Searches and sees if there exists a term.
bool AVLTree::RSearchTerm(Anode* ptr, string termName, bool found) {
    if (ptr == nullptr) return found;

    found = RSearchTerm(ptr->GetLeftPtr(), termName, found);
    found = RSearchTerm(ptr->GetRightPtr(), termName, found);
    if (ptr->GetTermName() == termName) {
        found = true;
        ptr->GetTerm().Display();
        return true;
    }

    return found;
}

//Wrapper that calls RSearchTerm. Also servces as the handler in this case.
void AVLTree::SearchTerm(string termName) {
    bool result = RSearchTerm(root, termName, false);
    if (!result) {
        cout << "Not found!\n";
    }
    else {
        cout << "Found!\n";
    }
}