#include <stack>
#include <iomanip>
#include "util/Color.h"
#include "Database.h"
#include "Recommender.h"
#include "util/AnimeList.h"
using namespace std;
class Program{
    string user;
    public:
    void run(){
        cout<<BOLDCYAN
        "         Anime Recommendation Engine                  "<<endl<<
        "               A DS Project by:                       "<<endl<<
        " K19-0304 Umer, K19-1308 Mohsin, K19-0177 Abdul-Rehman"<<endl<<RESET;
        cout << "Login as: ";
        cin >> user;
        int choice=1;
        while(choice==1 || choice==2){
            cls;
            cout <<CYAN<< "1. My Anime List\n2. Get recommendations\n3-9. exit\n"<<RESET;
            cin >> choice;
            if(choice == 1)
                run_db();
            if(choice == 2)
                run_recommender();
        }
    }
    
    void run_db(){
        Database db;
        db.from_file();
        vector<string> anime = db.user(user);
        int choice=1;
        while(choice == 1 || choice == 2){
            cls;
            cout <<YELLOW<< "1. View your list\n2. Rate an anime\n3. Import myanimelist profile\n4-9. To Exit\n"<<RESET;
            cin >> choice;
            if(choice==1){
                AnimeList a(anime);
                int idx;
                cout<<MAGENTA;
                while((idx = a.show()) != -1){
                    string rating = db.getdb()[user][anime[idx]].asString();
                    cls;
                    cout <<RED<< "Title: " << anime[idx] << '\n';
                    cout <<GREEN<< "Rating: " << rating << '\n';
                    cout <<BLUE<< "Synopsis: " << db.get_anime_details(anime[idx]) << '\n'<<RESET;
                    cin.get();
                    cin.ignore();
                }
                cout<<RESET;
            }
            else if(choice==2){
                vector<string> list = db.top100();
                AnimeList a(list);
                int idx = a.show();
                if(idx>=0 && idx<list.size()){
                    int r;
                    cout << "Rating: ";
                    cin >> r;
                    if(0<=r<=10)
                       db.insert(user, list[idx], r);
                }
            }
            else if(choice==3){
                string username;
                cout <<GREEN<< "MyAnimeList username: ";
                cin >> username;
                map<string,int> name_score;
                db.from_myanimelist(username, name_score);
                int i=0;
                for(const auto& p : name_score){
                    db.insert(user, p.first, p.second);
                    i++;
                }
                cout << "Loaded " << i << " Entries\n"<<RESET;
                cin.get();
                cin.ignore();
            }
        }
        db.save();
    }
    void run_recommender(){
        Recommender r(user);
        stack<pair<string,double>> recs;
        r.get_recommendations(recs, 10);
        cls;
        int i=10;
        char c;
        cout<<"\t\tRecommendations depending on your taste:\n";
        cin.clear();
        cin.ignore();
        while(!recs.empty()) 
        {
            cls;
            cout<<BOLDGREEN<<"Recommendation "<<i<<":\n";
            cout<<"Anime Name:\t"<<recs.top().first<<"\nPredicted Rating:\t"<< setprecision(2) <<recs.top().second<<endl;
            recs.pop(); 
            i--;
            cout<<"Press any key to go to next Anime";
            cin.get();
        }
        cout<<RESET;
    }
};
