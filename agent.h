#pragma once

#include <string>
#include <string_view>
#include <memory>
#include <vector>

namespace telegram {

struct Message {
    int chat_id;
    std::string text;
    int message_id;
};

struct Sticker {
    int chat_id;
    std::string id;
};

struct Gif {
    int chat_id;
    std::string id;
};

struct Photo {
    int chat_id;
    std::string id;
};

struct Update {
    int id;
    Message message;
};

struct BotCharacteristics {
    int id;
    bool is_bot;
    std::string username;
    std::string first_name;
};

struct AgentError : std::runtime_error {
    AgentError(int http_code, std::string details)
        : std::runtime_error{"api error: code=" + std::to_string(http_code) +
                             " details=" + details},
          http_code{http_code},
          details{std::move(details)} {
    }

    int http_code;
    std::string details;
};

class Agent {
public:
    virtual ~Agent() = default;
    virtual BotCharacteristics GetMe() = 0;
    virtual void SendMessage(Message message) = 0;
    virtual void SendSticker(Sticker sticker) = 0;
    virtual void SendGif(Gif gif) = 0;
    virtual void SendPhoto(Photo photo) = 0;
    virtual std::vector<Update> GetUpdates(int offset = 0, int timeout = 0) = 0;
};

std::unique_ptr<Agent> CreateAgent(std::string url);

}  // namespace telegram