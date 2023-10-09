#include <crow.h>
#include <crow/middlewares/cors.h>
#include "threads/threads_container.h"
#include "globals/globals.h"
#include "routers/student_router/student_router.h"

/* Global variables and objects definition */
WebSocketAdapter* ws_server;
std::vector<Student> students;
/* End of definition */

int main(int argc, char** argv) {
    try {
        // Create a thread to run WebSocket server
        std::thread ws_thread(ThreadsContainer::websocket_server_thread);

        // Add a web server
        crow::App<crow::CORSHandler> app;

        // Setting router
        StudentRouter student_router(app);

        CROW_ROUTE(app, "/")
        ([]() {
            return "Hello World!";
        });

        app.port(4444).run();

        ws_thread.join();
    }
    catch (std::exception const& err) {
        std::cerr << "Exception: " << err.what() << std::endl;
    }
    return 0;
}
