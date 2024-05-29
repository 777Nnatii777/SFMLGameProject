#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

class maingra {
private:
    sf::RenderWindow oknomaingra;
    std::vector<sf::RectangleShape> squares; // zmienna członkowska do przechowywania kwadratów

public:
    maingra() : oknomaingra(sf::VideoMode(800, 800), "SFML Window Game", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize) {
        // Inicjalizacja bloków
        inicjalizowanieblokow();
    }

    void inicjalizowanieblokow() {
        // przypisywanie kolorów kwadratom
        std::vector<sf::Color> colors = {
            sf::Color::Red, sf::Color::Green, sf::Color::Blue,
            sf::Color::Yellow, sf::Color::Magenta, sf::Color::Cyan,
            sf::Color(83, 90, 217), sf::Color(200, 80, 130), sf::Color(128, 128, 128)
        };

        float squareSize = 150.0f;
        float margin = 25.0f;
        float offsetX = 25.0f;
        float offsetY = 25.0f;

        for (int i = 0; i < 9; ++i) {
            sf::RectangleShape square;
            square.setSize(sf::Vector2f(squareSize, squareSize));
            square.setFillColor(colors[i]);
            square.setPosition(offsetX + (i % 3) * (squareSize + margin), offsetY + (i / 3) * (squareSize + margin));
            squares.push_back(square);
        }
    }

    void narysujkwadraty() {
        oknomaingra.clear(sf::Color::White);
        for (auto& square : squares) {
            oknomaingra.draw(square);
        }
        oknomaingra.display();
    }

    sf::RenderWindow& getWindow() {
        return oknomaingra;
    }
};

class startmenu {
private:
    sf::RenderWindow oknostartmenu;
    sf::RectangleShape zielony;
    sf::RectangleShape czerwony;

public:
    startmenu() : oknostartmenu(sf::VideoMode(400, 400), "SFML Window", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize) {
        // Inicjalizacja bloków
        tworzenieblokow();
    }

    // Specjalny getter do przesyłania obiektu prywatnego do main()
    sf::RenderWindow& pobierzprivateoknostartmenu() {
        return oknostartmenu;
    }

    // Funkcja do sprawdzania zdarzeń myszy
    void sprawdzaniemyszy(sf::Event& dzialaniemyszy) {
        while (oknostartmenu.pollEvent(dzialaniemyszy)) {
            if (dzialaniemyszy.type == sf::Event::Closed) {
                oknostartmenu.close();
            }
        }
    }

    // Funkcja do tworzenia bloków
    void tworzenieblokow() {
        zielony.setFillColor(sf::Color::Green);
        zielony.setSize(sf::Vector2f(150.0f, 100.0f));
        zielony.setPosition(125.0f, 80.0f);

        czerwony.setFillColor(sf::Color::Red);
        czerwony.setSize(sf::Vector2f(150.0f, 100.0f));
        czerwony.setPosition(125.0f, 220.0f);
    }

    // Funkcja do rysowania bloków
    void narysujbloki() {
        oknostartmenu.clear(sf::Color::White);
        oknostartmenu.draw(zielony);
        oknostartmenu.draw(czerwony);
        oknostartmenu.display();
    }

    sf::RectangleShape& getczerwony() {
        return czerwony;
    }
    sf::RectangleShape& getzielony() {
        return zielony;
    }
};

int main() {
    startmenu objstartmenu;
    sf::Event dzialaniemyszy;

    bool startNewGame = false;

    // Pętla renderująca
    while (objstartmenu.pobierzprivateoknostartmenu().isOpen()) {
        objstartmenu.sprawdzaniemyszy(dzialaniemyszy);   // Obsługa zdarzeń
        objstartmenu.narysujbloki();       // Rysowanie bloków

        if (dzialaniemyszy.type == sf::Event::MouseButtonPressed) {
            if (dzialaniemyszy.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(dzialaniemyszy.mouseButton.x, dzialaniemyszy.mouseButton.y);

                if (objstartmenu.getczerwony().getGlobalBounds().contains(mousePos)) {
                    std::cout << "Kliknieto czerwony" << std::endl;
                    objstartmenu.pobierzprivateoknostartmenu().close();
                }
                else if (objstartmenu.getzielony().getGlobalBounds().contains(mousePos)) {
                    std::cout << "Kliknieto zielony" << std::endl;
                    objstartmenu.pobierzprivateoknostartmenu().close();
                    startNewGame = true;
                }
            }
        }
    }

    if (startNewGame) {
        maingra gra;

        while (gra.getWindow().isOpen()) {
            sf::Event event;
            while (gra.getWindow().pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    gra.getWindow().close();
                }
            }

            gra.narysujkwadraty();
        }
    }

    return 0;
}
