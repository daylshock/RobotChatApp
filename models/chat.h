#pragma once

using namespace System;

namespace RobotChatApp 
{
    public ref class Message 
    {
    public:
        property String^ Text;
        property DateTime Date;
        property String^ SenderName;
        property bool IsFromUser;
    };

    public ref class Chat 
    {
    public:
        property String^ Id;
        property String^ Title;
        property Message^ LastMessage;
        property System::Collections::Generic::List<Message^>^ Messages;

        Chat() 
        {
            Id = Guid::NewGuid().ToString();
            Messages = gcnew System::Collections::Generic::List<Message^>();
        }
    };
}