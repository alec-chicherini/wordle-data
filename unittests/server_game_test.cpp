#include <boost/algorithm/string.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <enums/server_game.hpp>
#include <format>
#include <schemas/server_game.hpp>
#include <userver/server/handlers/http_handler_base.hpp>  //userver::formats::json::FromString
#include <userver/utest/utest.hpp>
#include <userver/utils/boost_uuid4.hpp>
using namespace wordle_json;

class GameServerTest : public ::testing::Test {
 protected:
  GameServerTest() {
    str_uuid = std::string("01234567-89ab-cdef-0123-456789abcdef");
  }
  std::string str_uuid;
};
class NewGameRequestBodyTest : public GameServerTest {
 protected:
  NewGameRequestBodyTest() {
    json_new_game_request =
        std::string(std::format(R"({{"user_uuid":"{}"}})", str_uuid));
  }

 public:
  std::string json_new_game_request;
};
class NewGameResponseBodyTest : public GameServerTest {
 protected:
  NewGameResponseBodyTest() {
    json_new_game_response =
        std::string(std::format(R"({{"game_uuid":"{}"}})", str_uuid));
  }

 public:
  std::string json_new_game_response;
};
class ProcessRowRequestBodyTest : public GameServerTest {
 protected:
  ProcessRowRequestBodyTest() {
    str_word = "ЗАЧЕМ";
    json_process_row_request = std::string(std::format(
        R"({{"user_uuid":"{}",
             "game_uuid":"{}", 
             "word":"{}"}})",
        str_uuid, str_uuid, str_word));
  }

 public:
  std::string json_process_row_request;
  std::string str_word;
};
class ProcessRowResponseBodyTest : public GameServerTest {
 protected:
  ProcessRowResponseBodyTest() {
    check_the_row_result_ = static_cast<int>(CheckTheRowResult::kWordIsAnswer);
    char_color_1 = static_cast<int>(TheCharColor::kGreen);
    char_color_2 = static_cast<int>(TheCharColor::kGreen);
    char_color_3 = static_cast<int>(TheCharColor::kGreen);
    char_color_4 = static_cast<int>(TheCharColor::kGreen);
    char_color_5 = static_cast<int>(TheCharColor::kGreen);
    number_of_attempts_left_ = 1;
    json_process_row_response = std::string(std::format(
        R"({{"check_the_row_result":{},
                         "the_char_colors":[{},{},{},{},{}],
                         "number_of_attempts_left":{}}})",
        check_the_row_result_, char_color_1, char_color_2, char_color_3,
        char_color_4, char_color_5, number_of_attempts_left_));
  }

 public:
  std::string json_process_row_response;
  int check_the_row_result_;
  int char_color_1;
  int char_color_2;
  int char_color_3;
  int char_color_4;
  int char_color_5;
  int number_of_attempts_left_;
};

UTEST_F(NewGameRequestBodyTest, Create) {
  auto uuid_rand = userver::utils::generators::GenerateBoostUuid();
  NewGameRequestBody obj_1;
  obj_1.user_uuid = uuid_rand;
  NewGameRequestBody obj_2{uuid_rand};
  NewGameRequestBody obj_3 = {.user_uuid = uuid_rand};

  EXPECT_EQ(obj_1.user_uuid, obj_2.user_uuid);
  EXPECT_EQ(obj_1.user_uuid, obj_3.user_uuid);
}

UTEST_F(NewGameRequestBodyTest, FromJson) {
  auto userver_json = userver::formats::json::FromString(json_new_game_request);
  NewGameRequestBody obj = userver_json.As<NewGameRequestBody>();

  auto boost_uuid = userver::utils::BoostUuidFromString(str_uuid);

  EXPECT_EQ(obj.user_uuid, boost_uuid);
}

UTEST_F(NewGameResponseBodyTest, Create) {
  auto uuid_rand = userver::utils::generators::GenerateBoostUuid();
  NewGameResponseBody obj_1;
  obj_1.game_uuid = uuid_rand;
  NewGameResponseBody obj_2{uuid_rand};
  NewGameResponseBody obj_3 = {.game_uuid = uuid_rand};

  EXPECT_EQ(obj_1.game_uuid, obj_2.game_uuid);
  EXPECT_EQ(obj_1.game_uuid, obj_3.game_uuid);
}

UTEST_F(NewGameResponseBodyTest, FromJson) {
  auto userver_json =
      userver::formats::json::FromString(json_new_game_response);
  NewGameResponseBody obj = userver_json.As<NewGameResponseBody>();

  auto boost_uuid = userver::utils::BoostUuidFromString(str_uuid);

  EXPECT_EQ(obj.game_uuid, boost_uuid);
}

UTEST_F(ProcessRowRequestBodyTest, CreateAndFromToJson) {
  ProcessRowRequestBody process_row_request_1 = {
      .user_uuid = userver::utils::BoostUuidFromString(str_uuid),
      .game_uuid = userver::utils::BoostUuidFromString(str_uuid),
      .word = str_word};

  auto userver_json =
      userver::formats::json::FromString(json_process_row_request);
  ProcessRowRequestBody process_row_request_2 =
      userver_json.As<ProcessRowRequestBody>();

  EXPECT_EQ(process_row_request_1.game_uuid, process_row_request_2.game_uuid);
  EXPECT_EQ(process_row_request_1.user_uuid, process_row_request_2.user_uuid);
  EXPECT_EQ(process_row_request_1.word, process_row_request_2.word);

  userver_json = userver::formats::json::ValueBuilder{process_row_request_1}
                     .ExtractValue();
  std::string json_process_row_request_1 =
      userver::formats::json::ToString(userver_json);

  boost::erase_all(json_process_row_request, "\n");
  boost::erase_all(json_process_row_request_1, "\n");
  boost::erase_all(json_process_row_request, " ");
  boost::erase_all(json_process_row_request_1, " ");
  EXPECT_EQ(json_process_row_request, json_process_row_request_1);
}

UTEST_F(ProcessRowResponseBodyTest, CreateAndFromToJson) {
  ProcessRowResponseBody process_row_response_1 = {
      .check_the_row_result = check_the_row_result_,
      .the_char_colors =
          std::vector<int>{char_color_1, char_color_2, char_color_3,
                           char_color_4, char_color_5},
      .number_of_attempts_left = number_of_attempts_left_};

  auto userver_json =
      userver::formats::json::FromString(json_process_row_response);
  ProcessRowResponseBody process_row_response_2 =
      userver_json.As<ProcessRowResponseBody>();

  EXPECT_EQ(process_row_response_1.check_the_row_result,
            process_row_response_2.check_the_row_result);
  EXPECT_EQ(process_row_response_1.number_of_attempts_left,
            process_row_response_2.number_of_attempts_left);
  EXPECT_EQ(process_row_response_1.the_char_colors.size(),
            process_row_response_2.the_char_colors.size());
  EXPECT_EQ(process_row_response_1.the_char_colors,
            process_row_response_2.the_char_colors);

  userver_json = userver::formats::json::ValueBuilder{process_row_response_1}
                     .ExtractValue();
  std::string json_process_row_response_1 =
      userver::formats::json::ToString(userver_json);
  boost::erase_all(json_process_row_response, "\n");
  boost::erase_all(json_process_row_response_1, "\n");
  boost::erase_all(json_process_row_response, " ");
  boost::erase_all(json_process_row_response_1, " ");
  EXPECT_EQ(json_process_row_response, json_process_row_response_1);
}
