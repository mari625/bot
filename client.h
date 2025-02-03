#pragma once

#include <telegram/agent.h>

#include <memory>
#include <fstream>

namespace telegram {

struct ClientError : std::runtime_error {
    ClientError(int http_code, std::string details)
        : std::runtime_error{"api error: code=" + std::to_string(http_code) +
                             " details=" + details},
          http_code{http_code},
          details{std::move(details)} {};

    int http_code;
    std::string details;
};

struct OffsetClientError : std::runtime_error {
    OffsetClientError() : std::runtime_error{"Something wrong with offset"} {};
};

class Client {
public:
    virtual ~Client() = default;
    virtual std::string GetUrl() = 0;
    virtual BotCharacteristics GetMe() = 0;
    virtual int GetOffset() = 0;
    virtual void SetOffset(int offset = 0) = 0;
    virtual void SendMessage(Message message) = 0;
    virtual void SendSticker(Sticker sticker) = 0;
    virtual void SendGif(Gif gif) = 0;
    virtual void SendPhoto(Photo photo) = 0;
    virtual std::vector<Update> GetUpdates(int offset = 0, int timeout = 0) = 0;
};

std::unique_ptr<Client> CreateApi(std::string bot_token = "123",
                                  std::string_view url = "http://localhost:8080");

}  // namespace telegram