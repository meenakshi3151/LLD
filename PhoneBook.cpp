#include<bits/stdc++.h>
using namespace std;

class PhoneNumber{
    public: 
    bool isEnd;
    PhoneNumber* child[10];
    PhoneNumber(){
        isEnd=false;
        for(int i=0;i<10;i++) child[i]=nullptr;
    }
};

class PhoneBook{
    public:
    
    PhoneNumber* root;
    
    PhoneBook() {
       root=new PhoneNumber();
    }
    
    void insertNumber(string nums) {
        PhoneNumber* node = root;
        int n=nums.length();
        for(int i=0;i<n;i++) {
            int num = nums[i]-'0';
            if(node->child[num]==nullptr) {
                node->child[num] = new PhoneNumber();
            }
            node = node->child[num];
        }
        node->isEnd = true;
        return;
    }
    
    bool searchNumber(string nums) {
        PhoneNumber* node = root;
        int n=nums.length();
        for(int i=0;i<n;i++) {
            int num = nums[i]-'0';
            if(node->child[num]==nullptr) {
                return false;
            }
            node = node->child[num];
        }
        return node->isEnd;
    }
    
    bool isPrefix(string nums) {
        PhoneNumber* node = root;
        int n=nums.length();
        for(int i=0;i<n;i++) {
            int num = nums[i]-'0';
            if(node->child[num]==nullptr) {
                return false;
            }
            node = node->child[num];
        }
        return true;
    }
    
    void findAllNumsWithPrefix(PhoneNumber* node, string pre, vector<string> &ans) {
        
        if(node->isEnd) {
            ans.push_back(pre);
            return;
        }
        
        for(int i=0;i<10;i++) {
            if(node->child[i]) {
                pre+=(i+'0');
                findAllNumsWithPrefix(node->child[i], pre, ans);
                pre.pop_back();
            }
        }
        return;
    }
    
    vector<string> giveSuggestions(string pre) {
        if(isPrefix(pre)==false) {
            cout<<"No number exists with the given letters.";
            return {};
        }
        PhoneNumber* node = root;
        int n=pre.length();
        for(int i=0;i<n;i++) {
            int num = pre[i]-'0';
            node = node->child[num];
        }
        vector<string> ans;
        findAllNumsWithPrefix(node, pre, ans);
        return ans;
    } 
};

int main() {

    PhoneBook* phoneBook = new PhoneBook();
    phoneBook->insertNumber("9876543210");
    phoneBook->insertNumber("9876500000");
    phoneBook->insertNumber("9123456789");
    phoneBook->insertNumber("9123000000");
    phoneBook->insertNumber("9000000000");
    cout << "Search 9876543210: "
         << phoneBook->searchNumber("9876543210") << endl;
    cout << "Search 9876500001: "
         << phoneBook->searchNumber("9876500001") << endl;
    cout << "Is prefix 9876: "
         << phoneBook->isPrefix("9876") << endl;
    cout << "Is prefix 9999: "
         << phoneBook->isPrefix("9999") << endl;
    vector<string> suggestions = phoneBook->giveSuggestions("9123");
    cout << "Suggestions for prefix 9123:" << endl;
    for (string s : suggestions) {
        cout << s << endl;
    }
    vector<string> suggestions2 = phoneBook->giveSuggestions("98");
    cout << "Suggestions for prefix 98:" << endl;
    for (string s : suggestions2) {
        cout << s << endl;
    }
    return 0;
}
