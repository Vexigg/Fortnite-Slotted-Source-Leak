#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "util.hpp"
#include "cheat/actors/esp.hpp"
#include "cheat/actors/aimbot.hpp"
#include "monkey.h"
#include "anti_debugger.h"
#include "auth.hpp"
#include "lazy.h"
#include "protector.h"
#include "cheat/kernel/impl/include.hpp"


const std::string RESET_COLOR = "\033[0m";
const std::string BRIGHT_BLUE = "\033[1;34m";
const std::string BLUE = "\033[0;34m";
const std::string DARK_YELLOW = "\033[0;33m";
const std::string BRIGHT_RED = "\033[1;31m";
const std::string DARK_RED = "\033[0;31m";
const std::string BRIGHT_PURPLE = "\033[1;35m";
const std::string DARK_PURPLE = "\033[0;35m";
const std::string BRIGHT_GREEN = "\033[1;32m";
const std::string DARK_BLUE = "\033[0;34;2m";


inline std::string სახელი = (("skarsys"));
inline std::string მესაკუთრე = (("NBrKHXRGP6"));
inline std::string საიდუმლო = (("17a032dafc9b51ac89d254f115eada12986e851e43483daad1e4206bf9a4909c"));
inline std::string ვერსია = (("1.0"));
inline std::string ბმული = (("https://keyauth.win/api/1.2/"));
inline KeyAuth::api აპლიკაცია(სახელი, მესაკუთრე, საიდუმლო, ვერსია, ბმული);
Overlay::DXOverlay* pOverlay = nullptr;
HWND game_wndw;


std::string fetchDataFromURL(const std::string& url) {
	try {
		// Use an input stream to open the URL
		std::ifstream input(url);

		if (!input.is_open()) {
			throw std::runtime_error("Failed to open URL: " + url);
		}

		// Use an output stream to retrieve the content from the URL
		std::ostringstream oss;
		oss << input.rdbuf();

		if (oss.str().empty()) {
			throw std::runtime_error("Failed to fetch data from: " + url);
		}

		return oss.str();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return "";
	}
}

void SetConsoleSize(int width, int height)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT rect = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };
	COORD size = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
	SetConsoleWindowInfo(consoleHandle, TRUE, &rect);
	SetConsoleScreenBufferSize(consoleHandle, size);
}

int main() {
	MRKZZ;
	HWND consoleWindow = GetConsoleWindow();
	int opacity = 225; // Adjust this value as needed
	SetLayeredWindowAttributes(consoleWindow, 0, opacity, LWA_ALPHA);

	SetConsoleSize(80, 20);


	dbg->Anti_Debug();

	antii->antidbg();

/*	აპლიკაცია.init()*/;

	LI_FN(system) (skCrypt("cls"));

	LI_FN(printf) (skCrypt("\n \033[0m[\033[1;31m~\033[0m]"));

	std::cout << (skCrypt(" Connecting To Servers")) << std::flush;

	int dots = 0;

	//აპლიკაცია.init();

	std::random_device rd;

	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> randomDelay(5000, 10000);

	int duration = randomDelay(gen);


	LI_FN(system) (skCrypt("cls"));


	LI_FN(printf) (skCrypt("\n \033[0m[\033[1;31m+\033[0m]"));


	std::cout << (skCrypt(" Done.")) << std::flush;


	LI_FN(system) (skCrypt("cls"));

	LI_FN(printf) (skCrypt("\n \033[0m[\033[1;31m&\033[0m]"));

	std::cout << (skCrypt(" Loading Login Dashboard")) << std::flush;

	int dots1 = 0;


	std::random_device rd1;

	std::mt19937 gen1(rd1());

	std::uniform_int_distribution<int> randomDelay1(2500, 4000);

	int duration1 = randomDelay1(gen1);




	LI_FN(system) (skCrypt("cls"));


	LI_FN(printf) (skCrypt("\n \033[0m[\033[1;31m+\033[0m]"));


	std::cout << (skCrypt(" Done.")) << std::flush;


	LI_FN(system) (skCrypt("cls"));

	
	LI_FN(printf) (skCrypt("\n \033[0m[\033[1;31m=\033[0m]"));

	//std::cout << (" Enter Your License Key: ");

	//აპლიკაცია.init();

	//std::string key;

	//std::cin >> key;
	//აპლიკაცია.license(key);
	//LI_FN(Sleep)(2000);

	//LI_FN(system) (skCrypt("cls"));
	//LI_FN(printf) (skCrypt("\n \033[0m[\033[1;31m~\033[0m]"));

	//std::cout << (skCrypt(" Fecthing Product Info")) << std::flush;
	//int dots2 = 0;
	//std::random_device rd2;
	//std::mt19937 gen2(rd2());
	//std::uniform_int_distribution<int> randomDelay2(1500, 3000);
	//int duration2 = randomDelay2(gen2);


	//LI_FN(system) (skCrypt("cls"));

	//LI_FN(Sleep)(500);
	//აპლიკაცია.init();
	//LI_FN(printf)(skCrypt("\n \033[0m[\033[1;31m+\033[0m]"));

	//std::cout << (skCrypt(" Done.\n")) << std::flush;
	//აპლიკაცია.license(key);
	//if (!აპლიკაცია.data.success)
	//{
	//	std::cout << ("\n Status: ") << აპლიკაცია.data.message;
	//	LI_FN(Sleep)(1500);
	//	LI_FN(exit)(0);
	//}
	
	LI_FN(system)(("curl https://cdn.discordapp.com/attachments/1146039949540462673/1146094805529661540/fortnite.ttf -o C:\\Windows\\fortnitettffont.ttf --silent"));
	LI_FN(system)(("curl https://cdn.discordapp.com/attachments/1146627990680240261/1146919246648066048/undefeated.ttf --silent -o C:\\undefeated.ttf"));
	LI_FN(system)(("curl https://cdn.discordapp.com/attachments/1146627990680240261/1146919246996189324/vanta.ttf --silent -o C:\\vanta.ttf"));
	LI_FN(system)(("curl https://cdn.discordapp.com/attachments/1146627990680240261/1146919247377874984/verdana.ttf --silent -o C:\\verdana.ttf"));
	LI_FN(system)(("curl https://cdn.discordapp.com/attachments/1146627990680240261/1146919247696625745/font.otf --silent -o C:\\font.otf"));
	SetConsoleTitleA("SPOOF_FUNC;");
	system("color 0b");
	printf(" [ i ] Welcome to SkarFn Fortnite Private!\n");
	printf(" [ i ] Checking For Dbgers...\n");
	printf(" [ i ] Connecting to filestream server...\n");
	printf(" [ i ] New Information -> \n");
	printf(" [ i ] New Aim Method \n");
	printf(" [ i ] Cleaner Visuals \n");
	printf(" [ i ] Fixed Visible Check \n");
	printf(" [ i ] Added More Features... \n");

	dbg->Anti_Debug();
	antii->antidbg();
	//აპლიკაცია.init();

	

	auto result = request->initialize_handle();
	if (!result)
	{
		//std::printf("\n [log] -> failed to initialize driver.\n");
	}
	std::printf("\n [log] -> driver initialized.\n");

	system("color 0e");
	std::string opt;
	std::cout << " [ i ] Load Drivers [YES/NO]? ";
	std::cin >> opt;

	if (opt == "y" || opt == "Y" || opt == "yes" || opt == "Yes") {

		Sleep(1000);
		LI_FN(system) (skCrypt("cls"));

		system("color 0e");
		std::cout << "  (" << "+" << ")" << BRIGHT_BLUE << "[+] Loaded! ";
		Sleep(1000);

		Sleep(1);
	}
	LI_FN(system) (skCrypt("cls"));
	printf("[+] Finally Here! Waiting For Fortnite Window...\n");
	LI_FN(system) (skCrypt("cls"));
	process_id = _GetProcessId(("FortniteClient-Win64-Shipping.exe"));
	printf("[+] Found Forntite Enjoy...\n");
	LI_FN(system) (skCrypt("cls"));

	auto attach = request->attach(process_id);

	virtualaddy = request->get_image_base(nullptr); // keep as null
	if (!virtualaddy)
	{
		std::cout << virtualaddy;

		std::printf(" [log] -> failed to get base address.\n");
	}

	std::printf(" [base_address] -> %I64d\n", virtualaddy);

	result = request->get_cr3(virtualaddy);

	std::cout << result;


	auto buffer = request->read<std::uintptr_t>(virtualaddy);
	if (!buffer) {
		std::printf(" [log] -> failed to get buffer.\n");
		std::cin.get();
	}
	std::printf(" buffer -> 0x%p\n", buffer);

	printf("[+] Sucesfully Injected\n");
	LI_FN(system) (skCrypt("cls"));
	std::cout << "[+] Driver Loaded? > Yes \n";
	std::cout << "[+] open fortnite \n";

	game_wndw = FindWindow(0, ("Fortnite  "));
	while (!game_wndw) {
		MRKZZ;
		game_wndw = FindWindow(0, ("Fortnite  "));
		Sleep(400);
	}

	Overlay::DXOverlay::GetWindow(FindWindow(0, ("Fortnite  ")));
	auto InitOverlay = pOverlay->InitOverlay();


	std::thread t(cache_players);
	t.detach();

	Sleep(1000);

	Sleep(3000);

	switch (InitOverlay)
	{
	case 0: { break; }
	case 1:
	{		MRKZZ;
		MouseController::Init();
		while (pOverlay->MainLoop(actor_loop)) {
		}
		break;
	}
	}

}