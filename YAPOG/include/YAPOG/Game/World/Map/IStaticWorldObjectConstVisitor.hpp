#ifndef YAPOG_ISTATICWORLDOBJECTCONSTVISITOR_HPP
# define YAPOG_ISTATICWORLDOBJECTCONSTVISITOR_HPP

# include "YAPOG/Macros.hpp"

namespace yap
{
  class MapElement;

  struct IStaticWorldObjectConstVisitor
  {
      virtual ~IStaticWorldObjectConstVisitor () {}

      virtual void Visit (const MapElement& visitable) = 0;
  };
} // namespace yap

#endif // YAPOG_ISTATICWORLDOBJECTCONSTVISITOR_HPP