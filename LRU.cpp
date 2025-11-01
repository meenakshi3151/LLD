#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int key;
    int val;
    Node* next;
    Node* prev;
    Node(int k, int v) {
        key = k;
        val=v;
        next=nullptr;
        prev=nullptr;
    }
};

class LRU{
    public:
    int lim;
    unordered_map<int, Node*> mp;
    Node* head = new Node(-1, -1);
    Node* tail = new Node(-1, -1);
    LRU(int capacity) {
        lim = capacity;
        head->next = tail;
        tail->prev = head;
    }
    void remove(Node* node) {
        Node* prevnode = node->prev;
        Node* nextnode = node->next;
        prevnode->next=nextnode;
        nextnode->prev=prevnode;
    }
    void insert(Node* node) {
        Node* nextnode = head->next;
        head->next=node;
        node->prev=head;
        node->next=nextnode;
        nextnode->prev = node;
    }
    void put(int key, int val) {
        if (mp.find(key) != mp.end()) {
            remove(mp[key]);
            mp.erase(key);
        }
        if(mp.size()==lim) {
            Node* lru = tail->prev;
            mp.erase(lru->key);
            remove(lru);
            delete lru;
        }
        Node* node = new Node(key, val);
        insert(node);
        mp[key]=node;
    }
    int get(int key) {
        if(mp.find(key)==mp.end()) return -1;
        remove(mp[key]);
        insert(mp[key]);
        return mp[key]->val;
    }
    void update(int key, int val) {
        if(mp.find(key)!=mp.end()) {
            remove(mp[key]);
        }
        Node* node = new Node(key, val);
        insert(node);
        mp[key]=node;
    }
};

int main() {
    LRU* lru = new LRU(4);
    lru->put(1, 100);
    lru->put(2, 200);
    lru->put(3, 100);
    cout << "Get(2): " << lru->get(2) << endl;
    cout << "Get(1): " << lru->get(1) << endl;
    lru->put(4, 100);
    lru->put(5, 100);
    cout << "Get(3): " << lru->get(3) << endl;
    delete lru;
    return 0;
}