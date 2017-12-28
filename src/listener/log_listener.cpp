//
// Created by isurangaperera on 12/27/17.
//

#include "log_listener.h"
#include <fluent-bit.h>

// Create library context
static flb_ctx_t *create_context() {
    flb_ctx_t *ctx;

    ctx = flb_create();
    if (!ctx) {
        return nullptr;
    }

    return ctx;
}

static std::map<std::string, flb_ctx_t *> &ctx_map() {
    static std::map<std::string, flb_ctx_t *> map;
    return map;
};

// Enable the input plugin
static bool create_input(flb_ctx_t *ctx) {
    int in_ffd, ret;

    in_ffd = flb_input(ctx, const_cast<char *>("cpu"), nullptr);
    if (in_ffd == -1) {
        flb_destroy(ctx);
        return false;
    }
    ret = flb_input_set(ctx, in_ffd,
                        "tag", "my_records",
                        NULL);
    if (ret == -1) {
        flb_destroy(ctx);
        return false;
    }

    return true;
}

// Enable output plugin
static bool create_output(flb_ctx_t *ctx) {
    int out_ffd, ret;
    out_ffd = flb_output(ctx, const_cast<char *>("stdout"), nullptr);
    if (out_ffd == -1) {
        flb_destroy(ctx);
        return false;
    }
    ret = flb_output_set(ctx, out_ffd,
                         "tag", "my_records",
                         NULL);
    if (ret == -1) {
        flb_destroy(ctx);
        return false;
    }

    return true;
}

std::map<std::string, Listener> &LogListener::create_map() {
    static std::map<std::string, Listener> lmap;
    return lmap;
}

bool LogListener::config_reload() {
    int ret;

    flb_ctx_t *ctx = create_context();
    create_input(ctx);
    create_output(ctx);

    ret = flb_start(ctx);

}

Listener LogListener::create(const std::string &name) {
    std::map<std::string, Listener> &lmap = create_map();
    auto it = lmap.find(name);
    if (it == lmap.end()) {
        throw "Unknown Type";
    }
    return it->second;
}

void LogListener::register_me(const std::string &name, Listener lst) {
    std::map<std::string, Listener> &lmap = create_map();
    lmap[name] = lst;
};



