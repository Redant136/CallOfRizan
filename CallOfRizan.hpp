#pragma once

#define kNgine_DEBUG
#include <kNgine/kNgine.hpp>

class MainCharacter;
extern kNgine::Camera *MainCamera;
extern MainCharacter *character;

class MainCharacter : public kNgine::ComponentGameObject
{
public:
  kNgine::SpriteMap *characterSprites;
  kNgine::RenderableSystem *spriteSystem;
  MainCharacter()
  {
    this->addComponent(new kNgine::NodeObjectComponent(this, MainCamera));
    characterSprites = new kNgine::SpriteMap();
    spriteSystem = new kNgine::RenderableSystem(this);
    spriteSystem->addSprite(
        new kNgine::RendererObject(
            this, new kNgine::SpriteAnimation(
                      this, characterSprites, kNgine::importSpriteSheet("mcSpriteSheet.png", 50, 37), 1.f / 16)),
        "main");
    characterSprites->offsetPixelsInSprites(NORTH, 1);

    // this->addComponent(new kNgine::physics::kPhysicsBodyComponent(this, kNgine::physics::kHitBoxRect(v2(1,1))));
    this->addComponent(kNgine::physics::kPhysicsBodyComponent::kPhysRect(this,v2(1,1)));

    this->addComponent(spriteSystem);
    kNgine::addObject(characterSprites);
  }
};
