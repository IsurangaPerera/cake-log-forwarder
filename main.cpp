#include "src/listener/log_listener.h"

int main() {
    Listener listener = LogListener::create("syslog");
    std::cout << listener->get_listener_identifier() << std::endl;
    return 0;
}
