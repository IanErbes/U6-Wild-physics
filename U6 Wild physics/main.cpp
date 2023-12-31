#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>

class Pelotas {
public:
    sf::CircleShape shape;
    float velocity;
    float acceleration;

    Pelotas(float radius, float initialVelocity, float initialAcceleration) {
        shape.setRadius(radius);
        shape.setFillColor(sf::Color::Cyan);
        shape.setPosition(rand() % 700 + 50, -radius); 
        velocity = 2.0f; 
        acceleration = 0.05f; 
    }
    void update() {
        velocity += acceleration;
        shape.move(0, velocity);
    }
};

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Wild Physcis");
    window.setFramerateLimit(60);

    sf::RectangleShape projectile(sf::Vector2f(10, 20));
    projectile.setFillColor(sf::Color::Magenta);
    projectile.setPosition(400, 550); 
    float projectileSpeed = -5.0f;    
    
    sf::Clock clock;
    sf::Time elapsedTime;

    int score = 0;

    std::vector<Pelotas> balls;

    srand(static_cast<unsigned int>(time(0)));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (clock.getElapsedTime().asSeconds() > 0.5f) {
                    projectile.setPosition(400, 550); 
                    clock.restart();
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && projectile.getPosition().x < 790) {
            projectile.move(5, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && projectile.getPosition().x > 0) {
            projectile.move(-5, 0);
        }

        if (rand() % 100 < 1) {
            balls.push_back(Pelotas(20, 2.0f, 0.1f));
        }

        for (auto& ball : balls) {
            ball.update();

            if (projectile.getGlobalBounds().intersects(ball.shape.getGlobalBounds())) {
                score += 10;
                ball.shape.setPosition(rand() % 700 + 50, -ball.shape.getRadius()); 
            }

            ball.velocity = 2.0f;

            if (ball.shape.getPosition().y > window.getSize().y) {
                ball.shape.setPosition(rand() % 700 + 50, -ball.shape.getRadius()); 
            }
        } 

        window.clear();

        window.draw(projectile);

        for (const auto& ball : balls) {
            window.draw(ball.shape);
        }

        sf::Font font;
        font.loadFromFile("arial.ttf"); 
        sf::Text scoreText("Puntaje: " + std::to_string(score), font, 20);
        scoreText.setPosition(10, 10);
        window.draw(scoreText);

        window.display();
    }

    return 0;
}
