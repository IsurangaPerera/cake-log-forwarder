#include "src/listener/log_listener.h"

int main() {

    Listener listener = LogListener::create("syslog");
    std::cout << listener->get_listener_identifier() << std::endl;
    listener->config_reload();

    int c, d;
    for ( c = 1 ; c <= 3276700000000 ; c++ )
        for ( d = 1 ; d <= 32767 ; d++ )
        {}

    return 0;
}
