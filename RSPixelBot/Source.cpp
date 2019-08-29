
#include <iostream>
#include <thread>
#include "BotInternals.h"


void CloseProgram(BotInternals * x);
void ShiftCheck(BotInternals * x);

int main(void)
{
	int x = 0;

	BotInternals * BotMain = new BotInternals;

	BotMain->BotInit();

	std::thread CloseThread(CloseProgram, BotMain);
	std::thread ShiftThread(ShiftCheck, BotMain);

	BotMain->SetClickPosition('O');
	BotMain->SetClickPosition('I');

	FreeConsole();
	while (1)
	{
		BotMain->ClickOre();
		BotMain->ClickInventory();
		Sleep(200);
		if (x >= 250)
		{
			Sleep(10000);
			x = 0;
		}
		x++;
	}

	return 0;
}

void CloseProgram(BotInternals * x)
{
	while (1)
	{
		if (GetAsyncKeyState('E') & 1)
		{
			x->CleanUp(x);
		}
		Sleep(200);
	}
}

void ShiftCheck(BotInternals * x)
{
	while (1)
	{
		if (GetAsyncKeyState(VK_SHIFT) != -32767)
		{
			x->ShiftClick();
		}
		Sleep(1000);
	}
}