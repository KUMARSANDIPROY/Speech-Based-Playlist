// SpeechPlaylist.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "guiapp.h"
#include <stdio.h>
#include <Windows.h>
#pragma warning(disable:4996)

using namespace SpeechPlaylist;
#pragma warning(disable:4996)
[STAThreadAttribute]

int main(array<System::String ^> ^args)
{

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	guiapp ^obj=gcnew guiapp();
	Application::Run(obj);
	return 0;
	return 0;
}

