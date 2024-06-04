#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono> // std::chrono::microseconds
#include <thread> // std::this_thread::sleep_for

//tak napsiane to sprawia ze maingra dziedziczy wszystko z public i protected z startmenu ale nie z private;
class maingra:public startmenu{


private:



public:


};




class startmenu {

protected:
    sf::RenderWindow oknostartmenu;
    sf::RectangleShape zielony;
    sf::RectangleShape czerwony;
    sf::Text tekststartmenu;
    sf::Font fontstartmenu;
    sf::Text tekststartmenu2;
    

public:
    startmenu() : oknostartmenu(sf::VideoMode(400, 400), "SFML Window", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize)
        
    {

    }

   

        sf::RenderWindow& pobierzprivateoknostartmenu() {
            return oknostartmenu;
        }

        bool rozpocznijnowagra = false;
        //sprawdzanie co robi mysza w funkcji
        void sprawdzaniemyszy(sf::Event& dzialaniemyszy) {
            while (oknostartmenu.pollEvent(dzialaniemyszy)) {
                if (dzialaniemyszy.type == sf::Event::Closed) {
                    oknostartmenu.close();
                }
                //definiuje co to znaczy ze klikniento lewy
                if (dzialaniemyszy.type == sf::Event::MouseButtonPressed) {
                    if (dzialaniemyszy.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2f pozycjamyszypodczasklikulewego(dzialaniemyszy.mouseButton.x, dzialaniemyszy.mouseButton.y);
                        //jesli klikniento na czerwony
                        if (czerwony.getGlobalBounds().contains(pozycjamyszypodczasklikulewego)) {
                            std::cout << "click red" << std::endl;
                            oknostartmenu.close();
                        }
                        else if (zielony.getGlobalBounds().contains(pozycjamyszypodczasklikulewego)) {
                            std::cout << "click red" << std::endl;
                            oknostartmenu.close();
                            rozpocznijnowagra = true;

                        }


                    }

                }

            }
        }

        void sprawdzaniestanurozpocznijnowagra() {

            if (rozpocznijnowagra) {
                maingra gra;


            }
        }


};

    


int main() {

	startmenu objstartmenu;
	sf::Event dzialaniemyszy;

	

    //dosłownie to jest tuta tylko temu a nie w maingra bo deklaruje tu sf::Event dzialaniemyszy bo inaczej by tu pusto bylo
	while (objstartmenu.pobierzprivateoknostartmenu().isOpen()) {
        objstartmenu.sprawdzaniemyszy(dzialaniemyszy);
	}


   


    return 0;

}