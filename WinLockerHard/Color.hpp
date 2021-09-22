#pragma once
#include <cstdint>
#include <cassert>
#include <d3d9.h>
class Color {
public:
	Color(float r, float g, float b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
	Color(float r, float g, float b,float a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	Color(float* clr)//may crash program
	{
		if (!clr)return;
		this->r = clr[0];
		this->g = clr[1];
		this->b = clr[2];
	}
	__forceinline float& get(int index) const noexcept {
		assert(index > 0 && index <= 2);
		static constexpr size_t fsize = sizeof(float);
		return *(float*)((uintptr_t)this + fsize * index);
	}
	__forceinline float& operator[](int index)const noexcept {
		assert(index > 0 && index <= 2);
		static constexpr size_t fsize = sizeof(float);
		return *(float*)((uintptr_t)this + fsize * index);
	}
	Color(const Color& clr)
	{
		this->r = clr.r;
		this->g = clr.g;
		this->b = clr.b;
		this->a = clr.a;
	}
	Color operator=(const Color& clr)
	{
		this->r = clr.r;
		this->g = clr.g;
		this->b = clr.b;
		this->a = clr.a;
		return *this;
	}
	Color() {};
	//Color 
	D3DCOLOR convert();
private:
	float r, g, b,a;//max 1.0f
};