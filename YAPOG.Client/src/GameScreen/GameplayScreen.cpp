#include "YAPOG/Graphics/Gui/GameInput/GameInputManager.hpp"
#include "YAPOG/Game/Factory/ObjectFactory.hpp"
#include "YAPOG/System/Network/Packet.hpp"
#include "YAPOG/System/IO/Log/Logger.hpp"
#include "YAPOG/Graphics/Gui/GuiManager.hpp"
#include "YAPOG/Graphics/ICamera.hpp"
#include "YAPOG/Graphics/Gui/WidgetBackground.hpp"
#include "YAPOG/Graphics/Gui/WidgetBorder.hpp"
#include "YAPOG/Game/Pokemon/Pokedex.hpp"
#include "YAPOG/Game/Pokemon/PokemonInfo.hpp"
#include "YAPOG/Graphics/Gui/HorizontalLayout.hpp"
#include "YAPOG/Graphics/Gui/VerticalLayout.hpp"
#include "YAPOG/Graphics/Gui/Menu.hpp"
#include "YAPOG/Graphics/Gui/PictureBox.hpp"
#include "YAPOG/System/StringHelper.hpp"
#include "YAPOG/Game/Pokemon/PokemonInfo.hpp"
#include "YAPOG/Graphics/Gui/TextBoxWidget.hpp"
#include "YAPOG/Graphics/Gui/GridMenu.hpp"
#include "YAPOG/Graphics/Gui/MultiLabelWidget.hpp"
#include "YAPOG/Game/Pokemon/Pokedex.hpp"
#include "YAPOG/Game/Pokemon/PokemonTeam.hpp"
#include "YAPOG/Game/Chat/GameMessage.hpp"

#include "GameScreen/GameplayScreen.hpp"
#include "World/Map/Player.hpp"
#include "World/Map/Map.hpp"
#include "Client/Session.hpp"
#include "Gui/GameGuiManager.hpp"
#include "Gui/GameMainMenu.hpp"
#include "Gui/ChatWidget.hpp"
#include "Gui/PokedexWidget.hpp"
#include "Gui/PokedexCompositeWidget.hpp"
#include "Gui/PokemonTeamWidget.hpp"

namespace ycl
{
  const yap::ScreenType GameplayScreen::DEFAULT_NAME = "Gameplay";

  const yap::Vector2 GameplayScreen::DEFAULT_WORLD_CAMERA_DEZOOM_FACTOR =
    yap::Vector2 (2.0f, 2.0f);

  GameplayScreen::GameplayScreen (yap::ICamera& worldCamera)
    : BaseScreen (DEFAULT_NAME)
    , world_ ()
    , worldCamera_ (worldCamera)
    , cameraController_ (worldCamera_)
    , player_ (nullptr)
    , moveController_ ()
    , lastForce_ ()
    , fpsDisplayTimer_ ()
    , gameGuiManager_ (nullptr)
    , mainMenu_ (nullptr)
    , pokedex_ (nullptr)
    , pokemonTeam_ (nullptr)
    , chat_ (nullptr)
    , fpsLabel_ (nullptr)
  {
  }

  GameplayScreen::~GameplayScreen ()
  {
    delete (chat_);
    chat_ = nullptr;
  }

  void GameplayScreen::HandleInit ()
  {
    BaseScreen::HandleInit ();

    session_.GetUser ().OnPlayerCreated += [this] (
      const User& sender,
      Player* args)
    {
      SetPlayer (args);
    };

    session_.GetUser ().OnMessageReceived += [this] (
      const User& sender,
      const yap::GameMessage& message)
    {
      chat_->AddMessage (message.GetContent ());
    };

    world_.OnMapChanged += [this] (
      const World& sender,
      const yap::ChangeEventArgs<Map*>& args)
    {
      SetCurrentMap (*args.Current);
    };

    session_.GetUser ().SetWorld (&world_);

    chat_ = new ChatWidget ();
    chat_->Init ();
    chat_->ChangeColor (sf::Color (0, 0, 0));
    chat_->Close ();

    chat_->OnMessageSent +=
    [this] (ChatWidget& sender, yap::GameMessage& args)
    {
      session_.GetUser ().SendGameMessage (args);
    };
    gameGuiManager_->AddGameWidget ("Chat", chat_);

    worldCamera_.Scale (DEFAULT_WORLD_CAMERA_DEZOOM_FACTOR);

    yap::PokemonTeam* team = new yap::PokemonTeam ();
    pokemonTeam_ = new PokemonTeamWidget (team);
    pokemonTeam_->Init ();
    pokemonTeam_->Close ();
    gameGuiManager_->AddGameWidget ("PokemonTeam", pokemonTeam_);

    yap::Pokedex* pokedexInfo = new yap::Pokedex ();
    for (int i = 1; i < 4; i++)
    {
      yap::PokemonInfo* pok = yap::ObjectFactory::Instance ().
        Create<yap::PokemonInfo> ("PokemonInfo", yap::ID  (i));

      pokedexInfo->AddPokemon (pok);
      pokedexInfo->AddPokemonSeen (pok);
      pokedexInfo->AddPokemonCaught (pok);
    }

    yap::PokemonInfo* pok = yap::ObjectFactory::Instance ().
      Create<yap::PokemonInfo> ("PokemonInfo", yap::ID  (16));

    pokedexInfo->AddPokemon (pok);
    pokedexInfo->AddPokemonSeen (pok);
    pokedexInfo->AddPokemonCaught (pok);

    pokedex_ = new PokedexWidget (pokedexInfo);
    pokedex_->Close ();
    pokedex_->Init ();

    gameGuiManager_->AddGameWidget ("Pokedex", pokedex_);

    mainMenu_ = new GameMainMenu ();
    mainMenu_->Init ("toto");
    mainMenu_->OnPokedexItemActivated += [this] (
      GameMainMenu& sender,
      const yap::EmptyEventArgs& args)
    {
      gameGuiManager_->SetCurrentWidget ("Pokedex");
    };
    mainMenu_->OnPokemonItemActivated += [this] (
      GameMainMenu& sender,
      const yap::EmptyEventArgs& args)
    {
      gameGuiManager_->SetCurrentWidget ("PokemonTeam");
    };

    gameGuiManager_->AddGameWidget ("Menu", mainMenu_);

    mainMenu_->Close ();

    fpsLabel_ = new yap::Label ();
    fpsLabel_->SetTextSize (18);

    guiManager_->AddChild (*fpsLabel_);
  }

  void GameplayScreen::HandleRun (
    const yap::Time& dt,
    yap::IDrawingContext& context)
  {
    if (fpsDisplayTimer_.DelayIsComplete (yap::Time (0.5f), true))
      fpsLabel_->SetText (
        "FPS: " +
        yap::StringHelper::ToString<int> (1.0f / dt.GetValue ()));

    world_.Update (dt);

    cameraController_.Update (dt);

    UpdatePlayer (dt);

    world_.Draw (context);

    BaseScreen::HandleRun (dt, context);
  }

  bool GameplayScreen::HandleOnEvent (const yap::GuiEvent& guiEvent)
  {
    switch (guiEvent.type)
    {
      case sf::Event::KeyPressed:

        switch (guiEvent.key.code)
        {
          case sf::Keyboard::Space:

            if (player_ != nullptr && player_->IsActive ())
              break;

            gameGuiManager_->SetCurrentWidget ("Menu");

            return true;

          case sf::Keyboard::C:

            if (player_ != nullptr && player_->IsActive ())
              break;

            gameGuiManager_->SetCurrentWidget ("Chat");

            return true;

          default: break;
        }

        break;

      case sf::Event::KeyReleased:

        switch (guiEvent.key.code)
        {
          default: break;
        }

      default: break;
    }

    if (gameInputManager_.GameInputIsActivated (
      yap::GameInputType::Down,
      guiEvent))
    {
      moveController_.EnableDirection (yap::Direction::South);
      return true;
    }

    if (gameInputManager_.GameInputIsActivated (
      yap::GameInputType::Up,
      guiEvent))
    {
      moveController_.EnableDirection (yap::Direction::North);
      return true;
    }

    if (gameInputManager_.GameInputIsActivated (
      yap::GameInputType::Left,
      guiEvent))
    {
      moveController_.EnableDirection (yap::Direction::West);
      return true;
    }

    if (gameInputManager_.GameInputIsActivated (
      yap::GameInputType::Right,
      guiEvent))
    {
      moveController_.EnableDirection (yap::Direction::East);
      return true;
    }

    if (gameInputManager_.GameInputIsDeactivated (
      yap::GameInputType::Down,
      guiEvent))
    {
      moveController_.DisableDirection (yap::Direction::South);
      return true;
    }

    if (gameInputManager_.GameInputIsDeactivated (
      yap::GameInputType::Up,
      guiEvent))
    {
      moveController_.DisableDirection (yap::Direction::North);
      return true;
    }

    if (gameInputManager_.GameInputIsDeactivated (
      yap::GameInputType::Left,
      guiEvent))
    {
      moveController_.DisableDirection (yap::Direction::West);
      return true;
    }

    if (gameInputManager_.GameInputIsDeactivated (
      yap::GameInputType::Right,
      guiEvent))
    {
      moveController_.DisableDirection (yap::Direction::East);
      return true;
    }

    if (guiEvent.type == sf::Event::KeyPressed)
    {
      if (guiEvent.key.code == sf::Keyboard::F10)
      {
        if (chat_->IsVisible ())
          chat_->Close ();
        else
          chat_->Open ();
        return true;
      }
    }

    if (gameInputManager_.GameInputIsActivated (
      yap::GameInputType::MapAction,
      guiEvent))
    {
      SendGameInput (yap::GameInputType::MapAction, true);
      return true;
    }

    if (gameInputManager_.GameInputIsDeactivated (
      yap::GameInputType::MapAction,
      guiEvent))
    {
      SendGameInput (yap::GameInputType::MapAction, false);
      return true;
    }

    return false;
  }

  Map& GameplayScreen::GetCurrentMap ()
  {
    return world_.GetCurrentMap ();
  }

  void GameplayScreen::SetCurrentMap (Map& map)
  {
    cameraController_.SetBounds (
      yap::FloatRect (
      yap::Vector2 (),
      map.GetSize ()));

    cameraController_.FocusTarget ();
  }

  void GameplayScreen::SetPlayer (Player* player)
  {
    player_ = player;

    moveController_.SetValue (player_->GetMaxVelocity ());

    cameraController_.SetTarget (*player);
    cameraController_.SetVelocityFactor (player->GetMaxVelocity ());
  }

  void GameplayScreen::UpdatePlayer (const yap::Time& dt)
  {
    if (player_ == nullptr)
      return;

    const yap::Vector2& force = moveController_.GetForce ();

    if (lastForce_ == force)
      return;

    SendApplyForce (force);

    player_->ApplyForce (force);

    lastForce_ = force;
  }

  void GameplayScreen::SendApplyForce (const yap::Vector2& force)
  {
    yap::Packet packet;
    packet.CreateFromType (yap::PacketType::ClientInfoApplyForce);

    packet.Write (force);

    session_.SendPacket (packet);
  }

  void GameplayScreen::SendGameInput (
    yap::GameInputType gameInputType,
    bool state)
  {
    yap::Packet packet;
    packet.CreateFromType (yap::PacketType::ClientInfoGameInput);

    packet.Write (static_cast<yap::Int16> (gameInputType));
    packet.Write (state);

    session_.SendPacket (packet);
  }

  void GameplayScreen::CreateGuiManager ()
  {
    gameGuiManager_ = new GameGuiManager ();

    guiManager_ = gameGuiManager_;
  }
} // namespace ycl
