#include <iostream>
#include <vector>

struct Node
{
    int value;
    Node *next;
    Node *prev;
    Node(int val) : value(val), next(nullptr), prev(nullptr) {}
    Node(int val, Node *right, Node *left)
    {
        value = val;
        next = right;
        prev = left;
    }
    void print()
    {
        std::cout << value << "\n";
    }
};

Node *Vec2DLL(std::vector<int> vec)
{
    Node *Head = new Node(vec[0]);
    Node *lastSeen = Head;

    for (int i = 1; i < vec.size(); i++)
    {
        Node *temp = new Node(vec[i]);
        temp->prev = lastSeen;
        lastSeen->next = temp;
        lastSeen = temp;
    }
    return Head;
}

void printDLL(Node *root)
{

    while (root)
    {
        std::cout << root->value << "-> ";
        root = root->next;
    }
    std::cout << "\n";
}
Node* SearchDLL(Node* root,int val){
    while(root){
        if(root->value == val)return root;
        root = root -> next;
    }
    return nullptr;
}

Node* deleteDLL(Node* Head, Node*del){
    if(!del)return Head;   
    if(Head==del){
        Head = del-> next;
    }
    if(del->prev)del->prev-> next = del -> next;
    if(del-> next)del->next->prev = del->prev;
    delete del;
    return Head;
}
Node* insertHead(Node* preHead , Node* head){
    preHead->prev = head;
    head ->next = preHead;
    return head;
}
Node* reverseDLL(Node* Head){
    if (Head == nullptr || Head->next == nullptr) return Head;

    Node* curr=Head;

    Node* temp = nullptr;
    while(curr){
        temp = curr->next;
        curr->next = curr->prev;
        curr->prev = temp;
        
        Head =curr;
        curr=temp;
    }
    return Head;
}

int main()
{
    std::vector<int> temp = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    Node *Head = Vec2DLL(temp);
    // Head = deleteDLL(Head , SearchDLL(Head,1));
    // printDLL(Head);
    // Head = insertHead(Head , new Node(0));
    // printDLL(Head);
    Head = reverseDLL(Head);
    printDLL(Head);

    return 0;
}