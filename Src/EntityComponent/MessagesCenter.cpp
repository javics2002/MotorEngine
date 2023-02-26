#include "MessagesCenter.h"
#include "Listener.h"
#include "Message.h"


namespace me {

    MessagesCenter::MessagesCenter() :
        message_(),
        listeners_()
    {
    };

    MessagesCenter::~MessagesCenter() {
        //listeners_.clear();
        listeners_.resize(0);
    };

    void MessagesCenter::loginListener(Listener* listener) {
        listeners_.push_back(listener);
    };

    void MessagesCenter::logoutListener(Listener* listener) {
        // Tengo la duda de si es correcto llamar al destructor del objeto en este punto...
        //listeners_.erase(std::remove(listeners_.begin(), listeners_.end(), listener), listeners_.end());
        std::remove(listeners_.begin(), listeners_.end(), listener);
        listeners_.pop_back();
    };

    void MessagesCenter::sendMessage(const Message& message) {
        message_ = message;
        notifyListeners();
    };

    const Message& MessagesCenter::getMessage() const {
        return message_;
    };

    void MessagesCenter::notifyListeners() {
        for (Listener* listener : listeners_) {
            listener->handleMessage(message_);
        };
    };

};