#include "YAPOG/Graphics/Gui/GuiManager.hpp"

#include "GameScreen/MainMenuScreen.hpp"
#include "Gui/MainMenu.hpp"

namespace ycl
{
  const yap::ScreenType MainMenuScreen::DEFAULT_NAME = "MainMenu";

  MainMenuScreen::MainMenuScreen ()
    : BaseScreen (DEFAULT_NAME)
  {
  }

  MainMenuScreen::~MainMenuScreen ()
  {
  }

  void MainMenuScreen::HandleInit ()
  {
    BaseScreen::HandleInit ();
   
    MainMenu* mainMenu = new MainMenu ();
    mainMenu->Init ();

    mainMenu->GetLoginItem ().OnActivated +=
      [&] (const yap::MenuItem& sender, const yap::EmptyEventArgs& args)
    {
      nextScreen_ = "Login";
    };

    guiManager_->AddChild (*mainMenu);
  }
  const yap::ScreenType& MainMenuScreen::HandleRun (
    const yap::Time& dt,
    yap::IDrawingContext& context)
  {
    return BaseScreen::HandleRun (dt, context);
  }
} // namespace ycl
