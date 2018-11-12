//
// Created by dpudov on 12.11.18.
//

#include "AbstractController.h"
#include "NetworkUtils.h"

namespace networkhelper {
    AbstractController::AbstractController() = default;

    AbstractController::~AbstractController() = default;

    void AbstractController::setEndpoint(const std::string &value) {
        uri endpointURI(value);
        uri_builder endpointBuilder;

        endpointBuilder.set_scheme(endpointURI.scheme());
        if (endpointURI.host() == "host_auto_ip4") {
            endpointBuilder.set_host(NetworkUtils::hostIP4());
        } else if (endpointURI.host() == "host_auto_ip6") {
            endpointBuilder.set_host(NetworkUtils::hostIP6());
        }
        endpointBuilder.set_port(endpointURI.port());
        endpointBuilder.set_path(endpointURI.path());

        _listener = http_listener(endpointBuilder.to_uri());

    }

    std::string AbstractController::endpoint() const {
        return std::__cxx11::string();
    }

    pplx::task<void> AbstractController::accept() {
        initRestOpHandlers();
        return _listener.open();
    }

    pplx::task<void> AbstractController::shutdown() {
        return _listener.close();
    }

    std::vector<utility::string_t> AbstractController::requestPath(const http_request &message) {
        auto relativePath = uri::decode(message.relative_uri().path());
        return uri::split_path(relativePath);
    }
}

