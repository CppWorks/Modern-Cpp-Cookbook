#pragma once

#include <iostream>
#include <string>
#include <vector>

// For checking types.
template <class T>
class TD;

namespace recipe_1_02 {

//  Typical examples of typedef declarations.
typedef unsigned char byte;
typedef unsigned char* pbyte;
typedef int array_t[10];
// typedef void(*fn)(byte, double);

template <typename T>
class foo {
  typedef T value_type;
};

typedef struct {
  int value;
} bar, *pbar;

// this is OK
typedef std::vector<int> vint_t;
vint_t v;

// Typedef declarations cannot be used with templates to create template type aliases. An
// std::vector<T>, for instance, is not a type (std::vector<int> is a type), but a sort of
// family of all types that can be created when the type placeholder T is replaced with an
// actual type.

// This is not possible. A typedef cannot be a template.
// template <class T>
// typedef std::vector<T> vec_t;
// vec_t<int> v;

template <typename T>
using vec_t = std::vector<T>;

template <class T>
class custom_allocator { /* ... */
};

// The driving purpose of the 'using' syntax is to define alias templates.
template <typename T>
using vec_t_ca = std::vector<T, custom_allocator<T>>;

void func(byte b, double d) { std::cout << b << " " << d << std::endl; }

void execute() {
  {
    // In C++11, a type alias is a name for another already declared type, and an alias
    // template is a name for another already declared template. Both of these types of
    // aliases are introduced with a new using syntax.

    using byte = unsigned char;
    using pbyte = unsigned char*;
    using array_t = int[10];
    // That is also consistent with the syntax for declaring std::function objects (e.g.
    // std::function<void(byte, double)> f).
    using fn = void(byte, double);

    byte b{42};
    pbyte pb = new byte[10]{0};
    // max 10 elements, less but not more.
    array_t a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    fn* f = func;
    f(65, 42.0);
  }

  {
    vec_t<int> vi;
    vec_t<std::string> vs;

    // Cannot be initialized as custom allocator is no a real allocator.
    // vec_t_ca<int> ca;

    using intVector = vec_t<int>;
    using stringVector = vec_t<std::string>;

    intVector iv;
    stringVector sv;
  }
}
}  // namespace recipe_1_02
