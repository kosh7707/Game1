#include "pch.h"
#include "Service.h"
#include "GameSession.h"
#include "ThreadManager.h"
#include "ClientPacketHandler.h"

using namespace std;

int main() {
	ClientPacketHandler::Init();

	ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>,
		100);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 5; i++)
	{
		GThreadManager->Launch([&service]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}

	cout << "Listening at 127.0.0.1:7777" << endl;

	while (true) 
	{

	}

	GThreadManager->Join();
}
