#include "YAPOG/Game/Pokemon/Pokemon.hpp"
#include "YAPOG/Game/Factory/XmlObjectIDLoader.hpp"
#include "YAPOG/Game/Factory/ObjectFactory.hpp"

namespace yap
{
  const UInt16 Pokemon::POKEMON_INITIAL_LEVEL = 1;

  Pokemon::Pokemon (const ID& staticID)
    : staticID_ (staticID)
  {
    pokemonInfo_ = ObjectFactory::Instance ().
      Create<PokemonInfo> ("PokemonInfo",  staticID);

    nature_ = ObjectFactory::Instance ().
      Create<NatureInfo> ("NatureInfo",  ID (2));

    level_ = Pokemon::POKEMON_INITIAL_LEVEL;

    stats_.ComputeStats (*pokemonInfo_, level_, *nature_);
    type_.SetType1 (ID (pokemonInfo_->GetType1 ()));
    type_.SetType2 (ID (pokemonInfo_->GetType2 ()));
  }

  Pokemon::Pokemon (const ID& staticID, const UInt16& level, const bool& shiny)
    : staticID_ (staticID_)
    , level_ (level)
    , shiny_ (shiny)
  {
    pokemonInfo_ = ObjectFactory::Instance ().
      Create<yap::PokemonInfo> ("PokemonInfo",  staticID);

    nature_ = ObjectFactory::Instance ().
      Create<NatureInfo> ("NatureInfo",  ID (1));

    stats_.ComputeStats (*pokemonInfo_, level_, *nature_);
    type_.SetType1 (ID (pokemonInfo_->GetType1 ()));
    type_.SetType2 (ID (pokemonInfo_->GetType2 ()));
  }

  void Pokemon::PrintStats ()
  {
    //pokeInfo_->PrintBaseStats ();

    std::cout
      << "---------------------------------------------" << std::endl
      << "              Current Statistics" << std::endl
      << "---------------------------------------------" << std::endl
      << "Level: " << level_ << std::endl
      << "Nature: " << nature_->GetName () << std::endl
      << "Type1: " << type_.GetType1 ().GetName () << std::endl
      << "Type2: " << type_.GetType2 ().GetName () << std::endl
      << "Current HP: " << stats_.GetHitPoint ().GetCurrentValue () << std::endl
      << "Max HP: " << stats_.GetHitPoint ().GetValue () << std::endl
      << "Attack: " << stats_.GetAttack ().GetValue () << std::endl
      << "Defense: " << stats_.GetDefense ().GetValue () << std::endl
      << "Special Attack: " << stats_.GetSpecialAttack ().GetValue () << std::endl
      << "Special Defense: " << stats_.GetSpecialDefense ().GetValue () << std::endl
      << "Speed: " << stats_.GetSpeed ().GetValue () << std::endl;
  }
}