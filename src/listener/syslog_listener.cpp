//
// Created by isurangaperera on 12/26/17.
//

#include <cstdint>
#include "log_listener.h"
#include "../listener_constants.h"
#include <fluent-bit.h>


class SyslogListener : public LogListener {

public:

    int get_listener_identifier() override {

        return ListenerConstants::SYSLOG_LISTENER;
    }

    int create_context() override {

        int ret;
        int in_ffd;
        int out_ffd;
        flb_ctx_t *ctx;

        // Create library context
        ctx = flb_create();
        if (!ctx) {
            return -1;
        }

        // Enable the input plugin
        in_ffd = flb_input(ctx, const_cast<char *>("cpu"), nullptr);
        if (in_ffd == -1) {
            flb_destroy(ctx);
            return -1;
        }
        ret = flb_input_set(ctx, in_ffd,
                            "tag", "my_records",
                            "ssl", "false",
                            NULL);
        if (ret == -1) {
            flb_destroy(ctx);
            return -1;
        }

        // Enable output plugin 'stdout' (print records to the standard output) *//*
        out_ffd = flb_output(ctx, const_cast<char *>("stdout"), nullptr);
        if (out_ffd == -1) {
            flb_destroy(ctx);
            return -1;
        }
        ret = flb_output_set(ctx, out_ffd,
                             "tag", "my_records",
                             "ssl", "false",
                             NULL);
        if (ret == -1) {
            flb_destroy(ctx);
            return -1;
        }

        return static_cast<int>(reinterpret_cast<uintptr_t>(ctx));
    }
};

REGISTER_LISTENER("syslog", SyslogListener);
