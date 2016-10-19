#pragma once

#include "Includes.h"

#ifndef MAINAPP_H
#define MAINAPP_H

class MainApp: public wxApp
{
public:
	MainApp();
	~MainApp();
	virtual bool OnInit();
};

#endif // !MAINAPP_H

