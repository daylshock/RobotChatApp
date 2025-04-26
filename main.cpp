#include "services/chatService.h"
#include "forms/chatListForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace RobotChatApp;

[STAThread]
int WinMain() 
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    ChatService^ chatService = gcnew ChatService();
    ChatListForm^ mainForm = gcnew ChatListForm(chatService);

    Application::Run(mainForm);

    return 0;
}