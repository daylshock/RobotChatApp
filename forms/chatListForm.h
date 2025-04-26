#pragma once
#include "services/chatService.h"

namespace RobotChatApp 
{
    public ref class ChatListForm : public System::Windows::Forms::Form 
    {
    private:
        ChatService^ chatService;
        System::Windows::Forms::ListView^ chatListView;
        
        void InitializeComponent();
        void LoadChats();
        void ChatListView_SelectedIndexChanged(Object^ sender, EventArgs^ e);

    public:
        ChatListForm(ChatService^ service);
    };
}
