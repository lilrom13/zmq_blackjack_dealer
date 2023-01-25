#ifndef __TABLE_HPP__
#define __TABLE_HPP__

#include <string>

#include "dealer.hpp"

#include <thread>

class table {

    std::string _table_id;

    dealer      _d;

    int         _players;

public:

    table(std::string table_id): _table_id(table_id), _d(), _players(0)
    {
    }

    ~table() {}

    static void *run(void *arg)
    {
        table *t = static_cast<table *>(arg);

        std::string t_id = t->getTableId();

        zmq::context_t context(1);
        zmq::socket_t worker(context, ZMQ_REQ);

        zmq_setsockopt (worker, ZMQ_IDENTITY, t_id.c_str(), strlen (t_id.c_str()));
        worker.connect("ipc://backend.ipc");

        std::cout << t_id << " is open " << std::endl;

        while (t->getPlayerSeated() <= 0)
        {
 
        }

        return (void *)t;
    }

    int getPlayerSeated()
    {
        return _players;
    }

    std::string getTableId()
    {
        return _table_id;
    }
};

#endif /* __TABLE_HPP__ */