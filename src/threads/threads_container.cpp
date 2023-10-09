#include "threads_container.h"
#include "../globals/globals.h"

void ThreadsContainer::websocket_server_thread() {
    ws_server = new WebSocketAdapter(4445);
    ws_server->start();
}