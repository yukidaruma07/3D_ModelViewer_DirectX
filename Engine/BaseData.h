#pragma once

/// <summary>
/// 描画を必要としないオブジェクトの基底クラス
/// </summary>
class BaseData {
protected:
private:
public:

	BaseData() {};
	virtual ~BaseData() {};

	virtual void Init() {};
	virtual void Release() {};
};