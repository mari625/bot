#include <string>
#include <iostream>
#include <telegram/bot.h>

int main() {
    std::string token = "6987739896:AAHYsjloy-h4jUkFkcSBIXOwRIDzsI0Ga5U";
    auto bot = telegram::CreateBot(token);
    bot->Run();
    return 0;
}
