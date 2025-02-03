#include <string>
#include <iostream>
#include <telegram/bot.h>

int main() {
    std::string token = "";
    auto bot = telegram::CreateBot(token);
    bot->Run();
    return 0;
}
