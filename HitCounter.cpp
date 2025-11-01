#include<bits/stdc++.h>
using namespace std;

class HitCounter{
    public:
    queue<pair<int, int>> hits;
    static int tothits;
    
    void hit(int timestamp){
        if(!hits.empty() && hits.back().first==timestamp) {
            hits.back().second++;
            tothits++;
            return;
        }
        hits.push({timestamp, 1});
        tothits++;
    }
    
    int gethits(int timestamp) {
        while(!hits.empty() && hits.front().first<timestamp-300) {
            tothits-=hits.front().second;
            hits.pop();
        }
        return tothits;
    }
};

int HitCounter::tothits = 0;

int main(){
    HitCounter* hc = new HitCounter();
    hc->hit(500);
    hc->hit(450);
    hc->hit(700);
    int hits = hc->gethits(705);
    cout<<"hits at 705: "<<hits;
    return 0;
}