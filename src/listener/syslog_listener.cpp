//
// Created by isurangaperera on 12/26/17.
//

#include <cstdint>
#include "log_listener.h"
#include "../listener_constants.h"

class SyslogListener : public LogListener {

public:

    int get_listener_identifier() override {
        return ListenerConstants::SYSLOG_LISTENER;
    }

    bool config_reload() override {
        LogListener::config_reload();
    }
};

REGISTER_LISTENER("syslog", SyslogListener);
