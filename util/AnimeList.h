#include <cstring>
#include <string>
#include <stack>
#include <vector>
#include <set>
#define MIN(x,y) ((x) < (y) ? (x) : (y)) //calculate minimum between two values
using namespace std;



class AnimeList{
    public:
    AnimeList(const vector<string>& l):list(l),i(0){}
    int show(){
        char input='n';
        int c = -1;
        while(input!='e' && input!='c'){
            cls;
            cout<<RED<<"n = Next Page \t p = Previous Page \t s = Search\t c = Choose\t e = Return\n"<<RESET;
            //cout<<MAGENTA;
            switch(input){
                case 'n':{   next(); break;  }
                case 'p':{   prev(); break;  }
                case 's':{   search(); break;}
            }
            cin >> input;
            cout<<RESET;
        }
        if(input=='c'){
            cout << "choice: ";
            cin >> c;
        }
        return c;
    }

    private:
    const uint INTERVAL = 10;
    const vector<string>& list;
    int i;
    void next(){
        if(i < list.size())
            i += INTERVAL;

        for(int j=i-INTERVAL; j<i; j++){
            if(j>=list.size())
                break;
            cout << j <<". "<< list[j] << '\n';
        }
        
    }
    void prev(){
        if(i>=2*INTERVAL)
            i -= INTERVAL;
            
        int j=i-INTERVAL;
        for(j; j<i; j++){
            if(j>=list.size())
                break;
            cout << j << ". "<<list[j] << '\n';
        }
    }

    void search(){
        string in;
        cout << "Search: ";
        cin.ignore();
        getline(cin, in);
        double scores[5] = {0};
        int ids[5] = {0};
        int id=0;
        for(int i=0; i<list.size(); i++){
            double score = dice_match(list[i], in);
            for(int j=0;j<5; j++){
                if(scores[j] < score){
                    scores[j] = score;
                    ids[j] = i;
                    break;
                }
            }
        }
        for(int i=0; i<5; i++)
            cout << ids[i] << ". " << list[ids[i]] << '\n';
    }
    double dice_match(const string s1, string s2) {
        //check fast cases
        if(s1 == s2)
            return 1;
        if(s1.length() < 2 || s2.length() < 2)
            return 0;
        
        set<string> s1_bigrams;
        set<string> s2_bigrams;
        set<string> temp;

        for(uint i = 0; i < (s1.length() - 1); i++)       // extract character bigrams from string1
                s1_bigrams.insert(s1.substr(i, 2));
        for(uint i = 0; i < (s2.length() - 1); i++)      // extract character bigrams from string2
                s2_bigrams.insert(s2.substr(i, 2));

        double matches = 0;
        int i = 0, j = 0;

        //get bigrams and compare
        for(const string &a : s1_bigrams){
            for(string b : s2_bigrams){
                // cout << a << ':' << b << endl;
                if(strncasecmp(a.c_str(), b.c_str(), 2) == 0){
                    matches += 2;
                    temp.insert(b);
                }
            }
            for(string b : temp)
                s2_bigrams.erase(b);
        }
        
        return matches / (s1.length() + s2.length() - 2);
    }
};