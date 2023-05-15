#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <thread>

HWND robloxHWND;
bool isEnabled = false;

std::string convert(wchar_t* lab) {
    std::wstring ws(lab);
    std::string str(ws.begin(), ws.end());
    return str;
}

bool isRbxActive()
{
    return (GetForegroundWindow() == robloxHWND);
}

std::string getWindowTitle(HWND handle)
{
    if (handle)
    {
        BOOL passObject;
        const int size = 32;

        wchar_t title[size];
        memset(title, 0, size);

        passObject = GetWindowTextW(handle, title, size);

        if (passObject)
        {
            return convert(title);
        }
    }
    return "NULL";
}

void init()
{
    // FindWindow is so fucked because it has none for this so i had to use this method <3
    while (true)
    {
        HWND currentHWND = GetForegroundWindow();
        if (currentHWND)
        {
            std::string getTitle = getWindowTitle(currentHWND);
            if (getTitle == "Roblox")
            {
                robloxHWND = currentHWND;
                system("cls");
                std::cout << "Initialized!\nRoblox-HWND: " << currentHWND;
                break;
            }
            else
            {
                system("cls");
                std::cout << "Please open Microsoft Roblox Client and click somewhere.";
            }
        }

        Sleep(1000);
    }

    Sleep(1000);
    system("cls");
    std::cout << "Keybind: INSERT" << std::endl;
    std::cout << "Enabled: " << (isEnabled ? "Enabled" : "Disabled");
}

void check()
{
    while (true)
    {
        if (isRbxActive() && isEnabled)
        {
            RECT rect = { NULL };
            if (GetWindowRect(robloxHWND, &rect)) {
                int sizeX = (rect.right - rect.left) / 2;
                int sizeY = (rect.bottom - rect.top) / 2;
                SetCursorPos(rect.left + sizeX, rect.top + sizeY);
            }
        }
        Sleep(1);
    }
}

void toggle()
{
    while (true)
    {
        if (GetAsyncKeyState(VK_INSERT))
        {
            isEnabled = not isEnabled;
            system("cls");
            std::cout << "Keybind: INSERT" << std::endl;
            std::cout << "Enabled: " << (isEnabled ? "Enabled" : "Disabled");
            Sleep(1000);
        }
        Sleep(25);
    }
}

int main()
{
    SetConsoleTitleA("MicrosoftRBX-CursorFix");
    std::thread mainThread(init);
    std::thread checkThread(check);
    std::thread toggleThread(toggle);
    mainThread.join();
    checkThread.join();
    toggleThread.join();
    std::cin.get();
}