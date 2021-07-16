#include "json.hpp" // https://github.com/nlohmann/json
#include "GameTimeline.h"
#include "RealTimeline.h"
#include "Player.h"
#include "Variant.h"
#include "Event.h"
#include "EventManager.h"
#include "InputHandler.h"
#include "DeathHandler.h"
#include "Wall.h"
#include "Food.h"
#include "DrawAsEllipse.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <zmq.hpp>
#include <string>

// for convenience
using json = nlohmann::json;

constexpr auto WIDTH = 800;
constexpr auto HEIGHT = 600;
GameTimeline timeline(new RealTimeline(), 100);
bool p_was_pressed = false;

int main() {
    float time_last_updated = timeline.getTime();
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Snake", sf::Style::Default);

    // Create and register event handlers
    InputHandler ih(1);
    EventManager::registerHandler("right arrow press", &ih);
    EventManager::registerHandler("left arrow press", &ih);
    EventManager::registerHandler("up arrow press", &ih);
    EventManager::registerHandler("down arrow press", &ih);
    DeathHandler dh(2);
    EventManager::registerHandler("death", &dh);
    EventManager::registerHandler("grow", &dh);


    // Create game objects
    Player snake(window);
    Wall left_wall(0, 0, 20, HEIGHT, window);
    Wall right_wall(WIDTH - 20, 0, 20, HEIGHT, window);
    Wall top_wall(0, 0, WIDTH, 20, window);
    Wall bottom_wall(0, HEIGHT - 20, WIDTH, 20, window);
    snake.getCollisionMediator()->addGameObject(left_wall);
    snake.getCollisionMediator()->addGameObject(right_wall);
    snake.getCollisionMediator()->addGameObject(top_wall);
    snake.getCollisionMediator()->addGameObject(bottom_wall);
    Food food(500, 500, new DrawAsEllipse(window, sf::Color(255,0,0)));
    snake.getCollisionMediator()->addGameObject(food);

    int my_id = -1;

    // Set up socket
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.connect("tcp://localhost:5555");

    // Send request to server
    json j;
    j["id"] = -1;
    std::string requestString = j.dump();
    char replyCharArray[100];
    strcpy(replyCharArray, requestString.c_str());
    zmq::message_t request(100);
    std::copy(replyCharArray, replyCharArray + 100, static_cast<char*>(request.data()));
    std::cout << "Waiting for server" << std::endl;
    socket.send(request);

    //  Get the reply 
    zmq::message_t reply;
    socket.recv(&reply);
    std::string replyString = std::string(static_cast<char*>(reply.data()));
    json j_reply = json::parse(replyString);
    my_id = j_reply["id"].get<int>();
    std::cout << "Connected to server" << std::endl;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            if (!p_was_pressed) {
                timeline.togglePause();
            }
            p_was_pressed = true;
        }
        else {
            p_was_pressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            std::map<std::string, variant> args;
            variant var{ variant::Type::TYPE_PLAYERPTR };
            var._asPlayerPtr = &snake;
            args["player"] = var;
            Event e("right arrow press", args, timeline.getTime(), timeline.getTime());
            EventManager::raise(e);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            std::map<std::string, variant> args;
            variant var{ variant::Type::TYPE_PLAYERPTR };
            var._asPlayerPtr = &snake;
            args["player"] = var;
            Event e("left arrow press", args, timeline.getTime(), timeline.getTime());
            EventManager::raise(e);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            std::map<std::string, variant> args;
            variant var{ variant::Type::TYPE_PLAYERPTR };
            var._asPlayerPtr = &snake;
            args["player"] = var;
            Event e("up arrow press", args, timeline.getTime(), timeline.getTime());
            EventManager::raise(e);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            std::map<std::string, variant> args;
            variant var{ variant::Type::TYPE_PLAYERPTR };
            var._asPlayerPtr = &snake;
            args["player"] = var;
            Event e("down arrow press", args, timeline.getTime(), timeline.getTime());
            EventManager::raise(e);
        }

        if (EventManager::getServerQueueSize() > 0) {
            // Request id from the server
            json j;
            j["id"] = my_id;
            j["events"] = EventManager::getEventsForServer();
            std::string requestString = j.dump();
            char replyCharArray[2000];
            strcpy(replyCharArray, requestString.c_str());
            zmq::message_t request(2000);
            std::copy(replyCharArray, replyCharArray + 2000, static_cast<char*>(request.data()));
            socket.send(request);

            //  Get the reply containing this client's ID and game object info
            zmq::message_t reply;
            socket.recv(&reply);
            std::string replyString = std::string(static_cast<char*>(reply.data()));
            json j_reply = json::parse(replyString);
            //std::cout << "Received reply " << replyString << std::endl;
            food.setPos(j_reply["x"].get<int>(), j_reply["y"].get<int>());
        }

        float time_passed = timeline.getTime() - time_last_updated;
        time_last_updated = timeline.getTime();
        for (int i = 0; i < time_passed; i++) {
            EventManager::handleEvents(time_last_updated);
            window.clear(sf::Color::Black);
            left_wall.update();
            right_wall.update();
            top_wall.update();
            bottom_wall.update();
            food.update();
            snake.update();
            window.display();
        }
    }

}