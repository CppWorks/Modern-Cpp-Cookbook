#pragma once

#include <cstring>
#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

namespace recipe_7_01 {
  bool write_data(char const* const filename, char const* const data, size_t const size)
  {
    auto success = false;
    std::ofstream ofile(filename, std::ios::binary);

    if (ofile.is_open()) {
      try {
        ofile.write(data, size);
        success = true;
      } catch (std::ios_base::failure&) {
        // handle the error
      }
      ofile.close();
    }

    return success;
  }

  size_t read_data(char const* const filename,
                   std::function<char*(size_t const)> allocator)
  {
    size_t readbytes = 0;
    std::ifstream ifile(filename, std::ios::ate | std::ios::binary);
    if (ifile.is_open()) {
      auto length = static_cast<size_t>(ifile.tellg());
      ifile.seekg(0, std::ios_base::beg);

      auto buffer = allocator(length);

      try {
        ifile.read(buffer, length);

        readbytes = static_cast<size_t>(ifile.gcount());
      } catch (std::ios_base::failure&) {
        // handle the error
      }

      ifile.close();
    }

    return readbytes;
  }

  void execute()
  {
    std::cout << "Recipe 7.01: Reading and writing raw data from/to binary files.\n"
              << "---------------------------------------------------------------\n";

    std::vector<unsigned char> output{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    {
      std::cout << "\nWrite the content of a buffer to a binary file:\n";

      // To write the content of a buffer to a binary file:

      // 1. Open a file stream for writing in binary mode:
      // To append content to an existing file, use 'std::ios::app | std::ios::binary'
      std::ofstream ofile("sample.bin", std::ios::binary);
      // 2. Ensure that the file is actually open:
      if (ofile.is_open()) {
        // 3. Write the data to the file by providing a pointer to the array of characters
        // and the number of characters to write:
        // Since the write method operates with strings of characters, a reinterpret_cast
        // is necessary if data is of another type, such as unsigned char in our example.
        // The write operation does not set a fail bit on failure, but may throw an
        // std::ios_base::failure exception.
        ofile.write(reinterpret_cast<char*>(output.data()), output.size());
        // Flush the content of the stream buffer to the actual disk file:
        ofile.close();
      }
    }

    {
      //  Compared to the others it is the fastest method, even though the alternatives
      //  may look more appealing from an object-oriented perspective.

      std::cout << "\nRead the content of a buffer to a binary file:\n";

      // To read the entire content of a binary file to a buffer:

      std::vector<unsigned char> input;

      // 1. Open a file stream to read from a file in the binary mode:
      std::ifstream ifile("sample.bin", std::ios::binary);
      // 2. Ensure that the file has been opened:
      if (ifile.is_open()) {
        // 3. Determine the length of the file by positioning the input position indicator
        // to the end of the file, read its value, and then move the indicator to the
        // beginning:
        // Calling seekg() to move the position indicator to the end can be avoided by
        // opening the file with the position indicator moved directly to the end. This
        // can be achieved using the std::ios::ate opening flag in the constructor (or the
        // open() method).
        ifile.seekg(0, std::ios_base::end);
        auto length = ifile.tellg();
        ifile.seekg(0, std::ios_base::beg);

        // 4. Allocate memory to read the content of the file:
        input.resize(static_cast<size_t>(length));
        // 5. Read the content of the file to the allocated buffer:
        ifile.read(reinterpret_cast<char*>(input.data()), length);

        // 5. Check that the read operation is completed successfully:
        assert(!ifile.fail() && length == ifile.gcount());

        // 6. Close the file stream:
        ifile.close();
      }

      std::cout << "Input and Output are " << (output == input ? "equal." : "not equal.") << std::endl;
    }

    {
      std::cout << "\nUse streams in vector constructor:\n";

      std::vector<unsigned char> input;

      std::ifstream ifile("sample.bin", std::ios::binary);
      if (ifile.is_open()) {
        input = std::vector<unsigned char>(std::istreambuf_iterator<char>(ifile), // from
                                           std::istreambuf_iterator<char>());     // to
        ifile.close();
      }

      std::cout << "Input and Output are " << (output == input ? "equal." : "not equal.") << std::endl;
    }

    {
      std::cout << "\nUse std::assign to read into vector:\n";

      std::vector<unsigned char> input;

      std::ifstream ifile("sample.bin", std::ios::binary);
      if (ifile.is_open()) {
        ifile.seekg(0, std::ios_base::end);
        auto length = ifile.tellg();
        ifile.seekg(0, std::ios_base::beg);

        input.reserve(static_cast<size_t>(length));
        input.assign(std::istreambuf_iterator<char>(ifile), // from
                     std::istreambuf_iterator<char>());     // to
        ifile.close();
      }

      std::cout << "Input and Output are "  << (output == input ? "equal." : "not equal.") << std::endl;
    }

    {
      std::cout << "\nUse std::copy to read into vector:\n";

      std::vector<unsigned char> input;

      std::ifstream ifile("sample.bin", std::ios::binary);
      if (ifile.is_open()) {
        ifile.seekg(0, std::ios_base::end);
        auto length = ifile.tellg();
        ifile.seekg(0, std::ios_base::beg);

        input.reserve(static_cast<size_t>(length));
        std::copy(std::istreambuf_iterator<char>(ifile), std::istreambuf_iterator<char>(),
                  std::back_inserter(input));
        ifile.close();
      }

      std::cout << "Input and Output are "  << (output == input ? "equal." : "not equal.") << std::endl;
    }

    {
      std::cout << "\nUse custom read and write function from and to vector:\n";

      std::vector<unsigned char> input;

      if (write_data("sample.bin", reinterpret_cast<char*>(output.data()),
                     output.size())) {
        if (read_data("sample.bin",
                      [&input](size_t const length) {
                        input.resize(length);
                        return reinterpret_cast<char*>(input.data());
                      })
            > 0) {
          std::cout << "Input and Output are "  << (output == input ? "equal." : "not equal.") << std::endl;
        }
      }
    }

    {
      std::cout << "\nUse custom read and write function from and to memory:\n";

      unsigned char* input = nullptr;
      size_t readb = 0;

      if (write_data("sample.bin", reinterpret_cast<char*>(output.data()),
                     output.size())) {
        if ((readb = read_data("sample.bin",
                               [&input](size_t const length) {
                                 input = new unsigned char[length];
                                 return reinterpret_cast<char*>(input);
                               }))
            > 0) {
          std::cout << "Input and Output are " << (memcmp(output.data(), input, output.size()) == 0 ? "equal."
                                                                         : "not equal.")
                    << std::endl;
        }
      }

      delete[] input;
    }
  }
}
