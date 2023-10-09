#include "student_router.h"
#include "../../controllers/student_controller/student_controller.h"

StudentRouter::StudentRouter(crow::App<crow::CORSHandler>& app) {
    this->set_routes(app);
}

StudentRouter::~StudentRouter() {
}

void StudentRouter::set_routes(crow::App<crow::CORSHandler>& app) {
    CROW_ROUTE(app, "/students")
    .methods(crow::HTTPMethod::POST)
    ([&](const crow::request& kReq, crow::response& res) {
        StudentsController::add_new_student(kReq, res);
    });

    CROW_ROUTE(app, "/students")
    .methods(crow::HTTPMethod::GET)
    ([&](const crow::request& kReq, crow::response& res) {
        StudentsController::get_all_students(kReq, res);
    });
}
