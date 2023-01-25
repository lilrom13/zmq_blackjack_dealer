#ifndef __BACKEND_HPP__
#define __BACKEND_HPP__

#include <map>
#include <set>

#include <zmq.hpp>
#include <zmq_addon.hpp>

#include "zhelper.h"

#include "table.hpp"

class backend {

    zmq::context_t _ctx;

    zmq::socket_t   _backend;
    zmq::socket_t   _frontend;

    std::map<std::string, table *> _table_map;

    std::set<std::string>                _clients;


public:

    backend(): 
        _ctx(1),
            _backend(_ctx, ZMQ_ROUTER),
                _frontend(_ctx, ZMQ_ROUTER)
    {
        _frontend.bind("tcp://*:5672"); // frontend
        _backend.bind("tcp://*:5673"); // backend

        // create a first table
        char table_id[10];
        
        s_create_id(table_id);

        std::string s_table_id(table_id);

        table *t1 = new table(s_table_id);

        // add table to table map
        _table_map.insert({s_table_id, t1});

        pthread_t worker;

        pthread_create(&worker, NULL, table::run, (void *) t1);
    }

    ~backend()
    {

    }

    void run()
    {
        zmq::active_poller_t ap;

        ap.add(_frontend, zmq::event_flags::pollin, [this](zmq::event_flags ef) {
            std::string client_id = s_recv(_frontend);

            std::cout << "client_id " << client_id << std::endl;

            std::string recv = s_recv(_frontend);

            std::cout << "empty " << recv << std::endl;

            recv = s_recv(_frontend);

            std::cout << "msg " << recv << std::endl;

            s_sendmore(&_frontend, client_id.c_str());
            s_sendmore(&_frontend, "");
            s_send(&_frontend, "hii");
        });

        while (1)
        {
            auto n = ap.wait(std::chrono::milliseconds(200));
            if (n)
            {
                std::cout << "got " << n << " sockets hit\n";
            }

        }
    }
};

#endif /* __BACKEND_HPP__ */