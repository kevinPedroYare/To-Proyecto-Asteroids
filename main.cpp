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
    ~Game(); // Agregado para liberar recursos
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
    std::vector<sf::Sprite> obstacles;

    sf::Font font;
    sf::Text scoreText;
    int score;

    sf::SoundBuffer hitBuffer;
    sf::Sound hitSound;

    sf::Time spawnTimer;
};

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "FinalTO"),
    playerTexture(), player(), obstacleTexture(), obstacles(),
    font(), scoreText(), score(0), hitBuffer(), hitSound(), spawnTimer() {
    // Cargar texturas
    if (!playerTexture.loadFromFile("tacho.png") || !obstacleTexture.loadFromFile("basura.png")) {
        // Manejar el error al cargar texturas
        std::cerr << "Error al cargar texturas." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // Inicializar jugador
    player.setTexture(playerTexture);
    player.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT - 50.0f);

    // Inicializar texto
    if (!font.loadFromFile("Futura Condensed.ttf")) {
        // Manejar el error al cargar la fuente
        std::cerr << "Error al cargar la fuente." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.0f, 10.0f);

    // Inicializar sonido
    if (!hitBuffer.loadFromFile("beep.wav")) {
        // Manejar el error al cargar el sonido
        std::cerr << "Error al cargar el sonido." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    hitSound.setBuffer(hitBuffer);
}

Game::~Game() {
    // Liberar recursos
    // No es necesario en este caso ya que los objetos sf::Texture y sf::SoundBuffer se encargan automáticamente de liberar sus recursos.
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
        }
        else if (event.type == sf::Event::KeyPressed) {
            handlePlayerInput(event.key.code, true);
        }
        else if (event.type == sf::Event::KeyReleased) {
            handlePlayerInput(event.key.code, false);
        }
    }
}

void Game::update(sf::Time deltaTime) {
    // Actualizar posición del jugador
    sf::Vector2f movement(0.0f, 0.0f);
    if (sf::Keyboard::isKeyPressed(IZQUIERDA) && player.getPosition().x > 0) {
        movement.x -= PLAYER_SPEED;
    }
    if (sf::Keyboard::isKeyPressed(DERECHA) && player.getPosition().x < WINDOW_WIDTH - player.getGlobalBounds().width) {
        movement.x += PLAYER_SPEED;
    }

    player.move(movement * deltaTime.asSeconds());

    // Actualizar obstáculos
    for (auto it = obstacles.begin(); it != obstacles.end();) {
        it->move(0.0f, OBSTACLE_SPEED * deltaTime.asSeconds());

        // Verificar colisiones con el jugador
        if (it->getGlobalBounds().intersects(player.getGlobalBounds())) {
            hitSound.play();
            score++;
            spawnTimer = sf::seconds(SPAWN_INTERVAL);
            it = obstacles.erase(it); // Utilizar el valor devuelto por erase para obtener el siguiente iterador válido
        }
        else {
            // Verificar si los obstáculos han llegado al final de la pantalla
            if (it->getPosition().y > WINDOW_HEIGHT) {
                score--;
                hitSound.play();
                it = obstacles.erase(it); // Utilizar el valor devuelto por erase para obtener el siguiente iterador válido
            }
            else {
                ++it;
            }
        }
    }

    // Controlar la frecuencia de aparición de obstáculos
    spawnTimer += deltaTime;
    if (spawnTimer >= sf::seconds(SPAWN_INTERVAL)) {
        spawnObstacle();
        spawnTimer = sf::Time::Zero;
    }

    // Actualizar el texto del puntaje
    scoreText.setString("Puntaje: " + std::to_string(score));
}

void Game::render() {
    window.clear();

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
    sf::Sprite obstacle(obstacleTexture);
    obstacle.setPosition(static_cast<float>(rand() % (WINDOW_WIDTH - static_cast<int>(obstacle.getGlobalBounds().width))), 0.0f);
    obstacles.push_back(obstacle);
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    // Manejar la entrada del jugador (por ejemplo, teclas de disparo, si es que se implementa)
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    Game game;
    game.run();

    return 0;
}

