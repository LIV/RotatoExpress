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

#pragma once

#include "SDL.h"
#include "openvr.h"

namespace RotatoExpress
{
class App
{
public:
	int run();

	void setup();
	void update();
	void draw();
	void cleanup();

	void restoreLaunchPlayArea();

	bool lockIdentityRotation = true;
	bool seatedMode = false;

	float xOffsetVal = 0;
	float yOffsetVal = 0;
	float zOffsetVal = 0;
	float speedVal = 0;
	bool alwaysOnTop = false;

	bool vrEnabled = true;
	uint64_t lastTickTime = 0;
	uint64_t lastRenderTickTime = 0;

	bool launchPlayAreaSet = false;
	vr::HmdMatrix34_t launchPlayArea;
	bool running = true;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	uint64_t framecount = 0;
};
}
