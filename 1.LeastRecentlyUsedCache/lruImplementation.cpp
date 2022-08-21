//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
// design the class in the most optimal way
struct Node{
    int key;
    int value;
    Node* prev;
    Node* next;
    Node(){
        prev = next = NULL;
    }
};
class LRUCache
{
    private:
    Node* head; // recently used side
    Node* tail; // least recently used side
    int capacity;
    map<int,Node*> cache;
    public:
    //Constructor for initializing the cache capacity with the given value.
    LRUCache(int cap)
    {
        this->capacity = cap;
        //dummy nodes which help to ignoring null cases
        this->head = new Node();
        this->tail = new Node();
        head->next = tail;
        tail->prev = head;
    }
    void addNode(Node* node){ // it add node newar head.. ie recently used side
        Node* nbr = head->next;
        node->prev = head;
        node->next = nbr;
        nbr->prev = node;
        head->next = node;
    }
    void removeNode(Node* node){  //it can remove node from any position
        Node* prev = node->prev;
        Node* next = node->next;
        prev->next = next;
        next->prev = prev;
        node->prev = node->next = NULL;
    }
    void moveToFront(Node* node){ //.. it can remove node from any position and then add it in recently used side ie. near head..
        removeNode(node);
        addNode(node);
    }
    //Function to return value corresponding to the key.
    int get(int key)
    {
        if(cache.find(key) == cache.end()){
            return -1;
        }
        Node* node = cache[key];
        moveToFront(node);
        return (node->value);
    }
    //Function for storing key-value pair.
    void set(int key, int value)
    {
        if(cache.find(key) == cache.end()){ //pair doesnt exist
            Node* node = new Node();
            node -> key = key;
            node -> value = value;
            
            if(cache.size() == capacity){
                Node* LRU_Node = tail->prev;
                cache.erase(LRU_Node->key);
                removeNode(LRU_Node);
            }
            
            cache[key] = node;
            addNode(node);
        }else{
            Node* node = cache[key];
            node->value = value;
            moveToFront(node);
        }
    }
};

//{ Driver Code Starts.

int main()
{
    int t;
    cin >> t;
    while (t--)
    {

        int capacity;
        cin >> capacity;
        LRUCache *cache = new LRUCache(capacity);
        
        int queries;
        cin >> queries;
        while (queries--)
        {
            string q;
            cin >> q;
            if (q == "SET")
            {
                int key;
                cin >> key;
                int value;
                cin >> value;
                cache->set(key, value);
            }
            else
            {
                int key;
                cin >> key;
                cout << cache->get(key) << " ";
            }
        }
        cout << endl;
    }
    return 0;
}

// } Driver Code Ends
