#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

/*special:
1 = SPACE
2 = ENTER
3 = CAPSLOCK
4 = BACKSPACE
*/

void press(char a,int special = -404)
{
	switch (special)
	{
	case -404: 	
		keybd_event(VkKeyScan(a), 1, 0, 0);
		Sleep(5);
		keybd_event(VkKeyScan(a), 1, KEYEVENTF_KEYUP, 0);
		break;
	case 1: 
		keybd_event(VK_SPACE, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0);
		Sleep(5);
		keybd_event(VK_SPACE, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		break;
	case 2:
		keybd_event(VK_RETURN, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0);
		Sleep(5);
		keybd_event(VK_RETURN, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		break;
	case 3:
		keybd_event(VK_CAPITAL, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0);
		Sleep(5);
		keybd_event(VK_CAPITAL, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		break;
	case 4:
		keybd_event(VK_BACK, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0);
		Sleep(5);
		keybd_event(VK_BACK, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		break;
	}

}

//Function from http://www.cplusplus.com/forum/general/48837/
void toClipboard(HWND hwnd, string& s) {
	OpenClipboard(hwnd);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	string alias[] = { "REM","STRING","DELAY","SHIFTDOWN","SHIFTUP","WINDOWSDOWN","WINDOWSUP","ENTER","CAPSLOCK","BACKSPACE","CTRLDOWN","CTRLUP","CLIPBOARD"};
	fstream file;
	file.open("payload.ini");
	if (!file.good()) { cerr << "1"; return 1; }

	string buff;
	int alias_size = sizeof(alias) / sizeof(alias[0]);
	while (getline(file, buff))
	{
		bool special=false;
		for (int i = 0; i < alias_size; i++)
		{
			if (buff.find(alias[i]) != string::npos)
			{
				switch (i)
				{
				case 0: special = true; continue;
				case 1: buff.erase(0, 6);
					for (int j = 0; i < buff.length(); i++)
					{
						if (buff[i] == ' ')press('x', 1);
						else press(buff[i]);
					} 
					special = true;
					break;
				case 2: {
						buff.erase(0, 5);
						int time = atoi(buff.c_str());
						Sleep(time);
						special = true;
						break;
						}
				case 3: keybd_event(VK_SHIFT, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0); special = true; break;
				case 4: keybd_event(VK_SHIFT, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0); special = true; break;
				case 5: keybd_event(VK_LWIN, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0); special = true; break;
				case 6: keybd_event(VK_LWIN, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0); special = true; break;
				case 7: press('x', 2); special = true; break;
				case 8: press('x', 3); special = true; break;
				case 9: {
					buff.erase(0, 9);
					int times;
					if (buff == " "||buff.empty()) times = 1;
					else times = atoi(buff.c_str());
					for(int i = 0; i < times; i++) press('x', 4);
					special = true; break;
				}
				case 10: keybd_event(VK_CONTROL, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0); special = true; break;
				case 11: keybd_event(VK_CONTROL, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0); special = true; break;
				case 12: 
					buff.erase(0, 10);
					toClipboard(NULL, buff);
					special = true;
					break;

				}
			}
		}
		if (!special)if(!buff.empty())press(buff[0]);
	}
	file.close();

}
/*Errors:
1 payload.ini probably dont exists
*/
