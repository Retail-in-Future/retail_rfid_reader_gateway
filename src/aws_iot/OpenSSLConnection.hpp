/*
 * Copyright 2010-2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

/**
 * @file OpenSSLConnection.hpp
 * @brief Defines a reference implementation for an OpenSSL library wrapper
 */

#pragma once

#include <fcntl.h>
#include <errno.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <openssl/x509v3.h>
#include <openssl/x509_vfy.h>
#include <string.h>

#include <NetworkConnection.hpp>
#include <ResponseCode.hpp>

using namespace std;
using namespace awsiotsdk;

namespace network {
    /**
     * @brief OpenSSL Wrapper Class
     *
     * Defines a reference wrapper for OpenSSL libraries
     */
    class OpenSSLConnection : public NetworkConnection {
        protected:
            string root_ca_location_;             ///< Pointer to string containing the filename (including path) of the root CA file.
            string device_cert_location_;         ///< Pointer to string containing the filename (including path) of the device certificate.
            string device_private_key_location_;  ///< Pointer to string containing the filename (including path) of the device private key file.
            bool server_verification_flag_;             ///< Boolean.  True = perform server certificate hostname validation.  False = skip validation \b NOT recommended.
            bool is_connected_;                         ///< Boolean indicating connection status
            struct timeval tls_handshake_timeout_;      ///< Timeout for TLS handshake command
            struct timeval tls_read_timeout_;           ///< Timeout for the TLS Read command
            struct timeval tls_write_timeout_;          ///< Timeout for the TLS Write command

            // Endpoint information
            uint16_t endpoint_port_;                    ///< Endpoint port
            string endpoint_;                     ///< Endpoint for this connection

            SSL_CTX *p_ssl_context_;                    ///< SSL Context instance
            SSL *p_ssl_handle_;                         ///< SSL Handle
            int server_tcp_socket_fd_;                  ///< Server Socket descriptor


            /**
             * @brief Set TLS socket to non-blocking mode
             *
             * @return ResponseCode - successful operation or TLS error
             */
            ResponseCode SetSocketToNonBlocking();

            /**
             * @brief Create a TCP socket and open the connection
             *
             * Creates an open socket connection
             *
             * @return ResponseCode - successful connection or TCP error
             */
            ResponseCode ConnectTCPSocket();

            /**
             * @brief Attempt connection
             *
             * Attempts TLS Connection
             *
             * @return ResponseCode - successful connection or TLS error
             */
            ResponseCode AttemptConnect();

            /**
             * @brief Create a TLS socket and open the connection
             *
             * Creates an open socket connection including TLS handshake.
             *
             * @return ResponseCode - successful connection or TLS error
             */
            ResponseCode ConnectInternal();

            /**
             * @brief Write bytes to the network socket
             *
             * @param string - const reference to buffer which should be written to socket
             * @return size_t - number of bytes written or Network error
             * @return ResponseCode - successful write or Network error code
             */
            ResponseCode WriteInternal(const string &buf, size_t &size_written_bytes_out);

            /**
             * @brief Read bytes from the network socket
             *
             * @param string - reference to buffer where read bytes should be copied
             * @param size_t - number of bytes to read
             * @param size_t - reference to store number of bytes read
             * @return ResponseCode - successful read or TLS error code
             */
            ResponseCode ReadInternal(util::Vector<unsigned char> &buf, size_t buf_read_offset,
                    size_t size_bytes_to_read, size_t &size_read_bytes_out);

            /**
             * @brief Disconnect from network socket
             *
             * @return ResponseCode - successful read or TLS error code
             */
            ResponseCode DisconnectInternal();

        public:

            OpenSSLConnection(string endpoint, uint16_t endpoint_port,
                    std::chrono::milliseconds tls_handshake_timeout,
                    std::chrono::milliseconds tls_read_timeout,
                    std::chrono::milliseconds tls_write_timeout,
                    bool server_verification_flag);

            /**
             * @brief Constructor for the OpenSSL TLS implementation
             *
             * Performs any initialization required by the TLS layer.
             *
             * @param string endpoint - The target endpoint to connect to
             * @param uint16_t endpoint_port - The port on the target to connect to
             * @param string root_ca_location - Path of the location of the Root CA
             * @param string device_cert_location - Path to the location of the Device Cert
             * @param string device_private_key_location - Path to the location of the device private key file
             * @param std::chrono::milliseconds tls_handshake_timeout - The value to use for timeout of handshake operation
             * @param std::chrono::milliseconds tls_read_timeout - The value to use for timeout of read operation
             * @param std::chrono::milliseconds tls_write_timeout - The value to use for timeout of write operation
             * @param bool server_verification_flag - used to decide whether server verification is needed or not
             *
             */
            OpenSSLConnection(string endpoint, uint16_t endpoint_port, string root_ca_location,
                    string device_cert_location, string device_private_key_location,
                    std::chrono::milliseconds tls_handshake_timeout,
                    std::chrono::milliseconds tls_read_timeout, std::chrono::milliseconds tls_write_timeout,
                    bool server_verification_flag);

            OpenSSLConnection(string endpoint, uint16_t endpoint_port, string root_ca_location,
                    std::chrono::milliseconds tls_handshake_timeout,
                    std::chrono::milliseconds tls_read_timeout, std::chrono::milliseconds tls_write_timeout,
                    bool server_verification_flag);

            /**
             * @brief Initialize the OpenSSL object
             *
             * Initializes the OpenSSL object
             */
            ResponseCode Initialize();

            /**
             * @brief sets the path to the root CA
             *
             * Called to change the location of the root CA after the constructor has initialized the OpenSSL object.
             *
             * @param root_ca_location
             */
            void SetRootCAPath(string root_ca_location) { root_ca_location_ = root_ca_location; }

            /**
             * @brief sets the endpoint and the port
             *
             * Called to change the endpoint and the port after the constructor has initialized the OpenSSL object.
             * @param endpoint
             * @param endpoint_port
             */
            void SetEndpointAndPort(string endpoint, uint16_t endpoint_port) {
                endpoint_ = endpoint;
                endpoint_port_ = endpoint_port;
            }

            /**
             * @brief Check if TLS layer is still connected
             *
             * Called to check if the TLS layer is still connected or not.
             *
             * @return bool - indicating status of network TLS layer connection
             */
            bool IsConnected();

            /**
             * @brief Check if Network Physical layer is still connected
             *
             * Called to check if the Network Physical layer is still connected or not.
             *
             * @return bool - indicating status of network physical layer connection
             */
            bool IsPhysicalLayerConnected();

            virtual ~OpenSSLConnection();
    };
}
