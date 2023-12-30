#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

#define IZQUIERDA sf::Keyboard::Left
#define DERECHA sf::Keyboard::Right
#define ARRIBA sf::Keyboard::Up
#define ABAJO sf::Keyboard::Down

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PLAYER_SPEED = 200.0f;
const float OBSTACLE_SPEED = 100.0f;
const float SPAWN_INTERVAL = 2.0f;

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();

    void spawnObstacle();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
    sf::RenderWindow window;
    sf::Clock clock;

    sf::Texture playerTexture;
    sf::Sprite player;

    sf::Texture obstacleTexture;
    sf::Texture obstacleTexture1;  // Nueva textura para un tipo de obstáculo
    sf::Texture obstacleTexture2;  // Nueva textura para otro tipo de obstáculo
    std::vector<sf::Sprite> obstacles;

    sf::Font font;
    sf::Text scoreText;
    int score;

    sf::SoundBuffer hitBuffer;
    sf::Sound hitSound;

    sf::Time spawnTimer;
    
    sf::Texture backgroundTexture;
    sf::Sprite background;

};

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "FinalTO"),
      playerTexture(), player(), obstacleTexture(), obstacleTexture1(), obstacleTexture2(), obstacles(),
      font(), scoreText(), score(0), hitBuffer(), hitSound(), spawnTimer()
{
    if (!playerTexture.loadFromFile("resources/tacho.png") || !obstacleTexture.loadFromFile("resources/basura1.png") ||
        !obstacleTexture1.loadFromFile("resources/basura2.png") || !obstacleTexture2.loadFromFile("resources/basura3.png")) {
        std::cerr << "Error al cargar texturas." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    player.setTexture(playerTexture);
    player.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - 50.0f);

    if (!font.loadFromFile("resources/Futura Condensed.ttf")) {
        std::cerr << "Error al cargar la fuente." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(10.0f, 10.0f);

    if (!hitBuffer.loadFromFile("resources/beep.wav")) {
        std::cerr << "Error al cargar el sonido." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    hitSound.setBuffer(hitBuffer);
    
    if (!backgroundTexture.loadFromFile("resources/fondo.png")) {
    std::cerr << "Error al cargar la imagen de fondo." << std::endl;
    std::exit(EXIT_FAILURE);
    }
    background.setTexture(backgroundTexture);

}

Game::~Game() {
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update(clock.restart());
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            handlePlayerInput(event.key.code, true);
        } else if (event.type == sf::Event::KeyReleased) {
            handlePlayerInput(event.key.code, false);
        }
    }
}

void Game::update(sf::Time deltaTime) {
    sf::Vector2f movement(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(IZQUIERDA) && player.getPosition().x > 0) {
        movement.x -= PLAYER_SPEED;
    }
    if (sf::Keyboard::isKeyPressed(DERECHA) && player.getPosition().x < WINDOW_WIDTH - player.getGlobalBounds().width) {
        movement.x += PLAYER_SPEED;
    }

    player.move(movement * deltaTime.asSeconds());

    for (auto it = obstacles.begin(); it != obstacles.end();) {
        it->move(0.0f, OBSTACLE_SPEED * deltaTime.asSeconds());

        if (it->getGlobalBounds().intersects(player.getGlobalBounds())) {
            hitSound.play();
            score++;
            spawnTimer = sf::seconds(SPAWN_INTERVAL);
            it = obstacles.erase(it);
        } else {
            if (it->getPosition().y > WINDOW_HEIGHT) {
                score--;
                hitSound.play();
                sf::SoundBuffer fallBuffer;
                sf::Sound fallSound;
                if (fallBuffer.loadFromFile("resources/beep2.wav")) {
                    fallSound.setBuffer(fallBuffer);
                    fallSound.play();
                }
                it = obstacles.erase(it);
            } else {
                ++it;
            }
        }
    }

    spawnTimer += deltaTime;
    if (spawnTimer >= sf::seconds(SPAWN_INTERVAL)) {
        spawnObstacle();
        spawnTimer = sf::Time::Zero;
    }

    scoreText.setString("Puntaje: " + std::to_string(score));
}

void Game::render() {
    window.clear();

    // Dibujar fondo
    window.draw(background);

    // Dibujar jugador
    window.draw(player);

    // Dibujar obstáculos
    for (const auto& obstacle : obstacles) {
        window.draw(obstacle);
    }

    // Dibujar texto de puntaje
    window.draw(scoreText);

    window.display();
}


void Game::spawnObstacle() {
    sf::Sprite obstacle;
    int obstacleType = rand() % 3;  // Asumiendo que hay 3 tipos de obstáculos en total

    switch (obstacleType) {
    case 0:
        obstacle.setTexture(obstacleTexture);
        break;
    case 1:
        obstacle.setTexture(obstacleTexture1);
        break;
    case 2:
        obstacle.setTexture(obstacleTexture2);
        break;
    default:
        break;
    }

    obstacle.setPosition(static_cast<float>(rand() % (WINDOW_WIDTH - static_cast<int>(obstacle.getGlobalBounds().width))), 0.0f);
    obstacles.push_back(obstacle);
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    Game game;
    game.run();

    return 0;
}

