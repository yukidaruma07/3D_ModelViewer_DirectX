#include "BootScene.h"
#include "ObjectManager.h"
#include "Triangle.h"
#include "Image.h"
#include "LoggerManager.h"
#include "FBX.h"
#include "Box.h"
#include "InputManager.h"
#include <Windows.h>
#include <DirectXMath.h>

using namespace DirectX;

BootScene::BootScene()
	: BaseScene("BootScene") {
}

BootScene::~BootScene() {
}

void BootScene::Init() {

}

void BootScene::Update() {
	static POINT beforePoint = InputManager::GetMousePoint();
	POINT nowPoint = InputManager::GetMousePoint();
	bool mouseInput = InputManager::IsPushMouse(0);
	LoggerManager::InfoDebug(std::to_string(beforePoint.x) + "," + std::to_string(nowPoint.x));

	if (!mouseInput) return;
	auto fbxList = ObjectManager::GetDrawObjectList<FBX>();
	if (fbxList.empty()) return;
	XMFLOAT3 postion = fbxList[0]->GetPosition();
	if (beforePoint.x < nowPoint.x) {
		fbxList[0]->SetPosition({postion.x + 0.1f, postion.y, postion.z});
	}
	else if (beforePoint.x > nowPoint.x) {
		fbxList[0]->SetPosition({ postion.x - 0.1f, postion.y, postion.z });
	}

	beforePoint = nowPoint;
}

void BootScene::Draw() {
}

void BootScene::Release() {
}
