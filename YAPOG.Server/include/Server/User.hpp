#ifndef YAPOG_SERVER_USER_HPP
# define YAPOG_SERVER_USER_HPP

# include "YAPOG/Macros.hpp"
# include "YAPOG/System/String.hpp"
# include "YAPOG/System/Network/IPacketHandler.hpp"
# include "YAPOG/System/Network/PacketHandler.hpp"

namespace yse
{
  class World;
  class Map;
  class Player;

  class User : public yap::IPacketHandler
  {
      DISALLOW_COPY(User);

    public:

      User ();
      virtual ~User ();

      void SetWorld (World* world);

      const yap::String& GetLogin () const;
      bool Login (const yap::String& login);

      /// @name IPacketHandler members.
      /// @{
      virtual bool HandlePacket (yap::IPacket& packet);
      virtual bool SendPacket (yap::IPacket& packet);

      virtual void AddRelay (yap::IPacketHandler* relay);
      virtual void RemoveRelay (yap::IPacketHandler* relay);
      virtual void SetParent (yap::IPacketHandler* parent);
      /// @}

    private:

      World& GetWorld ();

      void SetPlayer (Player* player);

      void HandleClientRequestStartInfo (yap::IPacket& packet);

      void SendChangeMap (Map& map);

      yap::PacketHandler packetHandler_;

      yap::String login_;

      World* world_;

      Player* player_;
  };
} // namespace yse

#endif // YAPOG_SERVER_USER_HPP
