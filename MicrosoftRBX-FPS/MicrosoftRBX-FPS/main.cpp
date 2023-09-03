#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <thread>
#include <fstream>
#include <string>


enum Button
{
    A, B, C, D, E, F, G, H, I, J, K,
    L, M, N, O, P, Q, R, S, T, U, V,
    W, X, Y, Z,

    LEFT_ARROW, RIGHT_ARROW, DOWN_ARROW, UP_ARROW,

    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

    DEL, HOME, END, PGUP, PGDOWN, INSERT,

    LEFT_CTRL, RIGHT_CTRL, LEFT_ALT, RIGHT_ALT,

    MINUS, PLUS, UNDERSCORE, EQUALS,

    FORWARD_SLASH, BACK_SLASH, PIPE,

    EXCLAMATION_MARK, ASPERAND, RIGHT_ANGLE_BRACKET, LEFT_ANGLE_BRACKET,
    UP_ANGLE_BRACKET,

    SEMICOLON, COLON, SINGLE_QUOTE, DOUBLE_QUOTE, PERIOD, COMMA,
    QUESTION_MARK,

    RIGHT_BRACKET, LEFT_BRACKET, RIGHT_CURLY, LEFT_CURLY,

    HASHTAG, DOLLAR_SIGN, PERCENT_SIGN, AMPERSAND, ASTERISK
};

int buttonenum_to_button(Button button);

int toggle_button = buttonenum_to_button(Button::INSERT);
std::string toggle_button_str = "INSERT";

HWND robloxHWND;
bool isEnabled = false;

int mode = 1;

bool isRightClickPressed = false;
POINT rememberedCursorPos = { 0, 0 };

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

BOOL IsFullscreen(HWND hwnd)
{
    RECT windowRect;
    RECT screenRect;

    if (GetWindowRect(hwnd, &windowRect))
    {
        screenRect.left = 0;
        screenRect.top = 0;
        screenRect.right = GetSystemMetrics(SM_CXSCREEN);
        screenRect.bottom = GetSystemMetrics(SM_CYSCREEN);

        if (EqualRect(&windowRect, &screenRect))
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
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
        RECT confineRect;
        RECT windowRect;

        if (GetWindowRect(robloxHWND, &windowRect))
        {
            confineRect = windowRect;

            confineRect.left += 10;
            confineRect.top += 42;
            confineRect.right -= 10;
            confineRect.bottom -= 10;

            BOOL isFullscreen = IsFullscreen(robloxHWND);

            if (isFullscreen)
            {
                confineRect.left = 1;
                confineRect.top = 4;
                confineRect.right = GetSystemMetrics(SM_CXSCREEN) - 1;
                confineRect.bottom = GetSystemMetrics(SM_CYSCREEN) - 1;
            }

            ClipCursor(&confineRect);
        }
    }
    else if (mode == 3)
    {
        RECT confineRect;
        RECT windowRect;

        if (GetWindowRect(robloxHWND, &windowRect))
        {
            confineRect = windowRect;

            confineRect.left += 10;
            confineRect.top += 42;
            confineRect.right -= 10;
            confineRect.bottom -= 10;

            BOOL isFullscreen = IsFullscreen(robloxHWND);

            if (isFullscreen)
            {
                confineRect.left = 1;
                confineRect.top = 4;
                confineRect.right = GetSystemMetrics(SM_CXSCREEN) - 1;
                confineRect.bottom = GetSystemMetrics(SM_CYSCREEN) - 1;
            }

            if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
            {
                if (!isRightClickPressed)
                {
                    isRightClickPressed = true;
                    GetCursorPos(&rememberedCursorPos);
                }
            }
            else
            {
                if (isRightClickPressed)
                {
                    SetCursorPos(rememberedCursorPos.x, rememberedCursorPos.y);
                    isRightClickPressed = false;
                }
            }

            POINT p;
            if (GetCursorPos(&p))
            {
                if (ScreenToClient(handle, &p))
                {
                    RECT rect = { NULL };
                    if (GetWindowRect(robloxHWND, &rect)) {
                        int sizeX = (rect.right - rect.left);
                        int sizeY = (rect.bottom - rect.top);
                    }
                }
            }

            ClipCursor(&confineRect);
        }
    }
}

// This code is shit but i cbf so it's someone elses problem
int buttonenum_to_button(Button button)
{
    switch (button)
    {
        case A:
            return 'A';
        case B:
            return 'B';
        case C:
            return 'C';
        case D:
            return 'D';
        case E:
            return 'E';
        case F:
            return 'F';
        case G:
            return 'G';
        case H:
            return 'H';
        case I:
            return 'I';
        case J:
            return 'J';
        case K:
            return 'K';
        case L:
            return 'L';
        case M:
            return 'M';
        case N:
            return 'N';
        case O:
            return 'O';
        case P:
            return 'P';
        case Q:
            return 'Q';
        case R:
            return 'R';
        case S:
            return 'S';
        case T:
            return 'T';
        case U:
            return 'U';
        case V:
            return 'V';
        case W:
            return 'W';
        case X:
            return 'X';
        case Y:
            return 'Y';
        case Z:
            return 'Z';
        case LEFT_ARROW:
            return VK_LEFT;
        case RIGHT_ARROW:
            return VK_RIGHT;
        case DOWN_ARROW:
            return VK_DOWN;
        case UP_ARROW:
            return VK_UP;
        case F1:
            return VK_F1;
        case F2:
            return VK_F2;
        case F3:
            return VK_F3;
        case F4:
            return VK_F4;
        case F5:
            return VK_F5;
        case F6:
            return VK_F6;
        case F7:
            return VK_F7;
        case F8:
            return VK_F8;
        case F9:
            return VK_F9;
        case F10:
            return VK_F10;
        case F11:
            return VK_F11;
        case F12:
            return VK_F12;
        case DEL:
            return VK_DELETE;
        case HOME:
            return VK_HOME;
        case END:
            return VK_END;
        case PGUP:
            return VK_PRIOR;
        case PGDOWN:
            return VK_NEXT;
        case INSERT:
            return VK_INSERT;
        case LEFT_CTRL:
            return VK_LCONTROL;
        case RIGHT_CTRL:
            return VK_RCONTROL;
        case LEFT_ALT:
            return VK_LMENU;
        case RIGHT_ALT:
            return VK_RMENU;
        case MINUS:
            return VK_OEM_MINUS;
        case PLUS:
            return VK_OEM_PLUS;
        case UNDERSCORE:
            return VK_OEM_MINUS;
        case EQUALS:
            return VK_OEM_PLUS;
        case FORWARD_SLASH:
            return VK_OEM_2;
        case BACK_SLASH:
            return VK_OEM_5;
        case PIPE:
            return VK_OEM_5;
        case EXCLAMATION_MARK:
            return '!';
        case ASPERAND:
            return '@';
        case RIGHT_ANGLE_BRACKET:
            return '>';
        case LEFT_ANGLE_BRACKET:
            return '<';
        case UP_ANGLE_BRACKET:
            return '^';
        case SEMICOLON:
            return VK_OEM_1;
        case COLON:
            return VK_OEM_1;
        case SINGLE_QUOTE:
            return VK_OEM_7;
        case DOUBLE_QUOTE:
            return VK_OEM_7;
        case PERIOD:
            return VK_OEM_PERIOD;
        case COMMA:
            return VK_OEM_COMMA;
        case QUESTION_MARK:
            return '?';
        case RIGHT_BRACKET:
            return VK_OEM_6;
        case LEFT_BRACKET:
            return VK_OEM_4;
        case RIGHT_CURLY:
            return VK_OEM_6;
        case LEFT_CURLY:
            return VK_OEM_4;
        case HASHTAG:
            return '#';
        case DOLLAR_SIGN:
            return '$';
        case PERCENT_SIGN:
            return '%';
        case AMPERSAND:
            return '&';
        case ASTERISK:
            return '*';
        default:
            return VK_INSERT;
    }
}

Button string_to_button(const std::string& str)
{
    if (str == "A")
        return Button::A;
    else if (str == "B")
        return Button::B;
    else if (str == "C")
        return Button::C;
    else if (str == "D")
        return Button::D;
    else if (str == "E")
        return Button::E;
    else if (str == "F")
        return Button::F;
    else if (str == "G")
        return Button::G;
    else if (str == "H")
        return Button::H;
    else if (str == "I")
        return Button::I;
    else if (str == "J")
        return Button::J;
    else if (str == "K")
        return Button::K;
    else if (str == "L")
        return Button::L;
    else if (str == "M")
        return Button::M;
    else if (str == "N")
        return Button::N;
    else if (str == "O")
        return Button::O;
    else if (str == "P")
        return Button::P;
    else if (str == "Q")
        return Button::Q;
    else if (str == "R")
        return Button::R;
    else if (str == "S")
        return Button::S;
    else if (str == "T")
        return Button::T;
    else if (str == "U")
        return Button::U;
    else if (str == "V")
        return Button::V;
    else if (str == "W")
        return Button::W;
    else if (str == "X")
        return Button::X;
    else if (str == "Y")
        return Button::Y;
    else if (str == "Z")
        return Button::Z;
    else if (str == "LEFT_ARROW")
        return Button::LEFT_ARROW;
    else if (str == "RIGHT_ARROW")
        return Button::RIGHT_ARROW;
    else if (str == "DOWN_ARROW")
        return Button::DOWN_ARROW;
    else if (str == "UP_ARROW")
        return Button::UP_ARROW;
    else if (str == "F1")
        return Button::F1;
    else if (str == "F2")
        return Button::F2;
    else if (str == "F3")
        return Button::F3;
    else if (str == "F4")
        return Button::F4;
    else if (str == "F5")
        return Button::F5;
    else if (str == "F6")
        return Button::F6;
    else if (str == "F7")
        return Button::F7;
    else if (str == "F8")
        return Button::F8;
    else if (str == "F9")
        return Button::F9;
    else if (str == "F10")
        return Button::F10;
    else if (str == "F11")
        return Button::F11;
    else if (str == "F12")
        return Button::F12;
    else if (str == "DEL")
        return Button::DEL;
    else if (str == "HOME")
        return Button::HOME;
    else if (str == "END")
        return Button::END;
    else if (str == "PGUP")
        return Button::PGUP;
    else if (str == "PGDOWN")
        return Button::PGDOWN;
    else if (str == "INSERT")
        return Button::INSERT;
    else if (str == "LEFT_CTRL")
        return Button::LEFT_CTRL;
    else if (str == "RIGHT_CTRL")
        return Button::RIGHT_CTRL;
    else if (str == "LEFT_ALT")
        return Button::LEFT_ALT;
    else if (str == "RIGHT_ALT")
        return Button::RIGHT_ALT;
    else if (str == "MINUS")
        return Button::MINUS;
    else if (str == "PLUS")
        return Button::PLUS;
    else if (str == "UNDERSCORE")
        return Button::UNDERSCORE;
    else if (str == "EQUALS")
        return Button::EQUALS;
    else if (str == "FORWARD_SLASH")
        return Button::FORWARD_SLASH;
    else if (str == "BACK_SLASH")
        return Button::BACK_SLASH;
    else if (str == "PIPE")
        return Button::PIPE;
    else if (str == "EXCLAMATION_MARK")
        return Button::EXCLAMATION_MARK;
    else if (str == "ASPERAND")
        return Button::ASPERAND;
    else if (str == "RIGHT_ANGLE_BRACKET")
        return Button::RIGHT_ANGLE_BRACKET;
    else if (str == "LEFT_ANGLE_BRACKET")
        return Button::LEFT_ANGLE_BRACKET;
    else if (str == "UP_ANGLE_BRACKET")
        return Button::UP_ANGLE_BRACKET;
    else if (str == "SEMICOLON")
        return Button::SEMICOLON;
    else if (str == "COLON")
        return Button::COLON;
    else if (str == "SINGLE_QUOTE")
        return Button::SINGLE_QUOTE;
    else if (str == "DOUBLE_QUOTE")
        return Button::DOUBLE_QUOTE;
    else if (str == "PERIOD")
        return Button::PERIOD;
    else if (str == "COMMA")
        return Button::COMMA;
    else if (str == "QUESTION_MARK")
        return Button::QUESTION_MARK;
    else if (str == "RIGHT_BRACKET")
        return Button::RIGHT_BRACKET;
    else if (str == "LEFT_BRACKET")
        return Button::LEFT_BRACKET;
    else if (str == "RIGHT_CURLY")
        return Button::RIGHT_CURLY;
    else if (str == "LEFT_CURLY")
        return Button::LEFT_CURLY;
    else if (str == "HASHTAG")
        return Button::HASHTAG;
    else if (str == "DOLLAR_SIGN")
        return Button::DOLLAR_SIGN;
    else if (str == "PERCENT_SIGN")
        return Button::PERCENT_SIGN;
    else if (str == "AMPERSAND")
        return Button::AMPERSAND;
    else if (str == "ASTERISK")
        return Button::ASTERISK;

    // No match found
    return Button::ASTERISK;
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

    // Open file with the Toggle Config
    std::ifstream file("_ToggleButton.txt");

    // Check if opening file failed
    if (!file.is_open())
    {
        std::cout << "Failed to open the file. Defaulting to INSERT." << std::endl;
    }
    else
    {
        // Change Toggle Button to chosen button enum
        std::getline(file, toggle_button_str);
        toggle_button = buttonenum_to_button(string_to_button(toggle_button_str));
    }

    // Close file
    file.close();

    std::cout << ("Keybind: ") << toggle_button_str << std::endl;
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
        if (GetAsyncKeyState(toggle_button))
        {
            isEnabled = not isEnabled;
            system("cls");
            std::cout << ("Roblox-HWND: ") << robloxHWND << std::endl;
            std::cout << ("Keybind: ") << toggle_button_str << std::endl;
            std::cout << ("Enabled: ") << (isEnabled ? "Enabled" : "Disabled");
            Sleep(1000);
        }
        Sleep(25);
    }
}

int main()
{
    std::cout << "1. Force Center Lock\n2. Lock Border\n3. Remember Last Cursor Position Upon Dragging w/ Lock Border\n   (Recommended for fixing the annoying cursor teleportation bug when right-clicking and dragging the mouse cursor)\n\n";
    std::cout << "Input: ";
    std::cin >> mode;

    if (mode == 1 || mode == 2 || mode == 3)
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
