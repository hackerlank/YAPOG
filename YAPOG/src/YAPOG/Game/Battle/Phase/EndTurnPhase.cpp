# include "YAPOG/Game/Battle/Phase/EndTurnPhase.hpp"

namespace yap
{
  EndTurnPhase::EndTurnPhase (Battle& battle)
    : BattlePhase (battle, BattlePhaseState::EndTurn)
  {
  }

  void EndTurnPhase::HandleStart ()
  {
    BattlePhase::HandleStart ();
    std::cout << "BEGIN END TURN PHASE !" << std::endl;
  }

  void EndTurnPhase::HandleUpdate (const Time& dt)
  {
    nextPhase_ = BattlePhaseState::EndBattle;
  }

  void EndTurnPhase::HandleEnd ()
  {
    BattlePhase::HandleEnd ();
    std::cout << "END END TURN PHASE !" << std::endl;
  }
}