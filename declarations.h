#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <string>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include "bass.h"
using namespace std;

/* ENUM */

enum Color { BLACK, DARK_BLUE, DARK_GREEN, DARK_TURQUOISE, DARK_RED, PURPLE,
             DARK_YELLOW, LIGHT_GRAY, GRAY, BLUE, GREEN, TURQUOISE, RED, PINK,
             YELLOW, WHITE }; // ЏҐаҐзЁб«Ґ­ЁҐ ¤«п гбв ­®ўЄЁ жўҐв  ў дг­ЄжЁЁ color()

/* Variables */
HANDLE consoleOutput;	// Хэндл вывода консоли
HANDLE consoleInput;	// Хэндл ввода	консоли

COORD cursorPos;		// Координаты курсора


int mode;		/// Выбр нный режим игры
/*- 1 - Человек против CPU
    2 - CPU против CPU -*/
bool alreadyPlay = false;	// Музыка уже воспроизводится?
bool loaded = false;		// Начата новая игра  или загружается старая?
char ranks[17][40];
// Параметры
bool sounds;
bool music;
int delay;					// Задержка между атаками компьютера

/*-----------------*/

/* Classes and structures*/

struct highscore
{
    int score;
    char nickname[17];

    bool record;		// Данный результат является последним записаным?
} hslist[6];

struct Coord
{
    int x, y;
    bool ESC;	//
};

class Player
{
public:
    int x, y;			// Координаты нахождения карты на консоли

    string nickname;	// Имя/Никнейм игрока
    int remain;			// Количество оставшихся кораблей
    int score;			// Счет игрока
    int damaged;		// Кол-во поврежденных частей
    int miss;			// Кол-во промахов

    bool cpu;			// Игрок человек или компьютер?
    int map[10][10];	// Карта игрока

    Player(int _x, int _y)
        : x(_x), y(_y), remain(20)
    { score = damaged = miss = 0;

    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            map[i][j] = 0;
    }

    void scrChange(bool hit); // Изменение счета в зависимости от попаданий
    void printMap();		  // Вывод карты
    void generateMap();	// Генерировать карту если это компьютер
    bool createMap();	// Создать карту если это человек

    int atackCPU(Player *pl);	// Атака, Если это компьютер.
    int atackHum(Player *pl);	// Атака, Если это человек
                                // Функции возвращают оставшееся количество
                                // кораблей противника

} p1(6, 3), p2(44, 3);

class User
{
    bool occupied;		// З нят  ли переменн я
public:
    int win2increasing;	// Побед до следующего зв ния

    char nickname[17];	// Никнейм
    int wins;			// Побед
    int lose;			// Проигрышей
    int rank;			// Текущее зв ние

    User() { occupied = false; nickname[0] = wins = lose = rank = 0; win2increasing = 5;}
    friend void load_userBase();
    friend void save_userBase();
    friend void put2base(bool win);
    friend void showUsers();
} userBase[256];

/* Functions */
void menu();											// Меню
int Play(HSTREAM &menuMusic, HCHANNEL &sound);			// Н ч ть игру
void setcursor(int X, int Y);							// Установка положения курсор  в консоли
void printSymb(int symbol, int times);					// К кой символ, и сколько р з вывести
void printPart(int type, bool horiz, int X, int Y);		// Вывод корабля. ук зыв ется количество з ним емых клеток, и проверяется н  Горизонтальность
void setcolor(Color Text, Color Background);			// Упрощение установки цвет
void printCenter(char *Text, int Y);					// Вывод текст  по центру
bool inputName(int X, int Y);							// Ввод имени игрок
int ingameMenu();										// Внутриигровое Меню
void mkFrame(int height, int width, int X, int Y);		// Созд ние р мки
void screen();											// Восст новление\вывод н  консоль
void load_userBase();									// З грузк  б зы пользов телей
void save_userBase();									// Выгрузк  б зы пользов телей
void playerState( bool win );							// Вывод сообщения о проигрыше\выигрыше и сохр нение б зы пользов телей
void put2base(bool win);								// Помещение результ т  игры игрок  в б зу
void showUsers();										// Вывести всех пользов телей игр вших в эту игру
void BlackMesa();										// П сх льное яйцо в виде эмблемы Black Mesa
void clearAll();                                        // Вернуть всё к исходному состоянию
Coord coord_input();                                    // Ввод Координат
void drawSettingWindow();                               // Перерисовать окно настроек

 // Menu entries
bool load(bool from_menu);				// З грузить игру
void new_game();			// Нов я игр
void save();
void records();
void about();		// Р зр ботк  н ч т  19.07
void settings();


#endif // DECLARATIONS_H
