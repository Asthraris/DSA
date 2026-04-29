#include <queue>
#include <vector>
using namespace std;

class myStackFA{
    vector<int> A;
    int TOP ;
    public:
    myStackFA():TOP(-1){}

    void push(int x) {
        A.push_back(x);
        TOP++;
    }

    int pop() {
        if (empty()) return -1;//this was causing error before
        int t = A[TOP];
        // A.pop_back(); WE WONT delete the data but we will keep that track of top , WE CAN DELETE the DATA BY POPBACK but that way STD::vector is gonna do all the lifting and the top var i created would be useless
        TOP--;
        return t;
    }
    
    int top() {
        return A[TOP];
    }
    
    bool empty() {
        return TOP==-1;
    }

};



class myStackFQ{
    queue<int> Q;
    public:
    myStackFQ(){}

    void push(int x) {
        Q.push(x);
        for (int i = 0; i < Q.size()-1; i++)
        {
            Q.push(Q.front());
            Q.pop();
        }
        //this loop brings the front ptr to the lastmost element added , while sending all the previous ones to the back
        
    }

    int pop() {
        if (empty()) return -1;//this was causing error before
        int temp = Q.front();
        Q.pop();
        return temp;
    }
    
    int top() {
        return Q.front();
    }
    
    bool empty() {
        return Q.empty();
    }

};

int main()
{
    myStackFA* x = new myStackFA();
    x->push(10);
    x->push(20);
    int z = x->pop();
    int y = x->top();
    bool a = x->empty();
    return 0;
}
