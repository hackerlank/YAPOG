#include "YAPOG/Game/World/Map/DynamicWorldObjectCollection.hpp"
#include "YAPOG/Game/World/Map/DynamicWorldObject.hpp"

namespace yap
{
  DynamicWorldObjectCollection::DynamicWorldObjectCollection ()
    : objects_ ()
  {
  }

  DynamicWorldObjectCollection::~DynamicWorldObjectCollection ()
  {
    for (const auto& it : objects_)
      delete it.second;
  }

  DynamicWorldObjectCollection::ItType
  DynamicWorldObjectCollection::begin ()
  {
    return objects_.begin ();
  }

  DynamicWorldObjectCollection::ConstItType
  DynamicWorldObjectCollection::begin () const
  {
    return objects_.begin ();
  }

  DynamicWorldObjectCollection::ItType
  DynamicWorldObjectCollection::end ()
  {
    return objects_.end ();
  }

  DynamicWorldObjectCollection::ConstItType
  DynamicWorldObjectCollection::end () const
  {
    return objects_.end ();
  }

  void DynamicWorldObjectCollection::AddObject (DynamicWorldObject* object)
  {
    objects_.Add (object->GetWorldID (), object);
  }

  void DynamicWorldObjectCollection::RemoveObject (const ID& worldID)
  {
    objects_.Remove (worldID);
  }

  DynamicWorldObject& DynamicWorldObjectCollection::GetObject (
    const ID& worldID)
  {
    return *objects_[worldID];
  }

  void DynamicWorldObjectCollection::Update (const Time& dt)
  {
    for (auto& it : objects_)
      it.second->Update (dt);
  }
} // namespace yap
