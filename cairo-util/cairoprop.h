/*
 *                 cairo-util - cairoprop.h
 * Header file containing some Cairo properties in order
 * to execute a small group of functions that require more
 *	           process information
*/

#ifndef CAIROPROP_H
#define CAIROPROP_H

#include <windows.h>

#define CAIRO_STATIC_PROCESS_CLASS_NAME		"HwndWrapper[CairoDesktop.exe"
#define CAIRO_STATIC_DESKTOP_CLASS_NAME		"WindowsForms10.Window.0.app.0.188dfdc_r6_ad1"
#define CAIRO_MAX_WINDOWS			13

typedef struct {
	HWND hWnd;
	char* cName;
	char* wName;
} CairoInfo_t;

CairoInfo_t cInfo[CAIRO_MAX_WINDOWS];

int CALLBACK EnumCairoWindows(HWND hwnd, LPARAM lParam) {
	char className[128];
	char windowTitle[128];
	static short index = 0;

	if (GetClassNameA(hwnd, className, sizeof(className)) && (GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle)) >= 0)) {
		if (strstr(className, CAIRO_STATIC_PROCESS_CLASS_NAME) || strstr(windowTitle, CAIRO_STATIC_DESKTOP_CLASS_NAME)) {
			cInfo[index].hWnd = hwnd;
			cInfo[index].cName = _strdup(className);
			cInfo[index].wName = _strdup(windowTitle);
			index++;
		}
	}

	return 1;
}

void ClearAllocatedMemory(void) {
	for (int i = 0; i < CAIRO_MAX_WINDOWS; i++) {
		free(cInfo[i].cName);
		free(cInfo[i].wName);
	}
}

#endif // !CAIROPROP_H
