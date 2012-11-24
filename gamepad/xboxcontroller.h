#pragma comment(lib, "XInput.lib")

#ifndef LIAM_XBOX_CONTROLLER
#define LIAM_XBOX_CONTROLLER

#include <windows.h>
#include <Xinput.h>

class XBOXController
{
private:
    XINPUT_STATE _controllerState;
    int _controllerNum;
public:
    XBOXController(int playerNumber);
    XINPUT_STATE GetState();
    bool IsConnected();
    void Vibrate(int leftVal = 0, int rightVal = 0);
};

#endif