#pragma once

#include "parameters/parameters.hpp"
#include <mqtt/Client.hpp>
#include <NetworkConnection.hpp>

using namespace std;
using namespace awsiotsdk;

class Client
{
    public:
        Client(const Parameters &param);
        virtual ~Client();
        bool connect();
        void disconnect();
        void run();
        bool publish(const string &payload);
        void stop();

    private:
        ResponseCode RunPublish(int msg_count);
        ResponseCode subscribe_callback(util::String topic_name,
                util::String payload,
                std::shared_ptr<mqtt::SubscriptionHandlerContextData> app_handler_data_ptr);
        ResponseCode disconnect_callback(string client_id,
                std::shared_ptr<DisconnectCallbackContextData> app_handler_data_ptr);
        virtual bool subscribe();
        virtual bool unsubscribe();
        virtual bool initialize_tls();
        virtual bool mqtt_connect();

    private:
        const Parameters &_param;
        std::shared_ptr<NetworkConnection> _network_connection_ptr;
        std::shared_ptr<mqtt::ConnectPacket> _connect_packet_ptr;
        std::shared_ptr<MqttClient> _iot_client_ptr;
};

