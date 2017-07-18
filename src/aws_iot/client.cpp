
#include <chrono>
#include <boost/core/ignore_unused.hpp>
#include "client.hpp"
#include "OpenSSLConnection.hpp"

using namespace std;

static const string RFID_READER_TOPIC = "rfid_reader";

Client::Client(const Parameters &param) :
    _param(param)
{
}

Client::~Client()
{
    disconnect();
}

bool Client::connect()
{
    bool result = false;

    result = initialize_tls();
    if (result) {
        result = mqtt_connect();
        if (result) {
            result = subscribe();
        }
    }
    return result;
}

void Client::disconnect()
{
    if (_iot_client_ptr && _iot_client_ptr->IsConnected()) {
        unsubscribe();
        _iot_client_ptr->Disconnect(chrono::milliseconds(_param.aws_iot_mqtt_command_timeout()));
    }
}

bool Client::initialize_tls()
{
    ResponseCode rc = ResponseCode::SUCCESS;

    std::shared_ptr<network::OpenSSLConnection> network_connection_ptr =
        std::make_shared<network::OpenSSLConnection>(_param.aws_iot_host(),
                                                       _param.aws_iot_mqtt_port(), 
                                                       _param.aws_iot_certs_root_ca(),
                                                       _param.aws_iot_certs_cert(),
                                                       _param.aws_iot_certs_private_key(),
                                                       chrono::milliseconds(_param.aws_iot_tls_handshake_timeout()),
                                                       chrono::milliseconds(_param.aws_iot_tls_read_timeout()),
                                                       chrono::milliseconds(_param.aws_iot_tls_write_timeout()),
                                                       true);
    rc = network_connection_ptr->Initialize();

    if (ResponseCode::SUCCESS != rc) {
        //AWS_LOG_ERROR(LOG_TAG_Client,
                //"Failed to initialize Network Connection. %s",
                //ResponseHelper::ToString(rc).c_str());
        rc = ResponseCode::FAILURE;
    } else {
        _network_connection_ptr = std::dynamic_pointer_cast<NetworkConnection>(network_connection_ptr);
    }
    return rc == ResponseCode::SUCCESS;
}

bool Client::mqtt_connect()
{
    ClientCoreState::ApplicationDisconnectCallbackPtr disconnect_handler_ptr =
        std::bind(&Client::disconnect_callback, this, std::placeholders::_1, std::placeholders::_2);

    _iot_client_ptr = std::shared_ptr<MqttClient>(MqttClient::Create(_network_connection_ptr,
                chrono::milliseconds(_param.aws_iot_mqtt_command_timeout()),
                disconnect_handler_ptr, nullptr));
    if (nullptr == _iot_client_ptr) {
        return false;
    }

    string client_id_tagged = _param.aws_iot_client_id();
    client_id_tagged.append("_pub_sub_tester_");
    client_id_tagged.append(std::to_string(rand()));
    std::unique_ptr<Utf8String> client_id = std::unique_ptr<Utf8String>(Utf8String::Create(client_id_tagged));

    ResponseCode rc = ResponseCode::SUCCESS;
    rc = _iot_client_ptr->Connect(chrono::milliseconds(_param.aws_iot_mqtt_command_timeout()),
                                  _param.aws_iot_mqtt_is_clean_session(),
                                  mqtt::Version::MQTT_3_1_1,
                                  chrono::seconds(_param.aws_iot_mqtt_alive_timeout()),
                                  std::move(client_id),
                                  nullptr, nullptr, nullptr);
    if (ResponseCode::MQTT_CONNACK_CONNECTION_ACCEPTED != rc) {
        return false;
    }
    return true;
}

bool Client::subscribe()
{
    util::String p_topic_name_str = RFID_READER_TOPIC;
    std::unique_ptr<Utf8String> p_topic_name = Utf8String::Create(p_topic_name_str);
    mqtt::Subscription::ApplicationCallbackHandlerPtr p_sub_handler = std::bind(&Client::subscribe_callback,
                                                                                this,
                                                                                std::placeholders::_1,
                                                                                std::placeholders::_2,
                                                                                std::placeholders::_3);
    std::shared_ptr<mqtt::Subscription> p_subscription =
        mqtt::Subscription::Create(std::move(p_topic_name), mqtt::QoS::QOS0, p_sub_handler, nullptr);
    util::Vector<std::shared_ptr<mqtt::Subscription>> topic_vector;
    topic_vector.push_back(p_subscription);

    ResponseCode rc = _iot_client_ptr->Subscribe(topic_vector,
            chrono::milliseconds(_param.aws_iot_mqtt_command_timeout()));
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return rc == ResponseCode::SUCCESS;
}

bool Client::unsubscribe()
{
    util::String p_topic_name_str = RFID_READER_TOPIC;
    std::unique_ptr<Utf8String> p_topic_name = Utf8String::Create(p_topic_name_str);
    util::Vector<std::unique_ptr<Utf8String>> topic_vector;
    topic_vector.push_back(std::move(p_topic_name));

    ResponseCode rc = _iot_client_ptr->Unsubscribe(std::move(topic_vector),
            chrono::milliseconds(_param.aws_iot_mqtt_alive_timeout()));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return rc == ResponseCode::SUCCESS;
}

ResponseCode Client::subscribe_callback(util::String topic_name,
        util::String payload,
        std::shared_ptr<mqtt::SubscriptionHandlerContextData> app_handler_data_ptr) {
    boost::ignore_unused(app_handler_data_ptr);
    std::cout << std::endl << "************" << std::endl;
    std::cout << "Received message on topic : " << topic_name << std::endl;
    std::cout << "Payload Length : " << payload.length() << std::endl;
    if (payload.length() < 50) {
        std::cout << "Payload : " << payload << std::endl;
    }
    std::cout << std::endl << "************" << std::endl;
    return ResponseCode::SUCCESS;
}

ResponseCode Client::disconnect_callback(string client_id,
    std::shared_ptr<DisconnectCallbackContextData> app_handler_data_ptr)
{
    boost::ignore_unused(app_handler_data_ptr);
    cout << "*******************************************" << endl
        << client_id << " Disconnected!" << endl
        << "*******************************************" << endl;
    return ResponseCode::SUCCESS;
}
