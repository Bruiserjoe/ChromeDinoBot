#include "Header.h"

std::string input;
POINT p;
POINT tail;
bool exitf = false;

//Fix dodger
//Checks if a bird that needs to be dodged is present
bool getBird(HWND win, HDC& hc) {
	POINT temp = { tail.x + 400, tail.y - 40 };
	COLORREF c = GetPixel(hc, temp.x, temp.y);
	if (c == 5460819) {
		std::cout << "Bird" << std::endl;
		return true;
	}
	return false;
}
//Checks for cacti or low bird
bool getObstacle(HWND win, HDC& h) {
	
	POINT temp = { tail.x + 300, tail.y + 30};
	SetCursorPos(temp.x, temp.y);
	COLORREF c = GetPixel(h, temp.x, temp.y);
	if (c == 5460819) {
		std::cout << "Obstacle" << std::endl;
		return true;
	}


	return false;
}
bool getLastOb(HWND win, HDC& hd) {
	POINT temp = { tail.x, tail.y + 30 };
	COLORREF c = GetPixel(hd, temp.x, temp.y);
	if (c != 5460819) {
		std::cout << "Going down" << std::endl;
		return false;
	}

	return true;
}

POINT getTail(HWND win, HDC& dc, int w, int h, int sx, int sy) {
	POINT temp = { 0, 0 };
	for (int i = 0; i < sx + w; i+=10) {
		for (int j = 0; j < sy + h; j++) {
			COLORREF c = GetPixel(dc, i, j);
			SetCursorPos(i, j);
			if (c == 5460819) {
				temp.x = i;
				temp.y = j;
				return temp;
			}

		}

	}

	return temp;
}
//Gives color in decimal form
void getColor() {
	LPCSTR windowname1 = "Iridium";
	HWND win = FindWindow(NULL, windowname1);
	POINT input;
	HDC dci = GetDC(win);
	GetCursorPos(&input);
	ScreenToClient(win, &input);
	COLORREF color = GetPixel(dci, input.x, input.y);
	std::cout << color << std::endl;
	Sleep(1000);
}



//Presses up arrow
void upD() {
	INPUT upper = { 0 };
	upper.type = INPUT_KEYBOARD;
	upper.ki.wVk = VK_UP;
	SendInput(1, &upper, sizeof(INPUT)); // Send KeyDown
	upper.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &upper, sizeof(INPUT)); // Send KeyUp
}
//Presses down arrow
void downD() {
	INPUT upper = { 0 };
	upper.type = INPUT_KEYBOARD;
	upper.ki.wVk = VK_DOWN;
	SendInput(1, &upper, sizeof(INPUT)); // Send KeyDown
	upper.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &upper, sizeof(INPUT)); // Send KeyUp
}
void birder() {
	LPCSTR winn1 = "Iridium";
	HWND hwnd2 = FindWindow(NULL, winn1);
	HDC hdcmem2 = GetDC(hwnd2);
	std::this_thread::sleep_for(std::chrono::seconds(45));
	while (!exitf) {
		if (getBird(hwnd2, hdcmem2)) {
			std::cout << "Dodging" << std::endl;
			upD();
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			if (!getLastOb(hwnd2, hdcmem2)) {
				downD();
			}
		}

	}

}
void jumper() {
	LPCSTR winn = "Iridium";
	HWND hwnd1 = FindWindow(NULL, winn);
	HDC hdcmem1 = GetDC(hwnd1);
	srand(time(NULL));
	while (!exitf) {
		if (getObstacle(hwnd1, hdcmem1)) {
			std::cout << "Jumping" << std::endl;
			upD();
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			if (!getLastOb(hwnd1, hdcmem1)) {
				downD();
			}
		}
		
	}

}


int main() {
	LPCSTR winn = "Iridium";
	HWND hwnd1 = FindWindow(NULL, winn);
	HDC hdcmem1 = GetDC(hwnd1);
	std::cout << "Type start when you are ready: ";
	std::cin >> input;
	tail = getTail(hwnd1, hdcmem1, 700, 650, 0, 0);
	std::cout << "X: " << tail.x << " Y:" << tail.y << std::endl;
	std::cout << std::endl;
	std::thread jump(jumper);
	std::thread bird(birder);
	while (!exitf) {
		if (GetAsyncKeyState(VK_LEFT)) {
			exitf = true;

		}
		/*if (GetAsyncKeyState(VK_RIGHT)) {
			getColor();
		}*/

			

	}
	bird.join();
	jump.join();

	return 0;

}