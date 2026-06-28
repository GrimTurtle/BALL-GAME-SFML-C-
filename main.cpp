#include <iostream>
#include <string>
int main() {
    std::string CharacterName = "";
    int health = 100;
    
std::cout << "What would you like to be called? " << std::endl;

  std::getline(std::cin,CharacterName);

    std::cout <<"Welcome to the shithole of C++ world " << CharacterName << "!" << std::endl;

    std::cout << "You are now in the C++ world, where you can create amazing things!" << std::endl;

    std::cout << "While you were walking you found a wild mushroom which looks delicious, and it's tempting you to eat it. " << std::endl;
    std::string Answer;
std::cout << "Do you want to eat it? (yes/no) " <<std::endl;
std::getline(std::cin, Answer);
if (Answer == "yes") {
    std::cout << "Oh no the mushroom you ate was poisonous and it damage your health!!" <<std::endl;
    health= health-20;
    std::cout << "Your total health is now:" << health << std::endl;
}
    else if (Answer == "no") {
        std::cout << "Good choice, you avoided the poisonous mushroom and your health is still:" << health << std::endl;
std::cout << "So what's your next move survivor?" << std::endl;
    }
    return 0;
}