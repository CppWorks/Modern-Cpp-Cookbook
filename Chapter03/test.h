#include <functional>
#include <iostream>

namespace test {
  int Func(int a, int b)
  {
    return a + b;
  }

  struct S {
    void operator()(int a)
    {
      std::cout << a << '\n';
    }
  };

  void execute()
  {
    std::cout << std::__invoke(Func, 10, 20) << '\n'; // 30
    std::__invoke(S(), 42);                           // 42
    std::__invoke([]() { std::cout << "hello\n"; });  // hello
  }
}
