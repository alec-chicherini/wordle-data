#include <userver/utest/utest.hpp>
#include <userver/utils/boost_uuid4.hpp>
#include <userver/server/handlers/http_handler_base.hpp> //userver::formats::json::FromString

#include <boost/uuid/uuid_generators.hpp>
#include <wordle_server_game.hpp>
#include <format>

using namespace wordle_json;
UTEST(NewGameRequestBodyCreate, Basic) {
  auto uuid_rand = userver::utils::generators::GenerateBoostUuid();
  NewGameRequestBody obj_1;
  obj_1.user_uuid = uuid_rand;
  NewGameRequestBody obj_2{uuid_rand};
  NewGameRequestBody obj_3 = {.user_uuid = uuid_rand};

  EXPECT_EQ(obj_1.user_uuid, obj_2.user_uuid);
  EXPECT_EQ(obj_1.user_uuid, obj_3.user_uuid);
}

UTEST(NewGameRequestBodyFromJson, Basic) {
  std::string str_uuid("0123456789abcdef0123456789abcdef");
  std::string json_uuid(std::format("{{\"user_uuid\":\"{}\"}}", str_uuid));

  auto userver_json = userver::formats::json::FromString(json_uuid);
  NewGameRequestBody obj = userver_json.As<NewGameRequestBody>();

  boost::uuids::string_generator gen;
  boost::uuids::uuid boost_uuid = gen(str_uuid);

  EXPECT_EQ(obj.user_uuid, boost_uuid);
}

UTEST(NewGameResponseBodyCreate, Basic) {
  auto uuid_rand = userver::utils::generators::GenerateBoostUuid();
  NewGameResponseBody obj_1;
  obj_1.game_uuid = uuid_rand;
  NewGameResponseBody obj_2{uuid_rand};
  NewGameResponseBody obj_3 = {.game_uuid = uuid_rand};

  EXPECT_EQ(obj_1.game_uuid, obj_2.game_uuid);
  EXPECT_EQ(obj_1.game_uuid, obj_3.game_uuid);
}

UTEST(NewGameResponseBodyFromJson, Basic) {
  std::string str_uuid("0123456789abcdef0123456789abcdef");
  std::string json_uuid(std::format("{{\"game_uuid\":\"{}\"}}", str_uuid));

  auto userver_json = userver::formats::json::FromString(json_uuid);
  NewGameResponseBody obj = userver_json.As<NewGameResponseBody>();

  boost::uuids::string_generator gen;
  boost::uuids::uuid boost_uuid = gen(str_uuid);

  EXPECT_EQ(obj.game_uuid, boost_uuid);
}

UTEST(ProcessRowRequestBodyFromJson, Basic) {
  ProcessRowRequestBody process_row_request;
  ///TODO
  EXPECT_EQ(true, true);
}

UTEST(ProcessRowResponseBodyFromJson, Basic) {
  ProcessRowRequestBody process_row_response;
  /// TODO
  EXPECT_EQ(true, true);
}
