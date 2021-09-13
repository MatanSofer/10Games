#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace std;
using namespace sf;
#define RED "\033[1;31m" //color red
#define GREEN "\033[1;32m" //color green
#define YELLOW "\033[1;33m" //color yellow
#define BLUE "\033[1;34m" //color blue
#define WHITE "\033[0m"    //color reset to white
void GameOneTetris();
void GameTwoDoodleJump();
void GameThreePuzzle();
void GameFourTRON();

const int M1 = 20;
const int N1 = 10;
const int W4 = 600;
const int H4 = 480;
int speed4 = 4;
bool field[W4][H4] = { 0 };
int field1[M1][N1] = { 0 };

struct Point1
{
    int x, y;
} a[4], b[4];
struct Point2
{
    int x, y;
};
struct player4 {
    int x, y, dir;
    Color color;
    player4(Color c) {
        x = rand() % W4;
        y = rand() % H4;
        color = c;
        dir = rand() % 4;
    }
    void tick4() {
        if (dir == 0) {
            y += 1;
        }
        if (dir == 0) {
            y += 1;
        }
        if (dir == 1) {
            y -= 1;
        }
        if (dir == 2) {
            y += 1;
        }
        if (dir == 3) {
            y -= 1;
        }
        if (x >= W4) {
            x = 0;
        }
        if (x < 0) {
            x = W4 - 1;
        }
        if (y >= H4) {
            y = 0;
        }
        if (y < 0) {
            y = H4 - 1;
        }

    }
    Vector3f getColor() {
        return Vector3f(color.r, color.g, color.b);
    }
};
int figures1[7][4] =
{
    1,3,5,7, // I
    2,4,5,7, // Z
    3,5,4,6, // S
    3,5,4,7, // T
    2,3,5,7, // L
    3,5,7,6, // J
    2,3,4,5, // O
};

bool check1(){
    for (int i = 0;i < 4;i++)
        if (a[i].x < 0 || a[i].x >= N1 || a[i].y >= M1) return 0;
        else if (field1[a[i].y][a[i].x]) return 0;

    return 1;
};


int main()
{
    int choise=1;
    cout <<" ____   _______    _______  _______  __   __  _______  _______ "<< endl;
    cout <<"|    | |  _    |  |       ||   _   ||  |_|  ||       ||       |"<< endl;
    cout <<" |   | | | |   |  |    ___||  |_|  ||       ||    ___||  _____|"<< endl;
    cout <<" |   | | | |   |  |   | __ |       ||       ||   |___ | |_____ "<< endl;
    cout <<" |   | | |_|   |  |   ||  ||       ||       ||    ___||_____  |"<< endl;
    cout <<" |   | |       |  |   |_| ||   _   || ||_|| ||   |___  _____| |"<< endl;
    cout <<" |___| |_______|  |_______||__| |__||_|   |_||_______||_______|"<< endl;
    
    cout <<RED<< "WELCOME TO 10 GAMES - USING SFML " <<WHITE<< endl;
    cout << "© Matan Sofer " << endl;
    cout <<BLUE<< "Enter the game number from list " <<WHITE<< endl;
    cout <<YELLOW<< "1.Tetris" <<WHITE<< endl;
    cout << YELLOW << "2.Doodle Jump" << WHITE << endl;
    cout << YELLOW << "3.Puzzle" << WHITE << endl;
    cout << YELLOW << "4.Tron" << WHITE << endl;
    cin >> choise;
    switch (choise) {
    case 1:
        GameOneTetris();
        break;
    case 2:
        GameTwoDoodleJump();
        break;
    case 3 :
        GameThreePuzzle();
    case 4:
        GameFourTRON();
    }

    return 0;
}
void GameOneTetris()
{
    srand(time(0));

    RenderWindow window(VideoMode(320, 480), "Tetris!");

    Texture t1, t2, t3;
    t1.loadFromFile("game1/tiles.png");
    t2.loadFromFile("game1/background.png");
    t3.loadFromFile("game1/frame.png");

    Sprite s(t1), background(t2), frame(t3);

    int dx = 0; bool rotate = 0; int colorNum = 1;
    float timer = 0, delay = 0.3;

    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::KeyPressed)
                if (e.key.code == Keyboard::Up) rotate = true;
                else if (e.key.code == Keyboard::Left) dx = -1;
                else if (e.key.code == Keyboard::Right) dx = 1;
        }

        if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;

        //// <- Move -> ///
        for (int i = 0;i < 4;i++) { b[i] = a[i]; a[i].x += dx; }
        if (!check1()) for (int i = 0;i < 4;i++) a[i] = b[i];

        //////Rotate//////
        if (rotate)
        {
            Point1 p = a[1]; //center of rotation
            for (int i = 0;i < 4;i++)
            {
                int x = a[i].y - p.y;
                int y = a[i].x - p.x;
                a[i].x = p.x - x;
                a[i].y = p.y + y;
            }
            if (!check1()) for (int i = 0;i < 4;i++) a[i] = b[i];
        }

        ///////Tick//////
        if (timer > delay)
        {
            for (int i = 0;i < 4;i++) { b[i] = a[i]; a[i].y += 1; }

            if (!check1())
            {
                for (int i = 0;i < 4;i++) field1[b[i].y][b[i].x] = colorNum;

                colorNum = 1 + rand() % 7;
                int n = rand() % 7;
                for (int i = 0;i < 4;i++)
                {
                    a[i].x = figures1[n][i] % 2;
                    a[i].y = figures1[n][i] / 2;
                }
            }

            timer = 0;
        }

        ///////check lines//////////
        int k = M1 - 1;
        for (int i = M1 - 1;i > 0;i--)
        {
            int count = 0;
            for (int j = 0;j < N1;j++)
            {
                if (field1[i][j]) count++;
                field1[k][j] = field1[i][j];
            }
            if (count < N1) k--;
        }

        dx = 0; rotate = 0; delay = 0.3;

        /////////draw//////////
        window.clear(Color::White);
        window.draw(background);

        for (int i = 0;i < M1;i++)
            for (int j = 0;j < N1;j++)
            {
                if (field1[i][j] == 0) continue;
                s.setTextureRect(IntRect(field1[i][j] * 18, 0, 18, 18));
                s.setPosition(j * 18, i * 18);
                s.move(28, 31); //offset
                window.draw(s);
            }

        for (int i = 0;i < 4;i++)
        {
            s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
            s.setPosition(a[i].x * 18, a[i].y * 18);
            s.move(28, 31); //offset
            window.draw(s);
        }

        window.draw(frame);
        window.display();
    }

}
void GameTwoDoodleJump()
{
    srand(time(0));
    RenderWindow app(VideoMode(400, 533), "Doodle Game!");
    app.setFramerateLimit(60);
    Texture t1, t2, t3;
    t1.loadFromFile("game2/background.png");
    t2.loadFromFile("game2/platform.png");
    t3.loadFromFile("game2/doodle.png");
    Sprite sBackground(t1), sPlat(t2), sPers(t3);
    Point2 plat[20];
    int x = 100;
    int y = 100;
    int h = 200;
    float dx = 0;
    float dy = 0; 

    
    for (int i = 0; i < 10; i++)
    {
        plat[i].x = rand() % 400;
        plat[i].y = rand() % 533;
    }
    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            x += 3;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            x -= 3;
        }
        dy += 0.2;
        y += dy;
        if (y > 500) {
            dy = dy - 10;
        }
        if (y < h) {
            for (int i = 0; i < 10;i++) {
                y = h;
                plat[i].y = plat[i].y - dy;
                if (plat[i].y > 533) {
                    plat[i].y = 0;
                    plat[i].x = rand() % 400;
                }
            }
        }
        for (int i = 0; i < 10; i++) {
            if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68) && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0)) {
                dy -= 10;
            }
        }
        sPers.setPosition(x, y);
        app.draw(sBackground);
        app.draw(sPers);
        for (int i = 0; i < 10; i++)
        {
            sPlat.setPosition(plat[i].x, plat[i].y);
            app.draw(sPlat);
        }
        app.display();
    }
    
     
}
void GameThreePuzzle()
{
    RenderWindow app(VideoMode(256, 256), "15-Puzzle!");
    app.setFramerateLimit(60);

    Texture t;
    t.loadFromFile("game3/15.png");

    int w = 64;
    int grid[6][6] = { 0 };
    Sprite sprite[20];

    int n = 0;
    for (int i = 0;i < 4;i++)
        for (int j = 0;j < 4;j++)
        {
            n++;
            sprite[n].setTexture(t);
            sprite[n].setTextureRect(IntRect(i * w, j * w, w, w));
            grid[i + 1][j + 1] = n;
        }

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();

            if (e.type == Event::MouseButtonPressed)
                if (e.key.code == Mouse::Left)
                {
                    Vector2i pos = Mouse::getPosition(app);
                    int x = pos.x / w + 1;
                    int y = pos.y / w + 1;

                    int dx = 0;
                    int dy = 0;

                    if (grid[x + 1][y] == 16) { dx = 1; dy = 0; };
                    if (grid[x][y + 1] == 16) { dx = 0; dy = 1; };
                    if (grid[x][y - 1] == 16) { dx = 0; dy = -1; };
                    if (grid[x - 1][y] == 16) { dx = -1;dy = 0; };

                    int n = grid[x][y];
                    grid[x][y] = 16;
                    grid[x + dx][y + dy] = n;

                    //animation
                    sprite[16].move(-dx * w, -dy * w);
                    float speed = 3;

                    for (int i = 0;i < w;i += speed)
                    {
                        sprite[n].move(speed * dx, speed * dy);
                        app.draw(sprite[16]);
                        app.draw(sprite[n]);
                        app.display();
                    }
                }

        }

        app.clear(Color::White);
        for (int i = 0;i < 4;i++)
            for (int j = 0;j < 4;j++)
            {
                int n = grid[i + 1][j + 1];
                sprite[n].setPosition(i * w, j * w);
                app.draw(sprite[n]);
            }

        app.display();
    }
}
void GameFourTRON()
{
    srand(time(0));

    RenderWindow window(VideoMode(W4, H4), "The Tron Game!");
    window.setFramerateLimit(60);

    Texture texture;
    texture.loadFromFile("game4/background.jpg");
    Sprite sBackground(texture);

    player4 p1(Color::Red), p2(Color::Green);

    Sprite sprite;
    RenderTexture t;
    t.create(W4, H4);
    t.setSmooth(true);
    sprite.setTexture(t.getTexture());
    t.clear();  t.draw(sBackground);

    bool Game = 1;

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) if (p1.dir != 2) p1.dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::Right)) if (p1.dir != 1)  p1.dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::Up)) if (p1.dir != 0) p1.dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::Down)) if (p1.dir != 3) p1.dir = 0;

        if (Keyboard::isKeyPressed(Keyboard::A)) if (p2.dir != 2) p2.dir = 1;
        if (Keyboard::isKeyPressed(Keyboard::D)) if (p2.dir != 1)  p2.dir = 2;
        if (Keyboard::isKeyPressed(Keyboard::W)) if (p2.dir != 0) p2.dir = 3;
        if (Keyboard::isKeyPressed(Keyboard::S)) if (p2.dir != 3) p2.dir = 0;

        if (!Game)    continue;

        for (int i = 0;i < speed4;i++)
        {
            p1.tick4();
            p2.tick4();
            if (field[p1.x][p1.y] == 1) Game = 0;
            if (field[p2.x][p2.y] == 1) Game = 0;
            field[p1.x][p1.y] = 1;
            field[p2.x][p2.y] = 1;

            CircleShape c(3);
            c.setPosition(p1.x, p1.y); c.setFillColor(p1.color);    t.draw(c);
            c.setPosition(p2.x, p2.y); c.setFillColor(p2.color);    t.draw(c);
            t.display();
        }

        ////// draw  ///////
        window.clear();
        window.draw(sprite);
        window.display();
    }
}