#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <Windows.h>


using namespace std;
using namespace nlohmann;

void stormprintf(string log)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("[");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("STORM");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("] ");
	string toprint = log + "\n";
	printf(toprint.c_str());
}

int system_no_output(std::string command)
{
	command.insert(0, "/C ");

	SHELLEXECUTEINFOA ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = "cmd.exe";
	ShExecInfo.lpParameters = command.c_str();
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;

	if (ShellExecuteExA(&ShExecInfo) == FALSE)
		return -1;

	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

	DWORD rv;
	GetExitCodeProcess(ShExecInfo.hProcess, &rv);
	CloseHandle(ShExecInfo.hProcess);

	return rv;
}

void DownloadFile(string url, string path)
{
	string command = "curl " + url + " -o \"" + path + "\"";
	system_no_output(command.c_str());
}

string GetFortnitePath()
{
	//credit to neonite++ for path finder
	std::ifstream f("C:\\ProgramData\\Epic\\UnrealEngineLauncher\\LauncherInstalled.dat");

	json launcherInstalled;
	f >> launcherInstalled;
	json installationList = launcherInstalled["InstallationList"];

	for (int i = 0; i < installationList.size(); i++)
	{
		if (installationList[i]["AppName"] == "Fortnite")
		{
			return installationList[i]["InstallLocation"];
		}
	}
	return "";
}


int main()
{
	stormprintf("Welcome to Storm V6");
	stormprintf("if you have any issues please join discord.gg/stormfn for help!");

	
	string FortnitePath = GetFortnitePath() + +"\\FortniteGame\\Binaries\\Win64\\";
	string todelete = FortnitePath + "FortniteClient-Win64-Shipping_BE.exe";
	string todelete1 = FortnitePath + "FortniteClient-Win64-Shipping_EAC.exe";
	std::remove(todelete.c_str());
	std::remove(todelete1.c_str());
	DownloadFile("https://cdn.storm-fn.dev/sslbypass.dll", FortnitePath + "Storm.dll");
	DownloadFile("https://cdn.storm-fn.dev/anticheats/be.exe", FortnitePath + "FortniteClient-Win64-Shipping_BE.exe");
	DownloadFile("https://cdn.storm-fn.dev/anticheats/eac.exe", FortnitePath + "FortniteClient-Win64-Shipping_EAC.exe");
	system_no_output("start com.epicgames.launcher://apps/Fortnite?action=launch");
	
	
	for (;;)
		;
}
