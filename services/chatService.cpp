#include "chatService.h"

namespace RobotChatApp 
{
	ChatService::ChatService() : random(gcnew Random)
	{
		chats = gcnew System::Collections::Generic::List<Chat^>();
		ChatService::InitializeTestData();
		botResponses = gcnew array<String^> {
											"���������, ���������� ���������.",
											"� ����� � �� ������ ������� ��� ������.",
											"������� �� ���� ���������! ��� � ���� ������?"
											};
	}
	void ChatService::InitializeTestData()
	{
		for (int i = 1; i <= 5; i++)
		{
			Chat^ chat = gcnew Chat();
			chat->Title = String::Format("��� {0}", i);
			
			Message^ message = gcnew Message();
			message->Text = String::Format("�������� ��������� {0}", i);
			message->Date = DateTime::Now.AddMinutes(-i);
			message->SenderName = "������������";
			message->IsFromUser = true;

			chat->Messages->Add(message);
			chat->LastMessage = message;
			chats->Add(chat);
		}
	}
	System::Collections::Generic::List<Chat^>^ ChatService::GetChats()
	{
		return chats;
	}
	Chat^ ChatService::GetChat(String^ id)
	{
		for each (Chat^ iter in chats)
		{
			if (iter->Id == id)
				return iter;
		}
		return nullptr;
	}

	void ChatService::SendMessage(String^ chatId, String^ messageText)
	{
		Chat^ chat = GetChat(chatId);

		if (chat == nullptr)
			return;
		
		Message^ userMessage = gcnew Message();
		userMessage->Text = messageText;
		userMessage->Date = DateTime::Now;
		userMessage->SenderName = "��";
		userMessage->IsFromUser = true;

		chat->Messages->Add(userMessage);

		int index = random->Next(botResponses->Length);
		String^ botResponse = botResponses[index];

		Message^ botMessage = gcnew Message();
		botMessage->Text = botResponse;
		botMessage->Date = DateTime::Now;
		botMessage->SenderName = "�����";
		botMessage->IsFromUser = false;

		chat->Messages->Add(botMessage);
		chat->LastMessage = botMessage;
	}
}