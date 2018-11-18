//
// Created by dpudov on 08.11.18.
//

#include "AbstractRequestRouter.h"

networkhelper::AbstractRequestRouter::AbstractRequestRouter() = default;

networkhelper::AbstractRequestRouter::~AbstractRequestRouter() = default;

bool networkhelper::AbstractRequestRouter::isValid(web::http::http_request message) {
    bool found = false;
    for (auto &entry : _routingEntries) {
        if (message.relative_uri().path() != entry.url || message.method() != entry.method) {
            continue;
        }
        entry.handler(message);
        found = true;
        break;
    }

    return found;
}
