/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */
#include "s3e.h"
#include "IwDebug.h"
#include "IwNUI.h"
#include "VungleSDK.h"

using namespace IwNUI;

const CColour COLOUR_GREY(0xffC9C0BC);
const CColour COLOUR_WHITE(0xffFFFFFF);

CButtonPtr defaultButton;
CButtonPtr incentivizedButton;
CButtonPtr mutedButton;

bool defaultClick(void* data, CButton* button) {
	VunglePlayAd();
	return true;
}

bool incentivizedClick(void* data, CButton* button) {
	VungleSDKPlayOption* opts = new VungleSDKPlayOption();
	opts->incentivized = true;
	VunglePlayAdWithOptions(opts);
	return true;
}

bool mutedClick(void* data, CButton* button) {
	VungleSDKPlayOption* opts = new VungleSDKPlayOption();
	opts->startMuted = true;
	VunglePlayAdWithOptions(opts);
	return true;
}

int32 OnAdPlayableChanged(void* systemData, void* userData) {
	bool adPlayble = (bool)systemData;
	defaultButton->SetAttribute("enabled", adPlayble);
	incentivizedButton->SetAttribute("enabled", adPlayble);
	mutedButton->SetAttribute("enabled", adPlayble);
	return 0;
}

// Main entry point for the application
int main()
{
    CAppPtr app = CreateApp();
    CWindowPtr window = CreateWindow();

    app->AddWindow(window);

    CViewPtr view = CreateView("canvas");
    window->SetChild(view);

	defaultButton = CreateButton(CAttributes()
		.Set("caption", "Default configuration")
		.Set("y1", "6%")
		.Set("x1", "10%")
		.Set("width", "80%")
		.Set("height", "25%")
		.Set("fontColour", COLOUR_WHITE)
		.Set("normal.image", "berlinSky.jpg")
		.Set("disabled", CAttributes()
			.Set("fontColour", COLOUR_GREY)
			.Set("image", "berlinSkyDisabled.jpg"))
		.Set("enabled", false)
		.Set("fontSize", "large"));
	defaultButton->SetEventHandler("click", (void*)NULL, &defaultClick);

	incentivizedButton = CreateButton(CAttributes()
		.Set("caption", "Incentivized")
		.Set("y1", "37%")
		.Set("x1", "10%")
		.Set("width", "80%")
		.Set("height", "25%")
		.Set("fontColour", COLOUR_WHITE)
		.Set("normal.image", "londonSky.jpg")
		.Set("disabled", CAttributes()
			.Set("fontColour", COLOUR_GREY)
			.Set("image", "londonSkyDisabled.jpg"))
		.Set("enabled", false)
		.Set("fontSize", "large"));
	incentivizedButton->SetEventHandler("click", (void*)NULL, &incentivizedClick);

	mutedButton = CreateButton(CAttributes()
		.Set("caption", "Muted")
		.Set("y1", "68%")
		.Set("x1", "10%")
		.Set("width", "80%")
		.Set("height", "25%")
		.Set("fontColour", COLOUR_WHITE)
		.Set("normal.image", "sfSky.jpg")
		.Set("disabled", CAttributes()
			.Set("fontColour", COLOUR_GREY)
			.Set("image", "sfSkyDisabled.jpg"))
		.Set("enabled", false)
		.Set("fontSize", "large"));
	mutedButton->SetEventHandler("click", (void*)NULL, &mutedClick);
	VungleSDKRegister(VUNGLESDK_CALLBACK_ADPLAYABLECHANGED, (s3eCallback)OnAdPlayableChanged, (void*)NULL);

	view->AddChild(defaultButton);
	view->AddChild(incentivizedButton);
	view->AddChild(mutedButton);

	VungleInit("vungleTest", "vungleTest", "vungleTest");

    app->ShowWindow(window);

    app->Run();

    //Terminate modules being used
    
    // Return
    return 0;
}
