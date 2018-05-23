#pragma once

#include <cassert>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <string>

#define STRINGIZE_HELPER(x) #x
#define STRINGIZE(x) STRINGIZE_HELPER(x)
#define LINE "Line "s + STRINGIZE(__LINE__) + std::string(": ")

namespace fs = std::experimental::filesystem;
using namespace std::string_literals;

namespace recipe_7_08 {
  void execute()
  {
    std::cout
      << "\nRecipe 7.08: Creating, copying, and deleting files and directories."
      << "\n-------------------------------------------------------------------\n\n";

    std::cout << "Clean directory with 'rm -rf temp'.\n";

    auto err = std::error_code{};
    auto basepath = fs::current_path();
    auto path = basepath / "temp";
    auto filepath = path / "sample.txt";

    std::cout << "path: " << basepath << std::endl;
    // create directories
    {
      std::cout << "Create directories.\n";
      auto success = fs::create_directory(path, err);
      if (err)
        std::cout << LINE << err.message() << std::endl;

      assert(success);

      auto temp = path / "tmp1" / "tmp2" / "tmp3";

      // Failure expected.
      success = fs::create_directory(temp, err);
      if (err)
        std::cout << LINE << err.message() << std::endl;
      assert(!success);

      success = fs::create_directories(temp, err);
      if (err)
        std::cout << LINE << err.message() << std::endl;

      assert(success);
    }

    // move directories
    {
      std::cout << "Move directories.\n";
      auto temp = path / "tmp1" / "tmp2" / "tmp3";
      auto newtemp = path / "tmp1" / "tmp3";

      fs::rename(temp, newtemp, err);
      if (err)
        std::cout << LINE << err.message() << std::endl;
    }

    // rename directories
    {
      std::cout << "Rename directories.\n";
      auto temp = path / "tmp1" / "tmp3";
      auto newtemp = path / "tmp1" / "tmp4";

      fs::rename(temp, newtemp, err);
      if (err)
        std::cout << LINE << err.message() << std::endl;
    }

    // create test file
    {
      std::cout << "Create test file.\n";
      std::ofstream f(filepath);
      f.write("sample", 6);
      f.close();
    }

    // create file link
    {
      std::cout << "Create file link.\n";
      auto linkpath = path / "sample.txt.link";

      fs::create_symlink(filepath, linkpath, err);
      if (err)
        std::cout << LINE << err.message() << std::endl;
    }

    // create directory link
    {
      std::cout << "Create directory link.\n";
      auto linkdir = basepath / "templink";
      fs::create_directory_symlink(path, linkdir, err);
      if (err)
        std::cout << LINE << err.message() << std::endl;
    }

    // copy file
    {
      std::cout << "Copy file.\n";
      // When it comes to copying files, there are two functions that can be used: copy()
      // and copy_file(). copy() also works for directories. copy_file() follows symbolic
      // links. To avoid doing that and copying the actual symbolic link, you must use
      // either copy_symlink() or copy() with the copy_options::copy_symlinks flag.
      auto success = fs::copy_file(filepath, path / "sample.bak", err);
      if (err)
        std::cout << LINE << err.message() << std::endl;

      assert(success);

      fs::copy(filepath, path / "sample.cpy", err);
      if (err)
        std::cout << LINE << err.message() << std::endl;
    }

    // rename a file
    {
      std::cout << "Rename a file.\n";
      auto newpath = path / "sample.log";
      fs::rename(filepath, newpath, err);
      if (err)
        std::cout << LINE << err.message() << std::endl;
    }

    // move a file
    {
      std::cout << "Move a file.\n";
      auto newpath = path / "sample.log";
      fs::rename(newpath, path / "tmp1" / "sample.log", err);
      if (err)
        std::cout << LINE << err.message() << std::endl;
    }

    // copy directory
    {
      std::cout << "Copy directory.\n";
      fs::copy(path, basepath / "temp2" , fs::copy_options::recursive, err);
      if (err)
        std::cout << LINE << err.message() << std::endl;
    }

    // delete file
    {
      std::cout << "Delete file.\n";
      auto success = fs::remove(path / "sample.cpy", err);
      if (err)
        std::cout << LINE << err.message() << std::endl;

      auto linkdir = path / "templink";
      success = fs::remove(linkdir, err);
      if (err)
        std::cout << LINE << err.message() << std::endl;
      assert(!success);
    }

    // remove directories
    {
      std::cout << "Remove directories.\n";
      auto temp = path / "tmp1" / "tmp4";
      auto success = fs::remove(temp, err);
      if (err)
        std::cout << LINE << err.message() << std::endl;

      assert(success);

      success = fs::remove_all(path, err) != static_cast<std::uintmax_t>(-1);
      if (err)
        std::cout << LINE << err.message() << std::endl;

      assert(success);
      success
        = fs::remove_all(basepath / "temp2", err) != static_cast<std::uintmax_t>(-1);
      if (err)
        std::cout << LINE << err.message() << std::endl;

      assert(success);
    }
  }
}
