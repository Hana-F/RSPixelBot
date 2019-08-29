#include "BotInternals.h"



BotInternals::BotInternals()
{
}

// Sets the bot up.
void BotInternals::BotInit()
{
	hdc = GetDC(HWND_DESKTOP);

	MouseSetting.type = INPUT_MOUSE;
	MouseSetting.mi.dwExtraInfo = 0;
	MouseSetting.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
	MouseSetting.mi.dx = NULL;
	MouseSetting.mi.dy = NULL;
	MouseSetting.mi.mouseData = 0;
	MouseSetting.mi.time = 0;

	KeyboardSetting.type = INPUT_KEYBOARD;
	KeyboardSetting.ki.dwExtraInfo = 0;
	KeyboardSetting.ki.dwFlags = 0;
	KeyboardSetting.ki.time = 0;
	KeyboardSetting.ki.wScan = NULL;
	KeyboardSetting.ki.wVk = VK_SHIFT;

	RECT * Desktop = new RECT;
	HWND * hWnd = new HWND;

	*hWnd = GetDesktopWindow();
	GetWindowRect(*hWnd, Desktop);

	VRes = Desktop->bottom;
	HRes = Desktop->right;

	delete Desktop;
	delete hWnd;

}
// Set the clicking position for the bot.
int BotInternals::SetClickPosition(char x)
{
	if (x == 'O')
	{
		std::cout << "Hover over the spot for clicking and press O.\n";
		while (1)
		{
			if (GetAsyncKeyState('O') & 1)
			{
				GetCursorPos(&OreLocation);
				Color = GetPixel(hdc, OreLocation.x, OreLocation.y);
				Red = GetRValue(Color);
				Green = GetGValue(Color);
				Blue = GetBValue(Color);
				TotalValue = Red + Green + Blue;
				return 0;
			}
			Sleep(10);
		}
	}
	if (x == 'I')
	{
		std::cout << "Hover over the first spot in your inventory and press I (Make sure it is emtpy).\n";
		while (1)
		{
			if (GetAsyncKeyState('I') & 1)
			{
				GetCursorPos(&InventoryLocation);
				InventoryBot.Color = GetPixel(hdc, InventoryLocation.x, InventoryLocation.y);
				InventoryBot.Red = GetRValue(InventoryBot.Color);
				InventoryBot.Green = GetGValue(InventoryBot.Color);
				InventoryBot.Blue = GetBValue(InventoryBot.Color);
				InventoryBot.TotalValue = InventoryBot.Red + InventoryBot.Green + InventoryBot.Blue;
				return 0;
			}
			Sleep(10);
		}
	}
	else
	{
		MessageBox(NULL, TEXT("Didn't use SetClickPosition properly."), TEXT("Function Error."), MB_ICONERROR);
		exit(1);
	}
}

// Shows the screen res. Use HRes or VRes.
int BotInternals::ShowScreenRes(char x)
{
	if (x == 'H')
		return HRes;
	if (x == 'V')
		return VRes;
	else
	{
		MessageBox(NULL, TEXT("Didn't use ShowScreenRes properly."), TEXT("Function Error."), MB_ICONERROR);
		exit(1);
	}
}

int BotInternals::GetOreColor()
{
	Color = GetPixel(hdc, OreLocation.x, OreLocation.y);
	Red = GetRValue(Color);
	Green = GetGValue(Color);
	Blue = GetBValue(Color);
	RTotalValue = Red + Green + Blue;
	return RTotalValue;
}

int BotInternals::GetInventoryColor()
{
	InventoryBot.Color = GetPixel(hdc, InventoryLocation.x, InventoryLocation.y);
	InventoryBot.Red = GetRValue(InventoryBot.Color);
	InventoryBot.Green = GetGValue(InventoryBot.Color);
	InventoryBot.Blue = GetBValue(InventoryBot.Color);
	InventoryBot.RTotalValue = InventoryBot.Red + InventoryBot.Green + InventoryBot.Blue;
	return InventoryBot.RTotalValue;
}

int BotInternals::ShowColorValue(char x)
{
	if (x == 'O')
	{
		return TotalValue;
	}
	if (x == 'I')
	{
		return InventoryBot.TotalValue;
	}
	else
	{
		MessageBox(NULL, TEXT("Didn't use ShowColorValue properly."), TEXT("Function Error."), MB_ICONERROR);
		exit(1);
	}
}

int BotInternals::ClickOre()
{
	int x;
	MouseSetting.mi.dx = OreLocation.x * (65535 / HRes);
	MouseSetting.mi.dy = OreLocation.y * (65535 / VRes);
	while (1)
	{
		SetCursorPos(OreLocation.x, OreLocation.y);
		x = GetOreColor();
		if (x == TotalValue)
		{
			SendInput(1, &MouseSetting, sizeof(INPUT));
		}
		if (x != TotalValue)
		{
			return 0;
		}
		Sleep(400);
	}
}

int BotInternals::ClickInventory()
{
	int x;
	MouseSetting.mi.dx = InventoryLocation.x * (65535 / HRes);
	MouseSetting.mi.dy = InventoryLocation.y * (65535 / VRes);
	while (1)
	{
		SetCursorPos(InventoryLocation.x, InventoryLocation.y);
		x = GetInventoryColor();
		if (x != InventoryBot.TotalValue)
		{
			SendInput(1, &MouseSetting, sizeof(INPUT));
		}
		if (x == InventoryBot.TotalValue)
		{
			return 0;
		}
		Sleep(400);
	}
	return 0;
}

void BotInternals::ShiftClick()
{
	SendInput(1, &KeyboardSetting, sizeof(INPUT));
}

void BotInternals::CleanUp(BotInternals * x)
{
	ReleaseDC(GetDesktopWindow(), hdc);

	KeyboardSetting.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &KeyboardSetting, sizeof(INPUT));

	delete x;

	exit(1);

}

HDC BotInternals::GetHDC()
{
	return hdc;
}



BotInternals::~BotInternals()
{
}
