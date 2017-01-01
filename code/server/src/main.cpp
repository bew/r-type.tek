/**
 * @file main.cpp
 * @author Benoit de Chezelles
 * @brief Main server
 */

#include <iostream>
#include <climits>
#include "Logs/Logger.hh"
#include "ServerLogLevel.hh"
#include "Server.hpp"

int main(int argc, char **argv) {
    logs::getLogger().registerBasicsLogLevel();
    logs::getLogger().registerLogLevel(new logs::ServerLogLevel());

    // Check if the given port is valid or use default one
    unsigned short port = Server::PORT;
    if (argc >= 2) {
        try {
            int value = std::stoi(argv[1]);
            if (value >= 0 && value <= SHRT_MAX)
                port = static_cast<unsigned short>(value);
        }
        catch (const std::exception &e) {
            logs::getLogger()[logs::ERRORS] << "Invalid port given (" << argv[1] << "), default will be used"
                                            << std::endl;
        }
    }

    Server server(Server::SERVER_TOKEN);

    // Check if the network's server started correctly
    port = server.initNetwork(port);
    if (port == 0) {
        logs::getLogger()[logs::ERRORS] << "There was an error while initializing server network" << std::endl;
        return EXIT_FAILURE;
    }
    logs::getLogger()[logs::SERVER] << "The server is running on port: " << port << "." << std::endl;

    server.run();

    return EXIT_SUCCESS;
}
