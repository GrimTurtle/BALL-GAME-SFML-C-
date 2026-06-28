#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(0));
    std::string CharacterName = "";
    int health = 100;
    
std::cout << "What would you like to be called? " << std::endl;

  std::getline(std::cin,CharacterName);

    std::cout <<"Welcome to the shithole of C++ world " << CharacterName << "!" << std::endl;
    std::cout << "\n" << std::endl;

    std::cout << "You are now in the C++ world, where you can create amazing things!" << std::endl;
    std::cout << "\n" << std::endl;
    std::cout << "Your total health is: " << health << "!" << "  Goodluck survivor!" << std::endl;
   

    while (health>0) {


    std::string Answer;

    std::cout << "While you were walking you found a wild mushroom which looks delicious, and it's tempting you to eat it. " << std::endl;
    std::cout << "\n" << std::endl;

    std::cout << "Do you want to eat it? (yes/no) " <<std::endl;
std::cout << "\n" << std::endl;

std::getline(std::cin, Answer);
  
    for(char &c : Answer) {
        c = std::tolower(c);
    }

if (Answer == "yes") {

    int coinFlip = std::rand() %2;

    std::cout <<"--------------------------" << std::endl;

    if (coinFlip == 0) 
    {
    std::cout << "Oh no the mushroom you ate was poisonous and it damage your health!!" <<std::endl;
    std::cout << "\n" << std::endl;

    std::cout<< "------------------------------------" << std::endl;

    health= health-20;

    std::cout << "Your total health is now:" << health << std::endl;

    std::cout << "\n" << std::endl;

    std::cout << "---------------------------------------" <<std::endl;
          }
   else if(coinFlip == 1)
   {
    std::cout << "Congratulations survivor, the mushroom you ate was delicious and it healed your health!!" << " Goodluck survivor!" << std::endl;
    std::cout << "\n" << std::endl;
    health = health + 20;
    std::cout << "Your total health is now:" << health << std::endl;
    std::cout << "\n" << std::endl;
    std::cout << "---------------------------------------" <<std::endl;
   }

}
else if(Answer == "no")
{
        std::cout << "Good choice, you avoided the unknown mushroom and your health is still:" << health << std::endl;

    std::cout << "\n" << std::endl;
    std::cout << "---------------------------------------" <<std::endl;

std::cout << "So what's your next move survivor?" << std::endl;
    
    }
    }
    std::cout << "Oh no you died, your health is now: " << health << std::endl;
return 0;
}

