#include <iostream>
#include <windows.h>

#define NAME_CLASS "TibiaClient"

struct address {
    uint32_t health = 0x063FE94;
    uint32_t mana = 0x063FE78;
    uint32_t level = 0x063FE88;
};

int main(void)
{
    HWND window = FindWindowA(NAME_CLASS, 0);
    if (!window) {
        MessageBoxA(0, "Desculpe mas não foi possivel localizar a janela do tibia.", "Tibia Info", 0);
        return 0;
    }

    DWORD id_process;
    GetWindowThreadProcessId(window, &id_process);
    if (id_process <= 0) {
        MessageBoxA(0, "Falha ao obter o ID do processo.", "Tibia Info", 0);
        return 0;
    }

    HANDLE handle = OpenProcess(0x10, true, id_process);
    if (!handle) {
        MessageBoxA(0, "Falha ao abrir o processo.", "Tibia Info", 0);
        return 0;
    }

    uint16_t health;
    uint16_t mana;
    uint32_t level;

    address address;

    while (true) {
        std::system("cls");
        ReadProcessMemory(handle, (LPVOID)address.health, &health, sizeof(health), 0);
        ReadProcessMemory(handle, (LPVOID)address.mana, &mana, sizeof(mana), 0);
        ReadProcessMemory(handle, (LPVOID)address.level,  &level, sizeof(level), 0);
        std::cout << "HEALTH: " << health << " / MANA: " << mana << " / LEVEL: " << level << std::endl;
    }

    return 0;
}

