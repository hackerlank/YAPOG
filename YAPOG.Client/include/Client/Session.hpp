#ifndef YAPOG_CLIENT_SESSION_HPP
# define YAPOG_CLIENT_SESSION_HPP

# include <SFML/Network/SocketSelector.hpp>

# include "YAPOG/Macros.hpp"
# include "YAPOG/System/Network/IPacketHandler.hpp"
# include "YAPOG/System/Network/PacketHandler.hpp"
# include "YAPOG/System/Network/ClientSocket.hpp"
# include "YAPOG/System/Network/NetworkHandler.hpp"
# include "YAPOG/System/IntTypes.hpp"
# include "YAPOG/System/Thread/Thread.hpp"

# include "Client/User.hpp"

namespace ycl
{
  class Session : public yap::IPacketHandler
  {
      DISALLOW_COPY(Session);

    public:

      static Session& Instance ();

      void Refresh ();

      void Login (const yap::String& login);

      User& GetUser ();

      /// @name IPacketHandler members.
      /// @{
      virtual bool HandlePacket (yap::IPacket& packet);
      virtual bool SendPacket (yap::IPacket& packet);

      virtual void AddRelay (yap::IPacketHandler* relay);
      virtual void SetParent (yap::IPacketHandler* parent);
      /// @}

    private:

      Session ();
      virtual ~Session ();

      bool Connect ();
      void HandleReception ();

      static const yap::String DEFAULT_REMOTE_IP;
      static const yap::Int16 DEFAULT_REMOTE_PORT;

      yap::PacketHandler packetHandler_;

      yap::Thread receptionThread_;
      bool receptionIsActive_;

      yap::ClientSocket socket_;
      yap::NetworkHandler networkHandler_;
      sf::SocketSelector socketSelector_;

      User user_;
  };
}

#endif // YAPOG_CLIENT_SESSION_HPP