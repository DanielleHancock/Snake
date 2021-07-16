#include "json.hpp" // https://github.com/nlohmann/json
#include "GameTimeline.h"
#include "RealTimeline.h"
#include <zmq.hpp>
#include <iostream>
#include "Event.h"
#include "EventManager.h"
#include "ServerEventHandler.h"
#include "ScriptManager.h"
#include "dukglue/dukglue.h"
#include "Food.h"

// for convenience
using json = nlohmann::json;

int num_of_clients = 0;
Food food(0, 0, nullptr);

GameTimeline timeline(new RealTimeline(), 100);

int main() {
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REP);
    socket.bind("tcp://*:5555");

    ScriptManager scripter = ScriptManager();
    scripter.loadScript("scriptFile.js");
    dukglue_register_method(scripter.getContext(), &Food::setPos, "setPos");

    ServerEventHandler seh(1, &scripter);
    EventManager::registerHandler("request new food position", &seh);
	
    while (true) {
        //  Wait for next request from client
        zmq::message_t request;
        socket.recv(&request);
        std::string requestString = std::string(static_cast<char*>(request.data()));
        json j = json::parse(requestString);
        int id = j["id"];
        //std::cout << id << std::endl;

        // Assign ID to new client
        if (id == -1) {
            std::cout << "New client" << std::endl;
            json j_reply;
            j_reply["id"] = num_of_clients;
            num_of_clients++;

            //send reply
            std::string replyString = j_reply.dump();
            char replyCharArray[50];
            strcpy(replyCharArray, replyString.c_str());
            zmq::message_t reply(50);
            std::copy(replyCharArray, replyCharArray + 50, static_cast<char*>(reply.data()));
            //std::cout << "Assigned ID to Client " << j_reply["id"] << std::endl;
            socket.send(reply);
        }
        else {
            // get any events in message and raise on server
            for (int i = 0; i < j["events"].size(); i++) {
                Event e(j["events"][i]);
                EventManager::raiseAndHandleNow(e);
            }

            //send reply
            json j_reply;
            j_reply["x"] = food.xPos();
            j_reply["y"] = food.yPos();
            std::string replyString = j_reply.dump();
            char replyCharArray[50];
            strcpy(replyCharArray, replyString.c_str());
            zmq::message_t reply(50);
            std::copy(replyCharArray, replyCharArray + 50, static_cast<char*>(reply.data()));
            socket.send(reply);
        }

    }

}