/**
Interface of a Listener.
*/

#pragma once

#ifndef __EC_LISTENER
#define __EC_LISTENER


namespace me {
    
    class Message;

    class Listener {
    public:

        /**
        Main method of the interface.
        Undefined method to be redefine by inheritance.

        This method is meant to be the definition
        of how to process messages and which should be process.
        @param Message to be process with the data that should be use.
        */
        virtual void handleMessage(const Message& message) {};

    };

};

#endif