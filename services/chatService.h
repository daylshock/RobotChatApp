#pragma once
#include "models/chat.h"

namespace RobotChatApp 
{
	public ref class ChatService
	{
	private:
		System::Collections::Generic::List<Chat^>^ chats;
		array<String^>^ botResponses;
		Random^ random;
		void InitializeTestData();

	public:
		ChatService();

		System::Collections::Generic::List<Chat^>^ GetChats();
		Chat^ GetChat(String^ id);
		void SendMessage(String^ chatId, String^ messageText);
	};
}