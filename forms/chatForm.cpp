#include "chatForm.h"

namespace RobotChatApp 
{
    ChatForm::ChatForm(ChatService^ service, Chat^ chat) 
    {
        chatService = service;
        currentChat = chat;
        InitializeComponent();
        LoadMessages();
    }

    void ChatForm::InitializeComponent() 
    {
        this->messagesListView = gcnew System::Windows::Forms::ListView();
        this->messageTextBox = gcnew System::Windows::Forms::TextBox();
        this->sendButton = gcnew System::Windows::Forms::Button();

        this->messagesListView->Dock = System::Windows::Forms::DockStyle::Fill;
        this->messagesListView->View = System::Windows::Forms::View::Details;
        this->messagesListView->Columns->Add("Sender", 150);
        this->messagesListView->Columns->Add("Message", 400);
        this->messagesListView->Columns->Add("Date", 100);

        this->messageTextBox->Dock = System::Windows::Forms::DockStyle::Fill;

        this->sendButton->Text = "Send";
        this->sendButton->Dock = System::Windows::Forms::DockStyle::Right;
        this->sendButton->Click += gcnew System::EventHandler(this, &ChatForm::SendButton_Click);

        System::Windows::Forms::Panel^ inputPanel = gcnew System::Windows::Forms::Panel();
        inputPanel->Dock = System::Windows::Forms::DockStyle::Bottom;
        inputPanel->Height = 40;
        inputPanel->Controls->Add(this->messageTextBox);
        inputPanel->Controls->Add(this->sendButton);

        this->Text = currentChat->Title;
        this->Controls->Add(this->messagesListView);
        this->Controls->Add(inputPanel);
    }

    void ChatForm::LoadMessages() 
    {
        messagesListView->Items->Clear();

        for each (Message^ message in currentChat->Messages)
        {
            System::Windows::Forms::ListViewItem^ item = gcnew System::Windows::Forms::ListViewItem(message->SenderName);
            item->SubItems->Add(message->Text);
            item->SubItems->Add(message->Date.ToString("g"));

            messagesListView->Items->Add(item);
        }
    }

    void ChatForm::SendButton_Click(Object^ sender, EventArgs^ e) 
    {
        if (String::IsNullOrWhiteSpace(messageTextBox->Text)) 
            return;

        chatService->SendMessage(currentChat->Id, messageTextBox->Text);
        messageTextBox->Clear();

        currentChat = chatService->GetChat(currentChat->Id);
        LoadMessages();
    }
}