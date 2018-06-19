#ifndef GOLGE_MESSAGES_H
#define GOLGE_MESSAGES_H

#include <Box2D/Box2D.h>

namespace golge
{
  class Entity;

  enum class MessageType {
    Test,
    Collision,
    Other
  };

  struct Message
  {
    Message(MessageType mt) {
      type = mt;
    }
    MessageType type;
  };

  
  struct CollisionMessage : public Message
  {
    CollisionMessage() : Message(MessageType::Collision) {}
    b2Contact *collision;
    std::shared_ptr<Entity> entityA;
    std::shared_ptr<Entity> entityB;
  };
  

} // golge

#endif