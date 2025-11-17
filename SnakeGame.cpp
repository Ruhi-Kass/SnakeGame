#include "SnakeGame.h"
#include "Utils.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sstream>

SnakeGame::SnakeGame()
    : gameOver(false), score(0), speedMs(INIT_SPEED_MS), dir(Dir::Stop)
{
    snake.push_back({WIDTH/2, HEIGHT/2});
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    placeFruit();
}

void SnakeGame::run()
{
    ConsoleRenderer renderer(WIDTH, HEIGHT+4); // +4 for score lines

    while (!gameOver) {
        renderer.clear();
        drawScene(renderer);
        handleInput(Keyboard::getKey());
        update();
        sleep_ms(speedMs);
    }

    // ---- Game Over screen ------------------------------------------------
    renderer.clear();
    std::ostringstream oss;
    oss << "\n\n\t\tGAME OVER!\n"
        << "\t\tFinal Score: " << score << "\n\n"
        << "\t\tPress any key to exit...\n";
    renderer.draw(oss.str());
    _getch();
}

void SnakeGame::drawScene(const ConsoleRenderer& r) const
{
    // borders
    for (int x = 0; x < WIDTH; ++x) r.draw('#', x, 0);
    for (int x = 0; x < WIDTH; ++x) r.draw('#', x, HEIGHT+1);
    for (int y = 0; y <= HEIGHT+1; ++y) {
        r.draw('#', 0, y);
        r.draw('#', WIDTH-1, y);
    }

    // snake
    r.draw('O', snake[0].x, snake[0].y);               // head
    for (size_t i = 1; i < snake.size(); ++i)
        r.draw('o', snake[i].x, snake[i].y);

    // fruit
    r.draw('*', fruit.x, fruit.y);

    // info lines (below the playfield)
    std::ostringstream info;
    info << "Score: " << score
         << "   |   WASD / Arrows = move   |   X = quit";
    r.draw(info.str() + "\n");
}

void SnakeGame::handleInput(Key k)
{
    if (k == Key::Quit) { gameOver = true; return; }

    Dir newDir = dir;
    switch (k) {
        case Key::Up:    if (dir != Dir::Down) newDir = Dir::Up;    break;
        case Key::Down:  if (dir != Dir::Up)   newDir = Dir::Down;  break;
        case Key::Left:  if (dir != Dir::Right)newDir = Dir::Left;  break;
        case Key::Right: if (dir != Dir::Left) newDir = Dir::Right; break;
        default: break;
    }
    dir = newDir;
}

void SnakeGame::update()
{
    if (dir == Dir::Stop) return;

    // move tail
    for (size_t i = snake.size() - 1; i > 0; --i)
        snake[i] = snake[i-1];

    // move head
    switch (dir) {
        case Dir::Up:    --snake[0].y; break;
        case Dir::Down:  ++snake[0].y; break;
        case Dir::Left:  --snake[0].x; break;
        case Dir::Right: ++snake[0].x; break;
        default: break;
    }

    // wall collision
    if (snake[0].x <= 0 || snake[0].x >= WIDTH-1 ||
        snake[0].y <= 0 || snake[0].y >= HEIGHT+1) {
        gameOver = true; return;
    }

    // self collision
    for (size_t i = 1; i < snake.size(); ++i)
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            gameOver = true; return;
        }

    // fruit
    if (snake[0].x == fruit.x && snake[0].y == fruit.y) {
        score += 10;
        snake.push_back(snake.back());   // grow
        placeFruit();
        if (speedMs > 60) speedMs -= 5;
    }
}

void SnakeGame::placeFruit()
{
    bool onSnake;
    do {
        onSnake = false;
        fruit.x = std::rand() % (WIDTH-2) + 1;
        fruit.y = std::rand() % (HEIGHT-1) + 1;
        for (const auto& s : snake)
            if (s.x == fruit.x && s.y == fruit.y) { onSnake = true; break; }
    } while (onSnake);
}