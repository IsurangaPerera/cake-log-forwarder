//
// Created by isurangaperera on 12/28/17.
//

#ifndef CAKE_LOG_FORWARDER_INIT_PARSER_H
#define CAKE_LOG_FORWARDER_INIT_PARSER_H

#include <iostream>

struct LogType {
    std::string type;
    std::string level;
};

struct Config {
    LogType type[5];
};

class Parser {

public:
    static Parser *get_instance();

private:
    Parser() = default;

    static Parser *parser;

    static struct Config p_config;

    LogType get_type_struct();

    Config *read_config(const std::string &inputFileName);

};

#endif //CAKE_LOG_FORWARDER_INIT_PARSER_H
