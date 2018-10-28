//
// Created by dpudov on 28.10.18.
//
#include "../cpr/include/cpr/cpr.h"
#include "../cpr/include/cpr/cprtypes.h"
#include "../cpr/include/cpr/body.h"
#include "../cpr/include/cpr/api.h"

int main()
{
    auto r = cpr::Post(cpr::Url{ "http://localhost:8800/user/create" },
                       cpr::Body{ R"({"nickname":"ImechkoFamiliya", "email":"email@example.com","password":"qwerty123"})" },
                       cpr::Header{ { "Content-Type", "application/json" } });

    return 0;
}
