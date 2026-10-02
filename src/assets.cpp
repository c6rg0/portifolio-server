#include "assets.h"
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

void Assets::req_store (char* buffer)
{
    std::string file_path = "/tmp/request_" + std::to_string(req_num);

    std::ofstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file!\n";
        exit(1);
    }

    file << buffer;
    file.close();
    req_num++;
}

std::string Assets::res_route (std::string target)
{
    content = res_content(target);
    payload = res_header();
    return payload.append(content);
}

std::string Assets::res_content (std::string target)
{
    std::filesystem::path file_path = std::filesystem::current_path();

    if (target == "/" || target.empty())
        file_path = file_path / "index.html";
    else
        file_path = file_path / target;

    if (!std::filesystem::exists(file_path)){
        std::cerr << "Error: File does not exist!\n";
        error_code = 404;
                          
        content_type = "application/json";
        content = 
            "{\"error\":\"Not Found\"}";

        return content;
    }

    std::ifstream file (file_path);
    if (!file.is_open ()) {
        std::cerr << "Error: Unable to open file!\n";
        error_code = 500;
                          
        content_type = "application/json";
        content = 
            "{\"error\":\"Unable to open file\"}";

        file.close();
        return content;
    }

    // Assuming that all content with be text...
    std::string content(
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>()
            );
    file.close();

    req_num++;
    return content;
}

std::string Assets::res_header ()
{
    //TODO:
    /*
    std::string std_header =
        "HTTP/1.1 200 OK\nContent-Type: text/html\nLocation: http://localhost:8080/\n\n";
    */

    // Get errmsg from code

    std::string error_msg = psbl_error_msgs[error_code];

    std::string header =
        // "HTTP/1.1 " + error_msg + "\n" + "Content-Type: " + content_type + ";\n" + "Content-Length: 21\nConnection: keep-alive\nKeep-Alive: timeout=5\n\n";
        "HTTP/1.1 " + error_msg + "\n" + "Content-Type: " + content_type + "\n" + "Connection: keep-alive\nKeep-Alive: timeout=5\n\n";

    return header;
}
