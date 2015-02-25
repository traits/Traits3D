#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace Traits3D
{
  class Font
  {
  public:
    class Repository
    {
      friend class Font;
    public:
      Repository() {}
      using MapType = std::map < std::string, const Font* > ;
      MapType::mapped_type& at(const MapType::key_type& key){ return map_.at(key); }
      MapType::mapped_type const& at(MapType::key_type&& key) const { return map_.at(key); }

    private:
      Repository(Repository const&) = delete;
      void operator=(Repository const&) = delete;
      MapType map_;
    };

    static Repository& repository();

    Font(const unsigned char* buffer = 0, size_t buflen = 0, std::string fname = std::string())
    :data(buffer, buffer + buflen), name(fname)
    {}
    const std::vector<unsigned char> data;
    const std::string name;  

  private:
    class StandardFonts;
    static void appendFont(const Font* val);
  };

} // ns
