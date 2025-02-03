#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>

#include <telegram/agent.h>

#include <iostream>

namespace telegram {

using ClientSession = Poco::Net::HTTPClientSession;
using SClientSession = Poco::Net::HTTPSClientSession;
using Request = Poco::Net::HTTPRequest;
using Response = Poco::Net::HTTPResponse;
using URI = Poco::URI;
using Object = Poco::JSON::Object;
using Array = Poco::JSON::Array;
using Parser = Poco::JSON::Parser;

class DerivedAgent : public Agent {
public:
    DerivedAgent(const std::string& first_uri) : first_uri_(first_uri) {
        URI uri = URI(first_uri_);
        std::string scheme = uri.getScheme();
        std::string host = uri.getHost();
        int port = uri.getPort();
        if (scheme == "http") {
            session_ = std::make_unique<ClientSession>(host, port);
        } else {
            session_ = std::unique_ptr<ClientSession>(new SClientSession(host, port));
        }
    };

    ~DerivedAgent() = default;

    BotCharacteristics GetMe() {
        BotCharacteristics about_bot;
        std::string new_uri = first_uri_;
        new_uri += "getMe";
        URI uri = Poco::URI(new_uri);
        std::string path = uri.getPathAndQuery();
        if (path.empty()) {
            path = "/";
        }
        auto host = uri.getHost();
        auto port = uri.getPort();
        Request request = Request(Request::HTTP_GET, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.add("Host", host);
        // request.write(std::cout);

        session_->sendRequest(request);

        Response response;

        std::istream& body = session_->receiveResponse(response);
        auto status = response.getStatus();
        if (status != 200 and status / 100 != 4) {
            throw AgentError(status, response.getReasonForStatus(status));
        }
        Parser parser;
        Poco::Dynamic::Var result = parser.parse(body);
        Object::Ptr object_ptr = result.extract<Object::Ptr>();
        bool ok_status = object_ptr->getValue<bool>("ok");
        if (ok_status) {
            Object::Ptr result_ptr = object_ptr->getObject("result");
            about_bot.username = result_ptr->getValue<std::string>("username");
            about_bot.is_bot = result_ptr->getValue<bool>("is_bot");
            about_bot.first_name = result_ptr->getValue<std::string>("first_name");
            about_bot.id = result_ptr->getValue<int>("id");
            return about_bot;
        } else {
            std::string description = object_ptr->getValue<std::string>("description");
            int error_code = object_ptr->getValue<int>("error_code");
            throw AgentError(error_code, description);
        }
        return about_bot;
    }

    void SendMessage(Message message) {
        URI uri_1 = Poco::URI(first_uri_);
        URI uri = Poco::URI(uri_1.getPath() + "sendMessage");

        Poco::JSON::Object json_body;
        json_body.set("chat_id", message.chat_id);
        json_body.set("text", message.text);
        if (message.message_id != 0) {
            json_body.set("reply_to_message_id", message.message_id);
        }
        std::stringstream ss;
        json_body.stringify(ss);
        Request request = Request(Request::HTTP_POST, uri.toString());
        auto host = uri_1.getHost();
        auto port = uri_1.getPort();
        request.setContentType("application/json");
        request.setContentLength(ss.str().size());
        std::ostream& os = session_->sendRequest(request);
        json_body.stringify(os);
        Response response;
        std::istream& body = session_->receiveResponse(response);
        auto status = response.getStatus();
        if (status != 200 and status / 100 != 4) {
            throw AgentError(status, response.getReasonForStatus(status));
        }
        // response.write(std::cout);
    }

    void SendSticker(Sticker sticker) {
        URI uri_1 = Poco::URI(first_uri_);
        URI uri = Poco::URI(uri_1.getPath() + "sendSticker");

        Poco::JSON::Object json_body;
        json_body.set("chat_id", sticker.chat_id);
        json_body.set("sticker", sticker.id);
        std::stringstream ss;
        json_body.stringify(ss);
        Request request = Request(Request::HTTP_POST, uri.toString());
        auto host = uri_1.getHost();
        auto port = uri_1.getPort();
        request.setContentType("application/json");
        request.setContentLength(ss.str().size());
        std::ostream& os = session_->sendRequest(request);
        json_body.stringify(os);
        Response response;
        std::istream& body = session_->receiveResponse(response);
        auto status = response.getStatus();
        if (status != 200 and status / 100 != 4) {
            throw AgentError(status, response.getReasonForStatus(status));
        }
        // response.write(std::cout);
    }

    void SendGif(Gif gif) {
        URI uri_1 = Poco::URI(first_uri_);
        URI uri = Poco::URI(uri_1.getPath() + "sendAnimation");

        Poco::JSON::Object json_body;
        json_body.set("chat_id", gif.chat_id);
        json_body.set("animation", gif.id);
        std::stringstream ss;
        json_body.stringify(ss);
        Request request = Request(Request::HTTP_POST, uri.toString());
        auto host = uri_1.getHost();
        auto port = uri_1.getPort();
        request.setContentType("application/json");
        request.setContentLength(ss.str().size());
        std::ostream& os = session_->sendRequest(request);
        json_body.stringify(os);
        Response response;
        std::istream& body = session_->receiveResponse(response);
        auto status = response.getStatus();
        if (status != 200 and status / 100 != 4) {
            throw AgentError(status, response.getReasonForStatus(status));
        }
        // response.write(std::cout);
    }

    void SendPhoto(Photo photo) {
        URI uri_1 = Poco::URI(first_uri_);
        URI uri = Poco::URI(uri_1.getPath() + "sendPhoto");

        Poco::JSON::Object json_body;
        json_body.set("chat_id", photo.chat_id);
        json_body.set("photo", photo.id);
        std::stringstream ss;
        json_body.stringify(ss);
        Request request = Request(Request::HTTP_POST, uri.toString());
        auto host = uri_1.getHost();
        auto port = uri_1.getPort();
        request.setContentType("application/json");
        request.setContentLength(ss.str().size());
        std::ostream& os = session_->sendRequest(request);
        json_body.stringify(os);
        Response response;
        std::istream& body = session_->receiveResponse(response);
        auto status = response.getStatus();
        if (status != 200 and status / 100 != 4) {
            throw AgentError(status, response.getReasonForStatus(status));
        }
        // response.write(std::cout);
    }

    Message GetMessage(Object::Ptr message) {
        Message structed_message;
        Object::Ptr chat = message->getObject("chat");
        structed_message.chat_id = chat->getValue<int>("id");
        structed_message.message_id = message->getValue<int>("message_id");
        if (message->has("text")) {
            structed_message.text = message->getValue<std::string>("text");
        }
        return structed_message;
    }

    std::vector<Update> GetUpdates(int offset, int timeout) {
        std::vector<Update> updates;
        std::string new_uri = first_uri_;
        new_uri += "getUpdates";
        URI uri = Poco::URI(new_uri);
        std::string path = uri.getPathAndQuery();
        if (path.empty()) {
            path = "/";
        }
        auto host = uri.getHost();
        auto port = uri.getPort();
        if (offset != 0 and timeout != 0) {
            path += "?offset=" + std::to_string(offset) + "&timeout=" + std::to_string(timeout);
        } else if (offset != 0) {
            path += "?offset=" + std::to_string(offset);
        } else if (timeout != 0) {
            path += "?timeout=" + std::to_string(timeout);
        }

        Request request = Request(Request::HTTP_GET, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.add("Host", host);
        // request.write(std::cout);

        session_->sendRequest(request);
        Response response;

        std::istream& body = session_->receiveResponse(response);
        auto status = response.getStatus();
        if (status != 200 and status / 100 != 4) {
            throw AgentError(status, response.getReasonForStatus(status));
        }
        Parser parser;
        Poco::Dynamic::Var result = parser.parse(body);
        Object::Ptr object_ptr = result.extract<Object::Ptr>();
        bool ok_status = object_ptr->getValue<bool>("ok");
        if (ok_status) {
            Array::Ptr result_ptr = object_ptr->getArray("result");
            size_t size = result_ptr->size();
            for (size_t i = 0; i < size; i++) {
                Update update;
                Object::Ptr object = result_ptr->getObject(i);
                Object::Ptr message_obj = object->getObject("message");
                Message message = GetMessage(message_obj);
                update.id = object->getValue<int>("update_id");
                update.message = message;
                updates.push_back(update);
            }
            return updates;
        } else {
            std::string description = object_ptr->getValue<std::string>("description");
            int error_code = object_ptr->getValue<int>("error_code");
            throw AgentError(error_code, description);
        }
    }

private:
    std::string first_uri_;
    std::unique_ptr<Poco::Net::HTTPClientSession> session_;
};

std::unique_ptr<Agent> CreateAgent(std::string url) {
    return std::make_unique<DerivedAgent>(url);
}

}  // namespace telegram
