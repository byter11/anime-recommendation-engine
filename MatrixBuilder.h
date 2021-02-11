#include "SparseMatrix.h"
#include "Database.h"
#include <vector>
using namespace std;

class MatrixBuilder{
    SparseMatrix<string>  *matrix;
    vector<string> animelist;
    
    public:
        MatrixBuilder(){
            matrix = new SparseMatrix<string>();
        }

        SparseMatrix<string>* from_row_list(vector<string> a){
            for(string s: a)
                matrix->insert_row(s);
            return matrix;
        }

        SparseMatrix<string>* from_file(){
            Database db;
            auto root = db.from_file();
            for(auto name : root.getMemberNames()){
                string s = name;
                matrix->insert_row(s);
                for(auto item : root[name].getMemberNames()){
                    if(find(animelist.begin(), animelist.end(), item) == animelist.end()){
                        animelist.push_back(item);
                        matrix->insert_col(item);
                    }
                    
                    matrix->add_node(name, item, root[name][item].asInt());
                }
            }
            return matrix;
        }
        // void test(){
        //     vector<int> s;
        //     sort(animelist.begin(), animelist.end());
        //     matrix->getrowvals("MurtazaboyX", s);
        //     for(int i=0; i<s.size(); i++)
        //         cout << animelist[i] << ' ' << s[i] << '\n';
        // }

};