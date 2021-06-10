#pragma once

#define kNgine_DEBUG
#include <kNgine/kNgine.hpp>

// using namespace kNgine;
class MainCharacter;
extern kNgine::Camera *MainCamera;
extern MainCharacter *character;

class MainCharacter : public kNgine::ComponentGameObject
{
private:
  bool right=true;

public:
  kNgine::SpriteMap *characterSprites;
  kNgine::RenderableSystem *spriteSystem;
  MainCharacter()
  {
    characterSprites = new kNgine::SpriteMap();
    spriteSystem = new kNgine::RenderableSystem(this);
    spriteSystem->addRenderable(
        new kNgine::RendererObject(
            this, new kNgine::SpriteAnimation(
                      this, characterSprites, kNgine::importSpriteSheet("mcSpriteSheet.png", 50, 37), 1.f / 16)),
        "main");
    characterSprites->offsetPixelsInSprites(NORTH, 1);

    // this->addComponent(new kNgine::physics::kPhysicsBodyComponent(this, kNgine::physics::kHitBoxRect(v2(1,1))));
    this->addComponent(kNgine::kPhysicsBodyComponent::kPhysRect(this,v2(1,1)));
    this->findComponent<kNgine::kPhysicsBodyComponent>("[k_physics_body]")->preCollision=[](kNgine::GameObject*obj){
      // print(obj->position);
    };

    kNgine::SpriteComponent *hookSpr = new kNgine::SpriteComponent(this, kNgine::fillSprite(400, 400, {255, 255, 255, 255}));
    hookSpr->spriteDimension = v2(5, 0.1);
    hookSpr->offset=v2(2.5,0);
    addComponent(hookSpr);
    kNgine::kPhysicsBodyComponent* hookHitbox=kNgine::kPhysicsBodyComponent::kPhysRect(this,v2(5,0.5))->toIntangibleHitBox();
    hookHitbox->preCollision=[](kNgine::GameObject*obj){
      print(obj->position);
    };
    addComponent(hookHitbox);

    
    this->addComponent(spriteSystem);
    kNgine::addObject(characterSprites);
    this->addComponent(new kNgine::NodeObjectComponent(this, MainCamera));
  }
  void update(std::vector<kNgine::msg> msgs)
  {
    ComponentGameObject::update(msgs);
    f32 time;
    v2 newVel = {0, 0};
    v2 mousePos;

    for (kNgine::msg m : msgs)
    {
      if (m.msgType == kNgine::msg::ASCII_KEY)
      {
        if (m.key & KeyBitmap(KEY_D))
        {
          newVel.x += 1;
        }
        if (m.key & KeyBitmap(KEY_A))
        {
          newVel.x -= 1;
        }
        if (m.key & KeyBitmap(KEY_W))
        {
          newVel.y += 1;
        }
        if (m.key & KeyBitmap(KEY_S))
        {
          newVel.y -= 1;
        }
        if (m.key & KeyBitmap(KEY_SPACE))
        {
          newVel.y += 5;
        }
        if (m.key & KeyBitmap(KEY_P))
        {
          std::cout << "position" << std::endl;
          std::cout << position.x << " " << position.y << std::endl;
        }
      }
      else if (m.msgType == kNgine::msg::CURSOR)
      {
        mousePos = m.cursorPos;
      }
      else if (m.msgType == kNgine::msg::TIME_ELAPSED)
      {
        time = m.time;
      }
    }
    newVel = V2MultiplyF32(newVel, time);
    newVel = V2MultiplyF32(newVel, 5);
    findComponent<kNgine::kPhysicsBodyComponent>(kNgine::ObjectFlags::Physics)->addVelocity(newVel);
    if (findComponent<kNgine::kPhysicsBodyComponent>(kNgine::ObjectFlags::Physics)->getVelocity().x < -0.1 && right)
    {
      v2 spriteDimension=findComponent<kNgine::RenderableSystem>("[Rend_SYS]")->getSpriteDimensions();
      spriteDimension.x*=-1;
      findComponent<kNgine::RenderableSystem>("[Rend_SYS]")->setSpriteDimensions(spriteDimension);
      right = false;
    }
    else if (findComponent<kNgine::kPhysicsBodyComponent>(kNgine::ObjectFlags::Physics)->getVelocity().x > 0.1 && !right)
    {
      v2 spriteDimension=findComponent<kNgine::RenderableSystem>("[Rend_SYS]")->getSpriteDimensions();
      spriteDimension.x*=-1;
      findComponent<kNgine::RenderableSystem>("[Rend_SYS]")->setSpriteDimensions(spriteDimension);
      right = true;
    }
  }
};
