#include "ConsoleInput.h"


void getInput(char& ch) {
	switch (os) {

	case OS::OS_WINDOWS:

		if (_kbhit()) {
			ch = _getch();
			ch = static_cast<char>(std::tolower(ch));
		}
		else {
			ch = ' ';
		}


		break;

	case OS::OS_LINUX:
		std::system("clear");
		break;

	default:
		std::cout << "Nose en que OS estas :v [Input]";
	}
}

void clear() {

	switch (os) {

	case OS::OS_WINDOWS:
	{
		// std::system("cls");

		// https://stackoverflow.com/questions/1387064/how-to-get-the-error-message-from-the-error-code-returned-by-getlasterror

		COORD coord{ 0,0 };

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		if (!SetConsoleCursorPosition(hConsole, coord))
		{

			DWORD errorMessageID = ::GetLastError();
			if (errorMessageID == 0) {
				std::cerr << "No error message has been recorded" << std::endl;
			}

			LPSTR messageBuffer = nullptr;

			size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

			std::string message(messageBuffer, size);

			LocalFree(messageBuffer);

			std::cerr << message << std::endl;
		}
	}
	break;

	case OS::OS_LINUX:
		std::system("clear");
		break;

	default:
		std::cout << "Nose en que OS estas :v [Clear]";
	}
}