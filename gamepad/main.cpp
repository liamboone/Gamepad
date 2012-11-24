#include "xboxcontroller.h"
#include <iostream>

XBOXController* Player1;

void GenerateKey(int vk, BOOL bExtended) {

        KEYBDINPUT  kb = {0};
        INPUT      Input = {0};


        /* Generate a "key down" */
        if (bExtended) { kb.dwFlags  = KEYEVENTF_EXTENDEDKEY; }
        kb.wVk  = vk;
        Input.type  = INPUT_KEYBOARD;
        Input.ki  = kb;
        SendInput(1, &Input, sizeof(Input));


        /* Generate a "key up" */
        ZeroMemory(&kb, sizeof(KEYBDINPUT));
        ZeroMemory(&Input, sizeof(INPUT));

        kb.dwFlags  =  KEYEVENTF_KEYUP;
        if (bExtended) { kb.dwFlags |= KEYEVENTF_EXTENDEDKEY; }
        kb.wVk = vk;
        Input.type = INPUT_KEYBOARD;
        Input.ki = kb;
        SendInput(1, &Input, sizeof(Input));

        return;
}

void GenerateKeyDown(int vk, BOOL bExtended) {

        KEYBDINPUT  kb = {0};
        INPUT      Input = {0};

        if (bExtended) { kb.dwFlags  = KEYEVENTF_EXTENDEDKEY; }
        kb.wVk  = vk;
        Input.type  = INPUT_KEYBOARD;
        Input.ki  = kb;
        SendInput(1, &Input, sizeof(Input));

        return;
}

void GenerateKeyUp(int vk, BOOL bExtended) {

        KEYBDINPUT  kb = {0};
        INPUT      Input = {0};

        kb.dwFlags  =  KEYEVENTF_KEYUP;
        if (bExtended) { kb.dwFlags |= KEYEVENTF_EXTENDEDKEY; }
        kb.wVk = vk;
        Input.type = INPUT_KEYBOARD;
        Input.ki = kb;
        SendInput(1, &Input, sizeof(Input));

        return;
}

WORD lastgamepad = 0;

int main(int argc, char* argv[])
{
    Player1 = new XBOXController(1);

    std::cout << "Instructions:\n";
    std::cout << "[A] Vibrate Left Only\n";
    std::cout << "[B] Vibrate Right Only\n";
    std::cout << "[X] Vibrate Both\n";
    std::cout << "[Y] Vibrate Neither\n";
    std::cout << "[BACK] Exit\n";

    while(true)
    {
		WORD gamepad = Player1->GetState().Gamepad.wButtons;
        if(Player1->IsConnected())
        {
            if( gamepad & ~lastgamepad & XINPUT_GAMEPAD_A )
            {
                GenerateKeyDown(VK_SHIFT, true);
				std::cout << "A Down" << std::endl;
            }
            if( ~gamepad & lastgamepad & XINPUT_GAMEPAD_A )
            {
                GenerateKeyUp(VK_SHIFT, true);
				std::cout << "A Up" << std::endl;
            }
			if( gamepad & ~lastgamepad & XINPUT_GAMEPAD_B )
            {
                GenerateKeyDown(VK_SHIFT, true);
				std::cout << "B Down" << std::endl;
            }
            if( ~gamepad & lastgamepad & XINPUT_GAMEPAD_B )
            {
                GenerateKeyUp(VK_SHIFT, true);
				std::cout << "B Up" << std::endl;
            }
			if( gamepad & ~lastgamepad & XINPUT_GAMEPAD_RIGHT_SHOULDER )
            {
                //GenerateKeyDown(VK_SHIFT, true);
				std::cout << "R_SHOULDER Down" << std::endl;
            }
            if( ~gamepad & lastgamepad & XINPUT_GAMEPAD_RIGHT_SHOULDER )
            {
                GenerateKeyUp('E', true);
                GenerateKeyDown('E', true);
                GenerateKeyUp('E', true);
                GenerateKeyDown('E', true);
				std::cout << "R_SHOULDER Up" << std::endl;
            }
			if( gamepad & ~lastgamepad & XINPUT_GAMEPAD_LEFT_SHOULDER )
            {
                //GenerateKeyDown(VK_SHIFT, true);
				std::cout << "L_SHOULDER Down" << std::endl;
            }
            if( ~gamepad & lastgamepad & XINPUT_GAMEPAD_LEFT_SHOULDER )
            {
                GenerateKeyUp('Q', true);
                GenerateKeyDown('Q', true);
                GenerateKeyUp('Q', true);
                GenerateKeyDown('Q', true);
				std::cout << "L_SHOULDER Up" << std::endl;
            }

			Player1->Vibrate( 256*Player1->GetState().Gamepad.bLeftTrigger, 256*Player1->GetState().Gamepad.bRightTrigger );
        }
        else
        {
            std::cout << "\n\tERROR! PLAYER 1 - XBOX 360 Controller Not Found!\n";
            std::cout << "Press Any Key To Exit.";
            std::cin.get();
            break;
        }
		lastgamepad = gamepad;
		Sleep( 1 );
    }

    delete(Player1);

    return( 0 );
}