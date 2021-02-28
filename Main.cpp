#include "Main.h"
#include "options.h"
#include <vector>
#include <iostream>

#include "imgui-docking/imgui_internal.h"

using namespace std;

/*

ImGui BASE V2 : by xo1337
#primerose gang

enjoy.

If you need help just send me a private message on UC or on discord

*/

void RunStyle()
{
	auto& style = ImGui::GetStyle();

	style.WindowMinSize = ImVec2(550, 500); // This sets the minimum window size

	style.FrameBorderSize = 0;
	style.WindowRounding = 0;
	style.TabRounding = 0;
	style.ScrollbarRounding = 0;
	style.FramePadding = ImVec2(8, 6);
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

	style.Colors[ImGuiCol_TitleBg] = ImColor(227, 0, 40, 255);			// The top bar color
	style.Colors[ImGuiCol_TitleBgActive] = ImColor(227, 0, 40, 255);			// When you press in the imgui menu
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(15, 15, 15, 50);		        // When the title is collapsed

	style.Colors[ImGuiCol_WindowBg] = ImColor(12, 12, 12, 255);				// Window Background

	style.Colors[ImGuiCol_Button] = ImColor(24, 25, 24, 255);			// button color
	style.Colors[ImGuiCol_ButtonActive] = ImColor(54, 53, 55);	        // button color when pressed
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(54, 53, 55);		    // button when hovered

	style.Colors[ImGuiCol_CheckMark] = ImColor(255, 255, 255, 255);			//check mark color

	style.Colors[ImGuiCol_FrameBg] = ImColor(36, 37, 36, 255);
	style.Colors[ImGuiCol_FrameBgActive] = ImColor(36, 37, 36, 255);
	style.Colors[ImGuiCol_FrameBgHovered] = ImColor(36, 37, 36, 255);

	style.Colors[ImGuiCol_Header] = ImColor(24, 24, 24, 255);			// for collapsing headers , etc
	style.Colors[ImGuiCol_HeaderActive] = ImColor(54, 53, 55);
	style.Colors[ImGuiCol_HeaderHovered] = ImColor(24, 24, 24, 100);

	style.Colors[ImGuiCol_ResizeGrip] = ImColor(51, 49, 50, 255);		    // the resize grip thing bottom right
	style.Colors[ImGuiCol_ResizeGripActive] = ImColor(54, 53, 55);			// when you hold it / active
	style.Colors[ImGuiCol_ResizeGripHovered] = ImColor(51, 49, 50, 255);			// when you hover over it

	style.Colors[ImGuiCol_SliderGrab] = ImColor(249, 79, 49, 255);
	style.Colors[ImGuiCol_SliderGrabActive] = ImColor(249, 79, 49, 255);

	style.Colors[ImGuiCol_Border] = ImColor(54, 54, 54);
	style.Colors[ImGuiCol_Separator] = ImColor(54, 54, 54);
	style.Colors[ImGuiCol_SeparatorActive] = ImColor(54, 54, 54);
	style.Colors[ImGuiCol_SeparatorHovered] = ImColor(54, 54, 54);
}



int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, LOADER_BRAND, NULL };
    RegisterClassEx(&wc);
    main_hwnd = CreateWindow(wc.lpszClassName, LOADER_BRAND, WS_POPUP, 0, 0, 5, 5, NULL, NULL, wc.hInstance, NULL);

    if (!CreateDeviceD3D(main_hwnd)) {
        CleanupDeviceD3D();
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    ShowWindow(main_hwnd, SW_HIDE);
    UpdateWindow(main_hwnd);

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr; 
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; 
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", ops::fontSize);
    
    ImGui_ImplWin32_Init(main_hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    //DWORD window_flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar;


    RECT screen_rect;
    GetWindowRect(GetDesktopWindow(), &screen_rect);
    auto x = float(screen_rect.right - WINDOW_WIDTH) / 2.f;
    auto y = float(screen_rect.bottom - WINDOW_HEIGHT) / 2.f;

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }

        static bool CustomStyle = false;
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        if (CustomStyle == true) { 
            RunStyle(); 
        }
        else {
            ImGui::StyleColorsDark();
        }
        {
            //change NULL to '&loader_active' if you want the x in the top right
            //uncomment the window_flags if you want window flags, what i mean is so you can remove the bar to hide and open the imgui menu etc...
    
            ImGui::SetNextWindowSize(ImVec2(800, 600));
            ImGui::Begin(LOADER_BRAND, NULL); 
            {
                ImGui::BeginChild("##main", ImVec2(ImGui::GetWindowWidth(), 40));

                auto xw = ImGui::GetWindowWidth();

                if (ImGui::Button("First Tab", ImVec2(xw / 4, 31))) {
                    ops::tab = 0;
                }
                ImGui::SameLine();
				if (ImGui::Button("Second Tab", ImVec2(xw / 4, 31))) {
                    ops::tab = 1;
				}
                ImGui::SameLine();
				if (ImGui::Button("Third Tab", ImVec2(xw / 4, 31))) {
                    ops::tab = 2;
				}
                ImGui::SameLine();
                ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical); //Vertical Separator
                ImGui::SameLine();
				if (ImGui::Button("Fourth Tab", ImVec2(xw / 4, 31))) {
                    ops::tab = 3;
				}ImGui::SameLine();

                ImGui::EndChild();
                ImGui::Separator();

                static bool On = false;

                if (ops::tab == 0) {

                    ImGui::Checkbox("Checkbox", &On);
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
					ImGui::Checkbox("Custom Style", &CustomStyle);
					ImGui::PopStyleVar();
					ImGui::SameLine();
					ImGui::Text("(?)");
					if (ImGui::IsItemHovered()) {
						ImGui::SetTooltip("Hey im a tooltip!, info: The 'ImGuiStyleVar_FramePadding' makes something bigger :)");
					}

                    if (ImGui::Button("Popup Modal")) {
                        ImGui::OpenPopup("PopupTest");
                        
                    }


				}if (ops::tab == 1) {

                    ImGui::Columns(2, "##columns_1", true);
                    ImGui::SetColumnOffset(1, ImGui::GetWindowWidth() / 2); //comment this out , if you want the column to move around etc...
                    const char* itemsArray[] = { "item 1","item 2" };
                    for (int i{ 0 }; i < IM_ARRAYSIZE(itemsArray); i++) {
                        if (ImGui::CollapsingHeader(itemsArray[i])) {
                            ImGui::Text(std::string("Hi from collapsing header: ").append(itemsArray[i]).c_str());
                            switch (i) {
                            case 0:
								ImGui::Spacing();
								ImGui::TextColored(ImColor(255, 0, 0, 255), std::string("Im some cool red colored text under item LOL: ").append(itemsArray[i]).c_str());
                                break;
                            case 1:
								ImGui::Spacing();
								ImGui::TextColored(ImColor(255, 0, 0, 255), std::string("Im some cool red colored text under item ").append(itemsArray[i]).c_str());
                                break;
                            }
                            
                        }
                    }

                    const char* nodes[] = { "node 1","node 2","node 3" };
                    for (int i{ 0 }; i < IM_ARRAYSIZE(nodes); i++) {
                        if (ImGui::TreeNode(nodes[i])) {
                            ImGui::Text(std::string("hi from node: ").append(nodes[i]).c_str());
                            ImGui::TreePop();
                        }
                    }

                    const char* comboItems[] = { "Combo Item 1","Combo Item 2","Combo Item 3" };
                    static int SelectedComboItem = NULL;
                    ImGui::Combo("##combo_label", &SelectedComboItem, comboItems, IM_ARRAYSIZE(comboItems));
                    ImGui::NextColumn();
                    ImGui::Text("this is the other side of the column");

                    static float yPos = 300;
                    static float xPos = 400;

                    ImGui::SliderFloat("##position_text", &yPos, 0, 1920);
                    ImGui::SliderFloat("##position_text2", &xPos, 0, 1920);

                    ImGui::SetCursorPosX(xPos);
                    ImGui::SetCursorPosY(yPos);
                    ImGui::Text("custom x & y poss(ed) text!");
                    

				}if (ops::tab == 2) {

                    auto x = ImGui::GetWindowWidth();
                    auto y = ImGui::GetWindowHeight();

                    const char* arrayItems[] = { "item 1","item 2", "item 3", "item 4" };
                    if (ImGui::BeginChild("##ArrayItems", ImVec2(x / 2, y))) {

						ImGui::ListBoxHeader("##listbox_header", ImVec2(x / 2, y - 300));
						for (int i = 0; i < IM_ARRAYSIZE(arrayItems); i++) {
							ImGui::CollapsingHeader(arrayItems[i]);
						}			
						ImGui::ListBoxFooter();
                        ImGui::Text("Current FPS: %f", ImGui::GetIO().Framerate);
                        ImGui::EndChild();
                    }
                    ImGui::SameLine();
                    ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
                    ImGui::SameLine();

                    static bool IsConsoleAlloced = false;
                    static bool NewLine = true;
                    static char buffer[512] = "";

                    if (ImGui::BeginChild("##CPlusPlusConsole", ImVec2(x / 2, y))) {

						ImGui::InputTextMultiline("##MultiLineInputBuffer", buffer, IM_ARRAYSIZE(buffer), ImVec2(x , y - 300));
						if (ImGui::Button("Send Message")) {
							if (!IsConsoleAlloced) {
								MessageBoxA(NULL, "Please alloc the console", NULL, NULL);
							}
							else {
								if (NewLine) {
									std::cout << buffer << std::endl;
								}
								else {
									std::cout << buffer;
								}

							}
						}
						ImGui::SameLine();
						if (ImGui::Button("Alloc Console")) {
							if (IsConsoleAlloced) {
								MessageBoxA(NULL, "The console is already allocated.", NULL, NULL);
							}
							else {
								IsConsoleAlloced = true;
								AllocConsole();
								FILE* f;
								freopen_s(&f, "CONOUT$", "w", stdout);
							}
						}
						
						if (ImGui::Button("Clear")) {
							system("cls");
						}
						ImGui::SameLine();
						if (ImGui::Button("Pause")) {
							system("pause");
						}
						ImGui::SameLine();
						ImGui::Checkbox("New Line", &NewLine);
						ImGui::SameLine();
						ImGui::Text("(?)");
						if (ImGui::IsItemHovered()) {
							ImGui::SetTooltip("this will create a new line in the console");
						}
                        ImGui::EndChild();
                    }

                   


				}if (ops::tab == 3) {

                    static float float_value = 0;
                    static int int_value = 0;
                    static int value;

					ImGui::SliderFloat("##float_slider", &float_value, 0.0f, 100.0f, "%.5f : Float Value");
                    ImGui::SliderInt("##int_slider", &int_value, 0, 100, "%d : Int Value");

                    ImGui::Text("Current Float Value: %f", float_value);
                    ImGui::Separator();
                    ImGui::Text("Current Int Value: %i", int_value);
                    if (ImGui::Button("(counter) Click me")) {
                        value++;
                    }
                    ImGui::SameLine();
                    ImGui::Text("Counter: %i", value);
					std::vector<const char*> items = { "item 1", "item 2","im a cool item :)","whats good" };
					ImGui::ListBox("##listbox_id", &ops::SelectedListBoxItem, items.data(), items.size());
					std::string text_data = "Current Item: ";
					text_data += items[ops::SelectedListBoxItem];
					ImGui::Text(text_data.c_str());

                    /*
					if (ImGui::BeginChild("##child_id", ImVec2(ImGui::GetWindowWidth() / 2, 70)))
                    {
                        ImGui::EndChild();
                    }
					// this also works :)
                    */

                    ImGui::BeginChild("##child_id", ImVec2(ImGui::GetWindowWidth() / 2, ImGui::GetWindowHeight() - 300), true); //true for border
                    ImGui::Text("hi from inside the child");
                    ImGui::Text("Arrow Button"); ImGui::SameLine();
                    ImGui::ArrowButton("##ArrowButton1", ImGuiDir_Down);
                    static bool active = false;
                    ImGui::RadioButton("RadioButton", &active);
                    ImGui::EndChild();
				}

                

                
                

                //================================================================
                
                auto PopupFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
                static char input[256];
                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);
				if (ImGui::BeginPopupModal("PopupTest", NULL, PopupFlags)) {
					ImGui::Text("Hi from the popup!");

                    ImGui::InputText("##input_text", input, IM_ARRAYSIZE(input));

                    ImGui::InputTextWithHint("##input_text_hint", "Im a hint", input, IM_ARRAYSIZE(input));

                    ImGui::InputTextMultiline("##input_text_multiline", input, IM_ARRAYSIZE(input), ImVec2(ImGui::GetWindowWidth() / 2, 100));

					if (ImGui::Button("close")) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
                ImGui::PopStyleVar();
            }
            ImGui::End();

			
        }
        ImGui::EndFrame();

        g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
            ResetDevice();
        }
        if (!loader_active) {
            msg.message = WM_QUIT;
        }
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    DestroyWindow(main_hwnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            g_d3dpp.BackBufferWidth = LOWORD(lParam);
            g_d3dpp.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}