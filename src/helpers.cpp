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

#include "helpers.h"

namespace RotatoExpress
{
	vr::HmdMatrix34_t helpers::vrRotMatMul(const vr::HmdMatrix34_t& m1, const vr::HmdMatrix33_t& m2)
	{
		vr::HmdMatrix34_t result{};
		//for each row in m1
		for (int row = 0; row < 3; row++)
		{
			float row_v0 = m1.m[row][0];
			float row_v1 = m1.m[row][1];
			float row_v2 = m1.m[row][2];

			//for each column in m2
			for (int column = 0; column < 3; column++)
			{
				float col_v0 = m2.m[0][column];
				float col_v1 = m2.m[1][column];
				float col_v2 = m2.m[2][column];

				result.m[row][column] = (row_v0 * col_v0) + (row_v1 * col_v1) + (row_v2 * col_v2);
			}
		}

		return result;
	}

	glm::mat4 helpers::GetRotationMatrixFromHMDMatrix(const vr::HmdMatrix34_t& m)
	{
		glm::vec4 row0(m.m[0][0], m.m[0][1], m.m[0][2], 0);
		glm::vec4 row1(m.m[1][0], m.m[1][1], m.m[1][2], 0);
		glm::vec4 row2(m.m[2][0], m.m[2][1], m.m[2][2], 0);
		glm::vec4 row3(0, 0, 0, 1);
		return { row0, row1, row2, row3 };
	}
}