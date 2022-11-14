# Advanced Programming Course - HW3&4
<p  align="center"> <b>Homework 3&4 - Fall 2022 Semester <br> Deadline: Shanbe 5 Azar - 11:59 pm</b> </p>

</br>

## **Outline**
This homework has 2 parts:

- In the first part, we are going to implement a messenger with a server and users that can send each other messages. To do this you need to know your way around classes, inheritance, and polymorphism.
- The second part of the homework is focused on working with STL functions. So be prepared to work with concepts like lambda function, functor, and ... .


</br>
</br>


## **Messenger**
In order to implement our messenger we first need to define different messages (like text messages, voice messages, ...) that can be passed between our users. All these types of messages have some shared properties. So let's define a `Message` class with all these shared properties and then we can inherit different types of messages from the `Message` class.<br/>

## Message class
Define the `Message` class with the following member variables.
```cpp
class Message
{
public:

private:
    std::string type;     // type of the message ("text", "voice", ...)
    std::string sender;   // the username who send this message
    std::string receiver; // the username whom this message is intended for
    std::string time;     // creation time of the message
};
```
Now define the following member functions for `Message`. (you may not alter or change these functions but you may and probably should add some keywords to them)

- **constructor**<br/>
Define the following constructor to assign member variables of the class.
  ```cpp
  Message(std::string type, std::string sender, std::string receiver);
  ```
  the constructor assigns all the member variables except `time`. The `time` member variable is a string containing the date and the time of the creation of the message in GMT time and should be exactly in the format of `"Sun Nov 13 17:50:43 2022"`. (you can use `ctime` library to do this)

- **default constructor**<br/>
Define a default constructor for the class and use **constructor delegation** to assign the member variables.
  ```cpp
  Message();
  ```

- **getter functions**<br/>
Since all the class's member variables are private we need *getter functions* for them. define a getter function for all the member variables:
  ```cpp
  std::string get_type();
  std::string get_sender();
  std::string get_receiver();
  std::string get_time();
  ```

- **operator<<**<br/>
First, define the following *print* function
  ```cpp
  void print(std::ostream &os);
  ```
  this function will get an `ostream` object (like *cout*) and fills it with the information of the message. the output should be something like this:
  ```cpp
  *************************
  david -> jenifer
  message type: text
  message time: Sun Nov 13 17:50:43 2022
  *************************
  ```

  Now implement the << operator and use the print function in it to print out the `Message` class
  ```cpp
  std::ostream& operator<<(std::ostream &os, const Message &c);
  ```

  **Question.** why do you think we defined the `print` function and didn't implement everything in operator<< itself? (answer this question after you implemented `TextMessage` and `VoiceMessage` classes)

<br/>

Now that we defined the shared properties of different kinds of messages in the `Message` class, we can derive other Messages from it. In this homework, we only need *text message* and *voice message*. So let's go and implement them.

## TextMessage class
The `TextMessage` class inherits from the `Message` class and has one extra member variable named `text` which stores the *text* of the message.
```cpp
class TextMessage : public Message
{
public:

private:
    std::string text;
};
```

Now let's define the needed member functions of this class. (you may not alter or change these functions but you may and probably should add some keywords to them)

- **constructor**<br/>
Define the following constructor to assign member variables of the class.
  ```cpp
  TextMessage(std::string text, std::string sender, std::string receiver);
  ```

- **print**<br/>
  ```cpp
  void print(std::ostream &os);
  ```
  Implement the `print` function so that it prints out the information of the `TextMessage` class. something like this:
  ```cpp
  *************************
  david -> jenifer
  message type: text
  message time: Sun Nov 13 17:50:43 2022
  text: hello everybody
  *************************
  ```
  **Note.** Make arrangements so that `TEST6` works properly.

- **get_text**<br/>
Since we have a new member variable we need to implement its getter function as well.
  ```cpp
  std::string get_text();
  ```

## VoiceMessage class
The `VoiceMessage` class inherits from the `Message` class and has one extra member variable called `voice` which is an array of bytes(unsigned char) that stores the voice's data. For the sake of simplicity, we will always fill the `voice` with random bytes with the size of 5.
```cpp
class VoiceMessage : public Message
{
public:

private:
    std::vector<unsigned char> voice;
};
```

Now let's define the needed member functions of this class. (you may not alter or change these functions but you may and probably should add some keywords to them)

- **constructor**<br/>
Define the following constructor to assign member variables of the class.
  ```cpp
  VoiceMessage(std::string sender, std::string receiver);
  ```
  and fill the `voice` member variable with 5 random bytes.

- **print**<br/>
  ```cpp
  void print(std::ostream &os);
  ```
  Implement the `print` function so that it prints out the information of the `VoiceMessage` class. something like:
  ```cpp
  *************************
  david -> jenifer
  message type: voice
  message time: Sun Nov 13 17:50:43 2022
  voice: 166 240 216 41 129 
  *************************
  ```
  The above numbers are generated by converting each byte of `voice` to an `int`.

  **Note.** Make arrangements so that `TEST9` works properly.

- **get_voice**<br/>
Since we have a new member variable we need to implement its getter function as well.
  ```cpp
  std::vector<unsigned char> get_voice();
  ```

<br/>
<hr/>
<br/>

Now that we have our Message classes we can go on and implement the `Server` and `User` classes. The `Server` and `User` classes are correlated with each other, So read all the instructions first and then try to implement both classes at the same time. (Trying to implement one of them first and then the other one is not a good idea)


## User class
The `User` class represents the users that want to send messages to each other so we have to implement the functionality of sending different kinds of messages (text and voice). The other important thing is that users should be able to send their messages safely. In order to do this we will use RSA keys. (if you're not familiar with RSA keys, it will be further explained in the TA class)
**Note.** You can find all the functions you need to work with RSA in the `crypto.cpp/h` files.<br/>
Now, let's go ahead and define the `User` class.

```cpp
class User
{
public:

private:
    std::string username;     // username of the user
    std::string private_key;  // private key of the user
    Server* const server;     // a pointer to the server for communications
};
```
Now let's discuss the needed member functions for the `User` class. (you may not alter or change these functions but you may and probably should add some keywords to them)

- **constructor**<br/>
  Define the following constructor to assign member variables of the class.
  ```cpp
  User(std::string username, std::string private_key, Server* server);
  ```

- **get_username**<br/>
  The only member variable that we want others to see is the `username` so let's define a getter function for it.
  ```cpp
  std::string get_username();
  ```


- **send_text_message**<br/>
  Create a function so that users can send text messages to each other. (`receiver` is the username of the user to whom we want to send a message). return true if the message has been sent successfully and return false otherwise.
  ```cpp
  bool send_text_message(std::string text, std::string receiver);
  ```
  you need the `create_message` function of the `Server` class to do this.


- **send_voice_message**<br/>
  Create a function so that users can send voice messages to each other (`receiver` is the username of the user to whom we want to send message). return true if the message has been sent successfully and return false otherwise.
  As previously discussed in the `VoiceMessage`, voice messages are always random data with a 5-byte length.
  ```cpp
  bool send_voice_message(std::string receiver);
  ```
  you need the `create_message` function of the `Server` class to do this.


<br/>
<br/>

## Server class
`Server` is a class responsible to store the information of the users and messages.
```cpp
class Server
{
public:

private:
    std::vector<User> users;                        // to store our users
    std::map<std::string, std::string> public_keys; // map usernames to their publickeys
    std::vector<Message*> messages;                 // to store all the messages sent by users
};
```
Now let's go ahead and define the needed member functions for the `Server` class. (as always you may not alter or change these functions but you may and probably should add some keywords to them)

- **default constructor**<br/>
  Since none of the member variables don't need any specific initialization, we only need to define a default constructor for the class.
  ```cpp
  Server();
  ```

- **getter functions**<br/>
  Let's define the getter functions for our member variables.
  ```cpp
  std::vector<User> get_users();
  std::map<std::string, std::string> get_public_keys();
  std::vector<Message*> get_messages();
  ```


- **create_user**<br/>
  This function creates a user using the `username` input. if the `username` already exists in the server this function should throw an std::logic_error.
  ```cpp
  User create_user(std::string username);
  ```
  Server is also responsible to create a public and private key pair for each user. the private key will be passed to the user and the public key should be stored in the `public_keys` member variable.

- **create_message**<br/>
  Using this function we can add a message to the server. each user that wants to add a message to the server **must sign its username as a signature** so that the server can authenticate whether or not the message is from the sender.
  ```cpp
  bool create_message(Message* msg, std::string signature);
  ```
  (you need to authenticate the signature of the sender first in order to add the message to the `messages` member variable)

For the rest of the member functions of the `Server` class, you must only use STL functions and **you are not allowed to use `while`, `for`, or any other kind of loops in these functions**.


- **get_all_messages_from**<br/>
  This function returns all the messages sent from the `username`.
  ```cpp
  std::vector<Message*> get_all_messages_from(std::string username);
  ```

- **get_all_messages_to**<br/>
  This function returns all the messages sent to the `username`.
  ```cpp
  std::vector<Message*> get_all_messages_to(std::string username);
  ```

- **get_chat**<br/>
  This function returns all the messages between the `user1` and `user2`. (doesn't matter who is the sender or receiver)
  ```cpp
  std::vector<Message*> get_chat(std::string user1, std::string user2);
  ```

- **sort_msgs**<br/>
  This function sorts the `msgs` with respect to the creation time of the messages.
  ```cpp
  void sort_msgs(std::vector<Message*> msgs);
  ```

<br/>
<br/>

# Hint
Instructions to use functions in the `crypto.cpp/h`  file.
- To generate RSA key pairs do:
	```cpp
	std::string public_key{}, private_key{};
	crypto::generate_key(public_key, private_key);
	```
- To sign and authenticate a string with your RSA keys, use:
	```cpp
	std::string signature = crypto::signMessage(private_key, "my data");
	bool authentic = crypto::verifySignature(public_key, "my data", signature);
	```

<br/>
<br/>

# **STL**
Implement the following functions using STL approaches. You are not allowed to use any kind of loops (`while`, `for`, ...) in these functions.<br/>
Implement your functions in the `stl.h` file.

- **initial_vector_with_3_mutiplies**<br/>
  This function gets a vector and fills it with multiplies of 3 (3, 6, 9, 12, ...) with respect to `size`.
  ```cpp
  void initial_vector_with_3_mutiples(std::vector<int>& v, size_t size)
  ```
  *Note.* you can find an example usage of this function in `TEST23`.<br/>
  *Hint.* use `std::generate`!

- **count_unique_above**<br/>
  Count all the unique elements that are higher than `n` in vector `v`.
  ```cpp
  int count_unique_above(std::vector<int> v, int n)
  ```
  *Note.* you can find an example usage of this function in `TEST24`.<br/>
  *Hint.* use `std::count_if`!

- **vector_to_string**<br/>
  convert a vector to a string backward and separate the elements with `separator`.
  ```cpp
  std::string vector_to_string(std::vector<int> v, char separator)
  ```
  *Note.* you can find an example usage of this function in `TEST25`.<br/>
  *Hint.* use `std::accumulate`!

**Challenge.** What problem arises when you put the definition of your functions in a `.h` file? How we can solve this problem?

<br/>
<br/>

# **Finally**
As mentioned before, keep all your implementations in `message.cpp/h`, `serve.cpp/h`, `user.cpp/h`, and `stl.h`. do not alter other files at all. In case you want to test your code you may only use the `debug` section of the `main.cpp` which will be explained in the TA class.

<br/>

```cpp
if (true) // make false to run unit tests  
{ 
	// debug section 
}  
else  
{  
	::testing::InitGoogleTest(&argc, argv);  
	std::cout << "RUNNING TESTS ..." << std::endl;  
	int ret{RUN_ALL_TESTS()};  
	if (!ret)  
		std::cout << "<<<SUCCESS>>>" << std::endl;  
	else  
	  std::cout << "FAILED" << std::endl;  
}  
return 0;
```
<br/>
<p  align="center"> <b>GOOD LUCK</b> </p>


<br/>
<p align="center">
<img src="resources/final.jpeg" alt="final"
title="final" width="400" align="middle" />
</p>
<br/>