#include <iostream>
#include <tuple>
#include <memory>
#include <utility>
#include <typeinfo>

template <class... T>
struct mp_list {
};

// C++11 stype simple metafunction
template <class T>
using add_pointer = T*;
template <class T>
using add_reference = T&;
template <class T>
using add_const = const T;

// Rename
template <class A, template <class...> class B>
struct mp_rename_impl;
template <template <class...> class A, class... T, template <class...> class B>
struct mp_rename_impl<A<T...>, B> {
    using type = B<T...>;
};
template <class A, template <class... T> class B>
using mp_rename = typename mp_rename_impl<A, B>::type;

// Size
template <class T>
struct mp_sizeof_impl;
template <class... T>
struct mp_sizeof_impl<mp_list<T...>> {
    using type = std::integral_constant<std::size_t, sizeof...(T)>;
};
template <class T>
using mp_sizeof = typename mp_sizeof_impl<T>::type;

// Transform
template <class A, template <class... T> class B>
struct mp_transform_impl;
template <template <class... L> class A,
          class... L,
          template <class... T> class B>
struct mp_transform_impl<class A<L...>, B> {
    using type = A<B<L>...>;  // Note the position of "..."
};
template <class A, template <class... T> class B>
using mp_transform = typename mp_transform_impl<A, B>::type;

// Zipwith2
template <template <class U, class V> class BinaryFunc, class A, class B>
struct mp_zipwith2_impl;
template <template <class... L> class A,
          class... L,
          class... R,
          template <class U, class V> class BinaryFunc>
struct mp_zipwith2_impl<BinaryFunc, A<L...>, A<R...>> {
    using type = A<BinaryFunc<L, R>...>;
};
template <template <class U, class V> class BinaryFunc, class A, class B>
using mp_zipwith2 = typename mp_zipwith2_impl<BinaryFunc, A, B>::type;

int main()
{
    std::cout << typeid(mp_list<int, float>).name() << std::endl;
    std::cout << typeid(mp_list<int, float>).name() << std::endl;
    std::cout << typeid(mp_rename<mp_list<int, float>, std::tuple>).name()
              << std::endl;
    std::cout << typeid(mp_sizeof<mp_list<int, float>>).name() << std::endl;
    std::cout << typeid(mp_transform<mp_list<int, float>, add_pointer>).name()
              << std::endl;
    std::cout << typeid(mp_zipwith2<std::pair, mp_list<double, bool, float>,
                                    mp_list<int, float, int>>).name()
              << std::endl;
}
