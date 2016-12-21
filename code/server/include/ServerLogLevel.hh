//
// Created by tookie on 12/21/16.
//

#pragma once

#include <fstream>
#include <string>
#include <stdexcept>

namespace logs
{

    static const std::string SERVER = "server";

    using ServerLogException = std::runtime_error;

    class ServerLogLevel: public ALogLevel
    {
    public:
        ServerLogLevel();

        virtual ~ServerLogLevel();

        virtual std::string getLogLevelName() const;

        virtual std::ostream& getLogLevelStream();

    private:
        std::ofstream _file;
    };

}


#endif //PROJECT_SERVERLOGLEVEL_HPP
