//
// Created by isurangaperera on 12/26/17.
//

#ifndef CAKE_LOG_FORWARDER_CAKE_LOG_LISTENER_H
#define CAKE_LOG_FORWARDER_CAKE_LOG_LISTENER_H

#include <map>
#include <iostream>

class LogListener;

typedef LogListener *Listener;

class LogListener {
private:
    static std::map<std::string, Listener> &create_map() {
        static std::map<std::string, Listener> lmap;
        return lmap;
    }

public:
    virtual int get_listener_identifier() = 0;

    virtual int create_context() = 0;

    /** make one. */
    static Listener create(const std::string &name) {
        std::map<std::string, Listener> & lmap = create_map();
        auto it = lmap.find(name);
        if (it == lmap.end()) {
            throw "Unknown Type";
        }
        return it->second;
    }

    /** register a simulator listener with a given name */
   static void register_me(const std::string &name, Listener lst) {
        std::map<std::string, Listener> & lmap = create_map();
        lmap[name] = lst;
    };

};

/** registration by name */
template<class _s>
class register_listener {
public:
    explicit register_listener(const std::string &name) {
        Listener lst(new _s());
        LogListener::register_me(name, lst);
    };

#define REGISTER_LISTENER(name, type) \
    namespace {     \
        register_listener<type> fac(name); \
    };
};

#endif /* CAKE_LOG_FORWARDER_CAKE_LOG_LISTENER_H */
