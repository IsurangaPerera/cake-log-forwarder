//
// Created by isurangaperera on 12/28/17.
//

#include "parser.h"
#include <fstream>
#include <sstream>
#include "../json.h"

Parser *Parser::parser;
struct Config Parser::p_config;

Parser *Parser::get_instance() {
    if (parser == nullptr) {
        parser = new Parser();
    }

    return parser;
}

LogType Parser::get_type_struct() {

    struct LogType type;
    return type;
}

Config *Parser::read_config(const std::string &inputFileName) {

    short int index = 0;

    // Create an input filestream
    std::ifstream ifs(inputFileName);
    if (!ifs) {
        std::cout << "*ERROR** Could not read input file " << inputFileName << "\n";
        return nullptr;
    }

    // Read the file stream into a string stream
    std::stringstream iss;
    iss << ifs.rdbuf();
    ifs.close();

    // Parse the input stream
    nlohmann::json doc;
    try {
        doc << iss;
    } catch (std::invalid_argument *e) {
        std::cout << "*ERROR** Could not parse input file " << inputFileName
                  << "\n";
        std::cout << "Please check for correctness using a linter.\n";
        return nullptr;
    }

    // Read the boundary information
    try {
        auto log_types = doc["log_types"];
        for (const auto &object : log_types) {

            struct LogType p_type = Parser::get_type_struct();
            p_type.type = object["type"].get<std::string>();
            p_type.level = object["log_level"].get<std::string>();

            Parser::p_config.type[index++] = p_type;
        }

    } catch (std::exception *e) {
        std::cout << "**ERROR** \"Boundary\" key not found. \n";
        return nullptr;
    }

    return &p_config;
}
