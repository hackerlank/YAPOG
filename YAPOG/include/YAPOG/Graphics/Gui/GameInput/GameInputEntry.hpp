#ifndef YAPOG_GAMEINPUTENTRY_HPP
# define YAPOG_GAMEINPUTENTRY_HPP

# include "YAPOG/Macros.hpp"
# include "YAPOG/Graphics/Gui/GuiEvent.hpp"

namespace yap
{
  class YAPOG_LIB GameInputEntry
  {
      DISALLOW_COPY(GameInputEntry);

    public:

      GameInputEntry ();
      virtual ~GameInputEntry ();

      bool IsActive () const;
      bool IsActivated () const;
      bool IsDeactivated () const;

      /// @brief Specifies if the event parameters (key, mouse button...)
      /// correpond to this game input entry.
      virtual bool IsActive (const GuiEvent& guiEvent) const = 0;

      void BeginUpdate ();
      virtual void Update (const GuiEvent& guiEvent) = 0;
      void EndUpdate ();

    protected:

      void Activate (bool isActive);

    private:

      bool isActive_;
      bool previousIsActive_;
  };
} // namespace yap

#endif // YAPOG_GAMEINPUTENTRY_HPP
