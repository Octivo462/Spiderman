#include <SFML/Graphics.hpp>
#include <cmath>

int main() {
    const float width = 800.f;
    const float height = 600.f;
    sf::RenderWindow window(sf::VideoMode(width, height), "Spider-Cube");
    window.setFramerateLimit(60);

    sf::RectangleShape cube(sf::Vector2f(30.f, 30.f));
    cube.setFillColor(sf::Color::Red);
    cube.setOrigin(15.f, 15.f);

    sf::Vector2f pos(100.f, 300.f);
    sf::Vector2f prev_pos = pos;
    sf::Vector2f gravity(0.f, 0.8f);
    sf::Vector2f anchor;

    bool IsSwinging = false;
    float rest_length = 0.f;
    float max_stretch = 1.5f;
    float stiffness = 0.1f;   
    float friction = 0.995f;   
    float bounce = 0.7f;       



    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        bool IsBtnPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        if (IsBtnPressed) {
            anchor = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        }

        if (IsBtnPressed && !IsSwinging) {
            IsSwinging = true;
            sf::Vector2f diff = pos - anchor;
            rest_length = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        }
        else if (!IsBtnPressed && IsSwinging) {
            IsSwinging = false;
        }

        sf::Vector2f velocity = (pos - prev_pos) * friction;
        prev_pos = pos;
        pos += velocity + gravity;

        if (IsSwinging) {
            sf::Vector2f diff = pos - anchor;
            float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
            float max_length = rest_length * max_stretch;

            if (dist > max_length) {
                sf::Vector2f unitDir = diff / dist;
                pos = anchor + unitDir * max_length;
            }
            else if (dist > rest_length) {
                sf::Vector2f unitDir = diff / dist;
                pos -= unitDir * (dist - rest_length) * stiffness;
            }
        }

        sf::Vector2f vel_after = pos - prev_pos;

        if (pos.y > height - 15.f) {
            pos.y = height - 15.f;
            prev_pos.y = pos.y + vel_after.y * bounce;
        }
        if (pos.y < 15.f) {
            pos.y = 15.f;
            prev_pos.y = pos.y + vel_after.y * bounce;
        }
        if (pos.x < 15.f) {
            pos.x = 15.f;
            prev_pos.x = pos.x + vel_after.x * bounce;
        }
        if (pos.x > width - 15.f) {
            pos.x = width - 15.f;
            prev_pos.x = pos.x + vel_after.x * bounce;
        }

        window.clear(sf::Color::Black);

        if (IsSwinging) {
            sf::Vertex line[] = {
                sf::Vertex(anchor, sf::Color::White),
                sf::Vertex(pos, sf::Color::White)
            };
            window.draw(line, 2, sf::Lines);
        }

        cube.setPosition(pos);
        window.draw(cube);
        window.display();
    }
}
