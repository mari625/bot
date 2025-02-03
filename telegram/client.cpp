#include <telegram/client.h>

#include <vector>
#include <iostream>

namespace telegram {

class DerivedClient : public Client {
public:
    DerivedClient(const std::string& uri) : uri_(uri){};

    ~DerivedClient() = default;

    std::string GetUrl() {
        return uri_;
    }

    BotCharacteristics GetMe() {
        BotCharacteristics bot_info;
        auto agent = CreateAgent(uri_);
        try {
            bot_info = agent->GetMe();
        } catch (AgentError error) {
            if (error.http_code / 100 == 4) {
                throw ClientError(error.http_code, error.details);
            } else {
                throw error;
            }
        }
        return bot_info;
    }

    int GetOffset() {
        int offset = 0;
        std::ifstream in;
        in.open("offset.txt");
        if (in.peek() != EOF) {
            in >> offset;
        }
        in.close();
        return offset;
    }

    void SetOffset(int offset) {
        std::ofstream out;
        out.open("offset.txt");
        out << offset << std::endl;
        out.close();
    }

    std::vector<Update> GetUpdates(int offset, int timeout) {
        timeout_ = timeout;
        auto agent = CreateAgent(uri_);
        std::vector<Update> updates;
        try {
            std::vector<Update> incoming_updates = agent->GetUpdates(offset, timeout_);
            for (Update update : incoming_updates) {
                if (update.id > GetOffset()) {
                    updates.emplace_back(update);
                }
            }
            return updates;
        } catch (AgentError error) {
            if (error.http_code / 100 == 4) {
                throw ClientError(error.http_code, error.details);
            } else {
                throw error;
            }
        }
        return updates;
    }

    void SendMessage(Message message) {
        auto agent = CreateAgent(uri_);
        try {
            agent->SendMessage(message);
        } catch (AgentError error) {
            if (error.http_code / 100 == 4) {
                throw ClientError(error.http_code, error.details);
            } else {
                throw error;
            }
        }
    }

    void SendSticker(Sticker sticker) {
        auto agent = CreateAgent(uri_);
        try {
            agent->SendSticker(sticker);
        } catch (AgentError error) {
            if (error.http_code / 100 == 4) {
                throw ClientError(error.http_code, error.details);
            } else {
                throw error;
            }
        }
    }

    void SendGif(Gif gif) {
        auto agent = CreateAgent(uri_);
        try {
            agent->SendGif(gif);
        } catch (AgentError error) {
            if (error.http_code / 100 == 4) {
                throw ClientError(error.http_code, error.details);
            } else {
                throw error;
            }
        }
    }

    void SendPhoto(Photo photo) {
        auto agent = CreateAgent(uri_);
        try {
            agent->SendPhoto(photo);
        } catch (AgentError error) {
            if (error.http_code / 100 == 4) {
                throw ClientError(error.http_code, error.details);
            } else {
                throw error;
            }
        }
    }

private:
    std::string uri_;
    int timeout_ = 5;
};

std::unique_ptr<Client> CreateApi(std::string bot_token, std::string_view url) {
    std::string temp(url);
    temp += "bot" + bot_token + "/";
    return std::make_unique<DerivedClient>(temp);
}

}  // namespace telegram
