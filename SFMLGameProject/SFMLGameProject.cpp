#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

class clasprzegrana {
private:
    sf::RenderWindow oknoprzegrana;
    sf::RectangleShape niebieski;
    sf::RectangleShape czerwony;

public:
    clasprzegrana() : oknoprzegrana(sf::VideoMode(800, 800), "SFML Window Game", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize) {
        inicjalizowanieblokow();
    }

    void inicjalizowanieblokow() {
        niebieski.setFillColor(sf::Color::Blue);
        niebieski.setSize(sf::Vector2f(200.0f, 150.0f));
        niebieski.setPosition(150.0f, 325.0f);

        czerwony.setFillColor(sf::Color::Red);
        czerwony.setSize(sf::Vector2f(200.0f, 150.0f));
        czerwony.setPosition(450.0f, 325.0f);
    }

    sf::RenderWindow& pobierzoknoprzegana() {
        return oknoprzegrana;
    }

    


    void sprawdzKlikniecie(sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

            if (niebieski.getGlobalBounds().contains(mousePos)) {

                oknoprzegrana.close();
            }
            else if (czerwony.getGlobalBounds().contains(mousePos)) {
                oknoprzegrana.close();
                exit(0); // Dodajemy to, aby zamknąć cały program
            }
        }
    }

    void narysujbloki() {
        oknoprzegrana.clear(sf::Color::Black);
        oknoprzegrana.draw(niebieski);
        oknoprzegrana.draw(czerwony);
        oknoprzegrana.display();
    }
};

class wygrana {
    // Klasa wygrana, na razie pusta
};

class maingra {
private:
    sf::RenderWindow oknomaingra;
    std::vector<sf::RectangleShape> squares;
    std::vector<sf::Color> poczatkowekolory;
    sf::Clock clock;
    int przeliczanie;
    bool bialycheck;
    int currentsuareindex;
    std::vector<int> wylosowanasekwencja;
    std::vector<int> wpisanasekwencja;
    bool sequenceComplete;
    bool usermozeklikac;
    sf::Clock clockodswiezania;
    bool flashgreen;
    bool flashred;
    bool wygrana;
    bool przegrana;

public:
    maingra() : oknomaingra(sf::VideoMode(800, 800), "SFML Window Game", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize),
        przeliczanie(0), bialycheck(false), currentsuareindex(-1), sequenceComplete(false), usermozeklikac(false), flashgreen(false), flashred(false) {
        inicjalizowanieblokow();
        srand(static_cast<unsigned>(time(0)));
    }

    void inicjalizowanieblokow() {
        std::vector<sf::Color> colors(9, sf::Color::White);
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
            poczatkowekolory.push_back(colors[i]);
        }
    }

    void narysujkwadraty() {
        oknomaingra.clear(sf::Color::Black);
        for (auto& square : squares) {
            oknomaingra.draw(square);
        }
        oknomaingra.display();
    }

    void aktualizujKolory() {
        if (przeliczanie < 3) {
            sf::Time elapsed = clock.getElapsedTime();

            if (!bialycheck && elapsed.asSeconds() >= 1.0f) {
                currentsuareindex = rand() % squares.size();
                squares[currentsuareindex].setFillColor(sf::Color::Green);
                wylosowanasekwencja.push_back(currentsuareindex);
                clock.restart();
                bialycheck = true;
            }
            else if (bialycheck && elapsed.asSeconds() >= 0.5f) {
                squares[currentsuareindex].setFillColor(sf::Color::White);
                clock.restart();
                bialycheck = false;
                przeliczanie++;
            }
        }
        else {
            sequenceComplete = true;
            usermozeklikac = true;
        }
    }

    void sprawdzKlikniecie(sf::Event& event) {
        if (usermozeklikac && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            for (int i = 0; i < squares.size(); ++i) {
                if (squares[i].getGlobalBounds().contains(mousePos)) {
                    wpisanasekwencja.push_back(i);
                    squares[i].setFillColor(sf::Color::Green);
                    clock.restart();

                    if (wpisanasekwencja.size() == wylosowanasekwencja.size()) {
                        if (wpisanasekwencja == wylosowanasekwencja) {
                            flashgreen = true;
                            clockodswiezania.restart();
                        }
                        else {
                            flashred = true;
                            clockodswiezania.restart();
                        }
                        wpisanasekwencja.clear();
                        usermozeklikac = false;
                    }
                    break;
                }
            }
        }
    }

    void resetColorsAfterUserClick() {
        if (clock.getElapsedTime().asSeconds() >= 0.5f) {
            for (int i = 0; i < squares.size(); ++i) {
                squares[i].setFillColor(sf::Color::White);
            }
        }
    }

    void flashAllGreen() {
        if (flashgreen) {
            if (clockodswiezania.getElapsedTime().asSeconds() < 0.5f) {
                for (auto& square : squares) {
                    square.setFillColor(sf::Color::Green);
                }
            }
            else if (clockodswiezania.getElapsedTime().asSeconds() < 1.0f) {
                for (auto& square : squares) {
                    square.setFillColor(sf::Color::White);
                }
            }
            else {
                flashgreen = false;
                wygrana = true;
            }
        }
    }

    void flashAllRed() {
        if (flashred) {
            if (clockodswiezania.getElapsedTime().asSeconds() < 0.5f) {
                for (auto& square : squares) {
                    square.setFillColor(sf::Color::Red);
                }
            }
            else if (clockodswiezania.getElapsedTime().asSeconds() < 1.0f) {
                for (auto& square : squares) {
                    square.setFillColor(sf::Color::White);
                }
            }
            else {
                flashred = false;
                przegrana = true;
            }
        }

        if (przegrana) {
            clasprzegrana losewindow;

            while (losewindow.pobierzoknoprzegana().isOpen()) {
                sf::Event event;
                while (losewindow.pobierzoknoprzegana().pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        losewindow.pobierzoknoprzegana().close();
                    }
                    losewindow.sprawdzKlikniecie(event);
                }

                losewindow.narysujbloki();
            }
        }
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
        tworzenieblokow();
    }

    sf::RenderWindow& pobierzprivateoknostartmenu() {
        return oknostartmenu;
    }

    void sprawdzaniemyszy(sf::Event& dzialaniemyszy) {
        while (oknostartmenu.pollEvent(dzialaniemyszy)) {
            if (dzialaniemyszy.type == sf::Event::Closed) {
                oknostartmenu.close();
            }
        }
    }

    void tworzenieblokow() {
        zielony.setFillColor(sf::Color::Green);
        zielony.setSize(sf::Vector2f(150.0f, 100.0f));
        zielony.setPosition(125.0f, 80.0f);

        czerwony.setFillColor(sf::Color::Red);
        czerwony.setSize(sf::Vector2f(150.0f, 100.0f));
        czerwony.setPosition(125.0f, 220.0f);
    }

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

    while (objstartmenu.pobierzprivateoknostartmenu().isOpen()) {
        objstartmenu.sprawdzaniemyszy(dzialaniemyszy);
        objstartmenu.narysujbloki();

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
                gra.sprawdzKlikniecie(event);
            }

            gra.narysujkwadraty();
            gra.aktualizujKolory();
            gra.resetColorsAfterUserClick();
            gra.flashAllGreen();
            gra.flashAllRed();
        }
    }

    return 0;
}