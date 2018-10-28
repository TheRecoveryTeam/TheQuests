//
// Created by dpudov on 28.10.18.
//
#include "../cpr/include/cpr/cpr.h"
#include "../cpr/include/cpr/cprtypes.h"
#include "../cpr/include/cpr/body.h"
#include "../cpr/include/cpr/api.h"
#include <cassert>

void test_create_valid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/user/create"},
                       cpr::Body{
                               R"({"nickname":"ImechkoFamiliya", "email":"email@example.com","password":"qwerty123"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_create_invalid_email() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/user/create"},
                       cpr::Body{R"({"nickname":"ImechkoFamiliya", "password":"qwerty123"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_create_invalid_nickname() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/user/create"},
                       cpr::Body{R"({"email":"email@example.com","password":"qwerty123"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_create_invalid_password() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/user/create"},
                       cpr::Body{R"({"nickname":"ImechkoFamiliya", "email":"email@example.com"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_login_valid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/user/login"},
                       cpr::Body{R"({"email":"email@example.com","password":"qwerty123"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_login_invalid_email() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/user/login"},
                       cpr::Body{R"({"password":"qwerty123"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_login_invalid_password() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/user/login"},
                       cpr::Body{R"({"email":"email@example.com"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_logout_valid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/user/logout"},
                       cpr::Body{R"({})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_edit_valid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/user/edit"},
                       cpr::Body{R"({"email": "new.email@example.com", "nickname": "NewImechkoFamiliya"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_edit_invalid_email() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/user/edit"},
                       cpr::Body{R"({"nickname": "NewImechkoFamiliya"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_edit_invalid_nickname() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/user/edit"},
                       cpr::Body{R"({"email": "new.email@example.com"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_password_edit_valid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/user/password_edit"},
                       cpr::Body{R"({"password": "example123", "newPassword": "example123New"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_password_edit_invalid_new() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/user/password_edit"},
                       cpr::Body{R"({"password": "example123"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_password_edit_invalid_empty() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/user/password_edit"},
                       cpr::Body{R"({})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_password_edit_invalid_equal() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/user/password_edit"},
                       cpr::Body{R"({"password": "example123", "newPassword": "example123"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_password_edit_invalid_old() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/user/password_edit"},
                       cpr::Body{R"({"newPassword": "example123"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

int main() {
    test_create_valid();

    test_create_invalid_email();

    test_create_invalid_nickname();

    test_create_invalid_password();

    test_login_valid();

    test_login_invalid_email();

    test_login_invalid_password();

    test_logout_valid();

    test_edit_valid();

    test_edit_invalid_email();

    test_edit_invalid_nickname();

    test_password_edit_valid();

    test_password_edit_invalid_new();

    test_password_edit_invalid_old();

    test_password_edit_invalid_equal();

    test_password_edit_invalid_empty();

    return 0;
}
