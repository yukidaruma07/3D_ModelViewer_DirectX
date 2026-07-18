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
#include "../GameEngine.hpp"

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

	//if (!mouseInput) return;
	auto fbxList = ObjectManager::GetDrawObjectList<FBX>();
	if (fbxList.empty()) return;
	XMFLOAT3 postion = fbxList[0]->GetPosition();
	XMFLOAT3 rotation = fbxList[0]->GetRotation();
	XMFLOAT3 scale = fbxList[0]->GetScale();

	if (InputManager::IsPushKey(DIK_W)) {
		if (GameEngine::GetViewType() == ViewType::TRANSLATION) 
			fbxList[0]->SetPosition({ postion.x, postion.y, postion.z + 0.1f });
		else if (GameEngine::GetViewType() == ViewType::ROTATION)
			fbxList[0]->SetRotation({ rotation.x, rotation.y, rotation.z + 0.1f });
		else if (GameEngine::GetViewType() == ViewType::SCALE)
			fbxList[0]->SetScale({ scale.x, scale.y, scale.z + 0.1f });
	}
	if (InputManager::IsPushKey(DIK_S)) {
		if (GameEngine::GetViewType() == ViewType::TRANSLATION)
			fbxList[0]->SetPosition({ postion.x, postion.y, postion.z - 0.1f });
		else if (GameEngine::GetViewType() == ViewType::ROTATION)
			fbxList[0]->SetRotation({ rotation.x, rotation.y, rotation.z - 0.1f });
		else if (GameEngine::GetViewType() == ViewType::SCALE)
			fbxList[0]->SetScale({ scale.x, scale.y, scale.z - 0.1f });
	}
	if (InputManager::IsPushKey(DIK_A)) {
		if (GameEngine::GetViewType() == ViewType::TRANSLATION)
			fbxList[0]->SetPosition({ postion.x - 0.1f, postion.y, postion.z });
		else if (GameEngine::GetViewType() == ViewType::ROTATION)
			fbxList[0]->SetRotation({ rotation.x - 0.1f, rotation.y, rotation.z });
		else if (GameEngine::GetViewType() == ViewType::SCALE)
			fbxList[0]->SetScale({ scale.x - 0.1f, scale.y, scale.z });
	}
	if (InputManager::IsPushKey(DIK_D)) {
		if (GameEngine::GetViewType() == ViewType::TRANSLATION)
			fbxList[0]->SetPosition({ postion.x + 0.1f, postion.y, postion.z });
		else if (GameEngine::GetViewType() == ViewType::ROTATION)
			fbxList[0]->SetRotation({ rotation.x + 0.1f, rotation.y, rotation.z });
		else if (GameEngine::GetViewType() == ViewType::SCALE)
			fbxList[0]->SetScale({ scale.x + 0.1f, scale.y, scale.z });
	}
	if (InputManager::IsPushKey(DIK_LSHIFT)) {
		if (GameEngine::GetViewType() == ViewType::TRANSLATION)
			fbxList[0]->SetPosition({ postion.x, postion.y + 0.1f , postion.z });
		else if (GameEngine::GetViewType() == ViewType::ROTATION)
			fbxList[0]->SetRotation({ rotation.x, rotation.y + 0.1f , rotation.z });
		else if (GameEngine::GetViewType() == ViewType::SCALE)
			fbxList[0]->SetScale({ scale.x, scale.y + 0.1f , scale.z });
	}
	if (InputManager::IsPushKey(DIK_SPACE)) {
		if (GameEngine::GetViewType() == ViewType::TRANSLATION)
			fbxList[0]->SetPosition({ postion.x, postion.y - 0.1f, postion.z });
		else if (GameEngine::GetViewType() == ViewType::ROTATION)
			fbxList[0]->SetRotation({ rotation.x, rotation.y - 0.1f, rotation.z });
		else if (GameEngine::GetViewType() == ViewType::SCALE)
			fbxList[0]->SetScale({ scale.x, scale.y - 0.1f, scale.z });
	}

	/*
	if (beforePoint.x < nowPoint.x) {
		fbxList[0]->SetPosition({postion.x + 0.1f, postion.y, postion.z});
	}
	else if (beforePoint.x > nowPoint.x) {
		fbxList[0]->SetPosition({ postion.x - 0.1f, postion.y, postion.z });
	}
	*/

	beforePoint = nowPoint;
}

void BootScene::Draw() {
}

void BootScene::Release() {
}
