#include <iostream>

#include <zmq.hpp>

#include "backend.hpp"

int main(int ac, char **av)
{
    std::cout << "zmq-v." << ZMQ_VERSION_MAJOR << "." << ZMQ_VERSION_MINOR << "." << ZMQ_VERSION_PATCH << std::endl;
    std::cout << "cppzmq-v." << CPPZMQ_VERSION_MAJOR << "." << CPPZMQ_VERSION_MINOR << "." << CPPZMQ_VERSION_PATCH << std::endl;

    backend b;

    b.run();

    return 0;
}