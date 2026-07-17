#pragma once

class BaseData {
protected:
private:
public:

	BaseData() {};
	virtual ~BaseData() {};

	virtual void Init() {};
	virtual void Release() {};
};