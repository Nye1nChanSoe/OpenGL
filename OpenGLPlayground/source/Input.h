#pragma once

#include <utility>

class Input
{
public:
	static bool IsKeyPressed(int keycode) { return s_Input.IsKeyPressedImpl(keycode); }
	static bool IsMouseButtonPressed(int button) { return s_Input.IsMouseButtonPressedImpl(button); }
	static std::pair<float, float> GetMousePos() { return s_Input.GetMousePosImpl(); }
	static bool GetMousePosX() { return s_Input.GetMousePosXImpl(); }
	static bool GetMousePosY() { return s_Input.GetMousePosYImpl(); }

private:
	bool IsKeyPressedImpl(int keycode);
	bool IsMouseButtonPressedImpl(int button);
	std::pair<float, float> GetMousePosImpl();
	float GetMousePosXImpl();
	float GetMousePosYImpl();

protected:
	Input(){}
	Input(const Input& other) = delete;

private:
	static Input s_Input;
};