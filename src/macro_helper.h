/*******************************************************************************
 * Copyright (c) 2017-2018  David Graeff <david.graeff@web.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 */
#pragma once 
/**
 * This file contains some helper templates and macros.
 * - offset_of(&Object::member)
 * - is_base_of_template<Derived, Base> with Base<N> and N -> int
 */

#include <type_traits>
#include <functional>

template<class T>
struct remove_member_pointer {
  typedef T type;
};

template<class Parent, class T>
struct remove_member_pointer<T Parent::*> {
  typedef T type;
};

template<class T>
struct baseof_member_pointer {
  typedef T type;
};

template<class Parent, class T>
struct baseof_member_pointer<T Parent::*> {
  typedef Parent type;
};

template <template <int...> class C, int...Ts>
std::true_type is_base_of_template_impl(const C<Ts...>*);

template <template <int...> class C>
std::false_type is_base_of_template_impl(...);

template <typename T, template <int...> class C>
using is_base_of_template = decltype(is_base_of_template_impl<C>(std::declval<T*>()));

template <template <typename...> class C, typename...Ts>
std::true_type is_base_of_template_impl_f(const C<Ts...>*);

template <template <typename...> class C>
std::false_type is_base_of_template_impl_f(...);

template <typename T, template <typename...> class C>
using is_base_of_template_f = decltype(is_base_of_template_impl_f<C>(std::declval<T*>()));

// We need to determine the offset of c++ class members.
// That's not an easy task to do in compile time.
// This mixture of templates and a macro works for clang with some
// compiler warnings, which we ignore. Gcc is not entirely standard
// conform by allowing dynamic_casts in constant expressions.
#ifdef __GNUC__
template <typename T1, typename T2>
struct offset_of_impl {
    static T2 object;
    static constexpr uintptr_t offset(T1 T2::*member) {
        return uintptr_t(&(offset_of_impl<T1, T2>::object.*member)) - uintptr_t(&offset_of_impl<T1, T2>::object);
    }
};
template <typename T1, typename T2>
T2 offset_of_impl<T1, T2>::object;

template <typename T1, typename T2>
inline constexpr uintptr_t offset_of(T1 T2::*member) {
    return offset_of_impl<T1, T2>::offset(member);
}
#endif
#ifdef __clang__
#pragma GCC diagnostic push
#pragma clang diagnostic ignored "-Wundefined-var-template"
template<typename T> struct declval_helper { static T value; };

#define fold(x) (__builtin_constant_p(x) ? (x) : (x))
template<typename T, typename Z, Z T::*MPtr>
struct offset_helper {
    using TV = declval_helper<T>;
    char for_sizeof[(char *)&(TV::value.*MPtr) - (char *)&TV::value];
};
#pragma GCC diagnostic pop

#define offset_of(TYPE) sizeof(offset_helper<baseof_member_pointer<decltype(TYPE)>::type,remove_member_pointer<decltype(TYPE)>::type,TYPE>::for_sizeof)
#endif

