#ifndef sparsematrix
#define sparsematrix

#include<vector>
using namespace std;

template<class T>
struct Node{
    T col;
    T row;
    int val;
    Node* right;
    Node* down;
    Node(T x, T y, int val):
        col(x),
        row(y),
        val(val),
        right(NULL),
        down(NULL){}
};
template<class T>
struct header{
    T name;
    header* next;
    Node<T>* first;
    header():next(NULL), first(NULL) {}
    header(T n):
        name(n),
        next(NULL),
        first(NULL){}
};

template<class T>
class SparseMatrix{
    header<T>* row;
    header<T>* col;

    void insert_header(header<T>* h, header<T>* n){
        header<T>* prev=h;
        h = h->next;
        while(h && h->name < n->name){
            prev = h;
            h = h->next;
        }
        if(!h){
            prev->next = n;
        }
        else{
            n->next = h;
            prev->next = n;
        }
    }

    public:
    SparseMatrix(){
        row = new header<T>();
        col = new header<T>();
    }

    void add_node(T x, T y, int val){
        
        header<T>* r = row, *c = col;        
        Node<T> *node = new Node<T>(x,y,val), *cur, *prev=NULL;

        //Find row
        while(r && r->name != x)
            r = r->next;

        //Find column
        while(c && c->name != y)
            c = c->next;
        

        //Traverse row
        cur = r->first;
        while(cur){
            if(cur->row == y){
                cur->val = val;
                return;
            }
            
            if(cur->row > y)
                break;
            prev = cur;
            cur = cur->right;
        }
        //Connect node
        if(!prev){
            node->right = r->first;
            r->first = node;
        }
        else{
            node->right = prev->right;
            prev->right = node;
        }
        
        
        //Traverse column
        cur = c->first;
        prev = NULL;
        while(cur){
            if(cur->col == x){
                cur->val = val;
                return;
            }
            if(cur->col > x)
                break;
            prev = cur;
            cur = cur->down;
        }
        //Connect node
        if(!prev){
            node->down = c->first;
            c->first = node;
        }
        else{
            node->down = prev->down;
            prev->down = node;
        }
    }
    void insert_row(T n){
        insert_header(row, new header<T>(n));
    }

    void insert_col(T n){
        insert_header(col, new header<T>(n));
    }
    int getcell(T x, T y){
        header<T>* r = row;
        while(r && r->name != x)
            r = r->next;
        if(!r)
            return -1;
        Node<T>* n = r->first;
        while(n && n->row != y)
            n = n->right;
            
        if(n)
            return n->val;
        return -1;
    }
    vector<int> getrowvals(T name){
        vector<int> src;
        header<T> *r = row;
        header<T> *c = col->next;
        //Find rows
        while(r && r->name != name)
            r = r->next;
        if(!r)
            return src;
        
        Node<T> *t = r->first;
        while(t){
            while(c && c->name != t->row){
                    src.push_back(0);
                    c = c->next;
                }
            src.push_back(t->val);
            t = t->right;
            c = c->next;
        }
        while(c){
            src.push_back(0);
            c = c->next;
        }
        return src;
    }

    vector<string> rowMemberNames(){
        vector<string> n;
        header<T> *r = row->next;
        while(r){
            n.push_back(r->name);
            r = r->next;
        }
        return n;
    }
    vector<string> colMemberNames(){
        vector<string> n;
        header<T> *c = col->next;
        while(c){
            n.push_back(c->name);
            c = c->next;
        }
        return n;
    }

    int rowSize(){
        int count=0;
        header<T> *r = row->next;
        while(r){
            r = r->next;
            count++;
        }
        return count;
    }

    int colSize(){
        int count=0;
        header<T> *c = col->next;
        while(c){
            c = c->next;
            count++;
        }
        return count;
    }
    void printbyrow(){        
        header<T>* temp = row->next;
        Node<T>* n;
        cout << "R\n";
        while(temp){
            cout << temp->name << "--> ";
            n = temp->first;
            while(n){
                cout << '(' << n->col << ',' << n->row << ',' << n->val << ')' << "-> ";
                n = n->right;
            }
            temp = temp->next;
            cout << '\n';
        }
    }
};
#endif