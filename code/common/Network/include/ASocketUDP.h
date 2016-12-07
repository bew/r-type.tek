/**
* @file ASocketUDP.hh
* @author Tookie
* @brief abstraction of UDP socket
*/

#pragma once

#include "ASocket.hh"

/**
 * namespace that contains all network abstraction
 */
namespace network {

    /**
     * Representation of UDP socket abstraction
     */
    class ASocketUDP : public ASocket {
    public:
        /**
         * Constructor of ASocketUDP
         * @param port port use to socket connection
         */
        ASocketUDP(unsigned short port);
    };

}