//
// Created by dpudov on 28.10.18.
//

#include "../cpr/include/cpr/cpr.h"

void test_create_valid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/create"},
                       cpr::Body{
                               R"({"title": "Example", "description": "Lorem ipsum dolor sit amet", "image": "mock.png"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_create_invalid_title() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/create"},
                       cpr::Body{R"({"description": "Lorem ipsum dolor sit amet", "image": "mock.png"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_create_invalid_description() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/create"},
                       cpr::Body{R"({"title": "Example", "image": "mock.png"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_create_invalid_image() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/create"},
                       cpr::Body{R"({"title": "Example", "description": "Lorem ipsum dolor sit amet"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_destroy_valid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/destroy"},
                       cpr::Body{
                               R"({"id": "1"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_destroy_invalid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/destroy"},
                       cpr::Body{
                               R"({})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_edit_image_valid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/edit_image"},
                       cpr::Body{
                               R"({"id": "1", "image": "mockNew.png"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_edit_image_invalid_id() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/edit_image"},
                       cpr::Body{
                               R"({"image": "mockNew.png"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_edit_image_invalid_image() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/edit_image"},
                       cpr::Body{
                               R"({"id": "1"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_detail_valid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/detail"},
                       cpr::Body{
                               R"({"id": "1"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_detail_invalid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/detail"},
                       cpr::Body{
                               R"({})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_resources_valid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/resources"},
                       cpr::Body{
                               R"({"id": "1"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_resources_invalid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/resources"},
                       cpr::Body{
                               R"({})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_list_valid()
{
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/list"},
                       cpr::Body{
                               R"({"page":1, "limit":1, "authorId":1, "asc":true, "stage":"progress"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_list_invalid_page()
{
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/list"},
                       cpr::Body{
                               R"({"limit":1, "authorId":1, "asc":true, "stage":"progress"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_list_invalid_limit()
{
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/list"},
                       cpr::Body{
                               R"({"page":1000, "authorId":1, "asc":true, "stage":"progress"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}


void test_create_valid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/create"},
                       cpr::Body{
                               R"({"title": "Example", "description": "Lorem ipsum dolor sit amet", "image": "mock.png"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_create_invalid_title() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/create"},
                       cpr::Body{R"({"description": "Lorem ipsum dolor sit amet", "image": "mock.png"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_create_invalid_description() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/create"},
                       cpr::Body{R"({"title": "Example", "image": "mock.png"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_create_invalid_image() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/create"},
                       cpr::Body{R"({"title": "Example", "description": "Lorem ipsum dolor sit amet"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_destroy_valid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/destroy"},
                       cpr::Body{
                               R"({"id": "1"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_destroy_invalid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/destroy"},
                       cpr::Body{
                               R"({})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_edit_image_valid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/edit_image"},
                       cpr::Body{
                               R"({"id": "1", "image": "mockNew.png"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_edit_image_invalid_id() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/edit_image"},
                       cpr::Body{
                               R"({"image": "mockNew.png"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_edit_image_invalid_image() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/edit_image"},
                       cpr::Body{
                               R"({"id": "1"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_detail_valid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/detail"},
                       cpr::Body{
                               R"({"id": "1"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_detail_invalid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/detail"},
                       cpr::Body{
                               R"({})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_resources_valid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/resources"},
                       cpr::Body{
                               R"({"id": "1"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_resources_invalid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/resources"},
                       cpr::Body{
                               R"({})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_list_valid()
{
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/list"},
                       cpr::Body{
                               R"({"page":1, "limit":1, "authorId":1, "asc":true, "stage":"progress"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_list_invalid_page()
{
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/list"},
                       cpr::Body{
                               R"({"limit":1, "authorId":1, "asc":true, "stage":"progress"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_list_invalid_limit()
{
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/quest/list"},
                       cpr::Body{
                               R"({"page":1000, "authorId":1, "asc":true, "stage":"progress"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}


int main() {
    test_create_valid();

    test_create_invalid_description();

    test_create_invalid_image();

    test_create_invalid_title();

    test_destroy_valid();

    test_destroy_invalid();

    test_edit_image_valid();

    test_edit_image_invalid_id();

    test_edit_image_invalid_image();

    test_detail_valid();

    test_detail_invalid();

    test_resources_valid();

    test_resources_invalid();

    test_list_valid();

    test_list_invalid_page();

    test_list_invalid_limit();

    return 0;
}