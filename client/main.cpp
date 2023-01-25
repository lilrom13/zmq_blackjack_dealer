#include <iostream>

#include <zmq.hpp>
#include "zhelper.h"

int main()
{
 zmq::context_t context(1);
    zmq::socket_t client(context, ZMQ_REQ);

    s_set_id(client); // Set a printable identity
    client.connect("tcp://localhost:5672"); // frontend

    //  Send request, get reply
    s_send(client, "HELLO");
    std::string reply = s_recv(client);
    std::cout << "Client: " << reply << std::endl;
    return (NULL);
    return 0;
}