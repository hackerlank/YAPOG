#ifndef YAPOG_MAPAREA_HPP
# define YAPOG_MAPAREA_HPP

# include "YAPOG/Macros.hpp"
# include "YAPOG/Game/World/Map/DynamicWorldObject.hpp"
# include "YAPOG/Graphics/Vector2.hpp"

namespace yap
{
  class MapArea : public DynamicWorldObject
  {
      DISALLOW_ASSIGN(MapArea);

    public:

      virtual ~MapArea ();

    protected:

      explicit MapArea (const ID& id);

      MapArea (const MapArea& copy);

      void SetArea (const FloatRect& area);

    private:

      FloatRect area_;
  };
} // namespace yap

#endif // YAPOG_MAPAREA_HPP
