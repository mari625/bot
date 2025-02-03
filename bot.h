#pragma once

#include <telegram/client.h>

namespace telegram {

class Bot {
public:
    virtual ~Bot() = default;
    virtual void Run() = 0;

private:
    std::string token_;
};

std::unique_ptr<Bot> CreateBot(std::string bot_token);

}  // namespace telegram