        #ifndef IMGUI_UNITY_TOUCH_MENU_HPP
#define IMGUI_UNITY_TOUCH_MENU_HPP

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <imgui.h>
#include <imgui_impl_android.h>
#include <imgui_impl_opengl3.h>
#include <unistd.h>
#include "Misc/log.h"

namespace MENU {
    int (*GlWidth)();
    int (*GlHeight)();

    bool clearMouse = true, setup = false, dark;
    bool open = true;

    // --- ПЕРЕМЕННЫЕ ЧИТА ---
    // ESP
    bool espEnabled = false;
    bool espBox = true;
    bool espLine = false;
    bool espName = true;
    bool espDistance = true;

    // Aimbot
    bool aimbotEnabled = false;
    bool aimbotVisCheck = true;
    float aimbotFov = 90.0f;
    float aimbotSmooth = 5.0f;
    int selectedBone = 0; // 0 - Голова, 1 - Тело

    // Разное
    bool speedHack = false;
    float playerSpeed = 1.0f;

    void Setup() {
        if (setup) return;
        
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        
        ImGui::StyleColorsDark();
        ImGuiStyle& style = ImGui::GetStyle();
        style.ScaleAllSizes(3.0f); // Увеличиваем элементы под пальцы на телефоне
        
        setup = true;
    }

    void Draw() {
        if (!setup) {
            Setup();
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplAndroid_NewFrame(GlWidth ? GlWidth() : 1920, GlHeight ? GlHeight() : 1080);
        ImGui::NewFrame();

        if (open) {
            ImGui::SetNextWindowSize(ImVec2(650, 450), ImGuiCond_FirstUseEver);
            ImGui::Begin("StandChillow | Mod Menu", &open, ImGuiWindowFlags_NoSavedSettings);

            ImGui::Text("Status: Active | By User");
            ImGui::Separator();

            // Вкладки интерфейса
            if (ImGui::BeginTabBar("ModTabs")) {
                
                // Вкладка Визуалов (ESP)
                if (ImGui::BeginTabItem("ESP")) {
                    ImGui::Checkbox("Enable ESP", &espEnabled);
                    if (espEnabled) {
                        ImGui::Separator();
                        ImGui::Checkbox("Box ESP", &espBox);
                        ImGui::Checkbox("Line ESP", &espLine);
                        ImGui::Checkbox("Name ESP", &espName);
                        ImGui::Checkbox("Distance ESP", &espDistance);
                    }
                    ImGui::EndTabItem();
                }

                // Вкладка Аимбота
                if (ImGui::BeginTabItem("Aimbot")) {
                    ImGui::Checkbox("Enable Aimbot", &aimbotEnabled);
                    if (aimbotEnabled) {
                        ImGui::Separator();
                        ImGui::Checkbox("Visible Check", &aimbotVisCheck);
                        ImGui::SliderFloat("FOV Radius", &aimbotFov, 10.0f, 360.0f);
                        ImGui::SliderFloat("Smoothness", &aimbotSmooth, 1.0f, 20.0f);
                        
                        ImGui::Text("Target Bone:");
                        ImGui::RadioButton("Head", &selectedBone, 0); ImGui::SameItem();
                        ImGui::RadioButton("Chest", &selectedBone, 1);
                    }
                    ImGui::EndTabItem();
                }

                // Вкладка Дополнительно
                if (ImGui::BeginTabItem("Misc")) {
                    ImGui::Checkbox("Speedhack", &speedHack);
                    if (speedHack) {
                        ImGui::SliderFloat("Speed Multiplier", &playerSpeed, 1.0f, 5.0f);
                    }
                    ImGui::EndTabItem();
                }

                ImGui::EndTabBar();
            }

            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

#endif
