//
// Created by dpudov on 28.10.18.
//
#include "../cpr/include/cpr/cpr.h"
#include "../cpr/include/cpr/cprtypes.h"
#include "../cpr/include/cpr/body.h"
#include "../cpr/include/cpr/api.h"
#include <cassert>

void test_create_valid()
{
    auto r = cpr::Post(cpr::Url{ "http://localhost:8800/user/create" },
                       cpr::Body{ R"({"nickname":"ImechkoFamiliya", "email":"email@example.com","password":"qwerty123"})" },
                       cpr::Header{ { "Content-Type", "application/json" } });
    assert(r.status_code == 200);
}

void test_create_invalid_email()
{
    auto r = cpr::Post(cpr::Url{ "http://localhost:8800/user/create" },
                       cpr::Body{ R"({"nickname":"ImechkoFamiliya", "password":"qwerty123"})" },
                       cpr::Header{ { "Content-Type", "application/json" } });
    assert(r.status_code == 400);
}

void test_create_invalid_nickname()
{
    auto r = cpr::Post(cpr::Url{ "http://localhost:8800/user/create" },
                       cpr::Body{ R"({"email":"email@example.com","password":"qwerty123"})" },
                       cpr::Header{ { "Content-Type", "application/json" } });
    assert(r.status_code == 400);
}

void test_create_invalid_password()
{
    auto r = cpr::Post(cpr::Url{ "http://localhost:8800/user/create" },
                       cpr::Body{ R"({"nickname":"ImechkoFamiliya", "email":"email@example.com"})"},
                       cpr::Header{ { "Content-Type", "application/json" } });
    assert(r.status_code == 400);
}

void test_login_valid(){

}

void test_login_invalid_email(){

}

void test_login_invalid_password(){

}



int main()
{
    test_create_valid();

    test_create_invalid_email();

    test_create_invalid_nickname();

    test_create_invalid_password();

    return 0;
}
