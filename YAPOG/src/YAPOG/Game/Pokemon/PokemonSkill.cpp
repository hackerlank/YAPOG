#include "YAPOG/System/Error/Exception.hpp"
#include "YAPOG/Game/Factory/XmlObjectIDLoader.hpp"
#include "YAPOG/Game/Factory/ObjectFactory.hpp"
#include "YAPOG/Game/Pokemon/PokemonSkill.hpp"

namespace yap
{
  const UInt16 PokemonSkill::DEFAULT_PP_VALUE = 0;
  const UInt16 PokemonSkill::DEFAULT_MAX_PP_VALUE = 0;

  PokemonSkill::PokemonSkill ()
    : currentPP_ (DEFAULT_PP_VALUE)
    , maxPP_ (DEFAULT_MAX_PP_VALUE)
  {
    skillInfo_ = new SkillInfo ();
  }

  PokemonSkill::PokemonSkill (const ID& skillID)
    : currentPP_ (DEFAULT_PP_VALUE)
    , maxPP_ (DEFAULT_MAX_PP_VALUE)
  {
    SetSkillInfo (skillID);
  }

  const String& PokemonSkill::GetName () const
  {
    if (skillInfo_ == nullptr)
      throw Exception ("This skill's base informations doesn't exist !");

    return skillInfo_->GetName ();
  }

  const UInt16& PokemonSkill::GetLimitPPMax () const
  {
    if (skillInfo_ == nullptr)
      throw Exception ("This skill's base informations doesn't exist !");

    return skillInfo_->GetMaxPP ();
  }

  void PokemonSkill::SetSkillInfo (const ID& skillID)
  {
    skillInfo_ = ObjectFactory::Instance ().
      Create<SkillInfo> ("SkillInfo",  ID (skillID));

    maxPP_ = skillInfo_->GetPP ();
    Refill ();
  }

  void PokemonSkill::Refill ()
  {
    currentPP_ = maxPP_;
  }

  void PokemonSkill::Use ()
  {
    if (currentPP_ > 0)
      currentPP_--;
  }

  void PokemonSkill::AddPP (int value)
  {
    maxPP_ += value;

    if (maxPP_ > GetLimitPPMax ())
      maxPP_ = GetLimitPPMax ();
  }

  void PokemonSkill::RaiseToMaxPP ()
  {
    maxPP_ = GetLimitPPMax ();
  }
}