#pragma once
#include <dinput.h>
#include <Xinput.h>
#include <DirectXMath.h>

#pragma comment(lib, "XInput.lib")

namespace InputManager {

	/// <summary>
	/// InputManagerを初期化する関数
	/// </summary>
	/// <param name="hInstance">ウインドウのインスタンス</param>
	/// <param name="hwnd">ウインドウのハンドル</param>
	/// <returns></returns>
	int initialize(HINSTANCE hInstance, HWND hwnd);
	void update();
	void release();

	/// <summary>
	/// キーボードが押されたかを返す関数（※押しっぱなし関係無し）
	/// </summary>
	/// <param name="key">キーボードのキーの種類</param>
	/// <returns>押されている場合はtrueを返し、押されていない場合はfalseを返す。</returns>
	bool IsPushKey(int key);

	/// <summary>
	/// マウスが押されたかを返す関数（※押しっぱなし関係無し）
	/// </summary>
	/// <param name="button">マウスのボタンの種類</param>
	/// <returns>押されている場合はtrueを返し、押されていない場合はfalseを返す。</returns>
	bool IsPushMouse(int button);

	/// <summary>
	/// 現在のマウスの座標を取得する関数。（※InputManagerのupdateで更新される）
	/// </summary>
	/// <returns></returns>
	POINT GetMousePoint();

	/// <summary>
	/// コントローラーが押されているかを返す関数（※押しっぱなし関係無し）
	/// </summary>
	/// <param name="button">コントローラーのボタン</param>
	/// <returns></returns>
	bool IsControllerButtonPush(int button);

	/// <summary>
	/// 左スティックの縦方向の傾き（縦・横）を取得する関数
	/// </summary>
	DirectX::XMFLOAT2 GetControllerTiltLeft();

	/// <summary>
	/// 右スティックの縦方向の傾き（縦・横）を取得する関数
	/// </summary>
	DirectX::XMFLOAT2 GetControllerTiltRight();

	/// <summary>
	/// 左トリガーの押し込み具合を取得する関数
	/// </summary>
	float GetControllerLeftTrigger();

	/// <summary>
	/// 右トリガーの押し込み具合を取得する関数
	/// </summary>
	float GetControllerRightTrigger();

	/// <summary>
	/// コントローラーの振動を開始するコマンド
	/// </summary>
	/// <param name="leftSpeed">左のモーターの強さ</param>
	/// <param name="rightSpeed">右モーターの強さ</param>
	void StartControllerVibration(int leftSpeed, int rightSpeed);

	/// <summary>
	/// コントローラーの振動を停止する関数
	/// </summary>
	void StopControllerVibration();
}