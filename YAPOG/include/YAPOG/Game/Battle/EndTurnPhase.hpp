#ifndef YAPOG_ENDTURNPHASE_HPP
# define YAPOG_ENDTURNPHASE_HPP

# include "YAPOG/Macros.hpp"
# include "YAPOG/Game/Battle/BattlePhase.hpp"

namespace yap
{
  class YAPOG_LIB EndTurnPhase : public BattlePhase
  {
  public:
    EndTurnPhase ();

    /// @name BattlePhase members.
    /// @{
    virtual void HandleStart ();
    virtual void HandleUpdate (const Time& dt);
    virtual void HandleEnd ();
    /// @}
  };
} // namespace yap

#endif // YAPOG_ENDTURNPHASE_HPP
