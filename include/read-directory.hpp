#pragma once

#include <string>
#include <memory>
#include <sys/types.h>
#include <dirent.h>
#include <span>

class Directory
{
  private:
    auto OpenDirectory(const char* music_directory) const 
      -> std::unique_ptr<DIR, decltype(&closedir)>;

    std::unique_ptr<DIR, decltype(&closedir)> music_directory_ {
      opendir(std::format("{}{}", std::getenv("HOME"), "/music").c_str()), &closedir}; 
  
  public:
    explicit Directory(const char* music_directory)
      : music_directory_{OpenDirectory(music_directory)} {}
    
   auto GetDirectoryContents() -> std::span<dirent>;
};
