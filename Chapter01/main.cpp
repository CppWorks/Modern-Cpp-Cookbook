#include "recipe_1_01.h"
#include "recipe_1_02.h"
#include "recipe_1_03.h"
#include "recipe_1_04.h"
#include "recipe_1_05.h"
#include "recipe_1_06.h"
#include "recipe_1_07.h"
#include "recipe_1_08.h"
#include "recipe_1_09.h"
#include "recipe_1_10.h"
#include "recipe_1_11_1.h"
#include "recipe_1_11_2.h"
#include "recipe_1_11_3.h"
#include "recipe_1_12.h"
#include "recipe_1_13.h"

int main()
{
  // Using auto whenever possible
  recipe_1_01::execute();
  // Creating type aliases and alias templates
  recipe_1_02::execute();
  // Understanding uniform initialization
  recipe_1_03::execute();
  // Understanding the various forms of non-static member initialization
  recipe_1_04::execute();
  // Controlling and querying object alignment
  recipe_1_05::execute();
  // Using scoped enumerations
  recipe_1_06::execute();
  // Using override and final for virtual methods
  recipe_1_07::execute();
  // Using range-based for loops to iterate on a range
  recipe_1_08::execute();
  // Enabling range-based for loops for custom types
  recipe_1_09::execute();
  // Using explicit constructors and conversion operators to avoid implicit conversion
  recipe_1_10::execute();
  // call the print functions defined in their translation units
  // Note: the filex_run functions live in the same namespace which does not matter.
  // Using unnamed namespaces instead of static globals
  recipe_1_11_3::execute();
  recipe_1_11::file1_run();
  recipe_1_11::file2_run();
  // Using inline namespaces for symbol versioning
  recipe_1_12::client::execute();
  // Using structured bindings to handle multi-return values
  recipe_1_13::execute();

  return 0;
}
