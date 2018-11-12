//
// Created by dpudov on 12.11.18.
//

#ifndef THEQUESTS_NETWORKUTILS_H
#define THEQUESTS_NETWORKUTILS_H

#include <string>
#include "MicroService.h"

using namespace boost::asio;
using namespace boost::asio::ip;

namespace networkhelper {

    using HostInetInfo = tcp::resolver::iterator;

    class NetworkUtils {
    private:
        static HostInetInfo queryHostInetInfo();

        static std::string hostIP(unsigned short family);

    public:
        // gets the host IP4 string formatted
        static std::string hostIP4() {
            return hostIP(AF_INET);
        }

        // gets the host IP6 string formatted
        static std::string hostIP6() {

            return hostIP(AF_INET6);
        }

        static std::string hostName() {
            return ip::host_name();
        }
    };

}
#endif //THEQUESTS_NETWORKUTILS_H
