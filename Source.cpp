#include "Header.h"

std::string input;
POINT p;
POINT tail;
bool exitf = false;

bool getObstacle(HWND win, HDC& h) {
	
	POINT temp = { tail.x + 200, tail.y + 30};
	SetCursorPos(temp.x, temp.y);
	COLORREF c = GetPixel(h, temp.x, temp.y);
	if (c == 5460819) {
		std::cout << "Obstacle" << std::endl;
		return true;
	}


	return false;
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
void jumper() {
	LPCSTR winn = "Iridium";
	HWND hwnd1 = FindWindow(NULL, winn);
	HDC hdcmem1 = GetDC(hwnd1);
	tail = getTail(hwnd1, hdcmem1, 700, 650, 0, 0);
	std::cout << "X: " << tail.x << " Y:" << tail.y << std::endl;
	srand(time(NULL));
	while (!exitf) {
		if (getObstacle(hwnd1, hdcmem1)) {
			std::cout << "Jumping" << std::endl;
			upD();
		}
		
	}
	
}


int main() {
	std::cout << "Type start when you are ready: ";
	std::cin >> input;
	std::cout << std::endl;
	std::thread jump(jumper);
	while (!exitf) {
		if (GetAsyncKeyState(VK_DOWN)) {
			exitf = true;

		}
		/*if (GetAsyncKeyState(VK_RIGHT)) {
			getColor();
		}*/

			

	}
	jump.join();

	return 0;

}