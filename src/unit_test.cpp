#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <random>
#include <ctime>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "message.h"
#include "user.h"
#include "server.h"
#include "stl.h"

// TEST(HW3Test, TEST1) {
//     Message msg;
//     EXPECT_EQ(msg.get_type(), "");
//     EXPECT_EQ(msg.get_sender(), "");
//     EXPECT_EQ(msg.get_receiver(), "");

//     std::time_t now = std::time(0);
//     std::string time = std::ctime(&now);
//     time.erase(time.find_last_not_of(" \n\r\t")+1); //trim the string
//     EXPECT_EQ(msg.get_time(), time);
// }

// TEST(HW3Test, TEST2) {
//     Message msg{"text", "david", "jenifer"};
//     EXPECT_EQ(msg.get_type(), "text");
//     EXPECT_EQ(msg.get_sender(), "david");
//     EXPECT_EQ(msg.get_receiver(), "jenifer");

//     std::time_t now = std::time(0);
//     std::string time = std::ctime(&now);
//     time.erase(time.find_last_not_of(" \n\r\t")+1); //trim the string
//     EXPECT_EQ(msg.get_time(), time);
// }

// TEST(HW3Test, TEST3) {
//     Message msg{"text", "david", "jenifer"};
//     std::cout << msg;

//     // check if the '<<' output contains important information
//     std::stringstream ss;
//     ss << msg;
//     size_t found_type =  ss.str().find("text");
//     size_t found_sender =  ss.str().find("david");
//     size_t found_receiver =  ss.str().find("jenifer");
//     EXPECT_TRUE(found_type != std::string::npos);
//     EXPECT_TRUE(found_sender != std::string::npos);
//     EXPECT_TRUE(found_receiver != std::string::npos);
// }

// TEST(HW3Test, TEST4) {
//     TextMessage textmsg("hello", "david", "jenifer");
//     EXPECT_EQ(textmsg.get_text(), "hello");
//     EXPECT_EQ(textmsg.get_type(), "text");
//     EXPECT_EQ(textmsg.get_sender(), "david");
//     EXPECT_EQ(textmsg.get_receiver(), "jenifer");

//     std::time_t now = std::time(0);
//     std::string time = std::ctime(&now);
//     time.erase(time.find_last_not_of(" \n\r\t")+1); //trim the string
//     EXPECT_EQ(textmsg.get_time(), time);
// }

// TEST(HW3Test, TEST5) {
//     TextMessage textmsg("hello", "david", "jenifer");
//     std::cout << textmsg;

//     // check if the '<<' output contains important information
//     std::stringstream ss;
//     ss << textmsg;
//     size_t found =  ss.str().find("hello");
//     EXPECT_TRUE(found != std::string::npos);
// }

// TEST(HW3Test, TEST6) {
//     TextMessage textmsg("hello", "david", "jenifer");
//     Message* msg{&textmsg};
//     std::cout << *msg;

//     // check if the '<<' output contains important information
//     // by 'late binding' printing 'msg' must print the 'textmsg' info
//     std::stringstream ss;
//     ss << *msg;
//     size_t found =  ss.str().find("hello");
//     EXPECT_TRUE(found != std::string::npos);
// }

// TEST(HW3Test, TEST7) {
//     VoiceMessage voicemsg{"david", "jenifer"};
//     EXPECT_EQ(voicemsg.get_voice().size(), 5);
//     EXPECT_EQ(voicemsg.get_type(), "voice");
//     EXPECT_EQ(voicemsg.get_sender(), "david");
//     EXPECT_EQ(voicemsg.get_receiver(), "jenifer");

//     std::time_t now = std::time(0);
//     std::string time = std::ctime(&now);
//     time.erase(time.find_last_not_of(" \n\r\t")+1); //trim the string
//     EXPECT_EQ(voicemsg.get_time(), time);
// }

// TEST(HW3Test, TEST8) {
//     VoiceMessage voicemsg("david", "jenifer");
//     std::cout << voicemsg;

//     // check if the '<<' output contains important information
//     std::stringstream ss;
//     ss << voicemsg;
//     int first_byte = static_cast<int>(voicemsg.get_voice()[0]);
//     size_t found =  ss.str().find(std::to_string(first_byte));
//     EXPECT_TRUE(found != std::string::npos);
// }

// TEST(HW3Test, TEST9) {
//     VoiceMessage voicemsg("david", "jenifer");
//     Message* msg{&voicemsg};
//     std::cout << *msg;

//     // check if the '<<' output contains important information
//     // by 'late binding' printing 'msg' must print the 'voicemsg' info
//     std::stringstream ss;
//     ss << *msg;
//     int first_byte = static_cast<int>(voicemsg.get_voice()[0]);
//     size_t found =  ss.str().find(std::to_string(first_byte));
//     EXPECT_TRUE(found != std::string::npos);
// }

// TEST(HW3Test, TEST10) {
//     User user{"david", "", nullptr};
//     EXPECT_EQ(user.get_username(), "david");
// }

// TEST(HW3Test, TEST11) {
//     Server server;
//     EXPECT_EQ(server.get_users().size(), 0);
//     EXPECT_EQ(server.get_public_keys().size(), 0);
//     EXPECT_EQ(server.get_messages().size(), 0);
// }

// TEST(HW3Test, TEST12) {
//     Server server;
//     User david = server.create_user("david");

//     EXPECT_EQ(david.get_username(), "david");

//     EXPECT_EQ(server.get_users().size(), 1);
//     EXPECT_EQ(server.get_public_keys().size(), 1);
//     EXPECT_EQ(server.get_messages().size(), 0);
// }

// TEST(HW3Test, TEST13) {
//     Server server;
//     User david = server.create_user("david");
//     EXPECT_THROW(server.create_user("david"), std::logic_error); // username already exists
// }

// TEST(HW3Test, TEST14) {
//     Server server;
//     User david = server.create_user("david");
//     User jenifer = server.create_user("jenifer");

//     bool result = david.send_text_message("hello jenifer", "jenifer");
//     EXPECT_TRUE(result);

//     EXPECT_EQ(server.get_messages().size(), 1);
//     TextMessage* textmsg = reinterpret_cast<TextMessage*>(server.get_messages()[0]);
//     EXPECT_EQ(textmsg->get_text(), "hello jenifer");
// }

// TEST(HW3Test, TEST15) {
//     Server server;
//     User david = server.create_user("david");
//     User jenifer = server.create_user("jenifer");

//     bool result = david.send_voice_message("jenifer");
//     EXPECT_TRUE(result);

//     EXPECT_EQ(server.get_messages().size(), 1);
//     VoiceMessage* voicemsg = reinterpret_cast<VoiceMessage*>(server.get_messages()[0]);
//     EXPECT_EQ(voicemsg->get_voice().size(), 5);
// }

// TEST(HW3Test, TEST16) {
//     Server server;
//     User david = server.create_user("david");

//     bool result = david.send_text_message("hello jenifer", "jenifer"); // this time jenifer doesnt exist
//     EXPECT_FALSE(result);
//     EXPECT_EQ(server.get_messages().size(), 0);
// }

// TEST(HW3Test, TEST17) {
//     Server server;
//     User david = server.create_user("david");
//     User jenifer = server.create_user("jenifer");

//     VoiceMessage* voicemsg = new VoiceMessage("david", "jenifer");
//     bool result = server.create_message(voicemsg, "wrong signature");

//     EXPECT_FALSE(result);
//     EXPECT_EQ(server.get_messages().size(), 0);
// }

// TEST(HW3Test, TEST18) {
//     Server server;
//     User david = server.create_user("david");
//     User jenifer = server.create_user("jenifer");
//     User john = server.create_user("john");

//     david.send_text_message("hello jenifer", "jenifer");
//     jenifer.send_text_message("hi there", "david");
//     john.send_text_message("how you do'in", "david");
//     jenifer.send_voice_message("david"); 

//     EXPECT_EQ(server.get_messages().size(), 4);
// }

// TEST(HW3Test, TEST19) {
//     Server server;
//     User david = server.create_user("david");
//     User jenifer = server.create_user("jenifer");
//     User john = server.create_user("john");

//     david.send_text_message("hello jenifer", "jenifer");
//     jenifer.send_text_message("hi there", "david");
//     john.send_text_message("how you do'in", "david");
//     jenifer.send_voice_message("david"); 
//     david.send_voice_message("john");
//     david.send_voice_message("jenifer");

//     auto msgs = server.get_all_messages_from("david"); // 'while' and 'for' is not allowed in this function
//     EXPECT_EQ(msgs.size(), 3);
//     EXPECT_EQ(msgs[1]->get_type(), "voice");
// }

// TEST(HW3Test, TEST20) {
//     Server server;
//     User david = server.create_user("david");
//     User jenifer = server.create_user("jenifer");
//     User john = server.create_user("john");

//     david.send_text_message("hello jenifer", "jenifer");
//     jenifer.send_text_message("hi there", "david");
//     john.send_text_message("how you do'in", "david");
//     jenifer.send_voice_message("david"); 
//     david.send_voice_message("john");
//     david.send_voice_message("jenifer");

//     auto msgs = server.get_all_messages_to("jenifer"); // 'while' and 'for' is not allowed in this function
//     EXPECT_EQ(msgs.size(), 2);
//     EXPECT_EQ(msgs[0]->get_type(), "text");
// }

// TEST(HW3Test, TEST21) {
//     Server server;
//     User david = server.create_user("david");
//     User jenifer = server.create_user("jenifer");
//     User john = server.create_user("john");

//     david.send_text_message("hello jenifer", "jenifer");
//     jenifer.send_text_message("hi there", "david");
//     john.send_text_message("how you do'in", "david");
//     jenifer.send_voice_message("david"); 
//     david.send_voice_message("john");
//     david.send_voice_message("jenifer");

//     auto msgs = server.get_chat("david", "jenifer"); // 'while' and 'for' is not allowed in this function
//     EXPECT_EQ(msgs.size(), 4);
//     TextMessage* msg1 = reinterpret_cast<TextMessage*>(msgs[1]);
//     EXPECT_EQ(msg1->get_text(), "hi there");
// }

// TEST(HW3Test, TEST22) {
//     std::vector<Message*> msgs;
//     msgs.push_back(new TextMessage("message 1", "david", "jenifer"));
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     msgs.push_back(new TextMessage("message 2", "jenifer", "david"));
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     msgs.push_back(new TextMessage("message 3", "david", "jenifer"));
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     msgs.push_back(new TextMessage("message 4", "jenifer", "david"));

//     auto rng = std::default_random_engine {};
//     std::shuffle(std::begin(msgs), std::end(msgs), rng);

//     Server::sort_msgs(msgs); // 'while' and 'for' is not allowed in this function
//     EXPECT_EQ(reinterpret_cast<TextMessage*>(msgs[0])->get_text(), "message 1");
//     EXPECT_EQ(reinterpret_cast<TextMessage*>(msgs[1])->get_text(), "message 2");
//     EXPECT_EQ(reinterpret_cast<TextMessage*>(msgs[2])->get_text(), "message 3");
//     EXPECT_EQ(reinterpret_cast<TextMessage*>(msgs[3])->get_text(), "message 4");
// }

// TEST(HW3Test, TEST23) {
//     std::vector<int> v;
//     initial_vector_with_3_mutiplies(v, 3);
//     EXPECT_TRUE((v == std::vector<int>{3, 6, 9}));

//     initial_vector_with_3_mutiplies(v, 4);
//     EXPECT_TRUE((v == std::vector<int>{3, 6, 9, 12}));

//     initial_vector_with_3_mutiplies(v, 6);
//     EXPECT_TRUE((v == std::vector<int>{3, 6, 9, 12, 15, 18}));
// }

// TEST(HW3Test, TEST24) {
//     std::vector<int> v1{1, 2, 3, 1, 2, 3, 1, 2, 5, 5, 6, 5, 7, 8, 4, 5, 6, 7, 1, 2, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4};
//     EXPECT_EQ(count_unique_above(v1, 5), 4);

//     std::vector<int> v2{1, 2, 3, 4, 5, 6, 1, 2, 34, 6, 8, 4, 5, 7, 8, 3, 5, 6, 7, 8, 11, 32, 55, 11, 32, 44, 55, 54, 29, 44, 6, 44, 99};
//     EXPECT_EQ(count_unique_above(v2, 30), 6);
// }

// TEST(HW3Test, TEST25) {
//     std::vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9};
//     EXPECT_EQ(vector_to_string(v1, ','), "9,8,7,6,5,4,3,2,1");

//     std::vector<int> v2{1, 2, 3, 4, 5, 6, 7, 8, 9, 12, 14};
//     EXPECT_EQ(vector_to_string(v2, '*'), "14*12*9*8*7*6*5*4*3*2*1");
// }





