#include <bits/stdc++.h>

using namespace std;

// HINT : CACHE PROBLEMS WILL ALWAYS USE LL AND HASHMAPS 
// industry standards uses minheap more than LL but very complex for now
// cause we need O[1] lookup ,insertion,update


/*
Most advanced cache questions reduce to:
    HashMap + another DS
where hashmap gives:
    identity
    direct access
and second DS manages:
    ordering -> dll
    frequency -> bucket -dll
    expiry  ->
    randomness ->vector
    priority   ->
*/



struct node{
    // nodes do need to store their frequency , so we know which frequency bucket it currently belongs to , & shift them accordingly 
    // its not needed in normal LRU so not gonna use that but lets keep both same strcut for better code readablity
    int fre;
    int key,val;
    node* next;
    node* prev;
    node(int k,int v): key(k),val(v),fre(1),next(NULL),prev(NULL){    }
};


//this will work mostly like an LRU DLL: u will know how by helper functions , struct cause i dont want to mess with public private now
struct DLL{

    //THIS DATASTRUCTURE will only manage the layout of data , not any modification to it like value , key , frequency
    //so we can keep track 
    node* head, *tail;
    int size ;
    DLL(){
        head = new node(-1,-1);
        tail = new node(-1,-1);
        head->next = tail;
        tail->prev = head;
        size = 0;
    }
    //addnode it will add node to tail simulating addition to the MRU side latest node
    void addNode(node* n)
    {
        n->prev = tail->prev;
        n->prev->next = n;
        tail->prev = n;
        n->next = tail;
        size ++;
    }

    //remove node will remove node from any place
    void remove(node* n )
    {
        //gathbandhan
        n->prev->next = n->next;
        n->next->prev = n->prev;
        size--;
    }

    //special fucntion: remove last in prev version i used to manually remove last node from key but here i can do it by the DLL itself which is fatser
    node* removeLast()
    {
        //remove from head , simulating LRU removal upon cappped
        if(size>0){
            node* nd = head->next;
            remove(nd);
            return nd;
        }return nullptr;
    }
};



class LRUCache {
    int cap; 
    unordered_map<int,node*> key2node ;
    DLL* memory;
public:
    LRUCache(int capacity) {
        cap = capacity;
        memory = new DLL();
    }
    
    int get(int key) { 
        if(key2node.count(key) == false)return -1;
        
            //UPDATing: moving node to MRU side beofre sending the data back
        memory->remove(key2node[key]);
            //good since we are not deleteing the removed node in removeFunc so we stil has its ptr location saved in hashmap
        memory->addNode(key2node[key]);
            // thus insertng node to mRU side without recreating node
        return key2node[key]->val;
        
    }
    
    void put(int key, int value) {
        if (key2node.count(key))
        {
            //remove the dll node , not from cache till next line
            memory->remove(key2node[key]);
        }
        node* nd = new node(key,value);
        //rewriting the key value in the hashmap with the newly created node
        //putting this in curly braces to tell this is a single unit of map
        key2node[key]=nd;
        //insert in dll nodes layout 
        memory->addNode(nd);
        //since i have size var in DLL Too i can also use memory->size >cap
        if(key2node.size() > cap){
            node* lru = memory->removeLast();
            //remove the hashmaped value since the dll is removed
            key2node.erase(lru->key);
            //delete lru here since we know its not usefull now instead of removehelper func
            delete lru;
        }
    }
};


//  BUCKET Datastrcuture : since there can be multiple data having freq same 

class LFUCache {
//CANLLENGES : 
// 1.if multiple nodes have same we have to impl LRU inside them
//  keep track of frequency table with correatakes with that LRU
// 2. still manage to find node with o[1] individually , so we need to keep track of node with their key too
// 3. if i use one node the freq gonna shift one up and the node will link to MRU of new freq

// way:
// we need to 2 hashamps , one pointing to individual node , and one poiting to the freq
// when we remove we will from least freq dll in lru way
// visuals : Stack/LFU VISUAL.png


    unordered_map<int,node*> key2Node;
   /* LFU uses unordered_map<int, DLL> or unordered_map<int, DLL*> where each frequency has its own LRU doubly linked list bucket.
Each DLL stores nodes in MRU → LRU order for tie-breaking among same frequencies.
Nodes must store freq so they can move between frequency buckets in O(1).
LFU internally behaves like multiple mini-LRU caches grouped by frequency.
key -> Node* map gives direct access to cache nodes.
freq -> DLL map gives direct access to frequency buckets.
minFreq tracks the current minimum frequency for O(1) eviction.
On access: remove node from old freq DLL, increment freq, insert into new freq DLL front.
Eviction removes the tail node from freqMap[minFreq] because it is the least recently used among least frequently used nodes.
DLL structure is same as LRU cache implementation: insertFront(), removeNode(), removeTail().
Using unordered_map<int, DLL> is cleaner modern C++ since it avoids heap allocation for DLL objects.
Using unordered_map<int, DLL*> is older/common style to avoid accidental object copies and maintain stable object identity.
If using value semantics (DLL not pointer), copy constructor should usually be deleted because DLL manages raw node pointers.*/
    unordered_map<int,DLL*> fre2Dll;
    //min freq will keep track of ovsly , so we dont need to iterated of map to get the min if the freq keeps rising by usage of same data multiple times
    int minFreq;
    int cap;

    //SPECIAL : changes the data inside node like fre and rearranges them inside the DLL structures as per needed
    // this func is called whenevr the node is used or uddates cause its also managing the freq of that node
    void update(node* n)
    {
        int freq = n->fre;
        //thus by using ptr we are not coping the entire data just getting its ptr below
        DLL* list = fre2Dll[freq];
        //remove the node from any position that n is exixting not needed to be MRU OR LRU
        list->remove(n);

        //meaning the list is empty and its the last freq avail in freq table
        if(freq ==minFreq && list->size == 0)
        {
            minFreq++;
        }
        
        //update the atomic data
        n->fre ++;
        /*
        WHY USE COUNT INSTEAD OF FIND:
        count(key)
            Returns:
                0 → absent
                1  → present
            For unordered_map, keys are unique, so count is only 0 or 1.
            Cleaner for simple existence checks.
        find(key)
            Returns:
            iterator to element
            or .end()
        */
        // agar next freq dll exist nhi karta hai toh dynamicvally create karo
        if(!fre2Dll.count(n->fre)){
            fre2Dll[n->fre] = new DLL();
        }
        //then add that to the dll , which pos? see the dll ;)
        fre2Dll[n->fre]->addNode(n);
    }
public:
    LFUCache(int capacity) : cap(capacity),minFreq(0){}
    
    int get(int key) {
        //agar node exists nhi karta hai tab
        if(key2Node.find(key) == key2Node.end())return -1;
        node* nd = key2Node[key];
        //before return we need to readjust DS
        update(nd);
        return nd->val;
    }
    
    void put(int key, int value) {
        if(cap == 0 )return;

        if(key2Node.count(key))
        {
            node* nd = key2Node[key];
            //update with newer value
            nd->val =value; 
            update(nd);
            return;
        }
        //if cap is full
        if(key2Node.size() >= cap){
            DLL* list = fre2Dll[minFreq];
            //NOW i understand why i needed the node to be returned cause i also want the node which is removed so i can removed it also from the keymap, this is the way to think data flow like rn we knew where to dlete node on which criteria so we need to retrace at every place with taht info
            node* nd = list->removeLast();
            key2Node.erase(nd->key);
        }

        //newer node , which mean ist used only once so min freq will be 1
        node* nd = new node(key,value);
        key2Node[key] = nd;
        minFreq = 1;
        if(!fre2Dll.count(minFreq)){
            fre2Dll[minFreq] = new DLL();
        }
        fre2Dll[minFreq]->addNode(nd);
    }
};

int main()
{
    return 0;
}