#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 7;
const int Mod = 1e9 + 7;
typedef long long ll;

typedef struct poi{
    vector<int>Card;
    char name[100];
    int cardType,firstRank,secondRank,otherRank;
    bool operator < (const poi &man) const{
        if(cardType == man.cardType){
            if(firstRank == man.firstRank){
                if(secondRank == man.secondRank){
                    if(otherRank == man.otherRank){
                        return strcmp(name,man.name) < 0;
                    }
                    return otherRank > man.otherRank;
                }
                return secondRank > man.secondRank;
            }
            return firstRank > man.firstRank;
        }
        return cardType > man.cardType;
    }
    bool checkTwo(int i,int j){
        if(Card[i] == Card[j]) return true;
        return false;
    }

    void getIndex(void){
        if(Card[0] == 1 && Card[1] == 10 && Card[2] == 11
           && Card[3] == 12 && Card[4] == 13)
            cardType = 10;
        else if(Card[0] == Card[1] - 1 &&
                Card[1] == Card[2] - 1 &&
                Card[2] == Card[3] - 1 &&
                Card[3] == Card[4] - 1){
            cardType = 9;
            otherRank = Card[4];
        }else if((Card[0] == Card[1] && Card[1] == Card[2] &&
                Card[2] == Card[3] )){
            cardType = 8;
            firstRank = Card[0];
            otherRank = Card[4];
        }else if( Card[1] == Card[2] && Card[2] == Card[3] &&
                 Card[3] == Card[4]){
            cardType = 8;
            firstRank = Card[1];
            otherRank = Card[0];
        }else if(Card[0] == Card[1] && Card[1] == Card[2]){
            firstRank = Card[0];
            if(Card[3] == Card[4]){
                cardType = 7;
                otherRank = Card[3];
            }else{
                cardType = 6;
                otherRank = Card[3] + Card[4];
            }
        }else if(Card[1] == Card[2] && Card[2] == Card[3]){
            firstRank = Card[1];
            if(Card[0] == Card[4]){
                cardType = 7;
                otherRank = Card[0];
            }else{
                cardType = 6;
                otherRank = Card[0] + Card[4];
            }
        }else if(Card[2] == Card[3] && Card[3] == Card[4]){
            firstRank = Card[2];
            if(Card[0] == Card[1]){
                cardType = 7;
                otherRank = Card[0];
            }else{
                cardType = 6;
                otherRank = Card[0] + Card[1];
            }
        }else if(Card[0] == Card[1]){
            if(checkTwo(2,3)){
                firstRank = max(Card[0],Card[2]);
                secondRank = min(Card[0],Card[2]);
                cardType = 5;
                otherRank = Card[4];
            }else if(checkTwo(3,4)){
                firstRank = max(Card[0],Card[3]);
                secondRank = min(Card[0],Card[3]);
                cardType = 5;
                otherRank = Card[2];
            }else if(checkTwo(2,4)){
                firstRank = max(Card[0],Card[2]);
                secondRank = min(Card[0],Card[2]);
                cardType = 5;
                otherRank = Card[3];
            }
            else{
                firstRank = Card[0];
                cardType = 4;
                otherRank = Card[2] + Card[3] + Card[4];
            }
        }else if(checkTwo(1,2)){
            if(checkTwo(0,3)){
                firstRank = max(Card[1],Card[0]);
                secondRank = min(Card[1],Card[0]);
                cardType = 5;
                otherRank = Card[4];
            }else if(checkTwo(0,4)){
                firstRank = max(Card[1],Card[0]);
                secondRank = min(Card[1],Card[0]);
                cardType = 5;
                otherRank = Card[2];
            }else if(checkTwo(3,4)){
                firstRank = max(Card[1],Card[3]);
                secondRank = min(Card[1],Card[3]);
                cardType = 5;
                otherRank = Card[0];
            }else{
                firstRank = Card[1];
                cardType = 4;
                otherRank = Card[0] + Card[3] + Card[4];
            }
        }else if(checkTwo(2,3)){
            if(checkTwo(0,1)){
                firstRank = max(Card[0],Card[2]);
                secondRank = min(Card[0],Card[2]);
                cardType = 5;
                otherRank = Card[4];
            }else if(checkTwo(0,4)){
                firstRank = max(Card[0],Card[2]);
                secondRank = min(Card[0],Card[2]);
                cardType = 5;
                otherRank = Card[1];
            }else if(checkTwo(1,4)){
                firstRank = max(Card[1],Card[2]);
                secondRank = min(Card[1],Card[2]);
                cardType = 5;
                otherRank = Card[0];
            }else{
                firstRank = Card[2];
                cardType = 4;
                otherRank = Card[0] + Card[1] + Card[4];
            }
        }else if(checkTwo(3,4)){
            if(checkTwo(0,1)){
                firstRank = max(Card[0],Card[3]);
                secondRank = min(Card[0],Card[3]);
                cardType = 5;
                otherRank = Card[2];
            }else if(checkTwo(0,2)){
                firstRank = max(Card[0],Card[3]);
                secondRank = min(Card[0],Card[3]);
                cardType = 5;
                otherRank = Card[1];
            }else if(checkTwo(1,2)){
                firstRank = max(Card[3],Card[1]);
                secondRank = min(Card[3],Card[1]);
                cardType = 5;
                otherRank = Card[0];
            }else{
                firstRank = Card[3];
                cardType = 4;
                otherRank = Card[0] + Card[1] + Card[2];
            }
        }else {
            cardType = 1;
            otherRank = Card[0] + Card[1] + Card[2] + Card[3] + Card[4];
        }
    }

    void doIt(void){
        char t[20];
        cardType = 0;firstRank = 0;secondRank = 0;otherRank = 0;
        cin>>name>>t;
        int length = strlen(t);
        for(int i = 0 ; i < length ; i++){
            if(t[i] == 'A') Card.push_back(1);
            else if(t[i] == 'J') Card.push_back(11);
            else if(t[i] == 'Q') Card.push_back(12);
            else if(t[i] == 'K') Card.push_back(13);
            else if(t[i] == '1' && t[i+1] == '0'){
                Card.push_back(10);
                i++;
            }
            else Card.push_back(t[i] - '0');
        }
        sort(Card.begin(),Card.end());
        getIndex();
    }
}poi;

void solve(void){
    std::ios::sync_with_stdio(false);
    int n;
    while(cin>>n){
        vector<poi>haha(n);
        for(int i = 0 ; i < n ; i++)
            haha[i].doIt();
        sort(haha.begin(),haha.end());
        for(int i = 0 ; i < n ; i++)
            cout<<haha[i].name<<endl;
    }
}

int main(void){
    solve();
    return 0;
}
