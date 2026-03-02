#include <iostream>
#include <stack>
#include <vector>
#include <set>

struct Node
{
	int value;
	Node *next;

	Node(int val)
	{
		value = val;
		next = NULL;

	}
	void print(){
		std::cout<<value<<"\n";
	}
};

Node *Vec2LL(std::vector<int> vec)
{
    Node *Head = new Node(vec[0]);
    Node *lastSeen = Head;

    for (int i = 1; i < vec.size(); i++)
    {
        Node *temp = new Node(vec[i]);
        lastSeen->next = temp;
        lastSeen = temp;
    }
    return Head;
}
void printLL(Node* root){
	while(root){
		std::cout<<root->value<<" -> ";
		root = root->next;
	}
}

void DeleteNode(Node* root , int val){
	Node* lastNode = root;
	while(root){
		if(root->value == val){
			lastNode->next = root->next;
			//not asjed but ;
			delete root;
			//this will exit the program after removal for first occuaranec , if not return then the func will caue segmenation error due to deletion f rrot and access during root->next
			return;
		}
		lastNode = root;
		root= root->next;
	}
}
int lengthLL(Node *root){
	int counter = 0;
	while(root){
		counter++;
		root = root-> next;
	}
	return counter;
}

Node* SearchLL(Node* root , int val){
	while(root){
		if(root->value == val)return root;
		root=root->next;
	}
	return nullptr;
}

Node* MidLL(Node* root){
	Node* fast=root;
	Node* slow=root;
	while(fast && fast->next){
		fast=fast->next->next;
		slow=slow->next;
	}
	return slow;
}
Node* reverseLL(Node* head){
	Node* curr = head;
	Node* lastSeen = nullptr; 
	while(curr){
		Node* nextNode = curr->next;
		curr->next = lastSeen;
		lastSeen = curr;
		curr = nextNode;		
	}
	return lastSeen;
}

bool detectLoop(Node* head){
	//O[n] ,space - O[n]

	// std::set<Node*> visited;
	// while(head){
	// 	if(visited.find(head) != visited.end()){
	// 		return true;
	// 	}
	// 	visited.insert(head);
	// 	head = head->next;
	// }
	// return false;

	//O[n*k=loopsize] space-O[1]

	if(!head || !head->next )return false;
	Node* slow = head;
	Node* fast = head->next;

	while(slow != fast){
		if(!fast || !fast->next)return false;

		slow = slow->next;
		fast = fast->next->next;
	}
	return true;
}

Node* startingLoop_1(Node* head){

	if(!head || !head->next )return nullptr;
	Node* slow = head;
	Node* fast = head;

	//if fast==slow==head at begining this will directly cause while loop to not run 
	while(fast && fast->next){

		slow = slow->next;
		fast = fast->next->next;

		if(fast == slow)break;
	}
	
	if(!fast || !fast->next)return nullptr;//this will tell whether this ll has loop or not

	//new thing from here ,when slow =fast , that time we will resetslow and agin till slow and fast will meet thats the staring point
	slow = head;
	while(slow != fast){
		slow = slow->next;
		fast = fast->next;
	}
	return slow;//also can be returned fast since both are same

	//O[n] ,space - O[n]

	// std::set<Node*> visited;
	// while(head){
	// 	if(visited.find(head) != visited.end()){
	// 		return head;
	// 	}
	// 	visited.insert(head);
	// 	head = head->next;
	// }
	// return nullptr;
}

Node* startingLoop(Node*head){
	Node* slow = head;
	Node* fast = head;
	Node* dest = head;

	while(fast && fast->next){
		fast= fast->next->next;
		slow= slow->next;

		if(fast == slow){
			while(slow != dest){
				slow = slow->next;
				dest = dest->next;
			}
			return dest;
		}
	}
	return nullptr;
}

int main()
{
	Node* root = Vec2LL({1,2,3,4,5,6,7,8});
	
	// printLL();
	std::cout << (startingLoop(root) == nullptr )<<std::endl;

	return 0;
}
