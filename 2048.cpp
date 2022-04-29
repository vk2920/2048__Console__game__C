#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "menu.h"

#define _menu_items_count 4
const char* _menu_items_array[_menu_items_count] = {
    "Новая игра",
    "Продолжить последнюю игру",
    "Таблица рекордов",
    "Выйти из игры"
};

/// <summary>
/// Функция-заглушка (организация процесса игры)
/// </summary>
/// <param name="_fields">Массив с игровым полем (4x4)</param>
/// <returns>Результат работы функции</returns>
int play(int _fields[4][4]) {
    system("cls");
    printf("+------+------+------+------+\n");
    for (int _i = 0; _i < 4; _i++) {
        printf("|      |      |      |      |\n");
        for (int _j = 0; _j < 4; _j++) {
            if (_fields[_i][_j] > 999) printf("| %4d ", _fields[_i][_j]);
            else printf("|  %2d  ", _fields[_i][_j]);
        }
        printf("|\n|      |      |      |      |\n+------+------+------+------+\n");
    }
    int _key1 = _getch();
    int _key2 = _getch();

    if (_key1 == 224) {
        switch (_key2) {
            case 72: // Up
            {
                break;
            }
            case 75: // Left
            {
                break;
            }
            case 77: // Right
            {
                break;
            }
            case 80: // Down
            {
                break;
            }
        }
    }
    else {
        if (_key1 == 13) {

        }
    }

    return 1;
}

/// <summary>
/// Функция для инициализации нового игрового поля и начала новой игры
/// </summary>
/// <param name="_fields">Массив с игровым полем (4x4)</param>
/// <returns>Результат работы функции</returns>
int start_new_game(int _fields[4][4]) {
    // Выйдем в случае проблем с памятью
    if (!_fields)
        return 0;

    // Опустошим игровове поле
    for (int _i = 0; _i < 4; _i++)
    {
        for (int _j = 0; _j < 3; _j++)
        {
            if (_fields[_i][_j] != 0)
            {
                _fields[_i][_j] = 0;
            }
        }
    }

    // Сделаем случайную инициализацию
    srand(time(NULL));
    if (rand() % 2) {
        int _init_variant = rand() % 24;
        int _init_row = _init_variant / 6;
        int _init_row_config = _init_variant % 6;
        switch (_init_row_config) {
            case 0: // 2--2
            {
                _fields[_init_row][0] = 2;
                _fields[_init_row][3] = 2;
                break;
            }
            case 1: // -2-2
            {
                _fields[_init_row][1] = 2;
                _fields[_init_row][3] = 2;
                break;
            }
            case 2: // --22
            {
                _fields[_init_row][2] = 2;
                _fields[_init_row][3] = 2;
                break;
            }
            case 3: // -22-
            {
                _fields[_init_row][1] = 2;
                _fields[_init_row][2] = 2;
                break;
            }
            case 4: // 2-2-
            {
                _fields[_init_row][0] = 2;
                _fields[_init_row][2] = 2;
                break;
            }
            case 5: // 22--
            {
                _fields[_init_row][0] = 2;
                _fields[_init_row][1] = 2;
                break;
            }
        }
    }
    else {
        int _init_variant = rand() % 24;
        int _init_col = _init_variant / 6;
        int _init_col_config = _init_variant % 6;
        switch (_init_col_config) {
            case 0: // 2--2
            {
                _fields[0][_init_col] = 2;
                _fields[3][_init_col] = 2;
                break;
            }
            case 1: // -2-2
            {
                _fields[1][_init_col] = 2;
                _fields[3][_init_col] = 2;
                break;
            }
            case 2: // --22
            {
                _fields[2][_init_col] = 2;
                _fields[3][_init_col] = 2;
                break;
            }
            case 3: // -22-
            {
                _fields[1][_init_col] = 2;
                _fields[2][_init_col] = 2;
                break;
            }
            case 4: // 2-2-
            {
                _fields[0][_init_col] = 2;
                _fields[2][_init_col] = 2;
                break;
            }
            case 5: // 22--
            {
                _fields[0][_init_col] = 2;
                _fields[1][_init_col] = 2;
                break;
            }
        }
    }

    // Запустим игру
    return play(_fields);
}

/// <summary>
/// Функция для проверки, отсутствует ли начатая (неоконченная) игра
/// </summary>
/// <param name="_fields">Массив с игровым полем (4x4)</param>
/// <returns>Результат работы функции</returns>
int game_finished(int _fields[4][4])
{
    for (int _i = 0; _i < 3; _i++)
    {
        for (int _j = 0; _j < 3; _j++)
        {
            if (_fields[_i][_j] != 0)
            {
                return 0;
            }
        }
    }
    return 1;
}

/// <summary>
/// Функция для созранения игры в файл (перезаписывает предыдущее сохранение)
/// </summary>
/// <param name="_fields">Массив с игровым полем (4x4)</param>
/// <param name="_last_game">Указатель на файл для сохранения</param>
/// <returns>Результат работы функции</returns>
int save_game(int _fields[4][4], FILE* _last_game)
{
    if (!_fields || !_last_game)
        return 0;
    
    if (fwrite(_fields, sizeof(int), 16, _last_game) == 16)
        return 1;

    return 0;
}

/// <summary>
/// Функция для загрузки игры из файла
/// </summary>
/// <param name="_last_game">Указатель на файл с игрой</param>
/// <param name="_fields">Массив 4x4 с игровым полем</param>
/// <returns>Результат работы функции</returns>
int load_game(FILE* _last_game, int _fields[4][4])
{
    if (!_fields || !_last_game)
        return 0;
    
    if (fread(_fields, sizeof(int), 16, _last_game) == 16)
        return play(_fields);

    return 0;
}

/// <summary>
/// Главная функция программы
/// </summary>
/// <returns>Код выхода</returns>
int main() {
    FILE* laderboard_file = NULL;
    FILE* last_game = NULL;
    int fields[4][4];

    for (int _i = 0; _i < 4; _i++)
    {
        for (int _j = 0; _j < 4; _j++)
        {
            if (fields[_i][_j] != 0)
            {
                fields[_i][_j] = 0;
            }
        }
    }

    SetConsoleOutputCP(1251);
    while (1) {
        switch (select_from_menu(_menu_items_array, _menu_items_count, _menu_items_count - 1))
        {
        case 0: // Новая игра
        {
            system("cls");

            for (int _i = 0; _i < 4; _i++)
            {
                for (int _j = 0; _j < 4; _j++)
                {
                    if (fields[_i][_j] != 0)
                    {
                        fields[_i][_j] = 0;
                    }
                }
            }

            start_new_game(fields);

            break;
        }
        case 1: // Продолжить последнюю игру
        {
            system("cls");
        }
        case 2: // Таблица рекордов
        {
            system("cls");

            break;
        }
        case 3: // Выйти из игры
        {
            system("cls");
            if (!game_finished(fields))
            {
                last_game = fopen("last_game.dat", "wb+");
                if (!save_game(fields, last_game)) {
                    printf("Ошибка сохранения игры. Вы уверены, что хотите выйти? [ Y / N ] ");
                    int _flag;
                    while (1) {
                        int _a = _getch();
                        if (_a == 121 || _a == 173) {
                            _flag = 1;
                            break;
                        }
                        else if (_a == 110 || _a == 226) {
                            _flag = 0;
                            break;
                        }
                    }
                    if (_flag) {
                        fclose(laderboard_file);
                        fclose(last_game);
                        return 0;
                    }
                    else break;
                }
                fclose(laderboard_file);
                fclose(last_game);
                return 0;
            }
        }
        }
    }
}