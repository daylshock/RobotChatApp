#include "chatListForm.h"
#include "forms/chatForm.h"

namespace RobotChatApp 
{
	ChatListForm::ChatListForm(ChatService^ service) 
	{
		chatService = service;
		InitializeComponent();
		LoadChats();
	}
	void ChatListForm::InitializeComponent() 
	{
		this->chatListView = gcnew System::Windows::Forms::ListView();
		this->SuspendLayout();

        this->chatListView->Dock = System::Windows::Forms::DockStyle::Fill;
        this->chatListView->View = System::Windows::Forms::View::Details;
        this->chatListView->FullRowSelect = true;
        this->chatListView->Columns->Add("Название", 200);
        this->chatListView->Columns->Add("Последнее сообщение", 300);
        this->chatListView->Columns->Add("Отправитель", 150);
        this->chatListView->Columns->Add("Дата", 100);
        this->chatListView->SelectedIndexChanged +=
            gcnew System::EventHandler(this, &ChatListForm::ChatListView_SelectedIndexChanged);

        this->Text = "Список чатов";
        this->Controls->Add(this->chatListView);
        this->ResumeLayout(false);
	}
    void ChatListForm::LoadChats()
    {
        chatListView->Items->Clear();

        for each (Chat^ chat in chatService->GetChats()) 
        {
            System::Windows::Forms::ListViewItem^ item = gcnew System::Windows::Forms::ListViewItem(chat->Title);
            item->SubItems->Add(chat->LastMessage->Text);
            item->SubItems->Add(chat->LastMessage->SenderName);
            item->SubItems->Add(chat->LastMessage->Date.ToString("g"));
            item->Tag = chat->Id;

            chatListView->Items->Add(item);
        }
    }

    void ChatListForm::ChatListView_SelectedIndexChanged(Object^ sender, EventArgs^ e)
    {
        if (chatListView->SelectedItems->Count == 0) return;

        String^ chatId = (String^)chatListView->SelectedItems[0]->Tag;
        Chat^ chat = chatService->GetChat(chatId);

        ChatForm^ chatForm = gcnew ChatForm(chatService, chat);
        chatForm->Show();
    }
}