#pragma once
#include <crow.h>

class StudentsController
{
public:
    StudentsController();

    /**
    * method to handle get all students
    * @param kReq request
    * @param res response
    */
    static void get_all_students
    (
        const crow::request& kReq, 
        crow::response& res
    );

    /**
    * method to handle post a new student
    * @param kReq request
    * @param res response
    */
    static void add_new_student
    (
        const crow::request& kReq, 
        crow::response& res
    );
};
