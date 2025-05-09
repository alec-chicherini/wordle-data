#include <gtest/gtest.h>
#include <request_row_body.pb.h>
#include <request_new_game_body.pb.h>
#include <response_row_body.pb.h>
#include <response_new_game_body.pb.h>

#include <format>

using namespace wordle_data;

class GameServerTest : public ::testing::Test {
 protected:
  GameServerTest() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    str_uuid = std::string("01234567-89ab-cdef-0123-456789abcdef");
  }
  std::string str_uuid;
};
class RequestNewGameBodyTest : public GameServerTest {
 protected:
  RequestNewGameBodyTest() {}
};
class ResponseNewGameBodyTest : public GameServerTest {
 protected:
  ResponseNewGameBodyTest() {}
};
class RequestRowBodyTest : public GameServerTest {
 protected:
  RequestRowBodyTest() { str_word = "ЗАЧЕМ"; }

 public:
  std::string str_word;
};
class ResponseRowBodyTest : public GameServerTest {
 protected:
  ResponseRowBodyTest() { str_word = "ЗАТЕМ"; }

 public:
  std::string str_word;
};

TEST_F(RequestNewGameBodyTest, CreateAndFromToString) {
  UUID* uuid_ = new UUID;
  uuid_->set_value(str_uuid);
  RequestNewGameBody* obj_1 = new RequestNewGameBody();
  obj_1->set_allocated_user_uuid(uuid_);
  RequestNewGameBody* obj_2 = new RequestNewGameBody(*obj_1);
  EXPECT_EQ(obj_1->user_uuid().value(), obj_2->user_uuid().value());

  std::string serialized_1;
  obj_1->SerializeToString(&serialized_1);
  std::string serialized_2;
  obj_2->SerializeToString(&serialized_2);
  EXPECT_EQ(serialized_1, serialized_2);

  RequestNewGameBody* obj_3 = new RequestNewGameBody();
  RequestNewGameBody* obj_4 = new RequestNewGameBody();
  obj_3->ParseFromString(serialized_1);
  obj_4->ParseFromString(serialized_2);
  EXPECT_EQ(obj_3->user_uuid().value(), obj_4->user_uuid().value());
}

TEST_F(ResponseNewGameBodyTest, CreateAndFromToString) {
  UUID* uuid_ = new UUID;
  uuid_->set_value(str_uuid);
  ResponseNewGameBody* obj_1 = new ResponseNewGameBody();
  obj_1->set_allocated_game_uuid(uuid_);
  ResponseNewGameBody* obj_2 = new ResponseNewGameBody(*obj_1);
  EXPECT_EQ(obj_1->game_uuid().value(), obj_2->game_uuid().value());

  std::string serialized_1;
  obj_1->SerializeToString(&serialized_1);
  std::string serialized_2;
  obj_2->SerializeToString(&serialized_2);
  EXPECT_EQ(serialized_1, serialized_2);

  ResponseNewGameBody* obj_3 = new ResponseNewGameBody();
  ResponseNewGameBody* obj_4 = new ResponseNewGameBody();
  obj_3->ParseFromString(serialized_1);
  obj_4->ParseFromString(serialized_2);
  EXPECT_EQ(obj_3->game_uuid().value(), obj_4->game_uuid().value());
}

TEST_F(RequestRowBodyTest, CreateAndFromToString) {
  UUID* uuid_1 = new UUID;
  uuid_1->set_value(str_uuid);
  UUID* uuid_2 = new UUID;
  uuid_2->set_value(str_uuid);

  RequestRowBody process_row_request_1;
  process_row_request_1.set_allocated_game_uuid(uuid_1);
  process_row_request_1.set_allocated_user_uuid(uuid_2);
  process_row_request_1.set_word(str_word);

  std::string serialized_1;
  process_row_request_1.SerializeToString(&serialized_1);

  RequestRowBody process_row_request_2;
  process_row_request_2.ParseFromString(serialized_1);

  EXPECT_EQ(process_row_request_1.user_uuid().value(),
            process_row_request_2.user_uuid().value());
  EXPECT_EQ(process_row_request_1.game_uuid().value(),
            process_row_request_2.game_uuid().value());
  EXPECT_EQ(process_row_request_2.word(), str_word);
}

TEST_F(ResponseRowBodyTest, CreateAndFromToJson) {
  ResponseRowBody process_row_response_1;
  process_row_response_1.set_row_result(
      RowResult::kWordIsAnswer);
  process_row_response_1.add_the_char_colors(TheCharColor::kGreen);
  process_row_response_1.add_the_char_colors(TheCharColor::kNoneTheCharColor);
  process_row_response_1.add_the_char_colors(TheCharColor::kYellow);
  process_row_response_1.add_the_char_colors(TheCharColor::kGreen);
  process_row_response_1.add_the_char_colors(TheCharColor::kNoneTheCharColor);
  process_row_response_1.set_number_of_attempts(3);
  process_row_response_1.set_word_answer(str_word);

  std::string serialized_1;
  process_row_response_1.SerializeToString(&serialized_1);

  ResponseRowBody process_row_response_2;
  process_row_response_2.ParseFromString(serialized_1);
  EXPECT_EQ(process_row_response_2.number_of_attempts(), 3);
  EXPECT_EQ(process_row_response_2.row_result(),
            RowResult::kWordIsAnswer);
  EXPECT_EQ(process_row_response_2.the_char_colors(0), TheCharColor::kGreen);
  EXPECT_EQ(process_row_response_2.the_char_colors(1),
            TheCharColor::kNoneTheCharColor);
  EXPECT_EQ(process_row_response_2.the_char_colors(2), TheCharColor::kYellow);
  EXPECT_EQ(process_row_response_2.the_char_colors(3), TheCharColor::kGreen);
  EXPECT_EQ(process_row_response_2.the_char_colors(4),
            TheCharColor::kNoneTheCharColor);
  EXPECT_EQ(process_row_response_2.word_answer(), str_word);
}
