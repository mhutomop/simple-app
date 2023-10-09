#include "websocket_adapter.h"
#include <iostream>

WebSocketAdapter::WebSocketAdapter(const int& kPort) : kPort(&kPort), app_(nullptr) {
    struct PerSocketData {
    };
    #pragma pack(0)
    app_ = new uWS::App();
    app_->ws<PerSocketData>("/notification", {
        // Settings
        .compression = uWS::SHARED_COMPRESSOR,
        .maxPayloadLength = 1 * 1024 * 1024,
        .idleTimeout = 16,
        .maxBackpressure = 1 * 1024 * 1024,
        .closeOnBackpressureLimit = false,
        .resetIdleTimeoutOnSend = false,
        .sendPingsAutomatically = true,
        // Handlers
        .upgrade = nullptr,
        .open = [](auto* ws) {
            ws->subscribe("broadcast-notification");
        },
        .message = [](auto* /*ws*/, std::string_view /*message*/, uWS::OpCode /*opCode*/) {},
        .drain = [](auto* /*ws*/) {},
        .ping = [](auto* /*ws*/, std::string_view) {},
        .pong = [](auto* /*ws*/, std::string_view) {},
        .close = [](auto* /*ws*/, int /*code*/, std::string_view /*message*/) {}
    });
    app_->listen(kPort, [kPort](auto* listen_socket) {
        if (listen_socket) {
            std::cout << "WebSocket server is listening on port " << std::to_string(kPort) << std::endl;
        }
    });

    loop = uWS::Loop::get();
}

WebSocketAdapter::~WebSocketAdapter() {
    if (app_) {
        app_->close();
        delete app_;
    }
    delete kPort;
}

void WebSocketAdapter::start() {
    app_->run();
}

void WebSocketAdapter::broadcast_message(const std::string& kBroadcast, const std::string& kData) {
    app_->publish(kBroadcast, kData, uWS::OpCode::TEXT, false);
}
