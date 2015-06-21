#include <iostream>

template<class ...T>
struct add_return;

template<class T>
struct add_return<T>{
    using resulttype = T;
};

template<class T,class ...U>
struct add_return<T,U...>{
    using resulttype = decltype(T()+typename add_return<U...>::resulttype());
};

template<class T>
T add(T a){
    return a;
}

template<class T, class ...U>
typename add_return<T,U...>::resulttype add(T a, U... b){
    return a + add(b...);
}

int main()
{
    std::cout << add(3,33,5,3.3)<< std::endl;
}
