#ifndef YAPOG_CLIENT_MAP_HPP
# define YAPOG_CLIENT_MAP_HPP

# include "YAPOG/Game/World/Map/Map.hpp"

class Map : public yap::Map
{
  public:

    Map (const yap::ID& id);
    virtual ~Map ();
};

#endif // YAPOG_CLIENT_MAP_HPP
