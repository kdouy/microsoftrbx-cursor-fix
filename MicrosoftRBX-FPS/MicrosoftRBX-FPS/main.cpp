#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <thread>

HWND robloxHWND;
bool isEnabled = false;

int mode = 1;

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

void fixCursor(HWND handle)
{
    if (mode == 1)
    { 
        RECT rect = { NULL };
        if (GetWindowRect(robloxHWND, &rect)) {
            int sizeX = (rect.right - rect.left);
            int sizeY = (rect.bottom - rect.top);

            int centerX = (rect.right - rect.left) / 2;
            int centerY = (rect.bottom - rect.top) / 2;

            SetCursorPos(rect.left + centerX, rect.top + centerY);
        }
    }
    else if (mode == 2)
    {
        POINT p;
        if (GetCursorPos(&p))
        {
            if (ScreenToClient(handle, &p))
            {
                RECT rect = { NULL };
                if (GetWindowRect(robloxHWND, &rect)) {
                    int sizeX = (rect.right - rect.left);
                    int sizeY = (rect.bottom - rect.top);

                    int centerX = (rect.right - rect.left) / 2;
                    int centerY = (rect.bottom - rect.top) / 2;

                    POINT realP;
                    if (GetCursorPos(&realP))
                    {
                        // Don't judge this :(
                        if (p.x < 30)
                        {
                            SetCursorPos(rect.left + 100, realP.y);
                        }
                        else if (p.x > sizeX - 40)
                        {
                            SetCursorPos(rect.right - 100, realP.y);
                        }
                        else if (p.y < 70)
                        {
                            SetCursorPos(realP.x, rect.top + 100);
                        }
                        else if (p.y > sizeY - 40)
                        {
                            SetCursorPos(realP.x, rect.bottom - 100);
                        }
                    }
                }
            }
        }
    }
}

void init()
{
    // FindWindow is so fucked because it has none for this so i had to use this method <3
    std::cout << "Please open Microsoft Roblox Client and click somewhere.";
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
                std::cout << "Initialized!\nRoblox-Handle: " << currentHWND;
                break;
            }
        }

        Sleep(1000);
    }

    Sleep(1000);
    system("cls");
    std::cout << ("Roblox-HWND: ") << robloxHWND << std::endl;
    std::cout << ("Keybind: ") << "INSERT" << std::endl;
    std::cout << ("Enabled: ") << (isEnabled ? "Enabled" : "Disabled");
}

void check()
{
    while (true)
    {
        while (ShowCursor(false) >= 0);
        if (isRbxActive() && isEnabled)
        {
            fixCursor(robloxHWND);
        }
        Sleep(10);
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
            std::cout << ("Roblox-HWND: ") << robloxHWND << std::endl;
            std::cout << ("Keybind: ") << "INSERT" << std::endl;
            std::cout << ("Enabled: ") << (isEnabled ? "Enabled" : "Disabled");
            Sleep(1000);
        }
        Sleep(25);
    }
}

int main()
{
    std::cout << "1. Force Center Lock\n2. Lock Border\n\n";
    std::cout << "Input: ";
    std::cin >> mode;

    if (mode == 1 || mode == 2)
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

    std::cout << "Invalid option, please restart software." << std::endl;
    return 0;
}