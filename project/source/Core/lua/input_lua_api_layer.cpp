#include "lua/input_lua_api_layer.h"

#include "input.h"

using namespace Core;
using namespace Utils;
using namespace Lua;

void InputAPI::OnInit(){ 
    Global("Space_Key", 32);
    Global("0_Key", 48);
    Global("1_Key", 49);
    Global("2_Key", 50);
    Global("3_Key", 51);
    Global("4_Key", 52);
    Global("5_Key", 53);
    Global("6_Key", 54);
    Global("7_Key", 55);
    Global("8_Key", 56);
    Global("9_Key", 57);
    Global("A_Key", 65);
    Global("B_Key", 66);
    Global("C_Key", 67);
    Global("D_Key", 68);
    Global("E_Key", 69);
    Global("F_Key", 70);
    Global("G_Key", 71);
    Global("H_Key", 72);
    Global("I_Key", 73);
    Global("J_Key", 74);
    Global("K_Key", 75);
    Global("L_Key", 76);
    Global("M_Key", 77);
    Global("N_Key", 78);
    Global("O_Key", 79);
    Global("P_Key", 80);
    Global("Q_Key", 81);
    Global("R_Key", 82);
    Global("S_Key", 83);
    Global("T_Key", 84);
    Global("U_Key", 85);
    Global("V_Key", 86);
    Global("W_Key", 87);
    Global("X_Key", 88);
    Global("Y_Key", 89);
    Global("Z_Key", 90);
    Global("Shift_Key", 340);

    Function("IsKeyPressed", [this](unsigned int key){return IsKeyPressed(key);});
}

void InputAPI::OnUpdate(){
    Utils::Input* input = this->application->GetResource<Utils::Input>();
        
    double posX = 0;
    double posY = 0;

    double posDeltaX = 0;
    double posDeltaY = 0;

    input->GetMousePos(&posX, &posY);
    input->GetMousePosDelta(&posDeltaX, &posDeltaY);

    Global("CursorX", posX);
    Global("CursorY", posY);

    Global("CursorDeltaX", posDeltaX);
    Global("CursorDeltaY", posDeltaY);
}

bool InputAPI::IsKeyPressed(unsigned int key){ 
    Utils::Input* input = application->GetResource<Utils::Input>();
    return input->IsKeyDown(key);
}
