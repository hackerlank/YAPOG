#ifndef YAPOG_POKEMONFIGHTER_HPP
# define YAPOG_POKEMONFIGHTER_HPP

# include "YAPOG/Macros.hpp"
# include "YAPOG/Game/Pokemon/Pokemon.hpp"
# include "YAPOG/Game/Pokemon/PokemonStat.hpp"

namespace yap
{
  class YAPOG_LIB PokemonFighter
  {
  public:
    PokemonFighter (Pokemon* originalPokemon);

    /// @brief Specifics to the Original Pokemon
    /// {
    const String& GetName () const;
    const UInt16& GetLevel () const;
    const Gender& GetGender () const;
    UInt16 GetCurrentHP () const;
    UInt16 GetMaxHP () const;
    const collection::Array<PokemonSkill*>& GetMoves () const;
    float GetTypeEffectFactor (const TypeInfo& type) const;
    /// }

    const Attack& GetAttack () const;
    const Defense& GetDefense () const;
    const SpecialAttack& GetSpecialAttack () const;
    const SpecialDefense& GetSpecialDefense () const;
    const Speed& GetSpeed () const;

    void PrintBattleStats ();
    void PrintStats ();
  private:
    Pokemon* originalPokemon_;
    PokemonStat stats_;

  };
} // namespace yap

#endif // YAPOG_POKEMONFIGHTER_HPP