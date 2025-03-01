#include <boost/algorithm/string.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <enums/server_game.hpp>
#include <format>
#include <schemas/server_game.hpp>
#include <userver/formats/json.hpp> 
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
class RequestNewGameBodyTest : public GameServerTest {
 protected:
  RequestNewGameBodyTest() {
    json_new_game_request =
        std::string(std::format(R"({{"user_uuid":"{}"}})", str_uuid));
  }

 public:
  std::string json_new_game_request;
};
class ResponseNewGameBodyTest : public GameServerTest {
 protected:
  ResponseNewGameBodyTest() {
    json_new_game_response =
        std::string(std::format(R"({{"game_uuid":"{}"}})", str_uuid));
  }

 public:
  std::string json_new_game_response;
};
class RequestCheckTheRowBodyTest : public GameServerTest {
 protected:
  RequestCheckTheRowBodyTest() {
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
class ResponseCheckTheRowBodyTest : public GameServerTest {
 protected:
  ResponseCheckTheRowBodyTest() {
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

UTEST_F(RequestNewGameBodyTest, Create) {
  auto uuid_rand = userver::utils::generators::GenerateBoostUuid();
  RequestNewGameBody obj_1;
  obj_1.user_uuid = uuid_rand;
  RequestNewGameBody obj_2{uuid_rand};
  RequestNewGameBody obj_3 = {.user_uuid = uuid_rand};

  EXPECT_EQ(obj_1.user_uuid, obj_2.user_uuid);
  EXPECT_EQ(obj_1.user_uuid, obj_3.user_uuid);
}

UTEST_F(RequestNewGameBodyTest, FromJson) {
  auto userver_json = userver::formats::json::FromString(json_new_game_request);
  RequestNewGameBody obj = userver_json.As<RequestNewGameBody>();

  auto boost_uuid = userver::utils::BoostUuidFromString(str_uuid);

  EXPECT_EQ(obj.user_uuid, boost_uuid);
}

UTEST_F(ResponseNewGameBodyTest, Create) {
  auto uuid_rand = userver::utils::generators::GenerateBoostUuid();
  ResponseNewGameBody obj_1;
  obj_1.game_uuid = uuid_rand;
  ResponseNewGameBody obj_2{uuid_rand};
  ResponseNewGameBody obj_3 = {.game_uuid = uuid_rand};

  EXPECT_EQ(obj_1.game_uuid, obj_2.game_uuid);
  EXPECT_EQ(obj_1.game_uuid, obj_3.game_uuid);
}

UTEST_F(ResponseNewGameBodyTest, FromJson) {
  auto userver_json =
      userver::formats::json::FromString(json_new_game_response);
  ResponseNewGameBody obj = userver_json.As<ResponseNewGameBody>();

  auto boost_uuid = userver::utils::BoostUuidFromString(str_uuid);

  EXPECT_EQ(obj.game_uuid, boost_uuid);
}

UTEST_F(RequestCheckTheRowBodyTest, CreateAndFromToJson) {
  RequestCheckTheRowBody process_row_request_1 = {
      .user_uuid = userver::utils::BoostUuidFromString(str_uuid),
      .game_uuid = userver::utils::BoostUuidFromString(str_uuid),
      .word = str_word};

  auto userver_json =
      userver::formats::json::FromString(json_process_row_request);
  RequestCheckTheRowBody process_row_request_2 =
      userver_json.As<RequestCheckTheRowBody>();

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

UTEST_F(ResponseCheckTheRowBodyTest, CreateAndFromToJson) {
  ResponseCheckTheRowBody process_row_response_1 = {
      .check_the_row_result = check_the_row_result_,
      .the_char_colors =
          std::vector<int>{char_color_1, char_color_2, char_color_3,
                           char_color_4, char_color_5},
      .number_of_attempts_left = number_of_attempts_left_};

  auto userver_json =
      userver::formats::json::FromString(json_process_row_response);
  ResponseCheckTheRowBody process_row_response_2 =
      userver_json.As<ResponseCheckTheRowBody>();

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
