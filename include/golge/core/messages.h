#ifndef GOLGE_MESSAGES_H
#define GOLGE_MESSAGES_H

#include <Box2D/Box2D.h>

namespace golge
{
class Entity;

enum class MessageType
{
  Test,
  Collision,
  Sound,
  Other
};

struct Message
{
  Message(MessageType mt)
  {
    type = mt;
  }
  MessageType type;
};

struct CollisionMessage : public Message
{
  CollisionMessage() : Message(MessageType::Collision) {}
  b2Contact *collision;
  Entity *entityA;
  Entity *entityB;
};

struct SoundMessage : public Message
{
  SoundMessage() : Message(MessageType::Sound) {}
};

} // namespace golge

#endif