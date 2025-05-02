#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

const int width = 800, height = 600;
const float grav = 4, jump_str = -2;
const float move_speed = 8; 
const int pipe_width = 70, pipe_gap = 150;

struct pipe {
    RectangleShape top, bottom;
    float x;
    pipe(float xPos) {
        x = xPos;
        float heightTop = rand() % (height / 2);
        float heightBottom = height - heightTop - pipe_gap;

        top.setSize(Vector2f(pipe_width, heightTop));
        bottom.setSize(Vector2f(pipe_width, heightBottom));

        top.setFillColor(Color::Red);
        bottom.setFillColor(Color::Red);

        top.setPosition(x, 0);
        bottom.setPosition(x, heightTop + pipe_gap);
    }
    void move(float speed) {
        x -= speed;
        top.setPosition(x, 0);
        bottom.setPosition(x, top.getSize().y + pipe_gap);
    }
};

int main() {
    srand(time(0));

    RenderWindow rw(VideoMode(width, height), "Flappy");
    Texture flappy;
    if (!flappy.loadFromFile("/home/student/dddddd/Untitled folder/flappy.png")) {
        cout << "Error: Unable to load texture!" << endl;
        return -1;
    }
    Sprite flp;
    flp.setTexture(flappy);
    flp.setPosition(100, height / 2);

    float velocity = 0;

    vector<pipe> pipes;
    pipes.push_back(pipe(width));

    while (rw.isOpen()) {
        Event ev;
        while (rw.pollEvent(ev)) {
            if (ev.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
                rw.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                flp.move(0, -move_speed);
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                flp.move(0, move_speed);
            }
        }

        //velocity += grav;
        //flp.move(0, velocity);

        for (auto &pipe : pipes)
            pipe.move(0.1);

        if (pipes.front().x < -pipe_width) {
            pipes.erase(pipes.begin());
            pipes.push_back(pipe(width));
        }

        if (flp.getPosition().y < 0 || flp.getPosition().y > height) {
            flp.setPosition(100, height / 2); 
            velocity = 0;
        }

        for (auto &pipe : pipes) {
            if (flp.getPosition().x > pipe.x &&
                flp.getPosition().x < pipe.x + pipe_width &&
                (flp.getPosition().y < pipe.top.getSize().y || flp.getPosition().y > pipe.bottom.getPosition().y)) {
                rw.close(); 
            }
        }

        rw.clear();
        rw.draw(flp);
        for (auto &pipe : pipes) {
            rw.draw(pipe.top);
            rw.draw(pipe.bottom);
        }
        rw.display();
    }
    return 0;
}
