
#include "pch.h"
#include "Window.h"

#include "CPCore/Logging/Console.h"

void cpSetWindowShouldClose( CPpwindow window, CPbool close ) {
    window->shouldClose = close;
}

CPbool cpGetWindowShouldClose( CPpwindow window ) {
    return window->shouldClose;
}

void cpSetKeyDownCallback( CPpwindow window, CPkeyDownCallback callback ) { window->keyDownCallback = callback; }
void cpSetKeyUpCallback( CPpwindow window, CPkeyUpCallback callback ) { window->keyUpCallback = callback; }
void cpSetMouseButtonDownCallback( CPpwindow window, CPmouseButtonDownCallback callback ) { window->mouseButtonDownCallback = callback; }
void cpSetMouseButtonUpCallback( CPpwindow window, CPmouseButtonUpCallback callback ) { window->mouseButtonUpCallback = callback; }
void cpSetMouseMoveCallback( CPpwindow window, CPmouseMoveCallback callback ) { window->mouseMoveCallback = callback; }
void cpSetMouseScrollDownCallback( CPpwindow window, CPmouseScrollDownCallback callback ) { window->mouseScrollDownCallback = callback; }
void cpSetMouseScrollUpCallback( CPpwindow window, CPmouseScrollUpCallback callback ) { window->mouseScrollUpCallback = callback; }
void cpSetMouseCursorEnterCallback( CPpwindow window, CPmouseCursorEnterCallback callback ) { window->mouseCursorEnterCallback = callback; }
void cpSetMouseCursorLeaveCallback( CPpwindow window, CPmouseCursorLeaveCallback callback ) { window->mouseCursorLeaveCallback = callback; }
void cpSetWindowResizeCallback( CPpwindow window, CPwindowResizeCallback callback ) { window->windowResizeCallback = callback; }
void cpAttachParentClass( CPpwindow window, void *parentClass ) { window->parentClass = parentClass; }
void* cpGetParentClass( CPpwindow window ) { return window->parentClass; }