#include "CallOfRizan.hpp"
#include <iostream>

kNgine::Camera *MainCamera = new kNgine::Camera(20, 1920, 1080);
MainCharacter *character;

int main()
{
  character = new MainCharacter();
  kNgine::window_name = "CallOfRizan";
  kNgine::window_size = v2(1980, 1080);


  kNgine::addObject(character);

  { //floor
    kNgine::ComponentGameObject *floor = new kNgine::ComponentGameObject();
    floor->position = v3(0, -5, 0);

    // kNgine::physics::cpPhysicsBodyComponent *floorPhys = new kNgine::physics::b2Rect(floor, 20, 1, 50, 0.5f);
    // floorPhys->setStatic(false);

    kNgine::kPhysicsBodyComponent *floorPhys = kNgine::kPhysicsBodyComponent::staticBody(floor, kNgine::kHitBoxRect(v2(20, 1), 1, 0.5));
    floor->addComponent(floorPhys);

    kNgine::SpriteComponent *floorSpr = new kNgine::SpriteComponent(floor, kNgine::fillSprite(200, 200, {0, 255, 0, 255}));
    floorSpr->spriteDimension = v2(20, 1);
    floor->addComponent(floorSpr);

    kNgine::addObject(floor);
  }
  kNgine::addObject(new kNgine::cpPhysicsEngine(v2(0,-1)));

  kNgine::addObject(new kNgine::kPhysicsRenderer(MainCamera));

  kNgine::start();
  kNgine::cleanup();
  return 0;
}