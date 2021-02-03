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
		keybd_event(VkKeyScan(VK_SPACE), 1, 0, 0);
		Sleep(5);
		keybd_event(VkKeyScan(VK_SPACE), 1, KEYEVENTF_KEYUP, 0);
		break;
	case 2:
		keybd_event(VkKeyScan(VK_RETURN), 1, 0, 0);
		Sleep(5);
		keybd_event(VkKeyScan(VK_RETURN), 1, KEYEVENTF_KEYUP, 0);
		break;
	case 3:
		keybd_event(VkKeyScan(VK_CAPITAL), 1, 0, 0);
		Sleep(5);
		keybd_event(VkKeyScan(VK_CAPITAL), 1, KEYEVENTF_KEYUP, 0);
		break;
	case 4:
		keybd_event(VkKeyScan(VK_BACK), 1, 0, 0);
		Sleep(5);
		keybd_event(VkKeyScan(VK_BACK), 1, KEYEVENTF_KEYUP, 0);
		break;
	}

}

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	string alias[] = { "REM","STRING","DELAY","SHIFTDOWN","SHIFTUP","WINDOWSDOWN","WINDOWSUP","ENTER","CAPSLOCK","BACKSPACE","CTRLDOWN","CTRLUP"};
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
				case 3: keybd_event(VkKeyScan(VK_SHIFT), 1, 0, 0); special = true; break;
				case 4: keybd_event(VkKeyScan(VK_SHIFT), 1, KEYEVENTF_KEYUP, 0); special = true; break;
				case 5: keybd_event(VkKeyScan(VK_LWIN), 1, 0, 0); special = true; break;
				case 6: keybd_event(VkKeyScan(VK_LWIN), 1, KEYEVENTF_KEYUP, 0); special = true; break;
				case 7: press('x', 2); special = true; break;
				case 8: press('x', 3); special = true; break;
				case 9: press('x', 4); special = true; break;
				case 10: keybd_event(VkKeyScan(VK_CONTROL), 1, 0, 0); special = true; break;
				case 11: keybd_event(VkKeyScan(VK_CONTROL), 1, KEYEVENTF_KEYUP, 0); special = true; break;
				}
			}
		}
		if (!special)press(buff[0]);
	}
	file.close();
}
/*Errors:
1 payload.ini probably dont exists
*/

