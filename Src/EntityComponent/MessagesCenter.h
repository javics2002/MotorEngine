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
            mListeners.push_back(listener);
        };

        /**
        Log out a new Listener to stop taking it into account.
        @param Listener object.
        */
        void logoutListener(Listener* listener) {
            mListeners.erase(std::remove(mListeners.begin(), mListeners.end(), listener), mListeners.end());
        };

        /**
        Method to receive and process message events.
        @param Message with all information.
        */
        inline void sendMessage(const Message& message) {
            mMessage = message;
            notifyListeners();
        };

        /**
        Get the actual message information.
        @return Message with all information.
        */
        inline const Message& getMessage() const {
            return mMessage;
        };

        /**
        Method to communicate message events to all registered listeners.
        */
        void notifyListeners() {
            for (Listener* listener : mListeners) {
                listener->handleMessage(mMessage);
            };
        };

    private:

        Message mMessage;
        std::vector<Listener*> mListeners;

    };

};

#endif