#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef printf
#include <stdio.h>
#endif

#if !defined(HANDLE) || !defined(system)
#include <windows.h>
#endif

#ifndef _getch
#include <conio.h>
#endif

#include "menu.h"

/// <summary>
/// Ôóíêöèÿ äëÿ îïðåäåëåíèÿ ðàçìåðîâ îêíà êîíñîëè
/// </summary>
/// <returns></returns>
int* get_size() {
    int* res = (int*)calloc(3, sizeof(int));
    if (!res) return NULL;
    HANDLE hWndConsole;
    if (hWndConsole = GetStdHandle(-12)) {
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo)) {
            res[1] = consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
            res[2] = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
        }
        else res[0] = GetLastError();
    }
    else res[0] = GetLastError();
    return res;
}

/// <summary>
/// Ïðîñòàÿ ôóíêöèÿ äëÿ òåñòèðîâàíèÿ ââîäà ïðè ïîìîùè _getch()
/// Èñïîëüçóåòñÿ äëÿ îïðåäåëåíèÿ êîäîâ, ïîñûëàåìûõ êëàâèøàìè êëàâèàòóðû.
/// </summary>
/// <returns></returns>
int test_input() {
    for (int _i = 0; _i < 200; _i++) printf("%d ", _getch());
    return 0;
}

/// <summary>
/// Êàêèå ñòðîêè äîêóìåíòàöèè? Ýòî çàñåêðå÷åííàÿ ôóíêöèÿ
/// </summary>
void start_egg() {
    system("cls");
    FILE* egg = fopen("egg.txt", "rt");
    if (!egg) return;
    char* c = (char*)malloc(1024 * sizeof(char));
    if (c) {
        c[1023] = '\0';
        while (fread(c, sizeof(char), 1023, egg))
            printf("%s", c);
    }
    printf("\n");
    Sleep(2000);
}

/// <summary>
/// Ôóíêöèÿ äëÿ èíòåðàêòèâíîãî âûáîðà äåéñòâèÿ
/// </summary>
/// <param name="_menu">Ìàññèâ C-ñòðîê ñ íàçâàíèÿìè äåéñòâèé</param>
/// <param name="_mic">Êîëè÷åñòâî ýëåìåíòîâ ìàññèâà</param>
/// <param name="_exit_code">ID äåéñòâèÿ, èíòåðïðåòèðóåìîãî êàê âûõîä</param>
/// <returns>ID âûáðàííîãî äåéñòâèÿ</returns>
int select_from_menu(const char** _menu, const int _mic, int _exit_code) {
    int s = 0;
    int* size = get_size();
    int htab, vtab;
    const char _sep1[] = "+---------------------------------------+---------------------------------------+\n";
    const char _sep2[] = "+-  -       -       -       -       -  -+-  -       -       -       -       -  -+\n";
    while (1) {
        size = get_size();
        if (size && !size[0]) htab = (get_size()[1] - 80) / 2;
        else htab = 0;
        if (size && !size[0]) vtab = (get_size()[2] - _mic - 1) / 2;
        else vtab = 0;

        // Âûâîä ìåíþøêè
        system("cls");
        for (int _j = 0; _j < vtab; _j++) printf("\n");
        for (int _j = 0; _j < htab; _j++) printf(" ");
        printf("%s", _sep1);
        for (int _i = 0; _i < (_mic + 1) / 2; _i++) {
            for (int _j = 0; _j < htab; _j++) printf(" ");
            printf((2 * _i == s) ? "|\x1b[47;30m" : "|");
            printf("%38s \x1b[0m|", _menu[2 * _i]);
            if (2 * _i + 1 < _mic) {
                printf((2 * _i + 1 == s) ? "\x1b[47;30m" : "");
                printf(" %-38s\x1b[0m|\n", _menu[2 * _i + 1]);
            }
            else printf("                                       |\n");
            if (2 * _i + 1 != _mic) {
                for (int _j = 0; _j < htab; _j++) printf(" ");
                printf("%s", _sep2);
            }
        }
        for (int _j = 0; _j < htab; _j++) printf(" ");
        printf("%s", _sep1);

        // Èñêëþ÷èì ëîæíûå ñðàáàòûâàíèÿ
        int a = _getch();

        // 115 121 115 116 101 109
        if (a == 115 && _getch() == 121 && _getch() == 115 && _getch() == 116 && _getch() == 101 && _getch() == 109) {
            start_egg();
        }
        // 251 237 251 229 243 252
        else if (a == 251 && _getch() == 237 && _getch() == 251 && _getch() == 229 && _getch() == 243 && _getch() == 252) {
            start_egg();
        }

        else if (a == 13) { system("cls"); return s; }
        else if (a == 27 || a == 107) {
            system("cls");
            printf("Âû äåéñòâèòåëüíî õîòèòå âûéòè? [Y / Any]");
            int b = _getch();
            if (b == 121 || b == 237) return _exit_code;
            else continue;
        }

        // Ïîëó÷èì íàæàòèå êëàâèøè è èíòåðïðåòèðóåì åãî â äåéñòâèå
        else if (a == 224)
            switch (_getch()) {
            case 71: s = 0; break;                                                                   // Home
            case 79: s = _mic - 1; break;                                                            // End
            case 72: s -= 2; if (s == -2 || s == -1) s += (_mic % 2 == 0) ? _mic : _mic + 1; break;  // Up
            case 75: s -= 1; if (s == -1) s = _mic - 1; break;                                       // Left
            case 80: s += 2; if (s == _mic + 1 || s == _mic) s -= _mic; break;                       // Down
            case 77: s += 1; if (s == _mic) s = 0; break;                                            // Right
            case 107:                                                                                // <Alt+F4>
                system("cls");
                printf("Âû äåéñòâèòåëüíî õîòèòå âûéòè? [Y / <Alt+F4> / Any]");
                if (_getch() == 121 || _getch() == 107) return _exit_code;
            }

        // Íå ïîçâîëèì âûéòè çà ïðåäåëû äîïóñòèìûõ çíà÷åíèé
        if (s < 0) s = 0; else if (s >= _mic) s = _mic - 1;
    }
    free(size);
}

int menu_new(const char** _menu_item_list, const int _menu_items_count, const int _menu_columns, const int _selected_bg, const int _exit_answer) {
    return -1;
}