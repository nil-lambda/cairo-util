#include <stdio.h>
#include "keymap.h"
#include "cairoprop.h"

int __cdecl main(void) {
	if (!RegisterAllHotKeys()) {
		MessageBoxA(NULL, "One or more hotkeys did not register.\nAnother instance of the utility may be running.", "Exiting...", 0x0L);
		return 0;
	}

	ShowWindow(GetConsoleWindow(), SW_HIDE);
	EnumWindows(EnumCairoWindows, 0);

	MSG msg;
	while (GetMessageA(&msg, NULL, 0, 0) > 0) {
		if (msg.message == WM_HOTKEY) {
			for (int i = 0; i < CAIRO_UTILITY_MAX_SHORTCUTS; i++) {
				if (msg.wParam == sInfo[i].id) {
					sInfo[i].cairoFunction();
				}
			}
		}
	}

	UnregisterAllHotKeys();
	ClearAllocatedMemory();
	Beep(500, 750);

	return 0;
}
