#pragma once

#include <memory>
#include <string>
#include <string_view>

namespace recipe_10_02 {
// The original class is in recipe 10.02 and is called oldcontrol.

// 1. Put all private members, both data and functions, into a separate class.
// We
// will call this the pimpl class and the original class the public class.

// 2. In the header file of the public class, put a forward declaration to the
// pimpl class:
class control_pimpl;

class control {
  // 3. In the public class definition, declare a pointer to the pimpl class using
  // a unique_ptr. This should be the only private data member of the class:
  std::unique_ptr<control_pimpl, void (*)(control_pimpl *)> pimpl;

public:
  control();
  void set_text(std::string_view text);
  void resize(int const w, int const h);
  void show();
  void hide();
};

class control_copyable {
  std::unique_ptr<control_pimpl, void (*)(control_pimpl *)> pimpl;

public:
  control_copyable();

  control_copyable(control_copyable &&op) noexcept;
  control_copyable &operator=(control_copyable &&op) noexcept;

  control_copyable(const control_copyable &op);
  control_copyable &operator=(const control_copyable &op);

  void set_text(std::string_view text);
  void resize(int const w, int const h);
  void show();
  void hide();
};
}
