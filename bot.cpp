#include <telegram/bot.h>
#include <iostream>

namespace telegram {

class DerivedBot : public Bot {
private:
    std::string token_;
    std::unique_ptr<telegram::Client> client_;
    int timeout_ = 5;
    std::string greeting_ = "Hi! What I can do: \n";
    std::string about_ =
        "/random - random number \n /weather - The winter is coming \n /styleguide - joke about "
        "code review \n /sticker - sticker \n /gif - gif \n /about - information about my "
        "abilities \n /crash - crash of process \n /stop - end of process \n";

public:
    DerivedBot(const std::string& token) : token_(token) {
        client_ = telegram::CreateApi(token_, "https://api.telegram.org/");
    };

    ~DerivedBot() = default;

    void Run() {
        try {
            while (true) {
                std::vector<Update> updates =
                    client_->GetUpdates(client_->GetOffset() + 1, timeout_);
                for (Update update : updates) {
                    Message message = update.message;
                    std::string text = message.text;
                    if (text == "/start") {
                        std::string text = greeting_ + about_;
                        client_->SendMessage(Message(message.chat_id, text));
                    } else if (text == "/random") {
                        std::string text = std::to_string(std::rand());
                        client_->SendMessage(Message(message.chat_id, text));
                    } else if (text == "/weather") {
                        client_->SendMessage(Message(message.chat_id, "Winter Is Coming"));
                    } else if (text == "/styleguide") {
                        client_->SendPhoto(
                            Photo(message.chat_id, "https://i.imgur.com/Lc1dtWu.jpeg"));
                    } else if (text == "/sticker") {
                        client_->SendSticker(Sticker(message.chat_id,
                                                     "CAACAgIAAxkBAAEK7DBlcwI5a2ruv1HEcK_"
                                                     "3qi9CWer4JgACCh8AAkrrKUiW-wfFag0_4zME"));
                    } else if (text == "/gif") {
                        client_->SendGif(Gif(
                            message.chat_id,
                            "https://media1.tenor.com/m/9bC8wn-2rSwAAAAd/leonardo-dicaprio.gif"));
                    } else if (text == "/about") {
                        client_->SendMessage(Message(message.chat_id, about_));
                    } else if (text == "/crash") {
                        client_->SetOffset(client_->GetOffset() + 1);
                        abort();
                    } else if (text == "/stop") {
                        client_->SetOffset(client_->GetOffset() + 1);
                        client_->GetUpdates(client_->GetOffset(), 0);
                        exit(0);
                    } else if (!text.empty()) {
                        client_->SendMessage(
                            Message(message.chat_id, "Sorry, I don't understand you"));
                    }
                    client_->SetOffset(update.id);
                }
            }
        } catch (std::runtime_error error) {
            throw error;
        } catch (...) {
            throw std::runtime_error{"Something went wrong"};
        }
    }
};

std::unique_ptr<Bot> CreateBot(std::string bot_token) {
    return std::make_unique<DerivedBot>(bot_token);
}

}  // namespace telegram