/*
 *             cairo-util - keymap.h
 * Header file containing a map of key modifiers
 * in order to execute a small group of functions that
 * you are unable to do so while Cairo is set as a shell
*/

#ifndef KEYMAP_H
#define KEYMAP_H

#include <windows.h>
#include "cairoprop.h"

#define CAIRO_UTILITY_MAX_SHORTCUTS		4

#define ACTION_LOCK_MACHINE_KEYCOMBINATION	(MOD_CONTROL | MOD_ALT) // Ctrl + Alt
#define ACTION_LOCK_MACHINE_HOTKEY		'L'

#define ACTION_SHOW_DESKTOP_KEYCOMBINATION	(MOD_CONTROL) // Ctrl
#define ACTION_SHOW_DESKTOP_HOTKEY		'D'

#define ACTION_SHOW_CONTROL_KEYCOMBINATION	(MOD_CONTROL | MOD_ALT) // Ctrl + Alt
#define ACTION_SHOW_CONTROL_HOTKEY		'C'
#define SYSTEM_PATH_CONTROL_NAME		"control"

#define ACTION_EXIT_CAIROUT_HOTKEY		(VK_PRIOR) // Page Up

typedef void (*CairoFunction)();

typedef struct {
	unsigned int keyCombination;
	char key;
	CairoFunction cairoFunction;
	short id;
} ShortcutInfo_t;

int ContainsHwnd(HWND hwnd) {
	for (int i = 0; i < CAIRO_MAX_WINDOWS; i++) {
		if (cInfo[i].wName != NULL) {
			if (hwnd == cInfo[i].hWnd) {
				return 1;
			}
		}
	}

	return 0;
}

void __cdecl LockMachine(void) {
	LockWorkStation();
}

void __cdecl ShowDesktop(void) {
	HWND currentWindow = GetForegroundWindow();

	while (ContainsHwnd(currentWindow) == 0) {
		ShowWindow(currentWindow, SW_MINIMIZE);
		currentWindow = GetForegroundWindow();
		SetFocus(currentWindow);
	}
}

void __cdecl ShowControl(void) {
	system(SYSTEM_PATH_CONTROL_NAME);
}

void __cdecl TerminateUtility(void) {
	PostQuitMessage(0);
}

ShortcutInfo_t sInfo[CAIRO_UTILITY_MAX_SHORTCUTS] = {
	{ ACTION_LOCK_MACHINE_KEYCOMBINATION, ACTION_LOCK_MACHINE_HOTKEY, LockMachine, 0 },
	{ ACTION_SHOW_DESKTOP_KEYCOMBINATION, ACTION_SHOW_DESKTOP_HOTKEY, ShowDesktop, 1 },
	{ ACTION_SHOW_CONTROL_KEYCOMBINATION, ACTION_SHOW_CONTROL_HOTKEY, ShowControl, 2 },
	{ 0, ACTION_EXIT_CAIROUT_HOTKEY, TerminateUtility, 3 },
};

int RegisterAllHotKeys(void) {
	for (int i = 0; i < CAIRO_UTILITY_MAX_SHORTCUTS; i++) {
		if (!RegisterHotKey(NULL, sInfo[i].id, sInfo[i].keyCombination, sInfo[i].key)) {
			return 0;
		}
	}

	return 1;
}

void UnregisterAllHotKeys(void) {
	for (int i = 0; i < CAIRO_UTILITY_MAX_SHORTCUTS; i++) {
		UnregisterHotKey(NULL, sInfo[i].id);
	}
}

#endif // !KEYMAP_H
