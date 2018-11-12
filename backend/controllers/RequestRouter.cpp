//
// Created by dpudov on 08.11.18.
//

#include "RequestRouter.h"

RequestRouter::RequestRouter() = default;

void RequestRouter::handle_get_request(http_request message) {


}

void RequestRouter::handle_post_request(http_request message) {
    if (isValid(message)) {

    } else {

    }
}

bool RequestRouter::isValid(http_request message) {
    return false;
}
