#ifndef YAPOG_CLIENT_BATTLESCREEN_HPP
# define YAPOG_CLIENT_BATTLESCREEN_HPP

# include "YAPOG/Macros.hpp"

# include "GameScreen/BaseScreen.hpp"
# include "Battle/BattleInterface.hpp"

namespace ycl
{
  class Battle;

  class BattleScreen : public BaseScreen
  {
    DISALLOW_COPY(BattleScreen);

  public:

    BattleScreen ();
    virtual ~BattleScreen ();

  protected:

    virtual void HandleInit ();

    virtual const yap::ScreenType& HandleRun (
      const yap::Time& dt,
      yap::IDrawingContext& context);

  private:
    Battle* battle_;
    BattleInterface* battleInterface_;

    static const yap::ScreenType DEFAULT_NAME;
  };
} // namespace ycl

#endif // YAPOG_CLIENT_BATTLESCREEN_HPP
