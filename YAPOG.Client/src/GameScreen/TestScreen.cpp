#include "GameScreen/TestScreen.hpp"
#include "YAPOG/System/IO/Log/DebugLogger.hpp"
#include "YAPOG/Graphics/IDrawingContext.hpp"
#include "YAPOG/Graphics/ICamera.hpp"
#include "World/Map/MapReader.hpp"
#include "World/Map/Map.hpp"
#include "YAPOG/System/IO/Xml/XmlReader.hpp"
#include "YAPOG/System/StringHelper.hpp"
#include "YAPOG/Graphics/Game/Sprite/Sprite.hpp"
#include "YAPOG/Graphics/Game/Sprite/SpriteSet.hpp"
#include "YAPOG/Graphics/Game/Sprite/DirectionalSpriteSet.hpp"
#include "YAPOG/Graphics/Game/Sprite/ComposedSprite.hpp"
#include "YAPOG/Graphics/Gui/GameInput/GameInputManager.hpp"
#include "YAPOG/Graphics/Gui/GameInput/GameInputType.hpp"
#include "YAPOG/Graphics/Gui/GameInput/KeyboardGameInputEntry.hpp"
#include "YAPOG/Graphics/Gui/GameInput/GameInput.hpp"
#include "YAPOG/Content/ContentManager.hpp"
#include "YAPOG/Game/Factory/ObjectFactory.hpp"
#include "YAPOG/System/String.hpp"
#include "YAPOG/Game/Factory/XmlLoader.hpp"

///////////////////////////////
/// Just some ugly tests... ///
///////////////////////////////

using namespace yap;

DirectionalSpriteSet dss1;
GameInputManager& gim = yap::GameInputManager::Instance ();
ContentManager& cm = ContentManager::Instance ();
DebugLogger& dl = DebugLogger::Instance ();

ObjectFactory& of = ObjectFactory::Instance ();

TestScreen::TestScreen ()
  : yap::GameScreen ("Test")
  , textures_ ()
  , backTextures_ ()
  , anim1_ (100)
{
  // loadable types are registered
  of.RegisterLoader ("Map", new XmlLoader< ::Map, ::MapReader> (
                       Path ("Map"), "Map"));

  ::Map* map42 = of.Create< ::Map> ("Map", yap::ID (42));
  dl.LogLine ("MAP_ID=" + StringHelper::ToString (map42->GetID ().GetValue ()));
  dl.LogLine ("MAP_NAME=" + map42->GetName ());

  ::Map* map1 = of.Create< ::Map> ("Map", yap::ID (1));
  dl.LogLine ("MAP_ID=" + StringHelper::ToString (map1->GetID ().GetValue ()));
  dl.LogLine ("MAP_NAME=" + map1->GetName ());

  gim.AddGameInput (
    new GameInput (
      GameInputType::Action,
      new KeyboardGameInputEntry (Key::Return)));
  gim.AddGameInput (
    new GameInput (
      GameInputType::Misc,
      new KeyboardGameInputEntry (Key::M)));

  int animFlag = 0;

  for (int i = 0; i < 2000; ++i)
  {
    yap::Vector2 scaleFactor (0.7f, 0.7f);

    yap::Texture* texture = new yap::Texture ();
    texture->LoadFromFile ("boo.png");
//    texture->Move (yap::Vector2 (i * 400.0f, 0.0f));
    texture->Scale (scaleFactor);
    texture->ChangeColor (sf::Color (255, 90, 128, 128));
    textures_.Add (texture);

    if (animFlag++ < 2)
    {
//      dss1.AddSprite (yap::Direction::North, new yap::Sprite (texture));
      anim1_.AddFrame (new yap::Sprite (texture));
//      spr1_.SetTexture (texture);
    }

    texture = new yap::Texture ();
    texture->LoadFromFile ("boo.png");
//    texture->Move (yap::Vector2 (i * 400.0f + 200.0f, 0.0f));
    texture->ChangeColor (sf::Color (128, 255, 128, 128));
    texture->Scale (scaleFactor);
    backTextures_.Add (texture);

    if (animFlag++ < 2)
    {
//      dss1.AddSprite (yap::Direction::South, new yap::Sprite (texture));
      anim1_.AddFrame (new yap::Sprite (texture));
    }
  }

//  anim1_.Move (yap::Vector2 (100.0f, 100.0f));

  anim1_.ChangeState (yap::AnimatedSprite::PlayState::Loop);
//  anim1_.ChangeColor (sf::Color::Blue);
}

TestScreen::~TestScreen ()
{
/*  for (const auto& it : textures_)
    delete it;

  for (const auto& it : backTextures_)
  delete it;*/
}

const yap::ScreenType& TestScreen::HandleRun (
  const yap::Time& dt,
  yap::IDrawingContext& context)
{
//  yap::DebugLogger::Instance ().LogLine (1.0f / dt.GetValue ());

//  context.GetCamera ("Background World").Move (
//    yap::Vector2 (140.0f * dt.GetValue (), 0.0f));

  context.SetMode ("Background World");

//  for (auto it : backTextures_)
//    it->Draw (context);

  context.SetDefaultCamera ();

//  context.GetCamera ("World").Move (
//    yap::Vector2 (300.0f * dt.GetValue (), 0.0f));

//  for (auto it : textures_)
//    it->Draw (context);

  anim1_.Update (dt);
  anim1_.Draw (context);
//  dss1.Draw (context);
//  spr1_.Draw (context);
  DebugLogger::Instance().LogLine (1.0f/dt.GetValue());

  return nextScreen_;
}

void TestScreen::HandleInit ()
{
  guiManager_ = new yap::GuiManager ();
}

void TestScreen::HandleActivate ()
{
}

void TestScreen::HandleDeactivate ()
{
}

bool TestScreen::HandleOnEvent (const yap::GuiEvent& guiEvent)
{
  if (gim.GameInputIsActivated (yap::GameInputType::Action, guiEvent))
    dss1.SetCurrentSprite (yap::Direction::North);

  if (gim.GameInputIsActivated (yap::GameInputType::Misc, guiEvent))
    dss1.SetCurrentSprite (yap::Direction::South);

  return false;
}

bool TestScreen::HandleOnPriorityEvent (const yap::GuiEvent& guiEvent)
{
  return false;
}
