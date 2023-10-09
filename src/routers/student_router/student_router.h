#pragma once
#include <crow.h>
#include <crow/middlewares/cors.h>

class StudentRouter
{
public:
    StudentRouter(crow::App<crow::CORSHandler>& app);
    ~StudentRouter();
private:
    /**
     * method to set routes of Student
    */
   void set_routes(crow::App<crow::CORSHandler>& app);
};

