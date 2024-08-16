// Keybord Emulator for Arduino-based dance pad
// 28 JAN 2018
#include<windows.h>
#include<iostream>
#include<string>
#include<ctime>
#include<iomanip>

void send_keybd_event(INPUT*pInput,char code)
{
    if (!isalpha(code))
        return;

    bool release;
    if (isupper(code))
    {
        code = tolower(code);
        pInput->ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
        release = true;
    }
    else
    {
        pInput->ki.dwFlags = KEYEVENTF_SCANCODE; // KEYEVENTF_KEYDOWN
        release = false;
    }
    HKL kbl = GetKeyboardLayout(0);
    short int key = VkKeyScanEx(code,kbl);
    pInput->ki.wVk = 0;
    pInput->ki.wScan = MapVirtualKey(LOBYTE(key), MAPVK_VK_TO_VSC);
    SendInput(1,pInput,sizeof(INPUT));

    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::cout << " " << std::setw(2) << ltm->tm_hour << ":" << std::setw(2) << ltm->tm_min << ":" << std::setw(2) << ltm->tm_sec << " ";
    std::cout << "key '" << code << "'" << (release ? " released" : " pressed") << std::endl;
}

int main()
{
    DWORD dwEventMask;
    DWORD numBytesRead;
    HANDLE hComm;   // create serial port handle
    INPUT input;    // create keyboard input
    char TempChar;

    std::cout << std::setfill('0') << std::endl;
    std::cout << "#################################" << std::endl << std::endl;
    std::cout << "  Dance Pad Keyboard Emulator" << std::endl << std::endl;
    std::cout << "#################################" << std::endl << std::endl;
    std::cout << "please specify COM port number: ";
    std::string portNumber;
    std::getline(std::cin, portNumber);
    int portNum = stoi(portNumber);

    // setup the serial port handle
    char portName[256];
    sprintf_s(portName, "\\\\.\\COM%d", portNum);

    hComm = CreateFile(portName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hComm == INVALID_HANDLE_VALUE)
    {
        std::cout << std::endl << "Error in opening serial port " << portName << std::endl;
        std::cin.get();
        return 0;
    }
    else
    {
        std::cout << std::endl << "opening serial port " << portName << " successful" << std::endl;
    }

    DCB dcbSerialParams = { 0 }; // Initializing DCB structure
    GetCommState(hComm, &dcbSerialParams);      //retrieves  the current settings
    dcbSerialParams.BaudRate = CBR_9600;  // Setting BaudRate = 9600
    dcbSerialParams.ByteSize = 8;         // Setting ByteSize = 8
    dcbSerialParams.StopBits = ONESTOPBIT;// Setting StopBits = 1
    dcbSerialParams.Parity   = NOPARITY;  // Setting Parity = None
    SetCommState(hComm, &dcbSerialParams);

    // setup keyboard input
    input.type = INPUT_KEYBOARD;

    // set receive event mask
    SetCommMask(hComm, EV_RXCHAR);
    std::cout << std::endl << std::endl << " waiting for data reception" << std::endl;

    while (1)
    {
        WaitCommEvent(hComm, &dwEventMask, NULL); // wait for a character to be received
        while (1)
        {
            if (ReadFile(hComm, &TempChar, sizeof(TempChar), &numBytesRead, NULL))
            {
                send_keybd_event(&input,TempChar);
            } else {
                break;
            }
        }
    }

    CloseHandle(hComm); // close the serial port
    std::cout << "serial port disconnected";
    std::cin.get();
    return 0;
}