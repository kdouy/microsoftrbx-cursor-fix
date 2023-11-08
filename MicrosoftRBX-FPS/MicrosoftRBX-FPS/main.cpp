#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <thread>
#include <fstream>
#include <string>
#include <unordered_map>


enum class Button
{
    // Letters kinda break it for me idk why
   /* A, B, C, D, E, F, G, H, I, J, K,
    L, M, N, O, P, Q, R, S, T, U, V,
    W, X, Y, Z,*/

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


// Define a mapping from Button to int
const std::unordered_map<Button, int> buttonToValue = {
    /*{Button::A, 'A'}, {Button::B, 'B'}, {Button::C, 'C'}, {Button::D, 'D'},
    {Button::E, 'E'}, {Button::F, 'F'}, {Button::G, 'G'}, {Button::H, 'H'},
    {Button::I, 'I'}, {Button::J, 'J'}, {Button::K, 'K'}, {Button::L, 'L'},
    {Button::M, 'M'}, {Button::N, 'N'}, {Button::O, 'O'}, {Button::P, 'P'},
    {Button::Q, 'Q'}, {Button::R, 'R'}, {Button::S, 'S'}, {Button::T, 'T'},
    {Button::U, 'U'}, {Button::V, 'V'}, {Button::W, 'W'}, {Button::X, 'X'},
    {Button::Y, 'Y'}, {Button::Z, 'Z'},*/ {Button::LEFT_ARROW, VK_LEFT},
    {Button::RIGHT_ARROW, VK_RIGHT}, {Button::DOWN_ARROW, VK_DOWN},
    {Button::UP_ARROW, VK_UP}, {Button::F1, VK_F1}, {Button::F2, VK_F2},
    {Button::F3, VK_F3}, {Button::F4, VK_F4}, {Button::F5, VK_F5},
    {Button::F6, VK_F6}, {Button::F7, VK_F7}, {Button::F8, VK_F8},
    {Button::F9, VK_F9}, {Button::F10, VK_F10}, {Button::F11, VK_F11},
    {Button::F12, VK_F12}, {Button::DEL, VK_DELETE}, {Button::HOME, VK_HOME},
    {Button::END, VK_END}, {Button::PGUP, VK_PRIOR}, {Button::PGDOWN, VK_NEXT},
    {Button::INSERT, VK_INSERT}, {Button::LEFT_CTRL, VK_LCONTROL},
    {Button::RIGHT_CTRL, VK_RCONTROL}, {Button::LEFT_ALT, VK_LMENU},
    {Button::RIGHT_ALT, VK_RMENU}, {Button::MINUS, VK_OEM_MINUS},
    {Button::PLUS, VK_OEM_PLUS}, {Button::UNDERSCORE, VK_OEM_MINUS},
    {Button::EQUALS, VK_OEM_PLUS}, {Button::FORWARD_SLASH, VK_OEM_2},
    {Button::BACK_SLASH, VK_OEM_5}, {Button::PIPE, VK_OEM_5},
    {Button::EXCLAMATION_MARK, '!'}, {Button::ASPERAND, '@'},
    {Button::RIGHT_ANGLE_BRACKET, '>'}, {Button::LEFT_ANGLE_BRACKET, '<'},
    {Button::UP_ANGLE_BRACKET, '^'}, {Button::SEMICOLON, VK_OEM_1},
    {Button::COLON, VK_OEM_1}, {Button::SINGLE_QUOTE, VK_OEM_7},
    {Button::DOUBLE_QUOTE, VK_OEM_7}, {Button::PERIOD, VK_OEM_PERIOD},
    {Button::COMMA, VK_OEM_COMMA}, {Button::QUESTION_MARK, '?'},
    {Button::RIGHT_BRACKET, VK_OEM_6}, {Button::LEFT_BRACKET, VK_OEM_4},
    {Button::RIGHT_CURLY, VK_OEM_6}, {Button::LEFT_CURLY, VK_OEM_4},
    {Button::HASHTAG, '#'}, {Button::DOLLAR_SIGN, '$'},
    {Button::PERCENT_SIGN, '%'}, {Button::AMPERSAND, '&'},
    {Button::ASTERISK, '*'}
};

// Define a mapping from string to Button
const std::unordered_map<std::string, Button> stringToButton = {
    /*{"A", Button::A}, {"B", Button::B}, {"C", Button::C}, {"D", Button::D},
    {"E", Button::E}, {"F", Button::F}, {"G", Button::G}, {"H", Button::H},
    {"I", Button::I}, {"J", Button::J}, {"K", Button::K}, {"L", Button::L},
    {"M", Button::M}, {"N", Button::N}, {"O", Button::O}, {"P", Button::P},
    {"Q", Button::Q}, {"R", Button::R}, {"S", Button::S}, {"T", Button::T},
    {"U", Button::U}, {"V", Button::V}, {"W", Button::W}, {"X", Button::X},
    {"Y", Button::Y}, {"Z", Button::Z},*/ {"LEFT_ARROW", Button::LEFT_ARROW},
    {"RIGHT_ARROW", Button::RIGHT_ARROW}, {"DOWN_ARROW", Button::DOWN_ARROW},
    {"UP_ARROW", Button::UP_ARROW}, {"F1", Button::F1}, {"F2", Button::F2},
    {"F3", Button::F3}, {"F4", Button::F4}, {"F5", Button::F5},
    {"F6", Button::F6}, {"F7", Button::F7}, {"F8", Button::F8},
    {"F9", Button::F9}, {"F10", Button::F10}, {"F11", Button::F11},
    {"F12", Button::F12}, {"DEL", Button::DEL}, {"HOME", Button::HOME},
    {"END", Button::END}, {"PGUP", Button::PGUP}, {"PGDOWN", Button::PGDOWN},
    {"INSERT", Button::INSERT}, {"LEFT_CTRL", Button::LEFT_CTRL},
    {"RIGHT_CTRL", Button::RIGHT_CTRL}, {"LEFT_ALT", Button::LEFT_ALT},
    {"RIGHT_ALT", Button::RIGHT_ALT}, {"MINUS", Button::MINUS},
    {"PLUS", Button::PLUS}, {"UNDERSCORE", Button::UNDERSCORE},
    {"EQUALS", Button::EQUALS}, {"FORWARD_SLASH", Button::FORWARD_SLASH},
    {"BACK_SLASH", Button::BACK_SLASH}, {"PIPE", Button::PIPE},
    {"EXCLAMATION_MARK", Button::EXCLAMATION_MARK},
    {"ASPERAND", Button::ASPERAND},
    {"RIGHT_ANGLE_BRACKET", Button::RIGHT_ANGLE_BRACKET},
    {"LEFT_ANGLE_BRACKET", Button::LEFT_ANGLE_BRACKET},
    {"UP_ANGLE_BRACKET", Button::UP_ANGLE_BRACKET},
    {"SEMICOLON", Button::SEMICOLON}, {"COLON", Button::COLON},
    {"SINGLE_QUOTE", Button::SINGLE_QUOTE},
    {"DOUBLE_QUOTE", Button::DOUBLE_QUOTE}, {"PERIOD", Button::PERIOD},
    {"COMMA", Button::COMMA}, {"QUESTION_MARK", Button::QUESTION_MARK},
    {"RIGHT_BRACKET", Button::RIGHT_BRACKET},
    {"LEFT_BRACKET", Button::LEFT_BRACKET},
    {"RIGHT_CURLY", Button::RIGHT_CURLY},
    {"LEFT_CURLY", Button::LEFT_CURLY},
    {"HASHTAG", Button::HASHTAG}, {"DOLLAR_SIGN", Button::DOLLAR_SIGN},
    {"PERCENT_SIGN", Button::PERCENT_SIGN}, {"AMPERSAND", Button::AMPERSAND},
    {"ASTERISK", Button::ASTERISK}
};

// Define a mapping from int to Button
const std::unordered_map<int, Button> intToButton = {
    /*{'A', Button::A}, {'B', Button::B}, {'C', Button::C}, {'D', Button::D},
    {'E', Button::E}, {'F', Button::F}, {'G', Button::G}, {'H', Button::H},
    {'I', Button::I}, {'J', Button::J}, {'K', Button::K}, {'L', Button::L},
    {'M', Button::M}, {'N', Button::N}, {'O', Button::O}, {'P', Button::P},
    {'Q', Button::Q}, {'R', Button::R}, {'S', Button::S}, {'T', Button::T},
    {'U', Button::U}, {'V', Button::V}, {'W', Button::W}, {'X', Button::X},
    {'Y', Button::Y}, {'Z', Button::Z},*/ {VK_LEFT, Button::LEFT_ARROW},
    {VK_RIGHT, Button::RIGHT_ARROW}, {VK_DOWN, Button::DOWN_ARROW},
    {VK_UP, Button::UP_ARROW}, {VK_F1, Button::F1}, {VK_F2, Button::F2},
    {VK_F3, Button::F3}, {VK_F4, Button::F4}, {VK_F5, Button::F5},
    {VK_F6, Button::F6}, {VK_F7, Button::F7}, {VK_F8, Button::F8},
    {VK_F9, Button::F9}, {VK_F10, Button::F10}, {VK_F11, Button::F11},
    {VK_F12, Button::F12}, {VK_DELETE, Button::DEL}, {VK_HOME, Button::HOME},
    {VK_END, Button::END}, {VK_PRIOR, Button::PGUP}, {VK_NEXT, Button::PGDOWN},
    {VK_INSERT, Button::INSERT}, {VK_LCONTROL, Button::LEFT_CTRL},
    {VK_RCONTROL, Button::RIGHT_CTRL}, {VK_LMENU, Button::LEFT_ALT},
    {VK_RMENU, Button::RIGHT_ALT}, {VK_OEM_MINUS, Button::MINUS},
    {VK_OEM_PLUS, Button::PLUS}, {VK_OEM_MINUS, Button::UNDERSCORE},
    {VK_OEM_PLUS, Button::EQUALS}, {VK_OEM_2, Button::FORWARD_SLASH},
    {VK_OEM_5, Button::BACK_SLASH}, {VK_OEM_5, Button::PIPE},
    {'!', Button::EXCLAMATION_MARK}, {'@', Button::ASPERAND},
    {'>', Button::RIGHT_ANGLE_BRACKET}, {'<', Button::LEFT_ANGLE_BRACKET},
    {'^', Button::UP_ANGLE_BRACKET}, {VK_OEM_1, Button::SEMICOLON},
    {VK_OEM_1, Button::COLON}, {VK_OEM_7, Button::SINGLE_QUOTE},
    {VK_OEM_7, Button::DOUBLE_QUOTE}, {VK_OEM_PERIOD, Button::PERIOD},
    {VK_OEM_COMMA, Button::COMMA}, {'?', Button::QUESTION_MARK},
    {VK_OEM_6, Button::RIGHT_BRACKET}, {VK_OEM_4, Button::LEFT_BRACKET},
    {VK_OEM_6, Button::RIGHT_CURLY}, {VK_OEM_4, Button::LEFT_CURLY},
    {'#', Button::HASHTAG}, {'$', Button::DOLLAR_SIGN},
    {'%', Button::PERCENT_SIGN}, {'&', Button::AMPERSAND},
    {'*', Button::ASTERISK}
};

// Define a mapping from Button to string
const std::unordered_map<Button, std::string> buttonToString = {
    /*{Button::A, "A"}, {Button::B, "B"}, {Button::C, "C"}, {Button::D, "D"},
    {Button::E, "E"}, {Button::F, "F"}, {Button::G, "G"}, {Button::H, "H"},
    {Button::I, "I"}, {Button::J, "J"}, {Button::K, "K"}, {Button::L, "L"},
    {Button::M, "M"}, {Button::N, "N"}, {Button::O, "O"}, {Button::P, "P"},
    {Button::Q, "Q"}, {Button::R, "R"}, {Button::S, "S"}, {Button::T, "T"},
    {Button::U, "U"}, {Button::V, "V"}, {Button::W, "W"}, {Button::X, "X"},
    {Button::Y, "Y"}, {Button::Z, "Z"},*/ {Button::LEFT_ARROW, "LEFT_ARROW"},
    {Button::RIGHT_ARROW, "RIGHT_ARROW"}, {Button::DOWN_ARROW, "DOWN_ARROW"},
    {Button::UP_ARROW, "UP_ARROW"}, {Button::F1, "F1"}, {Button::F2, "F2"},
    {Button::F3, "F3"}, {Button::F4, "F4"}, {Button::F5, "F5"},
    {Button::F6, "F6"}, {Button::F7, "F7"}, {Button::F8, "F8"},
    {Button::F9, "F9"}, {Button::F10, "F10"}, {Button::F11, "F11"},
    {Button::F12, "F12"}, {Button::DEL, "DEL"}, {Button::HOME, "HOME"},
    {Button::END, "END"}, {Button::PGUP, "PGUP"}, {Button::PGDOWN, "PGDOWN"},
    {Button::INSERT, "INSERT"}, {Button::LEFT_CTRL, "LEFT_CTRL"},
    {Button::RIGHT_CTRL, "RIGHT_CTRL"}, {Button::LEFT_ALT, "LEFT_ALT"},
    {Button::RIGHT_ALT, "RIGHT_ALT"}, {Button::MINUS, "MINUS"},
    {Button::PLUS, "PLUS"}, {Button::UNDERSCORE, "UNDERSCORE"},
    {Button::EQUALS, "EQUALS"}, {Button::FORWARD_SLASH, "FORWARD_SLASH"},
    {Button::BACK_SLASH, "BACK_SLASH"}, {Button::PIPE, "PIPE"},
    {Button::EXCLAMATION_MARK, "EXCLAMATION_MARK"}, {Button::ASPERAND, "ASPERAND"},
    {Button::RIGHT_ANGLE_BRACKET, "RIGHT_ANGLE_BRACKET"}, {Button::LEFT_ANGLE_BRACKET, "LEFT_ANGLE_BRACKET"},
    {Button::UP_ANGLE_BRACKET, "UP_ANGLE_BRACKET"}, {Button::SEMICOLON, "SEMICOLON"},
    {Button::COLON, "COLON"}, {Button::SINGLE_QUOTE, "SINGLE_QUOTE"},
    {Button::DOUBLE_QUOTE, "DOUBLE_QUOTE"}, {Button::PERIOD, "PERIOD"},
    {Button::COMMA, "COMMA"}, {Button::QUESTION_MARK, "QUESTION_MARK"},
    {Button::RIGHT_BRACKET, "RIGHT_BRACKET"}, {Button::LEFT_BRACKET, "LEFT_BRACKET"},
    {Button::RIGHT_CURLY, "RIGHT_CURLY"}, {Button::LEFT_CURLY, "LEFT_CURLY"},
    {Button::HASHTAG, "HASHTAG"}, {Button::DOLLAR_SIGN, "DOLLAR_SIGN"},
    {Button::PERCENT_SIGN, "PERCENT_SIGN"}, {Button::AMPERSAND, "AMPERSAND"},
    {Button::ASTERISK, "ASTERISK"}
};

// Convert ButtonEnum to the VK value
int buttonenum_to_button(Button button)
{
    auto it = buttonToValue.find(button);
    return (it != buttonToValue.end()) ? it->second : VK_INSERT;
}

// Convert string to Button
Button string_to_button(const std::string& str)
{
    auto it = stringToButton.find(str);
    return (it != stringToButton.end()) ? it->second : Button::INSERT;
}

// Converts VK to Button
Button int_to_button(int value)
{
    for (const auto& entry : buttonToValue)
    {
        if (entry.second == value)
        {
            return entry.first;
        }
    }
    return Button::INSERT;
}

// Convert Button to string
std::string button_to_string(Button button)
{
    auto it = buttonToString.find(button);
    return (it != buttonToString.end()) ? it->second : "INSERT";
}

// Default button
int toggle_button = buttonenum_to_button(Button::INSERT);
std::string toggle_button_str = "INSERT";

int reinit_button = buttonenum_to_button(Button::PGUP);
std::string reinit_button_str = "PGUP";

// Defaults
HWND robloxHWND;
bool isEnabled = false;
int mode = 1;
bool isRightClickPressed = false;
POINT rememberedCursorPos = { 0, 0 };


std::string convert(wchar_t* lab)
{
    std::wstring ws(lab);
    std::string str(ws.begin(), ws.end());
    return str;
}

// Checks if Roblox is focused
bool isRbxActive()
{
    return (GetForegroundWindow() == robloxHWND);
}

// Read the function name
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

// Does the cursor fix by whatever mode is chosen
void fixCursor(HWND handle)
{
    if (mode == 1)
    {
        RECT rect = { NULL };
        if (GetWindowRect(robloxHWND, &rect))
        {
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
                if (GetWindowRect(robloxHWND, &rect))
                {
                    int sizeX = (rect.right - rect.left);
                    int sizeY = (rect.bottom - rect.top);

                    int centerX = (rect.right - rect.left) / 2;
                    int centerY = (rect.bottom - rect.top) / 2;

                    POINT realP;
                    if (GetCursorPos(&realP))
                    {
                        // Don't judge this :(
                        if (p.x < 1)
                        {
                            SetCursorPos(rect.left + 10, realP.y);
                        }
                        else if (p.x > sizeX - 18)
                        {
                            SetCursorPos(rect.right - 10, realP.y);
                        }
                        else if (p.y < 35)
                        {
                            SetCursorPos(realP.x, rect.top + 30);
                        }
                        else if (p.y > sizeY - 10)
                        {
                            SetCursorPos(realP.x, rect.bottom - 10);
                        }
                    }
                }
            }
        }
    }
    else if (mode == 3)
    {
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
                if (GetWindowRect(robloxHWND, &rect))
                {
                    int sizeX = (rect.right - rect.left);
                    int sizeY = (rect.bottom - rect.top);

                    POINT realP;
                    if (GetCursorPos(&realP))
                    {
                        if (isRightClickPressed && (realP.x != rememberedCursorPos.x || realP.y != rememberedCursorPos.y))
                        {
                            int adjustedX = realP.x;
                            int adjustedY = realP.y;

                            if (adjustedX < rect.left)
                                adjustedX = rect.left;
                            else if (adjustedX > rect.right)
                                adjustedX = rect.right;
                            if (adjustedY < rect.top)
                                adjustedY = rect.top;
                            else if (adjustedY > rect.bottom)
                                adjustedY = rect.bottom;

                            SetCursorPos(adjustedX, adjustedY);
                        }
                        else if (!isRightClickPressed)
                        {
                            if (p.x < 1)
                            {
                                SetCursorPos(rect.left + 10, realP.y);
                            }
                            else if (p.x > sizeX - 18)
                            {
                                SetCursorPos(rect.right - 10, realP.y);
                            }
                            else if (p.y < 35)
                            {
                                SetCursorPos(realP.x, rect.top + 30);
                            }
                            else if (p.y > sizeY - 10)
                            {
                                SetCursorPos(realP.x, rect.bottom - 10);
                            }
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
                Sleep(10);
                std::cout << "Initialized!" << std::endl;
                std::cout << ("Roblox-HWND: ") << robloxHWND << std::endl;
                std::cout << ("Keybind: ") << toggle_button_str << std::endl;
                std::cout << ("Enabled: ") << (isEnabled ? "Enabled" : "Disabled") << std::endl;
                std::cout << ("Reinit Keybind: ") << reinit_button_str << std::endl;
                std::cout << "Focus this window and press a button to change keybinds (some buttons may not work and it may not change keybind the first time you press just press the new bind multiple times)" << std::endl;
                break;
            }
        }

        Sleep(500);
    }
}

void toggle();

void toggle_button_listener()
{
    while (true)
    {
        for (const auto& entry : buttonToValue)
        {
            if (GetAsyncKeyState(entry.second) & 0x8000) // Check if key is pressed
            {
                HWND currentHWND = GetForegroundWindow();
                if (currentHWND)
                {
                    std::string getTitle = getWindowTitle(currentHWND);
                    if (getTitle == "MicrosoftRBX-CursorFix")
                    {
                        toggle_button = entry.second;
                        toggle_button_str = button_to_string(int_to_button(entry.second)); // Update the toggle button string
                        Sleep(75);
                        if (isEnabled)
                        {
                            toggle();
                        }
                        Sleep(350); // Debounce to avoid rapid changes
                    }
                }
            }
        }
        Sleep(100);
    }
    //HWND currentHWND = GetForegroundWindow();
    //if (currentHWND)
    //{
    //    std::string getTitle = getWindowTitle(currentHWND);
    //    if (getTitle == "MicrosoftRBX-CursorFix")
    //    {
    //        for (const auto& entry : buttonToValue)
    //        {
    //            if (GetAsyncKeyState(entry.second) & 0x8000) // Check if key is pressed
    //            {
    //                toggle_button = entry.second;
    //                toggle_button_str = button_to_string(int_to_button(entry.second)); // Update the toggle button string
    //                Sleep(75);
    //                if (isEnabled)
    //                {
    //                    toggle();
    //                }
    //                Sleep(350); // Debounce to avoid rapid changes
    //            }
    //        }
    //    }
    //}
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
            Sleep(50);
            std::cout << ("Roblox-HWND: ") << robloxHWND << std::endl;
            std::cout << ("Keybind: ") << toggle_button_str << std::endl;
            std::cout << ("Enabled: ") << (isEnabled ? "Enabled" : "Disabled") << std::endl;
            std::cout << ("Reinit Keybind: ") << reinit_button_str << std::endl;
            std::cout << "Focus this window and press a button to change keybinds (some buttons may not work and it may not change keybind the first time you press just press the new bind multiple times)" << std::endl;
            Sleep(500);
        }
        Sleep(100);
    }
}

void reinit()
{
    while (true)
    {
        if (GetAsyncKeyState(reinit_button))
        {
            init();
        }
        Sleep(50);
    }
    Sleep(100);
}

int main()
{
    SetConsoleTitleA("MicrosoftRBX-CursorFix");

    std::cout << "1. Force Center Lock\n2. Lock Border\n3. Remember Last Cursor Position Upon Dragging w/ Lock Border\n   (Recommended for fixing the annoying cursor teleportation bug when right-clicking and dragging the mouse cursor)\n\n";
    std::cout << "Input: ";
    std::cin >> mode;

    if (mode == 1 || mode == 2 || mode == 3)
    {
        std::thread mainThread(init);
        std::thread checkThread(check);
        std::thread toggleThread(toggle);
        std::thread toggleButtonThread(toggle_button_listener);
        std::thread reinitThread(reinit);

        mainThread.join();
        checkThread.join();
        toggleThread.join();
        toggleButtonThread.join();
        reinitThread.join();
        std::cin.get();
    }

    std::cout << "Invalid option, please restart software." << std::endl;
    return 0;
}