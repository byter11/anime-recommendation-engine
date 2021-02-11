#ifndef database
#define database

#include<fstream>
#include<vector>
#include<jsoncpp/json/json.h>
#include<cpr/cpr.h>
using namespace std;

class Database{
    Json::Value db;
    fstream file;
    public:
        const Json::Value getdb(){
            return db;
        }
        void save(){
            file = fstream("db.json", ios::out);
            file << db;
            file.close();
        }
        string get_anime_details(string anime){
            Json::Value store;
            
            cpr::Response r = cpr::Get(cpr::Url{"https://api.jikan.moe/v3/search/anime?q="+urlify(anime)});
            // cout << r.status_code;
            if(r.status_code != 200)
                return "";

            Json::CharReaderBuilder cb;
            Json::CharReader* reader= cb.newCharReader();
            string errors;
            reader->parse(r.text.c_str(), r.text.c_str()+r.text.size(), &store, &errors);
            return store["results"][0]["synopsis"].asString();
        }

        void insert(string name, string anime, int rating){
            db[name][anime] = rating;   
        }
        vector<string> user(string u){
            vector<string> list;
            for(string s: db[u].getMemberNames())
                list.push_back(s);
            return list;
        }
        map<string, int> from_myanimelist(string user, map<string, int>& m){
            Json::Value store;
            
            cpr::Response r = cpr::Get(cpr::Url{"https://api.jikan.moe/v3/user/"+user+"/animelist/all"});
            Json::CharReaderBuilder cb;
            Json::CharReader* reader= cb.newCharReader();
            string errors;
            reader->parse(r.text.c_str(), r.text.c_str()+r.text.size(), &store, &errors);

            for(Json::Value t : store["anime"]){
                if( stoi(t["watched_episodes"].asString()) != 0)
                    m.insert(make_pair(t["title"].asString(), stoi(t["score"].asString())));
            }
                
            return m;
        }
        Json::Value from_file(){
            file = fstream("db.json", ios::in);
            if(!file)
                file = fstream("db.json", ios::out);
            else
                file >> db;
               
            file.close();
            return db;
        }
        vector<string> top100(){
            vector<string> v;
            file = fstream("top100.txt", ios::in);
            if(file){
                string s;
                while(getline(file, s)){
                    v.push_back(s);   
                }
            }
            return v;
        }
        string urlify(const string &s) {
        string r;
        for (char c : s) {
            if (c == ' ')
            r.append("%20");
            else
            r.push_back(c);
        }
        return r;
        }
 
};

#endif