# Modern-Cpp-Cookbook

## Chapter 1 - Learning Modern Core Language Features
### 1.01 Using auto whenever possible
### 1.02 Creating type aliases and alias templates
### 1.03 Understanding uniform initialization
### 1.04 Understanding the various forms of non-static member initialization
### 1.05 Controlling and querying object alignment
### 1.06 Using scoped enumerations
### 1.07 Using override and final for virtual methods
### 1.08 Using range-based for loops to iterate on a range
### 1.09 Enabling range-based for loops for custom types
### 1.10 Using explicit constructors and conversion operators to avoid implicit conversion
### 1.11 Using unnamed namespaces instead of static globals
### 1.12 Using inline namespaces for symbol versioning
### 1.13 Using structured bindings to handle multi-return values

## Chapter 2 - Working with Numbers and Strings
### 2.01 Converting between numeric and string types
### 2.02 Limits and other properties of numeric types
### 2.03 Generating pseudo-random numbers
### 2.04 Initializing all bits of internal state of a pseudo-random number generator
### 2.05 Creating cooked user-defined literals
### 2.06 Creating raw user-defined literals
### 2.07 Using raw string literals to avoid escaping characters
### 2.08 Creating a library of string helpers
### 2.09 Verifying the format of a string using regular expressions
### 2.10 Parsing the content of a string using regular expressions
### 2.11 Replacing the content of a string using regular expressions
### 2.12 Using string_view instead of constant string references

## Chapter 3 - Exploring Functions
### 3.01 Defaulted and deleted functions
### 3.02 Using lambdas with standard algorithms
### 3.03 Using generic lambdas
### 3.04 Writing a recursive lambda
### 3.05 Writing a function template with a variable number of arguments
### 3.06 Using fold expressions to simplify variadic function templates
### 3.07 Implementing higher-order functions map and fold
### 3.08 Composing functions into a higher-order function
### 3.09 Uniformly invoking anything callable

## Chapter 4 - Preprocessor and Compilation
### 4.01 Conditionally compiling your source code
### 4.02 Using the indirection pattern for preprocessor stringification and concatenation
### 4.03 Performing compile-time assertion checks with static_assert
### 4.04 Conditionally compiling classes and functions with enable_if
### 4.05 Selecting branches at compile time with constexpr if
### 4.06 Providing metadata to the compiler with attributes

## Chapter 5 - Standard Library Containers, Algorithms, and Iterators
### 5.01 Using vector as a default container
### 5.02 Using bitset for fixed-size sequences of bits
### 5.03 Using vector<bool> for variable-size sequences of bits
### 5.04 Finding elements in a range
### 5.05 Sorting a range
### 5.06 Initializing a range
### 5.07 Using set operations on a range
### 5.08 Using iterators to insert new elements in a container
### 5.09 Writing your own random access iterator
### 5.10 Container access with non-member functions

## Chapter 6 - General Purpose Utilities
### 6.01 Expressing time intervals with chrono::duration
### 6.02 Measuring function execution time with a standard clock
### 6.03 Generating hash values for custom types
### 6.04 Using std::any to store any value
### 6.05 Using std::optional to store optional values
### 6.06 Using std::variant as a type-safe union
### 6.07 Visiting a std::variant
### 6.08 Registering a function to be called when a program exits normally
### 6.09 Using type traits to query properties of types
### 6.10 Writing your own type traits
### 6.11 Using std::conditional to choose between types

## Chapter 7 - Working with Files and Streams
### 7.01 Reading and writing raw data from/to binary files
### 7.02 Reading and writing objects from/to binary files
### 7.03 Using localized settings for streams
### 7.04 Using I/O manipulators to control the output of a stream
### 7.05 Using monetary I/O manipulators
### 7.06 Using time I/O manipulators
### 7.07 Working with filesystem paths
### 7.08 Creating, copying, and deleting files and directories
### 7.09 Removing content from a file
### 7.10 Checking the properties of an existing file or directory
### 7.11 Enumerating the content of a directory
### 7.12 Finding a file

## Chapter 8 - Leveraging Threading and Concurrency
### 8.01 Working with threads
### 8.02 Handling exceptions from thread functions
### 8.03 Synchronizing access to shared data with mutexes and locks
### 8.04 Avoiding using recursive mutexes
### 8.05 Sending notifications between threads
### 8.06 Using promises and futures to return values from threads
### 8.07 Executing functions asynchronously
### 8.08 Using atomic types
### 8.09 Implementing parallel map and fold with threads
### 8.10 Implementing parallel map and fold with tasks

## Chapter 9 - Robustness and Performance
### 9.01 Using exceptions for error handling
### 9.02 Using noexcept for functions that do not throw
### 9.03 Ensuring constant correctness for a program
### 9.04 Creating compile-time constant expressions
### 9.05 Performing correct type casts
### 9.06 Using unique_ptr to uniquely own a memory resource
### 9.07 Using shared_ptr to share a memory resource
### 9.08 Implementing move semantics

## Chapter 10 - Implementing Patterns and Idioms
### 10.01 Avoiding repetitive if...else statements in factory patterns
### 10.02 Implementing the pimpl idiom
### 10.03 Implementing the named parameter idiom
### 10.04 Separating interfaces from implementations with the non-virtual interface idiom
### 10.05 Handling friendship with the attorney-client idiom
### 10.06 Static polymorphism with the curiously recurring template pattern
### 10.07 Implementing a thread-safe singleton

## Chapter 11 - Exploring Testing Frameworks
### 11.01 Getting started with Boost.Test
### 11.02 Writing and invoking tests with Boost.Test
### 11.03 Asserting with Boost.Test
### 11.04 Using test fixtures with Boost.Test
### 11.05 Controlling output with Boost.Test
### 11.06 Getting started with Google Test
### 11.07 Writing and invoking tests with Google Test
### 11.08 Asserting with Google Test
### 11.09 Using test fixtures with Google Test
### 11.10 Controlling output with Google Test
### 11.11 Getting started with Catch
### 11.12 Writing and invoking tests with Catch
### 11.13 Asserting with Catch
### 11.14 Controlling output with Catch
