#pragma once

#include "Public/Application.h"

extern Application* CreateApplication();

int main(int argc, char* argv[])
{
	Application* app = CreateApplication();
	app->Run();
	delete app;

	return 0;
}