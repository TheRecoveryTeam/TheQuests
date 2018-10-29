//
// Created by dpudov on 28.10.18.
//

void test_add_valid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/card/add"},
                       cpr::Body{
                               R"({"questId": "1", "title": "CardTitle", "description": "Sample description", "type": "choose"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_add_invalid_questId() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/card/add"},
                       cpr::Body{
                               R"({"title": "CardTitle", "description": "Sample description", "type": "choose"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_add_invalid_title() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/card/add"},
                       cpr::Body{R"({"questId": "1", "description": "Sample description", "type": "choose"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_add_invalid_description() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/card/add"},
                       cpr::Body{R"({"questId": "1", "title": "CardTitle", "type": "choose"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_add_invalid_type() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/card/add"},
                       cpr::Body{R"({"questId": "1", "title": "CardTitle", "description": "Sample description"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_edit_valid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/card/edit"},
                       cpr::Body{
                               R"({"id": "1", "questId": "1", "title": "NewCardTitle", "description": "New Sample description", "type": "choose"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_edit_invalid_id() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/card/edit"},
                       cpr::Body{
                               R"({"questId": "1", "title": "NewCardTitle", "description": "New Sample description", "type": "choose"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_edit_invalid_questId() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/card/edit"},
                       cpr::Body{
                               R"({"id": "1", "title": "NewCardTitle", "description": "New Sample description", "type": "choose"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}


void test_edit_invalid_title() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/card/edit"},
                       cpr::Body{
                               R"({"id": "1", "questId": "1", "description": "New Sample description", "type": "choose"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_edit_invalid_description() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/card/edit"},
                       cpr::Body{
                               R"({"id":"1", "questId": "1", "title": "NewCardTitle", "type": "choose"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_edit_invalid_type() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/card/edit"},
                       cpr::Body{
                               R"({"id":"1", "questId": "1", "title": "NewCardTitle", "description": "New Sample description"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_remove_valid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/card/remove"},
                       cpr::Body{
                               R"({"id": "1"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_remove_invalid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/card/remove"},
                       cpr::Body{
                               R"({})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_get_valid() {
    auto r = cpr::Get(cpr::Url{"http://localhost:8800/card/get/1"});
    assert(r.status_code == 200);
}

void test_do_answer_valid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/card/do_answer"},
                       cpr::Body{
                               R"({"id": "1", "answer":"Pretty answer"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_do_answer_invalid_id() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/card/do_answer"},
                       cpr::Body{
                               R"({"answer":"Pretty answer"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_do_answer_invalid_answer() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/card/do_answer"},
                       cpr::Body{
                               R"({"id": "1"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_links_upsert_valid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/card/links_upsert"},
                       cpr::Body{
                               R"({"id": "1", "links":{"newAnswer": "link"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 200);
}

void test_links_upsert_invalid() {
    auto r = cpr::Post(cpr::Url{"http://localhost:8800/card/links_upsert"},
                       cpr::Body{
                               R"({"links":{"newAnswer": "link"})"},
                       cpr::Header{{"Content-Type", "application/json"}});
    assert(r.status_code == 400);
}

void test_list_valid() {
    auto r = cpr::Get(cpr::Url{"http://localhost:8800/card/list/1"});
    assert(r.status_code == 200);
}

void test_list_invalid() {
    auto r = cpr::Get(cpr::Url{"http://localhost:8800/card/list/"});
    assert(r.status_code == 400);
}

int main() {
    test_add_valid();

    test_add_invalid_questId();

    test_add_invalid_description();

    test_add_invalid_title();

    test_add_invalid_type();

    test_edit_valid();

    test_edit_invalid_description();

    test_edit_invalid_id();

    test_edit_invalid_questId();

    test_edit_invalid_title();

    test_edit_invalid_title();

    test_do_answer_valid();

    test_do_answer_invalid_answer();

    test_do_answer_invalid_id();

    test_get_valid();

    test_links_upsert_valid();

    test_links_upsert_invalid();

    test_list_valid();

    test_list_invalid();

    test_remove_valid();

    test_remove_invalid();
    return 0;
}