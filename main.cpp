/* Box2D helloworld.cpp combined with SFML */
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

static const float SCALE = 10.0; //10px = 1 meter
static const float WWIDTH= 800.0; //screen width
static const float WHEIGHT= 600.0; //screen width

b2Vec2 convertWorldToScreen( const b2Vec2& v) {
  return b2Vec2( (v.x * SCALE + WWIDTH/2) , -v.y * SCALE + WHEIGHT/4);
}

// This is a simple example of building and running a simulation
// using Box2D. Here we create a large ground box and a small dynamic
// box.
int main(int argc, char** argv)
{
  //Setup SFML
  sf::RenderWindow window( sf::VideoMode( WWIDTH,WHEIGHT), "It really is Box2D");

  B2_NOT_USED(argc);
  B2_NOT_USED(argv);

  // Textures
  sf::Texture GroundTexture;
  sf::Texture BoxTexture;
  GroundTexture.loadFromFile("grass.png");
  BoxTexture.loadFromFile("wood.png");
  // Sprites
  sf::Sprite GroundSprite;
  sf::Sprite BodySprite;
  GroundSprite.setTexture(GroundTexture);
  GroundSprite.setTextureRect(sf::IntRect(0, 0, 10 * SCALE, 2 * SCALE));
  GroundSprite.setOrigin(5 * SCALE, 1 * SCALE); // origin in middle

  BodySprite.setTexture( BoxTexture);
  BodySprite.setTextureRect(sf::IntRect(0, 0, 2 * SCALE, 2 * SCALE));
  BodySprite.setOrigin( 1 * SCALE, 1 * SCALE); //origin in middle

  // Define the gravity vector.
  b2Vec2 gravity(0.0f, -1.0f);

  // Construct a world object, which will hold and simulate the rigid bodies.
  b2World world(gravity);

  // Define the ground body.
  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(0.0f, -12.0f);


  // Call the body factory which allocates memory for the ground body
  // from a pool and creates the ground box shape (also from a pool).
  // The body is also added to the world.
  b2Body* groundBody = world.CreateBody(&groundBodyDef);

  // Define the ground box shape.
  b2PolygonShape groundBox;

  // The extents are the half-widths of the box.
  groundBox.SetAsBox(5.0f, 1.0f);

  // Add the ground fixture to the ground body.
  groundBody->CreateFixture(&groundBox, 0.0f);

  // Define the dynamic body. We set its position and call the body factory.
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(3.0f, 8.0f);
  b2Body* body = world.CreateBody(&bodyDef);
  body->SetTransform( body->GetPosition(), 1.2); //rotate

  // Define another box shape for our dynamic body.
  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(1.0f, 1.0f); //Half widths. so actually 2x2 box

  // Define the dynamic body fixture.
  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;

  // Set the box density to be non-zero, so it will be dynamic.
  fixtureDef.density = 1.0f;

  // Override the default friction.
  fixtureDef.friction = 0.3f;

  // Add the shape to the body.
  body->CreateFixture(&fixtureDef);

  // Prepare for simulation. Typically we use a time step of 1/60 of a
  // second (60Hz) and 10 iterations. This provides a high quality simulation
  // in most game scenarios.
  float32 timeStep = 1.0f / 60.0f;
  int32 velocityIterations = 6;
  int32 positionIterations = 2;

  // This is our little game loop.
  while (window.isOpen())
  {
    // Check if it's time to go
    sf::Event event;
    while (window.pollEvent( event))
    {
      if( event.type == sf::Event::Closed)
        window.close();
    }
    window.clear();
    // Instruct the world to perform a single step of simulation.
    // It is generally best to keep the time step and iterations fixed.
    world.Step(timeStep, velocityIterations, positionIterations);

    // Draw it
    // get the position and angle of the body
    b2Vec2 pos = body->GetPosition();
    float32 angle = body->GetAngle();
    pos = convertWorldToScreen( pos);

    BodySprite.setPosition(pos.x, pos.y);
    BodySprite.setRotation(180/b2_pi * angle);
    window.draw(BodySprite);

    // get the position and angle of the ground
    pos = groundBody->GetPosition();
    angle = groundBody->GetAngle();
    pos = convertWorldToScreen( pos);

    GroundSprite.setPosition(pos.x, pos.y);
    GroundSprite.setRotation(180/b2_pi * angle);
    window.draw(GroundSprite);


    window.display();
  }

  // When the world destructor is called, all bodies and joints are freed. This can
  // create orphaned pointers, so be careful about your world management.

  return 0;
}

