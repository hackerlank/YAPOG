#ifndef YAPOG_CLIENT_PLAYER_HPP
# define YAPOG_CLIENT_PLAYER_HPP

# include "YAPOG/Macros.hpp"
# include "YAPOG/Game/World/Map/IPlayer.hpp"

# include "World/Map/Character.hpp"

namespace ycl
{
  class Player : public Character
               , public yap::IPlayer
  {
      DISALLOW_ASSIGN(Player);

    public:

      Player (const yap::ID& id);
      virtual ~Player ();

      void SetName (const yap::String& name);

      void SetDialogManager (yap::IDialogManager& dialogManager);

      /// @name ICloneable members.
      /// @{
      virtual Player* Clone () const;
      /// @}

      /// @name IDialogActor members.
      /// @{
      virtual const yap::String& GetName () const;

      virtual const yap::ID& GetWorldID () const;

      virtual bool CanTalk (yap::IDialogActor& dialogActor) const;

      virtual void Talk (yap::IDialogActor& dialogActor);

      virtual void StopTalking ();

      virtual bool CanListen (yap::IDialogActor& dialogActor) const;

      virtual void Listen (yap::IDialogActor& dialogActor);

      virtual void StopListening ();

      virtual bool TryStartDialog (yap::IDialogManager& dialogManager);
      /// @}

      /// @name IPlayer members.
      /// @{
      virtual void Accept (yap::IDynamicWorldObjectVisitor& visitor);
      virtual void Accept (
        yap::IDynamicWorldObjectConstVisitor& visitor) const;

      virtual bool HasInputActivated (yap::GameInputType gameInputType) const;
      virtual bool HasInputDeactivated (
        yap::GameInputType gameInputType) const;
      virtual bool HasInputActive (yap::GameInputType gameInputType) const;

      virtual void Warp (const yap::ID& mapWorldID, const yap::Vector2& point);

      virtual void DestroyObject (const yap::ID& objectWorldID);

      virtual void TriggerBattle ();

      virtual yap::Event<
        yap::DynamicWorldObject&,
        const yap::Vector2&>& OnMovedEvent ();
      /// @}

    protected:

      Player (const Player& copy);

      virtual const yap::String& GetObjectFactoryTypeName () const;

    private:

      static const yap::String OBJECT_FACTORY_TYPE_NAME;

      static const yap::String DEFAULT_NAME;

      yap::String name_;

      yap::IDialogManager* dialogManager_;
  };
} // namespace ycl

#endif // YAPOG_CLIENT_PLAYER_HPP
