#pragma once

#include <Windows.h>
#include <iostream>

class BotInternals
{
private:
	HDC hdc;
	POINT OreLocation;
	POINT InventoryLocation;
	INPUT MouseSetting;
	INPUT KeyboardSetting;
	int VRes;
	int HRes;
	COLORREF Color;
	BYTE Red, Green, Blue, RRed, RGreen, RBlue;
	int TotalValue, RTotalValue;
	class InventoryInternals
	{
	public:
		COLORREF Color;
		BYTE Red, Green, Blue, RRed, RGreen, RBlue;
		int TotalValue, RTotalValue;
	};
	BotInternals::InventoryInternals InventoryBot;
public:
	BotInternals();
	void BotInit();
	int SetClickPosition(char);
	int ShowScreenRes(char x);
	int GetOreColor();
	int GetInventoryColor();
	int ShowColorValue(char x);
	int ClickOre();
	int ClickInventory();
	void ShiftClick();
	void CleanUp(BotInternals * x);
	HDC GetHDC();
	~BotInternals();
};

