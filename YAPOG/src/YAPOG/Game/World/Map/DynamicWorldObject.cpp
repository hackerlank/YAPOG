#include "YAPOG/Game/World/Map/DynamicWorldObject.hpp"
#include "YAPOG/Game/World/Map/Physics/PhysicsCore.hpp"
#include "YAPOG/Game/Factory/ObjectFactory.hpp"

namespace yap
{
  const String DynamicWorldObject::DEFAULT_INACTIVE_STATE = "Inactive";
  const Vector2 DynamicWorldObject::DEFAULT_MAX_VELOCITY =
    Vector2 (150.0f, 150.0f);

  DynamicWorldObject::DynamicWorldObject (const ID& id)
    : WorldObject (id)
    , OnVelocityChanged ()
    , OnStateChanged ()
    , worldID_ ()
    , state_ (DEFAULT_INACTIVE_STATE)
    , physicsCore_ (nullptr)
    , maxVelocity_ (DEFAULT_MAX_VELOCITY)
  {
  }

  DynamicWorldObject::~DynamicWorldObject ()
  {
    delete physicsCore_;
    physicsCore_ = nullptr;
  }

  DynamicWorldObject::DynamicWorldObject (const DynamicWorldObject& copy)
    : WorldObject (copy)
    , worldID_ (copy.worldID_)
    , state_ (copy.state_)
    , physicsCore_ (nullptr)
    , maxVelocity_ (copy.maxVelocity_)
  {
    if (copy.physicsCore_ != nullptr)
      SetPhysicsCore (copy.physicsCore_->Clone ());
  }

  const ID& DynamicWorldObject::GetWorldID () const
  {
    return worldID_;
  }

  void DynamicWorldObject::SetWorldID (const ID& id)
  {
    worldID_ = id;
  }

  const ID& DynamicWorldObject::GetTypeID () const
  {
    return ObjectFactory::Instance ().GetID (GetObjectFactoryTypeName ());
  }

  const Vector2& DynamicWorldObject::GetMaxVelocity () const
  {
    return maxVelocity_;
  }

  void DynamicWorldObject::SetMaxVelocity (const Vector2& maxVelocity)
  {
    maxVelocity_ = maxVelocity;
  }

  void DynamicWorldObject::SetPhysicsCore (PhysicsCore* physicsCore)
  {
    if (physicsCore_ == physicsCore)
      return;

    delete physicsCore_;

    physicsCore_ = physicsCore;

    physicsCore_->OnMoved +=
      [&] (const PhysicsCore& sender, const EmptyEventArgs& args)
    {
      TryChangeState ("Moving");
    };

    physicsCore_->OnStopped +=
      [&] (const PhysicsCore& sender, const EmptyEventArgs& args)
    {
      SetInactive ();
    };

    physicsCore_->OnVelocityChanged +=
      [&] (const PhysicsCore& sender,
           const ChangeEventArgs<const Vector2&>& args)
    {
      HandleOnVelocityChanged (args.Old, args.Current);
    };
  }

  void DynamicWorldObject::ApplyForce (const Vector2& force)
  {
    physicsCore_->ApplyForce (force);

    HandleApplyForce (force);
  }

  const Vector2& DynamicWorldObject::GetMove () const
  {
    return physicsCore_->GetMove ();
  }

  void DynamicWorldObject::RawSetVelocity (const Vector2& velocity)
  {
    physicsCore_->RawSetVelocity (velocity);
  }

  bool DynamicWorldObject::IsActive () const
  {
    return GetLogicalState () != DEFAULT_INACTIVE_STATE;
  }

  const String& DynamicWorldObject::GetState () const
  {
    return state_.GetName ();
  }

  const String& DynamicWorldObject::GetLogicalState () const
  {
    return state_.GetLogicalName ();
  }

  bool DynamicWorldObject::TryChangeState (const String& state)
  {
    if (IsActive ())
    {
      if (state_.IsJoinedTo (state))
      {
        SetState (state);
        return true;
      }

      if (state != DEFAULT_INACTIVE_STATE)
        return GetState () == state;

      SetInactive ();

      return true;
    }

    SetState (state);

    return true;
  }

  void DynamicWorldObject::SetInactive ()
  {
    SetState (DEFAULT_INACTIVE_STATE);
  }

  void DynamicWorldObject::SetState (const String& state)
  {
    state_ = state;

    HandleSetState (state);
  }

  bool DynamicWorldObject::IsMoving () const
  {
    return GetLogicalState () == "Moving";
  }

  void DynamicWorldObject::Update (const Time& dt)
  {
    HandleUpdate (dt);
  }

  void DynamicWorldObject::HandleApplyForce (const Vector2& force)
  {
  }

  void DynamicWorldObject::HandleUpdate (const Time& dt)
  {
    physicsCore_->Update (dt);
  }

  void DynamicWorldObject::HandleSetState (const String& state)
  {
    OnStateChanged (*this, state);
  }

  void DynamicWorldObject::HandleMove (const Vector2& offset)
  {
    WorldObject::HandleMove (offset);
  }

  void DynamicWorldObject::HandleOnVelocityChanged (
    const Vector2& oldVelocity,
    const Vector2& currentVelocity)
  {
    OnVelocityChanged (
      *this,
      ChangeEventArgs<const Vector2&> (
        oldVelocity,
        currentVelocity));
  }
} // namespace yap
