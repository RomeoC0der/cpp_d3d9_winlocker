#pragma once
class IBaseInterface {
public:
	IBaseInterface() {};
	virtual ~IBaseInterface() { this->release(); };
	virtual void release() {};
};