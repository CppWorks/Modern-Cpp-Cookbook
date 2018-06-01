#pragma once

// We will see how to avoid if...else statements in factory patterns (a factory
// is a function or object that is used to create other objects) using a map of
// functions.

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <typeinfo>

namespace recipe_10_01 {
using namespace std::string_literals;

class Image {};

class BitmapImage : public Image {};
class PngImage : public Image {};
class JpgImage : public Image {};

// Factory interface:
struct IImageFactory {
  virtual std::shared_ptr<Image> Create(std::string_view type) = 0;
};

struct ImageFactoryClassic : public IImageFactory {
  virtual std::shared_ptr<Image> Create(std::string_view type) override {
    // If the argument to check was an integral type (for instance, an
    // enumeration type), the sequence of if...else could have also be written
    // in the form of a switch statement.

    if (type == "bmp")
      return std::make_shared<BitmapImage>();
    else if (type == "png")
      return std::make_shared<PngImage>();
    else if (type == "jpg")
      return std::make_shared<JpgImage>();

    return nullptr;
  }
};

// 1. Implement the factory interface:
struct ImageFactory : public IImageFactory {
  virtual std::shared_ptr<Image> Create(std::string_view type) override {
    // 2.Define a map where the key is the type of objects to create and the
    // value is a function that creates objects ((a shared_ptr of a derived
    // class is implicitly converted to a shared_ptr of a base class):
    static std::map<std::string, std::function<std::shared_ptr<Image>()>>
        mapping{{"bmp", []() { return std::make_shared<BitmapImage>(); }},
                {"png", []() { return std::make_shared<PngImage>(); }},
                {"jpg", []() { return std::make_shared<JpgImage>(); }}};

    // 3.To create an object, look up the object type in the map and, if it is
    // found, use the associated function to create a new instance of the
    // type:
    auto it = mapping.find(type.data());
    if (it != mapping.end())
      return it->second();

    return nullptr;
  }
};

struct IImageFactoryByType {
  virtual std::shared_ptr<Image> Create(std::type_info const &type) = 0;
};

struct ImageFactoryByType : public IImageFactoryByType {
  virtual std::shared_ptr<Image> Create(std::type_info const &type) override {
    auto it = mapping.find(&type);
    if (it != mapping.end())
      return it->second();

    return nullptr;
  }

private:
  // The map is defined as a static member of the class, and the objects are
  // not created based on the format name, but on the type information, as
  // returned by the typeid operator:
  static std::map<std::type_info const *,
                  std::function<std::shared_ptr<Image>()>>
      mapping;
};

std::map<std::type_info const *, std::function<std::shared_ptr<Image>()>>
    ImageFactoryByType::mapping{
        {&typeid(BitmapImage),
         []() { return std::make_shared<BitmapImage>(); }},
        {&typeid(PngImage), []() { return std::make_shared<PngImage>(); }},
        {&typeid(JpgImage), []() { return std::make_shared<JpgImage>(); }}};

void execute() {
  std::cout << "Recipe 10.01: Avoiding repetitive if...else statements in "
               "factory patterns.\n"
            << "-------------------------------------------------------------"
               "--------------\n";

  {
    std::cout << "Creating a png (classic style).\n";
    auto factory = ImageFactoryClassic{};
    auto image = factory.Create("png");
  }

  {
    std::cout << "\nCreating a png (function map style).\n";
    auto factory = ImageFactory{};
    auto image = factory.Create("png");
  }

  {
    std::cout << "\nCreating a png (function map style using type instead of "
                 "string).\n";
    auto factory = ImageFactoryByType{};
    auto movie = factory.Create(typeid(PngImage));
  }
}
}
