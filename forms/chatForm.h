#pragma once
#include "services/chatService.h"

namespace RobotChatApp 
{
    public ref class ChatForm : public System::Windows::Forms::Form 
    {
    private:
        ChatService^ chatService;
        Chat^ currentChat;

        System::Windows::Forms::ListView^ messagesListView;
        System::Windows::Forms::TextBox^ messageTextBox;
        System::Windows::Forms::Button^ sendButton;

        void InitializeComponent();
        void LoadMessages();
        void SendButton_Click(Object^ sender, EventArgs^ e);

    public:
        ChatForm(ChatService^ service, Chat^ chat);
    };
}