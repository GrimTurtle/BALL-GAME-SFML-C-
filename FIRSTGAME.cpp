#include <SFML/Graphics.hpp>
#include <iostream>

int main()

{

sf::RenderWindow window(sf::VideoMode({1366, 720}), "Bounce" );

//FOR CIRCLE

sf::CircleShape circle(10.f);           
circle.setFillColor(sf::Color::Blue);
circle.setPosition({683.f, 360.f});

float radius=10.f;
float velocityX=1.f;
float velocityY=1.f;
float circlespeed=0.1f;


// FOR PANEL

sf::RectangleShape panel({100.f, 20.f});
panel.setFillColor(sf::Color::Red);
panel.setPosition({633.f, 700.f});
float panelspeed = 2.f;


while (window.isOpen())
{
   while(auto event = window.pollEvent())
   {
    if (event->is<sf::Event::Closed>())
    window.close();
   }

   //FOR PANEL MOVEMENT


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
   panel.move({-panelspeed, 0.f});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
   panel.move({panelspeed, 0.f});
   
    //FOR LEFT EDGE

    if(panel.getPosition().x < 0.f)
   panel.setPosition({0.f, panel.getPosition().y});

    //FOR RIGHT EDGE

   if(panel.getPosition().x > 1366.f-panel.getSize().x)
   panel.setPosition({ 1366.f-panel.getSize().x, panel.getPosition().y});

    //FOR TOP EDGE

   if(panel.getPosition().y <0.f)
   panel.setPosition({panel.getPosition().x, 0.f});

    //FOR BOTTOM EDGE

   if(panel.getPosition().y > 720.f-panel.getSize().y)
   panel.setPosition({panel.getPosition().x, 720.f-panel.getSize().y});



if (circle.getGlobalBounds().findIntersection(panel.getGlobalBounds()))
{
    velocityY= -std::abs(velocityY);
    circle.setPosition({circle.getPosition().x, panel.getPosition().y-radius*2});
}

//FOR CIRCLE MOVEMENT

  circle.move({velocityX, velocityY});

  //FOR LEFT EDGE

  if(circle.getPosition().x <= 0.f)
  {
    velocityX= std::abs(velocityX);
    circle.setPosition({0.f , circle.getPosition().y});
  }


  //FOR RIGHT EDGE


  if(circle.getPosition().x >= 1366.f-radius * 2)
  {
    velocityX= -std::abs(velocityX);
    circle.setPosition({1366.f - radius * 2, circle.getPosition().y});
  }


  //FOR TOP EDGE

  if(circle.getPosition().y <= 0.f)
  {
    velocityY=std::abs(velocityY);
    circle.setPosition({circle.getPosition().x, 0.f});
  }
  

  //FOR BOTTOM EDGE

  if(circle.getPosition().y >= 720-radius*2)
  {
    velocityY= -std::abs(velocityY);
    circle.setPosition({circle.getPosition().x, 720.f-radius*2});
  }

window.clear(sf::Color::Black);
window.draw(circle);
window.draw(panel);
window.display();

}

return 0;

}
