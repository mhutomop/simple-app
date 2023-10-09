#pragma once
#include <uwebsockets/App.h>

class WebSocketAdapter
{
public:
    WebSocketAdapter(const int& kPort);
    ~WebSocketAdapter();

    /**
    * method to start WebSocket server
    */
    void start();
    /**
    * method to broadcast message to all WebSocket clients
    * @param kData data to be sent to clients
    */
    void broadcast_message(const std::string& kBroadcast, const std::string& kData);

    uWS::Loop* loop;
private:
    const int* kPort;

    uWS::App* app_;
};

