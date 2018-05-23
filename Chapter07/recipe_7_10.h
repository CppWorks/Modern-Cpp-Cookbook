#pragma once

#include <cassert>
#include <chrono>
#include <experimental/filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace fs = std::experimental::filesystem;

namespace recipe_7_10 {
  void execute()
  {
    std::cout
      << "\nRecipe 7.10: Checking the properties of an existing file or directory."
      << "\n----------------------------------------------------------------------\n\n";

    auto path = fs::current_path() / "sample.plays";
    auto err = std::error_code{};

    // file exists
    {
      std::cout << "To check whether a path refers to an existing filesystem object, use exists():\n";
      auto exists = fs::exists(path, err);
      std::cout << "file exists: " << std::boolalpha << exists << std::endl;
    }

    // paths equivalent
    {
      std::cout << "\nTo check whether two different paths refer to the same filesystem object, use equivalent():\n";
      auto same = fs::equivalent(path, fs::current_path() / "." / "main.cpp");

      std::cout << "equivalent: " << same << std::endl;
    }

    // file size
    {
      std::cout << "\nTo retrieve the size of a file in bytes, use file_size():\n";
      auto size = fs::file_size(path, err);
      std::cout << "file size: " << size << std::endl;
    }

    // number of hard links
    {
      std::cout << "\nTo retrieve the count of hard links to a filesystem object, use hard_link_count():\n";
      auto links = fs::hard_link_count(path, err);
      if (links != static_cast<uintmax_t>(-1))
        std::cout << "hard links: " << links << std::endl;
      else
        std::cout << "hard links: error" << std::endl;
    }

    // last write time
    {
      std::cout << "\nTo retrieve or set the last modification time for a filesystem object, use last_write_time():\n";
      auto lwt = fs::last_write_time(path, err);
      auto time = decltype(lwt)::clock::to_time_t(lwt);
      auto localtime = std::localtime(&time);

      std::cout << "last write time: " << std::put_time(localtime, "%c") << std::endl;

      // modify last write time
      {
        using namespace std::chrono_literals;

        fs::last_write_time(path, lwt - 30min);

        lwt = fs::last_write_time(path, err);
        time = decltype(lwt)::clock::to_time_t(lwt);
        localtime = std::localtime(&time);

        std::cout << "last write time: " << std::put_time(localtime, "%c") << std::endl;
      }
    }

    // status
    {
      std::cout << "\nTo retrieve POSIX file attributes, such as type and permissions, use "
                   "the status() function. This function follows symbolic links. To "
                   "retrieve the file attributes of a symbolic link without following "
                   "it, use symlink_status():\n";
      auto print_perm = [](fs::perms p) {
        std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
                  << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
                  << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
                  << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
                  << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
                  << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
                  << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
                  << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
                  << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
                  << std::endl;
      };

      auto status = fs::status(path, err);
      std::cout << "type: " << static_cast<int>(status.type()) << std::endl;
      std::cout << "permissions: ";
      print_perm(status.permissions());
    }

    // file types
    {
      std::cout << "\nTo check whether a path refers to a particular type of filesystem "
                   "object, such as file, directory, symbolic link, and so on, use "
                   "functions is_regular_file(), is_directory(), is_symlink(), and so "
                   "on:\n";
      std::cout << "regular file? " << fs::is_regular_file(path, err) << std::endl;
      std::cout << "directory? " << fs::is_directory(path, err) << std::endl;
      std::cout << "char file? " << fs::is_character_file(path, err) << std::endl;
      std::cout << "symlink? " << fs::is_symlink(path, err) << std::endl;
    }
  }
}
