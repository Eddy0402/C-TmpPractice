#include <iostream>
#include <vector>

using namespace std;

template<class Func, class ...T>
struct accumulate_return;

template<class Func, class T>
struct accumulate_return<Func, T>{
    using type = T;
};

template<class Func, class T,class ...U>
struct accumulate_return<Func, T, U...>{
    using type = decltype(Func()(T(),typename accumulate_return<Func, U...>::type()));
};

template<class Func, class T>
T accumulate(T a){
    return a;
}
template<class Func, class T, class ...U>
typename accumulate_return<Func, T,U...>::type
accumulate (T a, U... b){
    return Func()(a, accumulate<Func>(b...));
}

struct func{
    vector<int> operator() (vector<int> a, vector<int> b){
        a.insert(a.begin(), b.begin(), b.end());
        return a;
    }
};

int main(){
    vector<int> a{2,4,6,3};
    vector<int> b{5,9,8,0};
    vector<int> c{6,-3,6,3};
    for(auto i : accumulate<func>(a,b,c)){
        cout << i << " ";
    }
    cout << endl;
}
