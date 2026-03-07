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
	std::cout<<"(HEAD) ";
	while(root){
		std::cout<<root->value<<" -> ";
		root = root->next;
	}
	std::cout<<"NULL\n";
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

int lengthLoopLL(Node* head){
	Node *slow =head,*fast=head;
	int ctr =0;
	while(fast && fast->next){
		fast = fast->next->next;
		slow = slow->next;

		if(fast==slow){
			do{
				fast = fast ->next;
				ctr++;
			}while(fast != slow);
			break;
		}
	}
	return ctr;
}

bool isPalindromeLL(Node* head){
	std::stack<int> stack;
	Node *curr = head;
	//fill the stack
	while(curr){
		stack.push(curr->value);
		curr = curr ->next;
	}

	curr =head;
	for(int i = 0 ; i <stack.size();i++){
		if(stack.top()!= curr->value){
			return false;
		}
		curr = curr->next;
		stack.pop();
	}
	return true;
}

Node* groupOddEvenLL(Node* head){
	if(!head || !head->next) return head;


	Node* odd = head;
    Node* even = head->next;
    Node* evenHead = even;

	while(even && even->next){
		odd->next = even->next;
		odd = odd->next;
		
		even->next = odd->next;
		even = even ->next; 
	}
	odd->next = evenHead;
	return head;
}

Node* deleteNthEnd(Node* head , int n){

	Node* fakeHead = new Node(0);
	fakeHead->next = head;
	Node *fast = fakeHead,*slow=fakeHead;
	for(int i = 0 ; i <= n ;i++){
		fast = fast->next;
	}

	//reach till end
	while(fast){
		fast = fast->next;
		slow = slow->next;
	}

	Node* temp = slow->next;
	slow->next = slow->next->next;
	delete temp;

	head = fakeHead->next;
	delete fakeHead;

	return head;
}

//2095. Delete the Middle Node of a Linked List
Node* deleteMiddle(Node* head){
	if(!head || !head->next) return nullptr;


	Node *fast = head,*slow =head;
	Node * lastslow = nullptr;
	//this will put slow at Floor(n/2)
	while(fast && fast->next){
		fast=fast->next->next;
		lastslow = slow;
		slow=slow->next;
	}
	lastslow->next = slow->next;
	delete slow;
	return head;

}

int main()
{
	Node* root = Vec2LL({1});
	
	printLL(root);
	root = deleteMiddle(root);
	printLL(root);

	
	// std::cout << isPalindromeLL(root) <<std::endl;

	return 0;
}
