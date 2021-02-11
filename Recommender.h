#include<math.h>
#include "MatrixBuilder.h"
#include "util/MaxHeap.h"
using namespace std;

class Recommender{
    typedef vector< pair<string, double> > scorevec;
    
    public:
    Recommender(string user):user(user){
        
        MatrixBuilder builder;
        m = builder.from_file();
        //builder.test();
    }

    stack<pair<string,double>> get_recommendations(stack<pair<string,double>>& recommendations, int n){
        MaxHeap heap(m->colSize());
        vector<int> user_ratings = m->getrowvals(user);
        vector<string> anime = m->colMemberNames();
        vector<string> neighbours;
        
        get_nearest_neighbours(neighbours, (int)ceil(0.1*m->rowSize()));
        

        for(int i=0; i<user_ratings.size(); i++){
            if( user_ratings[i] == 0){
                double r = predict_rating(i, neighbours);
                if(r!=0)
                    heap.insert( anime[i], r );
            }
        }
        // cout << "\n\n";
        while(--n >= 0 && !heap.empty()){
            HeapNode h = heap.extractMax();
            recommendations.push(make_pair(h.name, h.score > 10 ? 10: h.score));
        }

        return recommendations;
    }

    private:
        string user;
        SparseMatrix<string>* m;

        void get_nearest_neighbours(vector<string>& names, int k){
            MaxHeap heap( m->rowMemberNames().size() );
            vector<int> user_list = m->getrowvals(user);

            for(string& s: m->rowMemberNames()){
                if(s==user)
                    continue;
                vector<int> values = m->getrowvals(s);
                heap.insert( s, cosine_similarity(user_list, values) );
            }
            while(--k >= 0)
                names.push_back(heap.extractMax().name);
            
        }

        double cosine_similarity(vector<int>& a,vector<int>& b){
                int product = 0, onesquare = 0, twosquare = 0;
                for(int i=0; i<a.size(); i++){
                    product += (int)a[i]*b[i];
                    onesquare += (int)a[i]*a[i];
                    twosquare += (int)b[i]*b[i];
                }
                if(product == 0)
                    return 0;
                return product / (sqrt(onesquare) * sqrt(twosquare));
        }

        double predict_rating(int idx, vector<string> neighbours){
            double score = 0.0;
            int count = 0;
            for(string& name: neighbours){
                vector<int> ratings = m->getrowvals(name); 
                if(ratings[idx] != 0){
                    score += ratings[idx] - user_avg(ratings);
                    count++;
                }
                
            }
            vector<int> u = m->getrowvals(user);
            if(count > 0){
                score /= count;
                score += user_avg(u);   
            }
            return score;
        }

        double user_avg(vector<int>& u){
            double avg = 0.0;
            int count =0;
            for(int& d: u){
                if(d != 0){
                    avg += d;
                    count++;
                }
            }
            return avg/count;
        }
};