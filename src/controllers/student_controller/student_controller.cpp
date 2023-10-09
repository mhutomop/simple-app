#include "student_controller.h"
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <iostream>
#include "../../globals/globals.h"

StudentsController::StudentsController() {
}

void StudentsController::get_all_students
(
    const crow::request& kReq, 
    crow::response& res
) 
{
    try {
        rapidjson::StringBuffer buffer(0, 1000);
        rapidjson::Writer<rapidjson::StringBuffer> response(buffer);
        response.StartObject();
        response.String("data", 4);
        response.StartArray();
        for (uint8_t i = 0; i < students.size(); i++) {
            response.StartObject();
            response.String("name", 4);
            response.String(students[i].name.c_str());
            response.String("nik", 3);
            response.String(students[i].nik.c_str());
            response.EndObject();
        }
        response.EndArray();
        response.EndObject();
        res.add_header("content-type", "application/json");
        res.write(buffer.GetString());
        res.end(); 
    }
    catch (std::exception const& err) {
        std::cerr << "Exception: " << err.what() << std::endl;
    }
}

void StudentsController::add_new_student
(
    const crow::request& kReq, 
    crow::response& res
) 
{
    try {
        rapidjson::Document request;
        request.Parse(kReq.body.c_str());

        Student student;
        student.name = request["name"].GetString();
        student.nik = request["nik"].GetString();
        students.push_back(student);

        rapidjson::StringBuffer buffer(0, 1000);
        rapidjson::Writer<rapidjson::StringBuffer> response(buffer);
        response.StartObject();
        response.String("message", 7);
        response.String("Successfully add new student!", 29);
        response.EndObject();
        res.add_header("content-type", "application/json");
        res.write(buffer.GetString());
        res.end();

        buffer.Clear();
        rapidjson::Writer<rapidjson::StringBuffer> ws_data(buffer);
        ws_data.StartObject();
        ws_data.String("message", 7);
        ws_data.String("Successfully add new student!", 29);
        ws_server->loop->defer([&buffer]() { 
            ws_server->broadcast_message("broadcast-notification", buffer.GetString());
            buffer.Clear();
        });
    }
    catch (std::exception const& err) {
        std::cerr << "Exception: " << err.what() << std::endl;
    }
}