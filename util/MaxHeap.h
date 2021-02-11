struct HeapNode{
    string name;
    double score;
    HeapNode():score(0){}
    HeapNode(string name, double score):name(name), score(score){}
    bool operator<(HeapNode& h1){
        return score < h1.score;
    }
    bool operator>(HeapNode& h1){
        return score > h1.score;
    }
    bool operator==(HeapNode& h1){
        return score == h1.score;
    }
    bool operator>=(HeapNode& h1){
        return score >= h1.score;
    }
    bool operator<=(HeapNode& h1){
        return score <= h1.score;
    }
};

class MaxHeap{
    HeapNode *arr;
    int capacity;
    int size;

    int parent(int i){
        return (i-1)/2;
    }
    
    void siftup(int i){
        int p = parent(i);
        if(i && arr[p] < arr[i]){
            swap(arr[i], arr[p]);
            siftup(p);
        }
    }
    void siftdown(int i){
        int l = left(i), r = right(i);
        int index = i;

        if(l < size && arr[l] > arr[index])
            index = l;
        if(r < size && arr[r] > arr[index])
            index = r;
        
        if(index != i){
            swap(arr[i], arr[index]);
            siftdown(index);
        }
    }
    public:
    bool empty() {
        return size == 0;
    }
    int left(int p){
        return (2*p)+1;
    }
    int right(int p){
        return (2*p)+2;
    }
    MaxHeap(int c):capacity(c),size(0){
        arr = new HeapNode[capacity];
    }

    void insert(string n, double s){
        arr[size] = HeapNode(n, s);
        siftup(size);
        size++;
    }
    HeapNode extractMax(){
        HeapNode max = arr[0];
        arr[0] = arr[--size];
        siftdown(0);
        return max;
    }

};