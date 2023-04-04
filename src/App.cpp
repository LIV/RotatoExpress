/*
 *	MIT License
 *
 * Copyright (c) 2019-2023 LIV Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer.h"

#include "App.h"
#include "helpers.h"

#define FMTFLOAT "%.2f"

namespace RotatoExpress
{
	int App::run()
	{
		while (running)
		{
			update();
			draw();
		}

		restoreLaunchPlayArea();
		cleanup();

		return 0;
	}

	void App::setup()
	{
		SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO);
		window = SDL_CreateWindow("LIV RotatoExpress v0.3",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			380, 170,
			0);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

#pragma region style
		auto& colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_WindowBg] = ImVec4{ 0.095f, 0.047f, 0.17f, 1.0f };
		colors[ImGuiCol_MenuBarBg] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };

		// Border
		colors[ImGuiCol_Border] = ImVec4{ 0.44f, 0.37f, 0.61f, 0.29f };
		colors[ImGuiCol_BorderShadow] = ImVec4{ 0.0f, 0.0f, 0.0f, 0.24f };

		// Text
		colors[ImGuiCol_Text] = ImVec4{ 0.0f, 1.0f, .105f, 1.0f };
		colors[ImGuiCol_TextDisabled] = ImVec4{ 0.5f, 0.5f, 0.5f, 1.0f };

		// Headers
		colors[ImGuiCol_Header] = ImVec4{ 0.13f, 0.13f, 0.17, 1.0f };
		colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
		colors[ImGuiCol_HeaderActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };

		// Buttons
		colors[ImGuiCol_Button] = ImVec4{ 0.13f, 0.13f, 0.17, 1.0f };
		colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
		colors[ImGuiCol_ButtonActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
		colors[ImGuiCol_CheckMark] = ImVec4{ 0.74f, 0.58f, 0.98f, 1.0f };

		// Popups
		colors[ImGuiCol_PopupBg] = ImVec4{ 0.1f, 0.1f, 0.13f, 0.92f };

		// Slider
		colors[ImGuiCol_SliderGrab] = ImVec4{ 0.44f, 0.37f, 0.61f, 0.54f };
		colors[ImGuiCol_SliderGrabActive] = ImVec4{ 0.74f, 0.58f, 0.98f, 0.54f };

		// Frame BG
		colors[ImGuiCol_FrameBg] = ImVec4{ 0.13f, 0.13, 0.17, 1.0f };
		colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
		colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };

		// Tabs
		colors[ImGuiCol_Tab] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
		colors[ImGuiCol_TabHovered] = ImVec4{ 0.24, 0.24f, 0.32f, 1.0f };
		colors[ImGuiCol_TabActive] = ImVec4{ 0.2f, 0.22f, 0.27f, 1.0f };
		colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };

		// Title
		colors[ImGuiCol_TitleBg] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
		colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };

		// Scrollbar
		colors[ImGuiCol_ScrollbarBg] = ImVec4{ 0.1f, 0.1f, 0.13f, 1.0f };
		colors[ImGuiCol_ScrollbarGrab] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4{ 0.24f, 0.24f, 0.32f, 1.0f };

		// Seperator
		colors[ImGuiCol_Separator] = ImVec4{ 0.44f, 0.37f, 0.61f, 1.0f };
		colors[ImGuiCol_SeparatorHovered] = ImVec4{ 0.74f, 0.58f, 0.98f, 1.0f };
		colors[ImGuiCol_SeparatorActive] = ImVec4{ 0.84f, 0.58f, 1.0f, 1.0f };

		// Resize Grip
		colors[ImGuiCol_ResizeGrip] = ImVec4{ 0.44f, 0.37f, 0.61f, 0.29f };
		colors[ImGuiCol_ResizeGripHovered] = ImVec4{ 0.74f, 0.58f, 0.98f, 0.29f };
		colors[ImGuiCol_ResizeGripActive] = ImVec4{ 0.84f, 0.58f, 1.0f, 0.29f };

		// Docking
		//colors[ImGuiCol_DockingPreview] = ImVec4{0.44f, 0.37f, 0.61f, 1.0f};

		auto& style = ImGui::GetStyle();
		style.TabRounding = 4;
		style.ScrollbarRounding = 9;
		style.WindowRounding = 7;
		style.GrabRounding = 3;
		style.FrameRounding = 3;
		style.PopupRounding = 4;
		style.ChildRounding = 4;

#pragma endregion

		ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
		ImGui_ImplSDLRenderer_Init(renderer);

		vr::EVRInitError error = vr::VRInitError_None;
		vr::VR_Init(&error, vr::VRApplication_Utility);
		if (error != vr::VRInitError_None) {
			vrEnabled = false;
			std::cout << "No VR" << std::endl;
		}
	}

	void App::update()
	{
		SDL_Event e{};
		while (SDL_PollEvent(&e))
		{
			ImGui_ImplSDL2_ProcessEvent(&e);
			switch (e.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			default:
				break;
			}
		}

		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		auto& io = ImGui::GetIO();
		ImGui::SetNextWindowPos({ 0,0 });
		ImGui::SetNextWindowSize(io.DisplaySize);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
		ImGui::Begin("One window to rulez y'all", nullptr, ImGuiWindowFlags_NoDecoration);
		ImGui::SliderFloat("Speed (dpt)", &speedVal, -1, 1, FMTFLOAT);
		ImGui::Checkbox("Lock to Zero", &lockIdentityRotation);
		ImGui::Checkbox("Seated Mode", &seatedMode);
		ImGui::SliderFloat("X Offset", &xOffsetVal, -3, 3, FMTFLOAT);
		ImGui::SliderFloat("Y Offset", &yOffsetVal, -3, 3, FMTFLOAT);
		ImGui::SliderFloat("Z Offset", &zOffsetVal, -3, 3, FMTFLOAT);
		if (ImGui::Checkbox("Stay on top", &alwaysOnTop))
			SDL_SetWindowAlwaysOnTop(window, alwaysOnTop ? SDL_TRUE : SDL_FALSE);
		ImGui::End();
		ImGui::PopStyleVar();

		if (vrEnabled)
		{
			if (SDL_GetTicks64() < lastTickTime + 1000 / 120)
				return;

			lastTickTime = SDL_GetTicks64();
			vr::HmdMatrix34_t currentPlayArea{};

			if (seatedMode)
				vr::VRChaperoneSetup()->GetWorkingSeatedZeroPoseToRawTrackingPose(&currentPlayArea);
			else
				vr::VRChaperoneSetup()->GetWorkingStandingZeroPoseToRawTrackingPose(&currentPlayArea);

			//Waiting 15 frames since to do the trick to make sure everything is setup. This is what old version of Rotato did anyways.
			if (framecount++ == 15) [[unlikely]]
			{
				launchPlayArea = currentPlayArea;
				launchPlayAreaSet = true;
			}

			if (!launchPlayAreaSet)
				return;

			const auto playAreaGlm = helpers::GetRotationMatrixFromHMDMatrix(currentPlayArea);
			auto playAreaNewGlm = glm::rotate(playAreaGlm, glm::radians(speedVal), glm::vec3(0, 1, 0));
			if (lockIdentityRotation)
				playAreaNewGlm = glm::identity<glm::mat4>();

			vr::HmdMatrix34_t playAreaNew = currentPlayArea;

			memcpy(playAreaNew.m, glm::value_ptr(playAreaNewGlm), sizeof(float) * 12);
			playAreaNew.m[0][3] = launchPlayArea.m[0][3] + xOffsetVal;
			playAreaNew.m[1][3] = launchPlayArea.m[1][3] + yOffsetVal;
			playAreaNew.m[2][3] = launchPlayArea.m[2][3] + zOffsetVal;

			if (seatedMode)
				vr::VRChaperoneSetup()->SetWorkingSeatedZeroPoseToRawTrackingPose(&playAreaNew);
			else
				vr::VRChaperoneSetup()->SetWorkingStandingZeroPoseToRawTrackingPose(&playAreaNew);
			vr::VRChaperoneSetup()->CommitWorkingCopy(vr::EChaperoneConfigFile::EChaperoneConfigFile_Live);
		}
	}

	void App::draw() {
		ImGui::Render();

		if (SDL_GetTicks64() > lastRenderTickTime + 1000 / 240)
		{
			SDL_RenderClear(renderer);
			ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
			SDL_RenderPresent(renderer);
			lastRenderTickTime = SDL_GetTicks64();
		}

		SDL_Delay(1);
	}

	void App::cleanup()
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	void App::restoreLaunchPlayArea()
	{
		if (launchPlayAreaSet)
		{
			if (seatedMode)
				vr::VRChaperoneSetup()->SetWorkingSeatedZeroPoseToRawTrackingPose(&launchPlayArea);
			else
				vr::VRChaperoneSetup()->SetWorkingStandingZeroPoseToRawTrackingPose(&launchPlayArea);
			vr::VRChaperoneSetup()->CommitWorkingCopy(vr::EChaperoneConfigFile::EChaperoneConfigFile_Live);
		}
	}
}
