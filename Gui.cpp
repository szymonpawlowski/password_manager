#include "Gui.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "Vault.h"

#include <filesystem>

using namespace std;

Gui::Gui(Vault& vault): vault(vault) {
    state = filesystem::exists("vault.json") ? AppState::Login : AppState::Init;

} ;

Gui::~Gui() {

};

void Gui::render() {
    ImGuiIO& io = ImGui::GetIO();

    ImVec2 windowSize = io.DisplaySize;
    ImVec2 windowPos(0, 0);

    ImGui::SetNextWindowSize(windowSize, ImGuiCond_Always);
    ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar;


    ImGui::Begin("Password Manager", nullptr, flags);

    switch (state) {
        case AppState::Init: renderInit(); break;
        case AppState::Login: renderLogin(); break;
        case AppState::Entries: renderEntries(); break;
        case AppState::AddEntry: renderAddEntry(); break;
        case AppState::RemoveEntry: renderRemoveEntry(); break;
        default: break;
    }

    ImGui::End();
}

void Gui::renderInit() {
    ImGui::InputText("Username", vaultNameInput, sizeof(vaultNameInput));
    ImGui::InputText("Password", initVaultKeyInput, sizeof(initVaultKeyInput), ImGuiInputTextFlags_Password);
    ImGui::InputText("Confirm password", initVaultKeyConfirmInput, sizeof(initVaultKeyConfirmInput), ImGuiInputTextFlags_Password);

    if (ImGui::Button("Initialize Vault")) {
        if (vault.initializeVault(vaultNameInput, initVaultKeyInput, initVaultKeyConfirmInput)) {
            state = AppState::Entries;
        } else {
            errorMessage = "Vault initialization error";
        }
    }
}

void Gui::renderLogin() {
    ImGui::Text("Login into %s", vault.getVaultName().c_str());
    ImGui::InputText("Password", loginVaultKeyInput, sizeof(loginVaultKeyInput), ImGuiInputTextFlags_Password);

    if (ImGui::Button("Log in")) {
        if (vault.unlockVault(loginVaultKeyInput)) {
            state = AppState::Entries;
        } else {
            errorMessage = "Wrong password";
        }
    }
}

void Gui::renderEntries() {
    ImGui::Text("Entries menu WIP");
}


void Gui::renderAddEntry() {
    ImGui::Text("Add new entry menu WIP");
}

void Gui::renderRemoveEntry() {
    ImGui::Text("Remove entry menu WIP");
}
