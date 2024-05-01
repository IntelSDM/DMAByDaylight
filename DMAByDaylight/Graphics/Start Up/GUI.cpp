#include "pch.h"
#include "GUI.h"
#include "entity.h"
#include "Form.h"
#include "Button.h"
#include "ColourPicker.h"
#include "Label.h"
#include "tab.h"
#include "TabController.h"
#include "Toggle.h"
#include "Slider.h"
#include "DropDown.h"
#include "ComboBox.h"
#include "KeyBind.h"
#include "TabListBox.h"
#include "TabListBoxController.h"
#include "TextBox.h"
#include "ConfigUtilities.h"
int SelectedTab = 1;
int SelectedSubTab = 0;
int TabCount = 0;
int KeyBindClipBoard = 0;
EntityVector MenuEntity;
bool MenuOpen = true;
D2D1::ColorF ColourPickerClipBoard = Colour(255,255,255);
D2D1::ColorF ColourPick = Colour(0, 150, 255, 255);
std::wstring ScreenWidth = std::to_wstring(Configs.Overlay.Width);
std::wstring ScreenHeight = std::to_wstring(Configs.Overlay.Height);
void CreateGUI()
{
	MenuEntity = std::make_shared<Container>();
	auto form = std::make_shared<Form>(100, 100.0f, 300, 200, 2, 30, LIT(L"DMA Dead By Daylight"), false);
	{
		auto tabcontroller = std::make_shared<TabController>();
		form->Push(tabcontroller);

		auto playeresptab = std::make_shared<Tab>(LIT(L"Player ESP"), 5, 5, &SelectedTab, 0, 20);
		{
			auto name = std::make_shared<Toggle>(100, 5, LIT(L"Name"), &Configs.Survivor.Name);
			playeresptab->Push(name);
			auto textcolour = std::make_shared<ColourPicker>(160, 6, &Configs.Survivor.TextColour);
			playeresptab->Push(textcolour);
			auto distance = std::make_shared<Toggle>(100, 25, LIT(L"Distance"), &Configs.Survivor.Distance);
			playeresptab->Push(distance);
			auto maxdistance = std::make_shared<Slider<int>>(100, 45, 150, LIT(L"Max Distance"), LIT(L"m"), 0, 1000, &Configs.Survivor.MaxDistance);
			playeresptab->Push(maxdistance);
			auto textsize = std::make_shared<Slider<int>>(100, 70, 150, LIT(L"Text Size"), LIT(L"px"), 4, 16, &Configs.Survivor.FontSize);
			playeresptab->Push(textsize);
		}
		tabcontroller->Push(playeresptab);
		auto killeresptab = std::make_shared<Tab>(LIT(L"Killer ESP"), 5, 30, &SelectedTab, 0, 20);
		{
			auto name = std::make_shared<Toggle>(100, 5, LIT(L"Name"), &Configs.Killer.Name);
			killeresptab->Push(name);
			auto textcolour = std::make_shared<ColourPicker>(160, 6, &Configs.Killer.TextColour);
			killeresptab->Push(textcolour);
			auto distance = std::make_shared<Toggle>(100, 25, LIT(L"Distance"), &Configs.Killer.Distance);
			killeresptab->Push(distance);
			auto maxdistance = std::make_shared<Slider<int>>(100, 45, 150, LIT(L"Max Distance"), LIT(L"m"), 0, 1000, &Configs.Killer.MaxDistance);
			killeresptab->Push(maxdistance);
			auto textsize = std::make_shared<Slider<int>>(100, 70, 150, LIT(L"Text Size"), LIT(L"px"), 4, 16, &Configs.Killer.FontSize);
			killeresptab->Push(textsize);
		}
		tabcontroller->Push(killeresptab);
		auto overlaytab = std::make_shared<Tab>(LIT(L"Overlay"), 5, 55, &SelectedTab, 0, 20);
		{
			auto overrideresolution = std::make_shared<Toggle>(100, 5, LIT(L"Override W2S Resolution"), &Configs.Overlay.OverrideResolution);
			overlaytab->Push(overrideresolution);
			auto screenwidth = std::make_shared<TextBox>(100, 35, LIT(L"Screen Width"), &ScreenWidth);
			screenwidth->SetValueChangedEvent([]()
				{
					try
					{
						Configs.Overlay.Width = std::stoi(ScreenWidth);
					}
					catch (std::exception ex)
					{
					}
				});
			overlaytab->Push(screenwidth);
			auto screenheight = std::make_shared<TextBox>(100, 70, LIT(L"Screen Height"), &ScreenHeight);
			screenheight->SetValueChangedEvent([]()
				{
					try
					{
						Configs.Overlay.Height = std::stoi(ScreenHeight);
					}
					catch (std::exception ex)
					{
					}
				});
			overlaytab->Push(screenheight);


		}
		tabcontroller->Push(overlaytab);
		auto configtab = std::make_shared<Tab>(LIT(L"Config"), 5, 80, &SelectedTab, 0, 20);
		{
			auto saveconfig = std::make_shared<Button>(100, 5, LIT(L"Save"), []()
				{


					SaveConfig(L"Default.json");
					CreateGUI(); // reinit/ reload
					SelectedTab = 1;

				});
			configtab->Push(saveconfig);

			auto loadconfig = std::make_shared<Button>(165, 5, LIT(L"Load"), []()
				{


					LoadConfig(L"Default.json");
					CreateGUI(); // reinit/ reload
					SelectedTab = 1;

				});
			configtab->Push(loadconfig);
		}
		tabcontroller->Push(configtab);
	}

	MenuEntity->Push(form);
	MenuEntity->Draw();
	MenuEntity->Update();
}

void SetFormPriority()
{
	// This sorts the host container (containerptr) which contains forms, as long as a form isn't parented to another form then this will allow it to draw over when clicked.
	// I swear to god if i need to make this work for forms inside forms for some odd reason in the future then i am going to throw a monitor out the window.
	std::sort(MenuEntity->GetContainer().begin(), MenuEntity->GetContainer().end(),
	          [](child a, child b) { return b->GetLastClick() < a->GetLastClick(); }
	);
}

float LastOpen = 0;

void Render()
{
	if (IsKeyClicked(VK_INSERT) && LastOpen < clock() * 0.00001f)
	{
		LastOpen = (clock() * 0.00001f) + 0.002f;
		MenuOpen = !MenuOpen;
	}

	MenuEntity->Draw();
	MenuEntity->GetContainer()[0]->Update(); // only allow stretching,dragging and other update stuff if it is the main form, prevents dragging and sizing the wrong forms.
	SetFormPriority();
}
