#pragma once

#include "aws_iot/client.hpp"

using namespace std;

class ClientMock: public Client
{
    public:
        ClientMock(const Parameters &param);

    private:
        virtual bool initialize_tls();
        virtual bool mqtt_connect();
        virtual bool subscribe();
        virtual bool unsubscribe();
};

