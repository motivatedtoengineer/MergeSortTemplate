#include <iostream>
#include <cassert>
#include <vector>
#include <cstdlib>

using namespace std;

//Defined class for less-than comparison
class Document {
    int priority;
public:
    Document(int priority);
    Document();
    friend bool operator< (const Document &l, const Document &r);
    friend bool operator> (const Document &l, const Document &r);
};

Document::Document(){
    priority = 0;
}

Document::Document(int p){
    priority = p;
}

//less than comparison
bool operator< (const Document &left, const Document &right)
{
    return left.priority < right.priority;
}

//greater than comparison
bool operator> (const Document &left, const Document &right) {
    return left.priority > right.priority;
}

//new function to deal with the sorting
template <class T>
void merge(vector<T> & a, vector<T> & x, int s, int e, int m){
    int i = s;
    int j = m + 1;
    int k = 0;
    
    while(i <= m && j <= e){
        if (a[i] < a[j]){
            x[k] = a[i];
            k++;
            i++;
        }
        else {
            x[k] = a[j];
            k++;
            j++;
        }
    }
    
    while(i <= m){
        x[k] = a[i];
        k++;
        i++;
    }
    
    while (j <= e){
        x[k] = a[j];
        k++;
        j++;
    }
    
    for (i = s; i <= e; i++){
        a[i] = x[i - s];
    }
}

template <class T>
void msort(vector<T> & a, vector<T> & x, int s, int e) {
    if (s >= e){
        return;
    }
    int m = (e + s)/2;
    msort(a, x, s, m);
    msort(a, x, m + 1, e);
    merge(a, x, s, e, m);
}

template<class T>
void merge_sort(vector<T> & v) {
    int n = v.size();
    vector<T> x(n);
    msort(v, x, 0, n - 1);
}

template <class T>
bool sorted(vector<T> & a) {
    for (int i = 0; i < a.size() - 1; ++i) {
        if (a[i] > a[i + 1]){
            return false;
        }
    }
    return true;
}

int main(int argc, char * args[]) {
    vector<int> a(1000);
    
    for (int i = 0; i < 1000; ++i) a[i] = -50 + rand() % 100;
    merge_sort(a);
    assert(sorted(a));
    
    vector<int> b(1001);
    for (int i = 0; i < 1001; ++i) b[i] = -50 + rand() % 100;
    merge_sort(b);
    assert(sorted(b));
    
    vector<int> c(1, 2);
    merge_sort(c);
    assert(sorted(c));
    
    
    vector<int> d (5);
    for (int i = 1; i <= d.size(); i++) d[i] = i;
    merge_sort(d);
    assert(sorted(d));
    
    vector<Document> e(5);

    for (int i = 4; i >= 0; i--) {
        Document doc(i);
        e[i] = doc;
    }
    merge_sort(e);
    assert(sorted(e));
    
    cout << "All tests passed." << endl;
}
