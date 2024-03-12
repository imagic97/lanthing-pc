/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2023 Zhennan Tu <zhennan.tu@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <string>
#include <vector>

namespace ltlib {

std::string getProgramFullpath();

std::string getProgramPath();

std::string getProgramName();

std::string getConfigPath(bool is_service = false);

bool isRunasLocalSystem();
bool isRunAsService();

int32_t getScreenWidth();
int32_t getScreenHeight();

struct DisplayOutputDesc {
    DisplayOutputDesc() = delete;
    DisplayOutputDesc(uint32_t w, uint32_t h, uint32_t f, uint32_t r)
        : width(w)
        , height(h)
        , frequency(f)
        , rotation(r) {}
    int32_t width;
    int32_t height;
    int32_t frequency;
    int32_t rotation;
};
DisplayOutputDesc getDisplayOutputDesc(const std::string& name);

bool changeDisplaySettings(uint32_t w, uint32_t h, uint32_t f);

bool setThreadDesktop();

bool selfElevateAndNeedExit();

struct Monitor {
    int32_t left;
    int32_t top;
    int32_t right;
    int32_t bottom;
    int32_t width;
    int32_t height;
    int32_t rotation;
    int32_t frequency;
    std::string name;
};

std::vector<Monitor> enumMonitors();

void openFolder(const std::string& path);

} // namespace ltlib