/**
Data structure that contains message event information.
*/

#pragma once

#ifndef __EC_MESSAGE
#define __EC_MESSAGE

#include <string>

#include "data_types.h"


namespace me {

    /**
    Defines the differents types of messages.
    */
    enum class MessageType : uint8_t {
        _PAUSE_START_,
        _PAUSE_OVER_,
        _ROUND_START_, 
        _ROUND_OVER_, 
        _GAME_START_,
        _GAME_OVER_
    };

    /**
    Defines the possible content of the message.

    Fact: 'union' data share the same portion of memory,
    that means that only one of those fields can be use at the same time.
    */
    union MessageData {
        State st;
        Collision col;
        Score score;
    };

    struct Message {
    public:

        /**
        Build the default foundation of the Message.
        */
        Message();

        /**
        Build the foundation of the Message.
        @param MessageType to identify the message.
        @param MessageData with the information to be communicate.
        */
        Message(MessageType type, MessageData data);

        /**
        This method is meant to be the definition
        of the dynamic memory that has to be safely delete.
        */
        virtual ~Message();

        /**
        Get the type of the actual message.
        @return MessageType.
        */
        inline MessageType getType() const {
            return type;
        };

        /**
        Get the data of the actual message.
        @return MessageData.
        */
        inline MessageData getData() const {
            return data;
        };

        /**
        Duplicate the actual message.
        @return Message.
        */
        virtual Message* clone() const;

    private:

        MessageType type;
        MessageData data;

    };

};

#endif