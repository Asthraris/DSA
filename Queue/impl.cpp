#include<queue>
#include<stack>
#include<vector>
using namespace std;

class myQueueFA{
    vector<int> A;
    int back ;
    int front;
    void Compaction(){
        if (front<=0)return;
        
        int t_size = size();
        for(int i = 0 ; i <t_size ; i++){
            A[i]=A[front + i];
        }
        front=0;
        back = t_size;
        //srink the vector
        A.resize(t_size);

    }
    public:
    myQueueFA():back(0),front(0){}

    void push(int x) {
        //means the front of the vector has shifted to 50 after 50times pop opr
        if(front>50){
            Compaction();
        }
        A.push_back(x);
        back++;
    }

    int pop() {
        if (empty()) return -1;//this was causing error before
        int t = A[front];
        front++;
        // A.pop_back(); WE WONT delete the data but we will keep that track of top , WE CAN DELETE the DATA BY POPBACK but that way STD::vector is gonna do all the lifting and the top var i created would be useless
        return t;
    }
    
    int peek() {
        if (empty()) return -1;//this was causing error before
        return A[front];
    }
    
    bool empty() {
        return back==front;
    }
    int size(){
        return back-front;
    }
};

class myQueueFSTACK{
    stack<int> S;
    public:
    myQueueFSTACK(){}

    void push(int x) {
        //using stack to store temp 
        stack<int> temp;
        //1st empty the stack
        while(!empty()){
            temp.push(S.top());
            S.pop();
        }
        //put new data at bottommost
        S.push(x);
        //fill stack up from the as it was [ REMEBER NO REVERSE IS NEEDED SINCE I AM HANDLING THAT IN EVERY PUSH STEP]
        while(!temp.empty()){
            S.push(temp.top());
            temp.pop();
        }
    }

    int pop() {
        if(empty())return -1;
        int t = S.top();
        S.pop();
        return t;
    }
    
    int peek() {
        if(empty())return -1;
        return S.top();
    }
    
    bool empty() {
        return S.empty();
    }
};

