#pragma once

#include <string>
#include <memory>
#include <sys/types.h>
#include <dirent.h>

class Directory
{
  private:

  public:
    std::unique_ptr<DIR, decltype(&closedir)> music_directory_ {
      opendir(std::format("{}{}", std::getenv("HOME"), "/music").c_str()), &closedir}; 
};
