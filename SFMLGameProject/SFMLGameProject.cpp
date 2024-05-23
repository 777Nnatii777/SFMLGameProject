#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

class Start {
public:
    sf::RenderWindow mainokno;

    Start() : mainokno(sf::VideoMode(400, 400), "SFML Window", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize)
    {
        zielony.setFillColor(sf::Color::Green);
        zielony.setSize(sf::Vector2f(150.0f, 100.0f));
        zielony.setPosition(125.0f, 80.0f);

        czerwony.setFillColor(sf::Color::Red);
        czerwony.setSize(sf::Vector2f(150.0f, 100.0f));
        czerwony.setPosition(125.0f, 220.0f);
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
                        void maingra();
                        maingra();
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

void maingra() {
    sf::RenderWindow gameWindow(sf::VideoMode(800, 800), "Game Window");

    std::vector<sf::Color> colors = {
        sf::Color::Red, sf::Color::Green, sf::Color::Blue,
        sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan,
        sf::Color(83,90,217), sf::Color(200, 80, 130), sf::Color(128, 128, 128)
    };

    std::vector<sf::RectangleShape> squares;
    float squareSize = 150.0f;
    float margin = 25.0f;
    float offsetX = 150.0f;
    float offsetY = 150.0f;

    for (int i = 0; i < 9; ++i) {
        sf::RectangleShape square;
        square.setSize(sf::Vector2f(squareSize, squareSize));
        square.setFillColor(colors[i]);
        square.setPosition(offsetX + (i % 3) * (squareSize + margin), offsetY + (i / 3) * (squareSize + margin));
        squares.push_back(square);
    }

    std::srand(std::time(nullptr));
    std::vector<int> randomIndices;
    for (int i = 0; i < 3; ++i) {
        int index = std::rand() % 9; // generate random index between 0 and 8
        randomIndices.push_back(index);
    }

    sf::Clock startClock;
    sf::Clock changeClock;
    int currentSquare = 0;
    bool reverseColor = false;
    bool startedChanging = false;

    while (gameWindow.isOpen()) {
        sf::Event event;
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                gameWindow.close();
        }

        if (startClock.getElapsedTime().asSeconds() > 3.0f) {
            startedChanging = true;
        }

        if (startedChanging && changeClock.getElapsedTime().asSeconds() > 1.0f) {
            changeClock.restart();

            int index = randomIndices[currentSquare];
            if (reverseColor) {
                squares[index].setFillColor(colors[index]);
                currentSquare++;
            }
            else {
                squares[index].setFillColor(sf::Color::White);
            }

            reverseColor = !reverseColor;

            if (currentSquare >= randomIndices.size()) {
                break; // break the loop after all 3 squares have been changed
            }
        }

        gameWindow.clear(sf::Color::Black);
        for (const auto& square : squares) {
            gameWindow.draw(square);
        }
        gameWindow.display();
    }
}

int main() {
    Start start;
    while (start.mainokno.isOpen()) {
        start.handleEvents();
        start.draw();
    }
    return 0;
}