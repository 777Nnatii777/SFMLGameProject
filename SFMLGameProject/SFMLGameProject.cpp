#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Start {
public:
    sf::RenderWindow mainokno;

    Start() : mainokno(sf::VideoMode(800, 800), "SFML Window", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize)
    {
        zielony.setFillColor(sf::Color::Green);
        zielony.setSize(sf::Vector2f(200.0f, 100.0f));
        zielony.setPosition(300.0f, 300.0f);

        czerwony.setFillColor(sf::Color::Red);
        czerwony.setSize(sf::Vector2f(200.0f, 100.0f));
        czerwony.setPosition(300.0f, 450.0f);
    }


    void handleEvents() {
        sf::Event sprawdzenie;
        while (mainokno.pollEvent(sprawdzenie)) {
            switch (sprawdzenie.type) {
            case sf::Event::Closed:
                mainokno.close();
                break;
            case sf::Event::MouseButtonPressed:

                if (sprawdzenie.mouseButton.button == sf::Mouse::Left) {

                    if (zielony.getGlobalBounds().contains(sf::Vector2f(sprawdzenie.mouseButton.x, sprawdzenie.mouseButton.y))) {
                        std::cout << "Kliknieto zielony" << std::endl;
                        mainokno.close();
                    }

                    else if (czerwony.getGlobalBounds().contains(sf::Vector2f(sprawdzenie.mouseButton.x, sprawdzenie.mouseButton.y))) {
                        std::cout << "Kliknieto czerwony, exit" << std::endl;
                        mainokno.close();
                        exit(0);
                    }
                }
                break;
            case sf::Event::Resized:
                std::cout << "New window width: " << sprawdzenie.size.width << " New window height: " << sprawdzenie.size.height << std::endl;
                break;
            default:
                break;
            }
        }
    }


    void draw() {
        mainokno.clear(sf::Color::White);

        mainokno.draw(zielony);

        mainokno.draw(czerwony);
        mainokno.display();
    }

private:
    sf::RectangleShape zielony;
    sf::RectangleShape czerwony;
};


void openGameWindow() {
    sf::RenderWindow gameWindow(sf::VideoMode(800, 800), "Game Window");

    while (gameWindow.isOpen()) {
        sf::Event event;
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                gameWindow.close();
        }
        gameWindow.clear(sf::Color::Black);

        gameWindow.display();
    }
}

int main() {
    Start start;
    while (start.mainokno.isOpen()) {
        start.handleEvents();
        start.draw();


        if (!start.mainokno.isOpen()) {

            openGameWindow();
        }
    }
    return 0;
}
