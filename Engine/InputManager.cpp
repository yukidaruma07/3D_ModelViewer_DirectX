#include "InputManager.h"
#include "../GameEngine.hpp"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace InputManager {
    inline LPDIRECTINPUT8 input_ = {};
    inline LPDIRECTINPUTDEVICE8 inputDevice_ = {};
    inline BYTE keys_[256] = {};

    inline LPDIRECTINPUTDEVICE8 mouseInputDevice_ = {};
    inline DIMOUSESTATE mouseState_ = {};
    inline POINT mousePoint_ = {};

    inline XINPUT_STATE controllerState_ = {};

}

int InputManager::initialize(HINSTANCE hInstance, HWND hwnd) {
    HRESULT result = {};

    /// 
    /// DirectInputの初期化
    /// 
    result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&input_, nullptr);   // DirectInputを初期化する関数

    result = input_->CreateDevice(GUID_SysKeyboard, &inputDevice_, nullptr);    //DirectInputのキーボードを作る関数
    result = inputDevice_->SetDataFormat(&c_dfDIKeyboard);                                      // デバイスがキーボードであることを示す
    result = inputDevice_->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

    result = input_->CreateDevice(GUID_SysMouse, &mouseInputDevice_, nullptr);  // DirectInputのマウスを作る関数
    result = mouseInputDevice_->SetDataFormat(&c_dfDIMouse);                                    // デバイスがマウスであることを示す
    result = mouseInputDevice_->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);   

    ///
    /// XInputの初期化
    /// 
    XInputGetState(0, &controllerState_);

    return 0;   // 最後まで成功すると0を返す
}

void InputManager::update() {
    inputDevice_->Acquire();
    inputDevice_->GetDeviceState(sizeof(keys_), &keys_);

    mouseInputDevice_->Acquire();
    mouseInputDevice_->GetDeviceState(sizeof(mouseState_), &mouseState_);

    GetCursorPos(&mousePoint_);
    ScreenToClient(GameEngine::GetWindowHandle(), &mousePoint_);
}

void InputManager::release() {
    input_->Release();
    inputDevice_->Release();
    mouseInputDevice_->Release();
}

bool InputManager::IsPushKey(int key) {
    if (keys_[key] & 0x80) {
        return true;
    }
    return false;
}

bool InputManager::IsPushMouse(int button) {
    if (mouseState_.rgbButtons[button] & 0x80) {
        return true;
    }
    return false;
}

POINT InputManager::GetMousePoint() {
    return mousePoint_;
}

bool InputManager::IsControllerButtonPush(int button) {
    if (controllerState_.Gamepad.wButtons & button) {
        return true;
    }
    return false;
}

DirectX::XMFLOAT2 InputManager::GetControllerTiltLeft()
{
    float x = controllerState_.Gamepad.sThumbLX;
    float y = controllerState_.Gamepad.sThumbLY;
    return DirectX::XMFLOAT2(x, y);
}

DirectX::XMFLOAT2 InputManager::GetControllerTiltRight() {
    float x = controllerState_.Gamepad.sThumbRX;
    float y = controllerState_.Gamepad.sThumbRY;
    return DirectX::XMFLOAT2(x, y);
}

float InputManager::GetControllerLeftTrigger() {
    return controllerState_.Gamepad.bLeftTrigger;
}

float InputManager::GetControllerRightTrigger() {
    return controllerState_.Gamepad.bRightTrigger;
}

void InputManager::StartControllerVibration(int leftSpeed, int rightSpeed) {
    XINPUT_VIBRATION vibration = {};
    vibration.wLeftMotorSpeed = leftSpeed;
    vibration.wRightMotorSpeed = rightSpeed;
    XInputSetState(0, &vibration);
}

void InputManager::StopControllerVibration() {
    XINPUT_VIBRATION vibration = {};
    vibration.wLeftMotorSpeed = 0;
    vibration.wRightMotorSpeed = 0;
    XInputSetState(0, &vibration);
}


