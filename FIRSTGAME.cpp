#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

enum class Gamestate
{
  Homescreen,
  Playing,
  GameOver,
  Highscore
};

void saveHighscore(int score)
{
  std::ofstream file("highscore.txt");
  file << score;
}

int loadHighscore()
{
  std::ifstream file("highscore.txt");
  int score =0;
  if (file.is_open())
    file >> score;
  return score;
}

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


//FOR TEXT

sf::Font font;
if 
(!font.openFromFile("PressStart2p-Regular.ttf"))
return -1;


//HOME SCREEN TEXT

sf::Text homeText(font);
homeText.setCharacterSize(48);
homeText.setFillColor(sf::Color::White);
homeText.setPosition({480.f, 150.f});
homeText.setString("Breakout");


//MENU TEXT

sf::Text menuText(font);
menuText.setCharacterSize(28);
menuText.setFillColor(sf::Color::White);
menuText.setString("NEW GAME");
menuText.setPosition({550.f, 320.f});

sf::Text highscoreText(font);
highscoreText.setCharacterSize(28);
highscoreText.setFillColor(sf::Color::White);
highscoreText.setPosition({530.f, 390.f});
highscoreText.setString("HIGH SCORE");



//ARROW SELECTOR

sf::Text arrowText(font);
arrowText.setCharacterSize(28);
arrowText.setFillColor(sf::Color::White);
arrowText.setString(">");


  //HIGHSCORE MENU

  sf::Text highscoremenuText(font);
  highscoremenuText.setCharacterSize(32);
  highscoremenuText.setFillColor(sf::Color::White);
  

  sf::Text backText(font);
  backText.setCharacterSize(24);
  backText.setFillColor(sf::Color::White);
  backText.setPosition({350.f, 500.f});
  backText.setString("PRESS BACKSPACE TO GO BACK");




//TOTAL SCORE TEXT

sf::Text scoreText(font);
scoreText.setCharacterSize(20);
scoreText.setFillColor(sf::Color::White);
scoreText.setPosition({10.f, 10.f});


//LIVES TEXT

sf::Text livesText(font);
livesText.setFillColor(sf::Color::White);
livesText.setCharacterSize({20});
livesText.setPosition({10.f, 40.f});


//GAME OVER TEXT

sf::Text gameoverText(font);
gameoverText.setCharacterSize(36);
gameoverText.setFillColor(sf::Color::White);
gameoverText.setPosition({450.f, 200.f});


//enum GAMESTATE

Gamestate currentState = Gamestate::Homescreen;

int score=0;
int lives=5;
int highscore= loadHighscore();
int selectedOption=0;
float shaketTimer=0.f;
bool waitingToResume = false;

std::srand(std::time(nullptr));
sf::Text resumeText(font);
resumeText.setCharacterSize(24);
resumeText.setFillColor(sf::Color::Yellow);
resumeText.setString("PRESS ENTER TO CONTINUE");
resumeText.setPosition({380.f, 360.f});

while (window.isOpen())
{
   while(auto event = window.pollEvent())
   {
    if (event->is<sf::Event::Closed>())
    window.close();


//HOMESCREEN KEYBOARD

  if (currentState == Gamestate::Homescreen)
    {
      if (auto* key = event->getIf<sf::Event::KeyPressed>())
      {
        if (key->code ==sf::Keyboard::Key::Up)
          selectedOption=0;
          if (key->code == sf::Keyboard::Key::Down)
            selectedOption=1;
            if (key->code == sf::Keyboard::Key::Enter)
            {
              if (selectedOption == 0)
              {
                score =0;
                lives=5;
                velocityX = 1.f * (std::rand() %2 == 0 ? 1.f : -1.f);
                velocityY=1.f * (std::rand()%2 == 0 ? 1.f : -1.f);
                circle.setPosition({683.f , 360.f});
                panel.setPosition({633.f, 700.f});
                currentState = Gamestate::Playing;
              }
            if (selectedOption==1)
            currentState = Gamestate::Highscore;

            }
      }
    }

//HOMESCREEN MOUSE

    if (currentState == Gamestate::Homescreen)
    {
    if (auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
    {
      if (mouse->button == sf::Mouse::Button::Left)
      {
        sf::Vector2f mousePos = {(float)mouse->position.x,(float)mouse->position.y};
        
      if (menuText.getGlobalBounds().contains(mousePos))
        {
          currentState = Gamestate::Playing;
          score=0;
          lives=5;
          velocityX=1.f * (std::rand()%2 == 0 ? 1.f : -1.f);
          velocityY=1.f * (std::rand()%2 == 0 ? 1.f : -1.f);
          circle.setPosition({683.f, 360.f});
          panel.setPosition({633.f, 700.f});
        }
      if (highscoreText.getGlobalBounds().contains(mousePos))
        currentState= Gamestate::Highscore;  
      }
      }
    }
  //GAMEOVER SCREEN

    if(currentState == Gamestate::GameOver)
    {
      if(auto*key = event->getIf<sf::Event::KeyPressed>())
      {
        if(key->code == sf::Keyboard::Key::R)
        {
          score =0;
          lives=5;
          velocityX=1.f * (std::rand () %2 == 0 ? 1.f : -1.f);
          velocityY=1.f * (std::rand() %2 == 0 ? 1.f : -1.f);
          circle.setPosition({683.f, 360.f});
          panel.setPosition({633.f, 700.f});
          currentState = Gamestate::Playing;
        }

      if (key->code == sf::Keyboard::Key::H)
        currentState= Gamestate::Highscore;
      if (key->code == sf::Keyboard::Key::Escape)
        currentState = Gamestate::Homescreen;
      }
    }

  //PLAYING STATE

  if(currentState==Gamestate::Playing)
  {
    if(auto*key = event->getIf<sf::Event::KeyPressed>())
    {
      if (key->code == sf::Keyboard::Key::Enter && waitingToResume)
      {
        waitingToResume = false;
        velocityX = 1.f * (std::rand() % 2 == 0 ? 1.f : -1.f);
        velocityY = 1.f * (std::rand() % 2 == 0 ? 1.f : -1.f);
      }
    }
  }

   

//HIGHSCORE SCREEN 


  if (currentState == Gamestate::Highscore)
  {
    if (auto*key = event->getIf<sf::Event::KeyPressed>())
      if (key->code == sf::Keyboard::Key::Backspace)
      currentState= Gamestate::Homescreen;
  }
   }
   if (currentState == Gamestate::Playing)

{

   
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

//PANEL COLLISION

  if (circle.getGlobalBounds().findIntersection(panel.getGlobalBounds()))
{
    velocityY= -std::abs(velocityY);
    circle.setPosition({circle.getPosition().x, panel.getPosition().y-radius*2});score++;
    if(velocityX >0) velocityX += 0.05f;
    else velocityX -= 0.05f;
    if (velocityY > 0) velocityY += 0.05f;
    else velocityY -= 0.05f;

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
    lives--;
    shaketTimer=0.5f;
    circle.setPosition({683.f, 360.f});
    velocityX=0.f;
    velocityY=0.f;
    waitingToResume = true;

    if (lives <= 0)
    {
    if (score > highscore)
    {
      highscore = score;
      saveHighscore(highscore);
    }
    currentState = Gamestate::GameOver;
    waitingToResume = false;
  }
}

if (shaketTimer > 0.f)
{
  shaketTimer -= 0.016f;
  float offsetX = (std::rand() %16) -8;
  float offsetY = (std::rand() %16) - 8;
  sf::View shakeview = window.getDefaultView();
  shakeview.setCenter({683.f + offsetX, 360.f + offsetY});
  window.setView(shakeview);
}

else

window.setView(window.getDefaultView());

scoreText.setString("SCORE: " + std::to_string(score));
livesText.setString("LIVES: " + std::to_string(lives));

}

if(currentState==Gamestate::Homescreen)
{
  menuText.setFillColor(selectedOption == 0 ? sf::Color::Cyan : sf::Color::White);
  highscoreText.setFillColor(selectedOption == 1 ? sf::Color::Cyan : sf::Color::White);

  float arrowY = selectedOption ==0 ? 320.f : 390.f;
  arrowText.setPosition({510.f, arrowY});

  sf::Vector2f mouse = {(float) sf::Mouse::getPosition(window).x,(float)sf::Mouse::getPosition(window).y};
  if (menuText.getGlobalBounds().contains(mouse))
  {
    menuText.setFillColor(sf::Color::Cyan);
    selectedOption = 0;
  }
  if (highscoreText.getGlobalBounds().contains(mouse))
  {
    highscoreText.setFillColor(sf::Color::Cyan);
    selectedOption = 1;
  }
}


//DRAW SECTION 


window.clear(sf::Color::Black);

if(currentState == Gamestate::Homescreen)
{
  window.draw(homeText);
  window.draw(arrowText);
  window.draw(menuText);
  window.draw(highscoreText);
}

else if (currentState == Gamestate::Playing)

{
window.draw(circle);
window.draw(panel);
window.draw(scoreText);
window.draw(livesText);
if (waitingToResume)
  window.draw(resumeText);
}

else if (currentState == Gamestate::Highscore)
{
  highscoremenuText.setString("HIGH SCORE: " + std::to_string(highscore));
  highscoremenuText.setPosition({430.f, 300.f});
  window.draw(highscoremenuText);
  window.draw(backText);
}
else if (currentState == Gamestate::GameOver)
{
  gameoverText.setString("GAME OVER\nScore: " + std::to_string(score) + 
  "\n\nR - RESTART\nH - HIGH SCORE\nESC - MENU");
  window.draw(gameoverText);
}
window.display();
}

return 0;

}
