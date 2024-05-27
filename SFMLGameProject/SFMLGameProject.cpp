#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

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
    void sprawdzaniemyszy() {
        sf::Event dzialaniemyszy;
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
};


int main() {
    startmenu objstartmenu;

    // Pętla renderująca
    while (objstartmenu.pobierzprivateoknostartmenu().isOpen()) {
        objstartmenu.sprawdzaniemyszy();   // Obsługa zdarzeń
        objstartmenu.narysujbloki();       // Rysowanie bloków
    }

    return 0;
}
