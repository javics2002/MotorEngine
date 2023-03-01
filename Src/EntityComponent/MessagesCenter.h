/**
Manager interface for message events.
*/

#pragma once

#ifndef __EC_MESSAGES_CENTER
#define __EC_MESSAGES_CENTER

#include <vector>

#include "Message.h"
#include "Listener.h"


namespace me {

    class MessagesCenter {
    public:

        /**
        Log in a new Listener to take it into account.
        @param Listener object.
        */
        void loginListener(Listener* listener) {
            listeners_.push_back(listener);
        };

        /**
        Log out a new Listener to stop taking it into account.
        @param Listener object.
        */
        void logoutListener(Listener* listener) {
            listeners_.erase(std::remove(listeners_.begin(), listeners_.end(), listener), listeners_.end());
        };

        /**
        Method to receive and process message events.
        @param Message with all information.
        */
        inline void sendMessage(const Message& message) {
            message_ = message;
            notifyListeners();
        };

        /**
        Get the actual message information.
        @return Message with all information.
        */
        inline const Message& getMessage() const {
            return message_;
        };

        /**
        Method to communicate message events to all registered listeners.
        */
        void notifyListeners() {
            for (Listener* listener : listeners_) {
                listener->handleMessage(message_);
            };
        };

    private:

        Message message_;
        std::vector<Listener*> listeners_;

    };

};

#endif