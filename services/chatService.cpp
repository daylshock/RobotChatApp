#include "chatService.h"

namespace RobotChatApp 
{
	ChatService::ChatService() : random(gcnew Random)
	{
		chats = gcnew System::Collections::Generic::List<Chat^>();
		ChatService::InitializeTestData();
		botResponses = gcnew array<String^> {
											"Интересно, расскажите подробнее.",
											"Я робот и не совсем понимаю ваш вопрос.",
											"Спасибо за ваше сообщение! Как я могу помочь?"
											};
	}
	void ChatService::InitializeTestData()
	{
		for (int i = 1; i <= 5; i++)
		{
			Chat^ chat = gcnew Chat();
			chat->Title = String::Format("Чат {0}", i);
			
			Message^ message = gcnew Message();
			message->Text = String::Format("Тестовое сообщение {0}", i);
			message->Date = DateTime::Now.AddMinutes(-i);
			message->SenderName = "Пользователь";
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
		userMessage->SenderName = "Вы";
		userMessage->IsFromUser = true;

		chat->Messages->Add(userMessage);

		int index = random->Next(botResponses->Length);
		String^ botResponse = botResponses[index];

		Message^ botMessage = gcnew Message();
		botMessage->Text = botResponse;
		botMessage->Date = DateTime::Now;
		botMessage->SenderName = "Робот";
		botMessage->IsFromUser = false;

		chat->Messages->Add(botMessage);
		chat->LastMessage = botMessage;
	}
}