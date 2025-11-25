#include <SFML/Graphics.hpp>

int main() {
    // SFML 3: Construction de la fenêtre
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML Window");

    // Créer un cercle rouge
    sf::CircleShape circle(50.f);  // Rayon de 50 pixels
    circle.setFillColor(sf::Color::Red);
    circle.setPosition({ 375.f, 275.f });  // Centré approximativement

    while (window.isOpen()) {
        // SFML 3: pollEvent → std::optional<sf::Event>
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.draw(circle);  // Dessiner le cercle
        window.display();
    }

    return 0;
}