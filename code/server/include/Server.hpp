/**
 * @file Server.hpp
 * @author Benoit de Chezelles
 * @brief Class for the server
 */

#ifndef SERVER_HPP_
# define SERVER_HPP_

# include <string>
# include <map>
# include <vector>
# include <memory>

class Server;

# include "Network/ServerTCP.hh"
# include "ServerRouter.hpp"
# include "Player.hpp"
# include "Account.hpp"
# include "Room.hpp"

/**
 * Represent the server
 */
class Server {
public:

    /**
     * The token that will be used to auth the server in UDP requests
     */
    static const std::string SERVER_TOKEN = "Jarvis";

    /**
     * Default port to use if non is provided
     */
    static const unsigned short PORT = 42403;

    /**
     * Construct a server instance
     *
     * @param token The server token used for identification on the network
     */
    Server(std::string const &token);

    /**
     * Destruct the server
     */
    ~Server();

    Server(Server const &other) = delete;

    Server &operator=(Server const &other) = delete;

public:
    /**
     * Initialize the server's network
     *
     * @param port The port on which to bind the server. If not given, an
     * available port will be used.
     * @return The used port, 0 if there where an error.
     */
    unsigned short initNetwork(unsigned short port = 0);

    /**
     * Run the main server logic
     */
    void run();

protected:
    /**
     * Process an incoming message from the given client
     *
     * @param client The client
     */
    void processMessage(std::shared_ptr<network::ClientTCP> client);

protected:
    /**
     * Store the association between a client socket and a Player
     * The players can be in any state
     */
    std::map<std::shared_ptr<network::ClientTCP>, std::shared_ptr<Player>> _players;

    /**
     * Store the association between a username and a Player
     */
    std::map<std::string, std::shared_ptr<Player>> _players_by_name;

    /**
     * Store the association between a username and a registered accounts
     * There cannot be 2 account with the same username
     */
    std::map<std::string, Account> _accounts;

    /**
     * Store the opened rooms
     */
    std::map<std::string, Room> _rooms;

    /**
     * The server name for network identification
     */
    std::string _serverToken;

    /**
     * The server socket
     */
    network::ServerTCP _serverSock;

    /**
     * The router for client's packets
     */
    ServerRouter _clientRouter;

    friend ServerRouter;
};

#endif /* !SERVER_HPP_ */
