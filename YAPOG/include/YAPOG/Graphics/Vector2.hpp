#ifndef YAPOG_VECTOR2_HPP
# define YAPOG_VECTOR2_HPP

# include <SFML/System/Vector2.hpp>

namespace yap
{
  typedef sf::Vector2f Vector2;

  static const Vector2 DEFAULT_POSITION = Vector2 (0.0f, 0.0f);
  static const Vector2 DEFAULT_SIZE = Vector2 (1.0f, 1.0f);

  Vector2 Vector2FromVector2u (const sf::Vector2u& vector2u);
} // namespace yap

#endif // YAPOG_VECTOR2_HPP