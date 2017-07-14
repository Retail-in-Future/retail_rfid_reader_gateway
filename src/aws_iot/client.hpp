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
        void run();
        bool publish(const string &payload);
        void stop();

    private:
        ResponseCode RunPublish(int msg_count);
        ResponseCode SubscribeCallback(util::String topic_name,
                util::String payload,
                std::shared_ptr<mqtt::SubscriptionHandlerContextData> p_app_handler_data);
        ResponseCode DisconnectCallback(string client_id,
                std::shared_ptr<DisconnectCallbackContextData> app_handler_data_ptr);
        ResponseCode Subscribe();
        ResponseCode Unsubscribe();
        virtual bool initialize_tls();
        virtual bool mqtt_connect();

    private:
        const Parameters &_param;
        std::shared_ptr<NetworkConnection> _network_connection_ptr;
        std::shared_ptr<mqtt::ConnectPacket> _connect_packet_ptr;
        std::shared_ptr<MqttClient> _iot_client_ptr;
};

