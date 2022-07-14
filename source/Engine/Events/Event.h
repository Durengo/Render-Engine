#pragma once

enum class EventType
{
	None = 0,
	// WINDOW
	WindowClose,
	WindowResize,
	WindowFocus,
	WindowLostFocus,
	WindowMoved,
	// APP
	AppTick,
	AppUpdate,
	AppRender,
	// KEYBOARD
	KeyPressed,
	KeyReleased,
	KeyTyped,
	// MOUSE
	MouseButtonPressed,
	MouseButtonReleased,
	MouseMoved,
	MouseScrolled
};

enum EventCategory
{
	None = 0,
	EventCategoryApplication = 1,
	EventCategoryInput = 2,
	EventCategoryKeyboard = 3,
	EventCategoryMouse = 4,
	EventCategoryMouseButton = 5
};