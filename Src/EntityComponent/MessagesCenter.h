/**
Manager interface for message events.
*/

#pragma once

#ifndef __EC_MESSAGES_CENTER
#define __EC_MESSAGES_CENTER

#include <vector>

#include "Message.h"


namespace me {

    class Listener;

    class MessagesCenter {
    public:

        /**
        Build the foundation of the MessagesCenter.
        */
        MessagesCenter();

        /**
        This method is meant to be the definition
        of the dynamic memory that has to be safely delete.
        */
        virtual ~MessagesCenter();

        /**
        Log in a new Listener to take it into account.
        @param Listener object.
        */
        void loginListener(Listener* listener);

        /**
        Log out a new Listener to stop taking it into account.
        @param Listener object.
        */
        void logoutListener(Listener* listener);

        /**
        Method to receive and process message events.
        @param Message with all information.
        */
        void sendMessage(const Message& message);

        /**
        Get the actual message information.
        @return Message with all information.
        */
        const Message& getMessage() const;

        /**
        Method to communicate message events to all registered listeners.
        */
        void notifyListeners();

    private:

        Message message_;
        std::vector<Listener*> listeners_;

    };

};

#endif