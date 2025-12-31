#pragma once

#include <string>
#include <memory>
#include <sys/types.h>
#include <dirent.h>
#include <span>
#include <vector>

class Directory
{
  private:
    auto OpenDirectory(const char* music_directory_path) const 
      -> std::unique_ptr<DIR, decltype(&closedir)>;

    std::unique_ptr<DIR, decltype(&closedir)> music_directory_ {
      opendir(std::format("{}{}", std::getenv("HOME"), "/music").c_str()), &closedir}; 
    std::vector<dirent> found_directories_ ();
  
  public:
    explicit Directory(const char* music_directory_path)
      : music_directory_{OpenDirectory(music_directory_path)} {}
    
   auto GetDirectoryContents() -> std::vector<std::string>;
};
