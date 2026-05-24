#ifndef PASSWORD_MANAGER_GUI_H
#define PASSWORD_MANAGER_GUI_H

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "Vault.h"

#include <string>

using namespace std;

enum class AppState {
    Init,
    Login,
    Entries,
    AddEntry,
    RemoveEntry
};

class Gui {
    private:
        AppState state;
        Vault& vault;

        char vaultNameInput[128] = {};
        char initVaultKeyInput[256] = {};
        char initVaultKeyConfirmInput[256] = {};
        char loginVaultKeyInput[256] = {};
        char entryServiceInput[256] = {};
        char entryUsernameInput[128] = {};
        char entryLoginInput[256] = {};
        char entryPasswordInput[256] = {};

        string errorMessage;
        string successMessage;

        void renderInit();
        void renderLogin();
        void renderEntries();
        void renderAddEntry();
        void renderRemoveEntry();

        void handleLoginInput(string vaultKey);

    public:
        Gui(Vault& vault);
        ~Gui();

        void render();

};

#endif //PASSWORD_MANAGER_GUI_H