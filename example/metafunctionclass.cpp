#include <iostream>
#include <typeinfo>

template <class T>
struct add_pointer {
    typedef T* type;
};

struct do_twice_f {
    template <class T, template <class U> class Func>
    struct apply {
        typedef typename Func<typename Func<T>::type>::type type;
    };
};

template <class T, template <class U> class Func>
struct do_twice {
    typedef typename Func<typename Func<T>::type>::type type;
};

int main()
{
    std::cout << typeid(do_twice_f::apply<int, add_pointer>::type).name() << std::endl;
}
