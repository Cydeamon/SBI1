/* ╚ёяюы№чєхЄё  ъюфшЁютър OEM866 Єръцх шчтхёЄэр  ъръ IBM866, CP866, csIBM866 */

#include "declarations.h"

#pragma comment( lib, "bass" )		// Подключение звуковой библиотеки Bass
#pragma comment( lib, "User32.lib")
/*----------- Классы -------------------------------------*/


void Player::scrChange(bool hit)	// Изменение счета игрока
{
	if( hit )
	{	
		damaged++;	
		score += 100;
	}
	else
	{
			miss++;
			score -= 20;
		
		if (score < 0) 
			score = 0;
	}	
}

void Player::generateMap()		// Генерирование карты
{
    int Y, X;		// Место в массиве для вставки корабля
    int parts;		// Количество частей
    int count;		// Счетчик для инкримента parts
    bool horiz;		// Горизонтально
	
	parts = 0;
	count = 0;

	for(int i = 0; i < 10; i++)
		for(int j = 0; j < 10; j++)
			map[i][j] = 0;

	for( int c = 0; c < 10; c++)
	{
		do
		{
			X = rand()%10;
			Y = rand()%10;
		} while( map[Y][X] == 3);	// Поиск свободной клетки

		if ((( Y < 9) && (map[Y+1][X] == 3) ) ||	
            (( Y > 0) && (map[Y-1][X] == 3) ) ||	 // Можно ли установить здесь корабль?
			(( X < 9) && (map[Y][X+1] == 3) ) ||	
			(( X > 0) && (map[Y][X-1] == 3) ))		
		{ 
			c--;
			continue;
		}
		
        //--------------- Вставка кораблей в карту-------------------*/
		
        int i;			// Для проверки наличия других кораблей
		horiz = rand()%2;	// Определение положения

		if( horiz )			
		{
			if( (parts + X) > 9 )
			{	c--; continue; }
		}
		else
		{
			if( (parts + Y) > 9 )
			{	c--; continue; }
        }							// Проверка на "вместимость"

        bool success = true;	// Проверка успешного завершения следующего цикла
		for( i = 0; i < (parts + 1); i++ )	// Нет нужды проверять если parts = 0
		{
			if( horiz )
			{
				if( ((Y < 9) && map[Y+1][X+i] == 3) ||
					((Y > 0) && map[Y-1][X+i] == 3) || map[Y][X+i+1])
						success = false;
			}
			else
			{
				if( ((X < 9) && map[Y+i][X+1] == 3) ||
					((X > 0) && map[Y+i][X-1] == 3) || map[Y+i+1][X])
						success = false;
			}
		}
        if ( !success)			// Если Проверка прошл  неуд чно
		{ c--; continue; }		// То иск ть новое место
			
        // Если все проверки прошли успешно, то можно р сположить корабль н  карте
		for(i = 0; i <= parts; i++)
		{
			if( horiz ) 
				map[Y][X+i] = 3;
			else
				map[Y+i][X] = 3;
		}
		count++;

        if( count == 4 - parts )	// Если вывелось дост точное количество кораблей
		{							// текущего тип , то...
			count = 0;				
            parts++;				// ...сменить тип корабля
		}
	}
}


int color(Color Text, Color Background)					// Получение числа, соответствующего указаному
{    return (Background * 16) + Text; }					// цвету текста и фона

/*- Создание карты игрока -*/
bool Player::createMap()
{
    int X, Y;	// X и Y недолжны выходить за рамки X и Y
    int arrX, arrY;	// Место в массиве вычесляющееся по формуле (X - X)/3, с Y делится на 2
    int parts =1;// Количество частей кораблей, которые должны выводится в данный(в цикле) момента
    int count;	// По ней определяется достигнуто ли ограничение parts'палубных кораблей
    int ships=0;// Количество кораблей

    bool ok;	// Позволена ли текущая позиция
    bool horiz = true; // Положение, если true - Горизонтально
    setcursor(x, y);   // Устанавливаем курсор в левый верхний угол.
	setcolor(WHITE, DARK_BLUE);

	X = x; Y = y;
    arrX = (X - x) / 3;		// Преобразование позиции в консоли в позицию в массиве
	arrY = (Y - y) / 2;
	count = 0;

/*-- Вспомогательные надписи --*/
	setcursor(0, 0);
	setcolor(WHITE,BLACK);
	for(int i = 0; i < 80; i++)
		cout << ' ';

    printCenter("Расстановка кораблей", 0);
	setcursor(0, 24);
	for(int i = 0; i < 80; i++)
		cout << ' ';
	setcursor(0, 0);
	setcursor(0, 24);
    cout << " Пробел - Смена положения, " << (char) 24 << (char) 25 << (char) 26 << (char) 27
         << " - Перемещение корабля, Enter - Выбрать позицию";
	for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)	// Очистк  массив
			map[i][j] = 0;

/*-- Р сст новк  кораблей --*/
	while( ships < 10)
	{	
        printMap();	// Обновляем вывод карты
		setcursor(X, Y);
		ok = true;
    /*---- Проверка н  выход з  гр ницы массив  -*/
		if( horiz) 
		{
			if( ((X - x) / 3) + (parts-1) <= 9)
			{
				for( int i = 0; i < parts; i++)
				{
					if( ((arrY > 0) && map[arrY-1][arrX + i] == 3) ||	
						((arrY < 9) && map[arrY+1][arrX + i] == 3) ||
                        ( map[arrY][arrX + i] == 3))// Если встретил сь часть корабля
						ok = false;					// то облом :) 11:03 25.07.12 Я в хорошем н строении
					
                    // Проверка есть ли д льше по Х корабль
					if( (arrX +i + 1 <= 9) && (map[arrY][arrX + i + 1] == 3))
						ok = false;

					if( (arrX > 0) && (map[arrY][arrX-1] == 3))
						ok = false;

					if( map[arrY][arrX] == 3)
						ok = false;
				}				
			}
			else 
				ok = false;

            if( ok )		// Если других кораблей не н ашлось
				{
					setcolor(GRAY, GREEN);
					
					for(int i = 0; i < parts; i++)
					{
						if(parts == 1)
							printPart(3, horiz, X + (i * 3), Y );
						else if( i == 0 )
							printPart(1, horiz, X + (i * 3), Y);
						else 
						{
							if( i != parts)
								printPart(0, horiz, X + (i * 3), Y);
							if( i == parts-1)
								printPart(2, horiz, X + (i * 3), Y);
						}
					}
					setcolor(WHITE, DARK_BLUE);
				}
                else		// Если встретил сь ошибк , но корабль помещ ется н  карте
				{
					setcolor(GRAY, RED);
					
					for(int i = 0; i < parts; i++)
					{
						if(parts == 1)
							printPart(3, horiz, X + (i * 3), Y );
						else if( i == 0 )
							printPart(1, horiz, X + (i * 3), Y);
						else 
						{
							if( i != parts)
								printPart(0, horiz, X + (i * 3), Y);
							if( i == parts-1)
								printPart(2, horiz, X + (i * 3), Y);
						}
					}
					setcolor(WHITE, DARK_BLUE);
				}
		}
	
		else // if (horiz) == false
		{
			if( ((Y - y) / 2) + (parts-1) <= 9)
			{
				for( int i = 0; i < parts; i++)
				{
					if( ((arrX > 0) && map[arrY + i][arrX-1] == 3) ||	
						((arrX < 9) && map[arrY + i][arrX+1] == 3) ||
                        ( map[arrY + i][arrX] == 3))// Если встретил сь часть корабля
						ok = false;					// то облом 
					
                    // Проверка есть ли д льше по Х корабль
					if( (arrY +i + 1 <= 9) && (map[arrY + i + 1][arrX] == 3))
						ok = false;

					if( (arrY > 0) && (map[arrY-1][arrX] == 3))
						ok = false;

					if( map[arrY][arrX] == 3)
						ok = false;
				}

				
			}
			else 
				ok = false;

            if( ok )		// Если других кораблей не н шлось
				{
					setcolor(GRAY, GREEN);
					
					for(int i = 0; i < parts; i++)
					{
						if(parts == 1)
							printPart(3, horiz, X, Y + (i * 2) );
						else if( i == 0 )
							printPart(1, horiz, X, Y + (i * 2));
						else 
						{
							if( i != parts)
								printPart(0, horiz, X, Y + (i * 2));
							if( i == parts-1)
								printPart(2, horiz, X, Y + (i * 2));
						}
					}
					setcolor(WHITE, DARK_BLUE);
				}
                else		// Если встретил сь ошибк , но корабль помещ ется н  карте
				{
					setcolor(GRAY, RED);
					
					for(int i = 0; i < parts; i++)
					{
						if(parts == 1)
							printPart(3, horiz, X, Y + (i * 2) );
						else if( i == 0 )
							printPart(1, horiz, X, Y + (i * 2));
						else 
						{
							if( i != parts)
								printPart(0, horiz, X, Y + (i * 2));
							if( i == parts-1)
								printPart(2, horiz, X, Y + (i * 2));
						}
					}
					setcolor(WHITE, DARK_BLUE);
				}
		}

        /*---------Проверка нажатых кл виш -----------*/
		
		while(  GetAsyncKeyState(VK_UP)		|| GetAsyncKeyState(VK_DOWN) ||
				GetAsyncKeyState(VK_RIGHT)  || GetAsyncKeyState(VK_LEFT) ||
				GetAsyncKeyState(VK_ESCAPE) || GetAsyncKeyState(VK_RETURN)||
                GetAsyncKeyState(VK_SPACE) ); // Защита от удерживания
		getch();

        if( GetAsyncKeyState(VK_UP) )		// Если нажата кнопка "Вверх"
		{
			if( arrY > 0)
			{
				Y -= 2;	// декриментиров ние по консоли
                --arrY;	// декриментиров ние по массиву
			}
		}
        if( GetAsyncKeyState(VK_DOWN) )		// Если нажата кнопка "Вниз"
		{
			if(  !horiz )
			{
				if(( arrY  + parts - 1 < 9))
				{
					Y += 2;
					++arrY;
				}
			}
			else if(arrY < 9)
			{
				Y += 2;
				++arrY;
			}

		}
        if( GetAsyncKeyState(VK_LEFT) )		// Если нажата кнопка "Влево"
		{
			if( arrX> 0)
			{
				X -= 3;
				--arrX;
			}
		}
        if( GetAsyncKeyState(VK_RIGHT) )	// Если нажата кнопка "Впр во"
		{
			if(horiz)
			{
				if( arrX + parts - 1< 9)
				{
					X += 3;
					++arrX;
				}
			}
			else if( arrX < 9 )
			{
				X += 3;
				++arrX;
			}
		}

        if( GetAsyncKeyState(VK_ESCAPE) ) // Если нажата кнопка [ESC]
		{
			return 0;
		}

        if( GetAsyncKeyState(VK_RETURN) ) // Если нажата кнопка Enter
		{
			if( ok )
			{
				if(horiz)
					for(int i = 0; i < parts; i++)
						map[arrY][arrX+i] = 3;
				else
					for(int i = 0; i < parts; i++)
						map[arrY+i][arrX] = 3;
					
				ships++;
				count++;
							
				X = x;
				Y = y;

				arrX = 0;
				arrY = 0;

				printMap();
			}


		}

		if( GetAsyncKeyState(VK_SPACE) )
		{
 			if( horiz )
			{
				if( arrY + (parts-2) < 9)
					horiz = false;
			}
			else if (arrX + (parts-2) < 9)
					horiz = true;
		}
		
    /*----- Увеличение частей кораблей ---*/
		if (count == 5 - parts)
		{
			count = 0;		
			parts++;
		}
	}

	return true;
}

/*----------------------------*/
int main()
{
    ::SetConsoleTitleA("Sea Battle By I1");
	consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);	// Получение хэндл  вывод  консоли
	srand(time(0));

	if (HIWORD(BASS_GetVersion())!=BASSVERSION) 
	{
        MessageBoxA (NULL, "╬°шсър тхЁёшш BASS.", "ю°шяър", 0);	// Проверка соответствия версии
        return 1;
	}

	if( !BASS_Init(-1, 44100, BASS_DEVICE_3D, 0, NULL))
	{
        MessageBoxA(NULL, "╬°шсър шэшЎшрышчрЎшш BASS", "╬°шяър", 0);
		return 1;
	}

	HSTREAM menuMusic = BASS_StreamCreateFile( false, "sounds/menu.mp3", 0, 0, // Созд ние
							BASS_SAMPLE_LOOP);						// дискриптор  поток 

    if( !menuMusic )
	{
         MessageBoxA(NULL, "╬°шсър ёючфрэш  фшёъЁшяЄюЁр яюЄюър", "ю°шяър", NULL);
		exit(1);
    }

    /*- Занесение званий в память -*/
	ifstream in ("data/ranks.dat");

    for(int i = 0; !in.eof(); i++)
    {
        in >> ranks[i];

        for(int j = 0; ranks[i][j] ; j++)
            if(ranks[i][j] == '_')
               ranks[i][j]  = ' ';
    }
    /*- Загрузка б зы пользов телей */
	load_userBase();
	
    /*- Загрузка н строек -*/
	ifstream set ("data/settings.dat");
	set >> music >> sounds >> delay;

    /*- Загрузка рекордов -*/
	ifstream hs ("data/highscore.dat");

	for(int i = 0; i < 6; i++)
	{
		hs >> hslist[i].nickname >> hslist[i].score;
	}
	
    if ( !music )				// Если в настройках указано что музыка не должна играть
        alreadyPlay = true;		// То сделать так чтобы она не играла

	if( !alreadyPlay )							// Если не воспроизводится
	{
		alreadyPlay = true;	
        BASS_ChannelPlay(menuMusic, true);		// Начало воспроизведения
	}

	while(true)
	{
        menu();	// В цикле оно для того чтобы юзер мог вернуться в меню
	}

	return 0;
}

void menu()
{
	while( GetAsyncKeyState(VK_ESCAPE) || GetAsyncKeyState(VK_RETURN));

	mode = 0;
	p1.cpu = false;
	
	for(int i = 0 ; i < 10; i++)
		for(int j = 0; j < 10; j++)
		{
			p1.map[i][j] = 0;
			p2.map[i][j] = 0;
		}

	loaded = false;
    ifstream menu ("data/menu_image.dat");	// Файл с верхним и нижним псевдографическим
	int X, Y;								// текстом
	char menuPart;
	
    HSTREAM menuMusic = BASS_StreamCreateFile( false, "sounds/menu.mp3", 0, 0, // Создание
                        BASS_SAMPLE_LOOP);						// дискриптора поток
	
		

	setcursor(0, 0);
	for(int i = 0; i < (80 * 7); i++)
	{
		menu >> menuPart;
		if(menuPart == '#')
		{
			setcolor(GRAY, BLACK);
			cout << (char) 176;
		}
		else
		{
			setcolor(GRAY, DARK_BLUE);
			cout << (char) 176;
		}
	}
    printSymb(196, 80);		// Рисов ние верхней части
	
	/*----- Очистк  центр  при возвр щении из другой функции --*/
	setcursor(0, 8);

	for(int i = 0; i < 80 * 9; i++)
		cout << ' ';
	
    // Рисов ние нижней части
	setcursor(0, 17);
	printSymb(196, 80);
	for(int i = 0; i < (80 * 7); i++)
	{
		menu >> menuPart;
		if(menuPart == '#')
		{
			setcolor(GRAY, BLACK);
			cout << (char) 176;
		}
		else
		{
			setcolor(GRAY, DARK_RED);
			cout << (char) 176;
        }							// Рисов ние нижней части
	}
	setcursor(0, 0);	// Испр вление смещения консоли


    setcolor(GRAY, BLACK);		// Установка цвет
	setcursor(20, 7);			

	cout << (char) 194; printSymb(196, 40); cout << (char) 194;

	X = 20; Y = 7;
	for( int i = 0; i < 9; i++)				// Рисов ние средней
	{
		setcursor(X, ++Y);
		cout << (char) 179; printSymb(' ', 40); cout << (char) 179;
	}

	setcursor(X, ++Y);
	cout << (char) 193; printSymb(196, 40); cout << (char) 193;

	/*----------------------- Меню  ----------------------------*/
               /*--- Перемещение по пунктам ---*/

	setcolor(WHITE, BLACK);
    int choise;		// Выбор пункта меню
	int move = 0;	// Перемещение по меню

    HCHANNEL sound = BASS_SampleGetChannel              // Получение дискриптора
        (BASS_SampleLoad(false, "sounds/select.mp3",	// канала
		NULL, NULL, 2, 0 ),
		false); 
	
	if( !sound )
	{
        MessageBoxA(NULL, "Ошибка получения дискриптора канала", "Ошыпка", NULL);
		return;
	}

	char *Menu[] =
	{
        "Новая Игра",
        "Загрузить игру",
        "Пользователи",
        "Настройки",
		"Рекорды",
        "О программе",
		"Выход"
	};

choise  = -1;
	Y = 9;
	move = 0;

	while(true)
	{
		for(int i = 9; i < 16; i++)
			printCenter(Menu[i-9], i);
		
		switch(move)
		{
		case 0:
			{
				setcolor(WHITE, GRAY);
				setcursor(20, Y);
				
				cout << (char) 198;
				printSymb(' ', 40);
				cout << (char) 181;
							
                printCenter("Новая Игра",		Y);
				setcolor(WHITE, BLACK);
			
				break;
			} 
		case 1:
			{
				setcolor(WHITE, GRAY);
				setcursor(20, Y);
				
				cout << (char) 198;
				printSymb(' ', 40);
				cout << (char) 181;

                printCenter("Загрузить игру",  Y);
				setcolor(WHITE, BLACK);
			
				break;
			}
		case 2:
			{
				setcolor(WHITE, GRAY);
				setcursor(20, Y);
				
				cout << (char) 198;
				printSymb(' ', 40);
				cout << (char) 181;

                printCenter("Пользователи",	   Y );
				setcolor(WHITE, BLACK);
			
				break;
			}
		case 3:
			{
				setcolor(WHITE, GRAY);
				setcursor(20, Y);
				
				cout << (char) 198;
				printSymb(' ', 40);
				cout << (char) 181;

                printCenter("Настройки",	   Y );
				setcolor(WHITE, BLACK);
			
				break;
			}
		case 4:
			{
				setcolor(WHITE, GRAY);	
				setcursor(20, Y);
				
				cout << (char) 198;
				printSymb(' ', 40);
				cout << (char) 181;

				printCenter("Рекорды",		   Y);
				setcolor(WHITE, BLACK);
			
				break;
			}
		case 5:
			{
				setcolor(WHITE, GRAY);	
				setcursor(20, Y);
				
				cout << (char) 198;
				printSymb(' ', 40);
				cout << (char) 181;

                printCenter("О программе",	   Y);
				setcolor(WHITE, BLACK);
			
				break;
			}
		case 6:
			{
				setcolor(WHITE, GRAY);
				setcursor(20, Y);
				
				cout << (char) 198;
				printSymb(' ', 40);
				cout << (char) 181;

				printCenter("Выход",		   Y);
				setcolor(WHITE, BLACK);
			
				break;
			}
		}


		if( move < 6 )
		{
            if( GetAsyncKeyState(VK_DOWN) )	// Если нажата кл виш  "Вниз"
			{
				move++;
				
				setcolor(GRAY, BLACK);
				setcursor(20, Y);
				cout << (char) 179; printSymb(' ', 40); cout << (char) 179;
				
				setcolor(WHITE, BLACK);
				printCenter(Menu[Y-9], Y); 

				Y++;
				if (sounds)			// +ёыш чтєъш тъы│ўхэv
					BASS_ChannelPlay(sound, true);
			}			
		}
		else if( GetAsyncKeyState(VK_DOWN) )
		{
				move = 0;				

				setcolor(GRAY, BLACK);
				setcursor(20, Y);
				cout << (char) 179; printSymb(' ', 40); cout << (char) 179;
				
				printCenter(Menu[Y-9], Y);
				setcolor(WHITE, BLACK);

				Y = 9;
				if (sounds)			// +ёыш чтєъш тъы│ўхэv
					BASS_ChannelPlay(sound, true);
		}
		if( move > 0 )
		{
            if( GetAsyncKeyState(VK_UP) )		// Если нажата кл виш  вверх
			{
				move--;

				setcolor(GRAY, BLACK);
				setcursor(20, Y);
				cout << (char) 179; printSymb(' ', 40); cout << (char) 179;
				
				printCenter(Menu[Y-9], Y);
				setcolor(WHITE, BLACK);

				Y--;
				if (sounds)			// +ёыш чтєъш тъы│ўхэv
                    BASS_ChannelPlay(sound, true);	// Проигрывание звук  при нажатии кл виши
			}
		}
		else if( GetAsyncKeyState(VK_UP) )
			{
				move = 6;

				setcolor(GRAY, BLACK);
				setcursor(20, Y);
				cout << (char) 179; printSymb(' ', 40); cout << (char) 179;
				
				printCenter(Menu[Y-9], Y);
				setcolor(WHITE, BLACK);

				Y = 15;
				if (sounds)			// +ёыш чтєъш тъы│ўхэv
					BASS_ChannelPlay(sound, true);
			}	
		

        if( GetAsyncKeyState(VK_RETURN))	// Переход к функции по нажатию Enter
			choise = move;					

		while( GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) ||
			   GetAsyncKeyState(VK_RETURN));

		

		/*----- Переход к выбр нной функции -----*/
		if( choise >= 0)
				
		switch(choise)
		{
		case 0:
				loaded = false;
				 
				for(int i = 0; i < 10; i++)
				{
					for(int j = 0; j < 10; j++)
					{
						p1.map[i][j] = 0;
						p2.map[i][j] = 0;
					}
				}
				p1.miss = p2.miss = p1.damaged = p2.damaged = p1.score = p2.score = 0;
				p1.remain = p2.remain = 20;

				if( Play(menuMusic, sound) == 2);
					return;
				break;

		case 1:
				alreadyPlay = true;	// Игр ет ли до сих пор музык ?
				if (load( true ))		// Вызыв ем функцию з грузки и ук зыв ем что вызов идет из меню
					Play(menuMusic, sound);
				return;
			
		case 2:
				showUsers();
				return;

		case 3:
				settings();
				return;

		case 4:
				alreadyPlay = false;
				records();
				return;

		case 5:
				about();
                return;
		
		case 6:
				exit(0);
		}
        getch();
	}

	BASS_Free();	// Освобождение устройств 
	
}

int Play( HSTREAM &menuMusic, HCHANNEL &sound)
{
	while( GetAsyncKeyState(VK_ESCAPE) || GetAsyncKeyState(VK_RETURN));

	strcat((char*) p1.nickname.c_str(), "");
	strcat((char*) p2.nickname.c_str(), "");

	if( !loaded )	
	{
		p1.score = p1.damaged = p1.miss;
		p2.score = p2.damaged = p2.miss;

		/*------- Выбор режим  и ввод имени ------*/
		int X, Y, _menu = 0, choise = -1;
		setcolor(WHITE, BLACK);

		X = 30; Y = 11;

		mkFrame(6, 20, X, Y);

		setcursor(32 , 12);
		cout << "Выберите режим: ";

		X = 34; Y = 14;
		while(choise < 0)
		{
			printCenter("Человек vs CPU",		14);
			printCenter("CPU vs CPU",   15);

			switch(_menu)
			{
			case 0:

				setcolor(WHITE, GRAY);
				printCenter("Человек vs CPU", 14);
				setcolor(WHITE, BLACK);

				break;

			case 1:
				setcolor(WHITE, GRAY);
				printCenter("CPU vs CPU", 15);
				setcolor(WHITE, BLACK);

				break;
			}
            /*------------  нажатия кл виш ---------*/
			if( _menu > 0)
			{
				if( GetAsyncKeyState(VK_UP) )
					_menu--;
			}
			else if( GetAsyncKeyState(VK_UP) )
				_menu = 1;

			if( _menu < 1 )
			{
				if( GetAsyncKeyState(VK_DOWN) )
					_menu++;
			}
			else if( GetAsyncKeyState(VK_DOWN) )
				_menu = 0;

            if( GetAsyncKeyState(VK_ESCAPE) )		// Если пользов тель решит выйти в меню нажатием ESC
				return 2;

			if( GetAsyncKeyState(VK_RETURN) )
			{
				choise = _menu;					// Выбор
				mode = _menu+1;
			}
			while( GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) ||
				GetAsyncKeyState(VK_RETURN));

			if(choise < 0)
				getch();		
		}
		/*--------------- Выбор режим  и ввод имени ------*/
		switch(choise)
		{
		case 0:

			p2.cpu = true;

			X = 27; Y = 13;
			mkFrame(5, 22, X, Y);

			setcursor(29, 14);
            cout << "Введите ваше имя";

			if(	!inputName(30, 15) )
				return 2;            

			
			break;
		case 1:
			p1.cpu = true;
			p2.cpu = true;

			break;	
		}

	}
	alreadyPlay = false;
	
/*------------- Рисуем фон--------------------------*/
	screen();

	if ( !loaded)
	{
		if( p1.cpu )
		{
			p1.generateMap();		// Если выбр н режим "CPU vs CPU"
			strcpy((char *)p1.nickname.c_str(), "CPU1");
			strcpy((char *)p2.nickname.c_str(), "CPU2");
		}
		else
		{
			p2.generateMap(); 
			
            p2.printMap(); // Рисуем карту Второго игрок

			if( !p1.createMap()	)
				return 2;		// Возвр щение в меню

			p1.printMap();
			strcat((char*)p2.nickname.c_str(), "CPU");	
		}

	}

	if( loaded || !p1.cpu)	//	Игр  человек  против CPU
	{
		bool win;

		setcursor(0, 24);
		printSymb(' ', 80);
		while ( true)
		{
			int res;
			setcolor(WHITE, BLACK);
			setcursor(0, 0);
			printSymb(' ', 80);
            printCenter("Ваш ход", 0);

			// Вывод результ тов
			setcursor(0, 1);
            cout << "Очки: " << p1.score << " Попаданий: " << p1.damaged << " Промахов: " << p1.miss;
			setcolor(DARK_GREEN, BLACK);
			cout << (char) 176;
			setcolor(WHITE, BLACK);

			setcursor(43, 1);
            cout << "Очки: " << p2.score << " Попаданий: " << p2.damaged << " Промахов: " << p2.miss;
			setcolor(DARK_GREEN, BLACK);
			cout << (char) 176;
			setcolor(WHITE, BLACK);

			res = p1.atackHum(&p2);
			if ( !res )
			{
				win = true;
				break;
			}
			if ( res == 50)		// Если в внутриигровом меню выбр н  опция выход  в меню
				return 2;		// то вернуть код который прекр тит выполнение функция Play и menu
			p2.y = 3;
			p2.printMap();

			if(p2.y != 3 )
				getch();

			
			setcursor(0, 0);
			setcolor(WHITE, BLACK);
			printSymb(' ', 80);
            printCenter("Ход противника", 0);
					
			if (!p2.atackCPU(&p1))
			{
				win = false;
				break;
			}
			p1.printMap();
		}
		playerState(win);
	}

	if(mode == 2)
	{
		p2.generateMap();
		p1.printMap();
		p2.printMap();
		Player *winner;		// └фЁхёё яюсхфшЄхы  (фр, яЁшч °ыхь яю яюўЄх :)
		while( true )
		{

			setcursor(0, 0);
			setcolor(WHITE, BLACK);
			printSymb(' ', 80);
			setcursor(36, 0);
			cout << "Ход " << p1.nickname;

			setcursor(0, 1);
            cout << "Очки: " << p1.score << " Попаданий: " << p1.damaged << " Промахов: " << p1.miss;
			
			
			if( !p1.atackCPU(&p2))
			{
				p2.printMap();
				winner = &p1;
				break;
			}
			
			p2.printMap();

			setcursor(0, 0);
			setcolor(WHITE, BLACK);
			printSymb(' ', 80);
			setcursor(36, 0);
			cout << "Ход " << p2.nickname;

			setcursor(43, 1);
            cout << "Очки: " << p2.score << " Попаданий: " << p2.damaged << " Промахов: " << p2.miss;
			if( !p2.atackCPU(&p1))
			{
				p1.printMap();
				winner = &p2;
				break;
			}
			p1.printMap();
		}
		
			

		mkFrame(3, 15, 32, 12);
		setcursor(34, 13);
		cout << winner->nickname << " победил";
		
		getch();
	}
}

/*---------- Упрощенн я Установка курсор  ---------*/
void setcursor(int X, int Y)
{
	cursorPos.X = X;
	cursorPos.Y = Y;

	SetConsoleCursorPosition(consoleOutput, cursorPos);
}

/* ----- К кой символ и сколько р з вывести */
void printSymb(int symbol, int times = 1)
{
	for(times; times; times--)
		cout << (char) symbol ;
}

/*------ Печ ть части корабля---------*/
/*type 
0 - Средняя часть корабля, 1 - Н ч ло корабля, 2 - конец корабля, 3 - Одниночный корабль
4 - Поврежденн я средняя часть, 5 - Поврежденное н ч ло корабля, 6 - Поврежденный конец корабля,
7 - Уничтоженный одиночный корабль
*/
void printPart(int type, bool horiz, int X, int Y)	
{
	setcursor(X, Y);

	if (type == 3)
	{
		cout << (char) 213 << (char) 205 << (char) 184;
		setcursor(X, Y+1);
		cout << (char) 212 << (char) 205 << (char) 190;
	}
	if (type == 7)
	{
		setcolor(RED, DARK_RED);
		cout << (char) 213 << (char) 205 << (char) 184;
		
		setcursor(X, Y+1);
		cout << (char) 212;
		setcolor(RED, BLUE);	  
		cout << (char) 177;
		setcolor(RED, DARK_RED);
		cout << (char) 190;
		
		setcolor(WHITE, DARK_BLUE);
	}

	if( horiz )		
	{
		switch(type)
		{
		case 0:
            {		// Не поврежденн я средняя часть корабля
				printSymb(205, 3);
				setcursor(X, Y+1);
				printSymb(205, 3);
				
				break;
			}
        case 1:		// Не поврежденное н ч ло корабля
			{
				cout << (char) 213 << (char) 205 << (char) 205; 
				setcursor(X, Y+1);
				cout << (char) 212 << (char) 205 << (char) 205; 
				
				break;
			}
        case 2:		// Не поврежденный конец корабля
			{
				cout  << (char) 205 << (char) 205 << (char) 184 ; 
				setcursor(X, Y+1);
				cout  << (char) 205 << (char) 205 << (char) 190 ;
				
				break;
			}
        case 4:		// Поврежденн я средняя часть корабля
			{
				setcolor(RED, DARK_RED);

				setcolor(BLUE, DARK_RED);
				printSymb(176);
				setcolor(RED, DARK_RED);
				printSymb(205, 2);
				setcursor(X, Y+1);
				printSymb(205, 2);

				setcolor(BLUE, DARK_RED);
				printSymb(176);

				setcolor(WHITE, DARK_BLUE);
				break;
			}
        case 5:		// Поврежденное н ч ло корабля
			{
				setcolor(RED, DARK_RED);

				cout << (char) 213 << (char) 205 << (char) 205; 
				setcursor(X, Y+1);
				cout << (char) 212 << (char) 205;

				setcolor(BLUE, DARK_RED);
				printSymb(176);
				setcolor(RED, DARK_RED);
				
				setcolor(WHITE, DARK_BLUE);
				break;
			}
		case 6:
			{
				setcolor(RED, DARK_RED);

				printSymb(205, 2);
				
				setcolor(BLUE, DARK_RED);
				cout << (char) 176; 
				
				setcolor(RED, DARK_RED);
				setcursor(X, Y+1);
				printSymb(205, 2);
				printSymb(190, 1); 

				setcolor(WHITE, DARK_BLUE);
				break;
			}
			
			
		}
	}
	else	// Если вертик льно
	{
		switch(type)
		{
		case 0:
			{
				cout << (char) 186 << ' ' << (char) 186;
				setcursor(X, Y+1);
				cout << (char) 186 << ' ' << (char) 186;
			
				break;
			}
		case 1:
			{		
				cout << (char) 214 << (char) 196 << (char) 183;
				setcursor(X, Y+1);
				cout << (char) 186 << ' ' << (char) 186;
				break;
			}
		case 2:
			{
				cout << (char) 186 << ' ' << (char) 186;
				setcursor(X, Y+1);
				cout << (char) 211 << (char) 196 << (char) 189;

				break;
			}
		case 4:
			{
				setcolor(RED, DARK_RED);
				cout << (char) 186 << ' ' << (char) 186;
				setcursor(X, Y+1);

				setcolor(RED, DARK_RED);
				cout << (char) 176;
				setcolor(BLUE, DARK_RED);
				cout << (char) 176;
				
				setcolor(RED, DARK_RED);
				cout << (char) 186;
			
				setcolor(WHITE, DARK_BLUE);
				break;
			}
		case 5:
			{
				setcolor(RED, DARK_RED);

				cout << (char) 214 << (char) 196 << (char) 183;
				setcursor(X, Y+1);
				
				cout << (char) 186; 
				setcolor(DARK_RED, DARK_BLUE);
				cout <<  (char) 176;

				setcolor(RED, DARK_RED);
				cout << (char) 186;
				
				
				setcolor(WHITE, DARK_BLUE);
				break;
			}
		case 6:
			{
				setcolor(RED, DARK_RED);

				cout << (char) 186 ;
				
				setcolor(BLUE, DARK_RED);
				cout << ' ' ;

				setcolor(RED, DARK_RED);
				cout << (char) 176;
				
				setcolor(RED, DARK_RED);
				setcursor(X, Y+1);
				cout << (char) 211 << (char) 196 << (char) 189;

				setcolor(WHITE, DARK_BLUE);
				break;	
			}
		}
	}
}

void setcolor(Color Text, Color Background)
{
	SetConsoleTextAttribute(consoleOutput, color(Text, Background));
}

void Player::printMap()	
{
	setcolor(WHITE, DARK_BLUE);

	int Y, X;
	int _x = x, _y = y;
	int xDefault = x;		// Н ч льн я позиция X;
		
	setcursor(x, y);

	for(Y = 0; Y < 10; Y++)
	{
		for(X = 0; X < 10; X++)
		{
			setcursor(_x, _y);
			
            /*- Если клетк  имеет поврежденную часть корабля -*/
			if(  map[Y][X] == 1)
			{
				
				if( ((Y == 9) || (  map[Y+1][X] != 1 &&  map[Y+1][X] != 3 )) &&  // Контроль выход  з  
                    ((Y == 0) || (  map[Y-1][X] != 1 &&  map[Y-1][X] != 3 )) &&  // пределы массив
					((X == 9) || (  map[Y][X+1] != 1 &&  map[Y][X+1] != 3 )) &&  // Является ли одиночным
					((X == 0) || (  map[Y][X-1] != 1 &&  map[Y][X-1] != 3 )) )
					printPart(7, true, _x, _y);

                /*----  Проверка по оси Y ----*/
                if( ((Y < 9) && ( map[Y+1][X] == 3 ||  map[Y+1][X] == 1)) &&	// является ли средней частью
					((Y > 0) && ( map[Y-1][X] == 3 ||  map[Y-1][X] == 1)))	// по вертик льной оси
					printPart(4, false, _x, _y);
				else
				{
                    /*- Проверка ниже текущей клетки-*/
                    if ( (Y < 9) && (map[Y+1][X] == 3 ||  map[Y+1][X] == 1))	// Является н ч лом корабля?
						printPart(5, false, _x, _y);				

                    /*- Проверка выше -*/
                    if ( (Y > 0) && (map[Y-1][X] == 3 ||  map[Y-1][X] == 1))	// Является концом корабля?
						printPart(6, false, _x, _y);
				}
                /*--------Проверка по оси X ------*/
                if( ( (X<9) && ( map[Y][X+1] == 3 ||  map[Y][X+1] == 1)) &&	// является ли средней частью
                    ( ( X ) && ( map[Y][X-1] == 3 ||  map[Y][X-1] == 1 )))	// по Горизонтальной оси?
					printPart(4, true, _x, _y);
				else
				{
                    if ( (X < 9) && ( map[Y][X+1] == 3 ||  map[Y][X+1] == 1))	// Является н ч лом корабля?
						printPart(5, true, _x, _y);				
					
                    if ( ( X ) && ( map[Y][X-1] == 3 ||  map[Y][X-1] == 1))	// Является концом корабля?
						printPart(6, true, _x, _y);
				}

			}
            /*- Если клетк  имеет не поврежденную часть корабля -*/
			else	// if(
            if( mode == 2 || ! cpu )	// Если режим "CPU vs CPU' или выводится карт  игрок
			{			
				if(  map[Y][X] == 3)
				{
                    /*----- Проверка н  одиночность -----*/

					if( ((Y == 9) || ( map[Y+1][X] != 1 &&  map[Y+1][X] != 3 )) && 
						((Y == 0) || ( map[Y-1][X] != 1 &&  map[Y-1][X] != 3 )) && 
						((X == 0) || ( map[Y][X-1] != 1 &&  map[Y][X-1] != 3 )) &&  // Является ли одиночным
						((X == 9) || ( map[Y][X+1] != 1 &&  map[Y][X+1] != 3 )) )	
						printPart(3, true, _x, _y);

                    /*----  Проверка по оси Y ----*/
				if( ((Y < 9) && (  map[Y+1][X] == 3 ||  map[Y+1][X] == 1)) &&		// Является ли средней
                    ((Y > 0) &&	(  map[Y-1][X] == 3 ||  map[Y-1][X] == 1)))		// частью
						printPart(0, false, _x, _y);
					else
					{
						if ( (Y < 9) && ( map[Y+1][X] == 3 ||  map[Y+1][X] == 1))	// Является н ч лом?
							printPart(1, false, _x, _y);	
						if ( ( Y ) && ( map[Y-1][X] == 3 ||  map[Y-1][X] == 1)) // Является концом?
							printPart(2, false, _x, _y);

					}

                    /*- Проверка по оси X ====-*/
					if( (( X > 0 ) && ( map[Y][X-1] == 3 ||  map[Y][X-1] == 1) ) && 
                        (( X < 9 ) && ( map[Y][X+1] == 3 ||  map[Y][X+1] == 1) ))	// Является ли средней частью
						printPart(0, true, _x, _y);
					else
					{								
						if( ( X ) && ( map[Y][X-1] == 3 ||  map[Y][X-1] == 1))	
							printPart(2, true, _x, _y);

						if( ( X < 9 ) && ( map[Y][X+1] == 3 ||  map[Y][X+1] == 1)	) // Контроль выход  з  пределы 
                            printPart(1, true, _x, _y);						// массив
					}									
					
				
				} // if(  map[Y][X] == 3)
				if ( ! map[Y][X] ) // Если текущ я клетк  пуст 
				{
					cout << "   ";
					setcursor( _x, _y+1);
					cout << "   ";
				}
			}
			else if( map[Y][X] == 3 ||  map[Y][X] == 0 )
			{
				setcolor(WHITE, BLACK);
				cout << "   ";
				setcursor( _x, _y+1);
				cout << "   ";
				setcolor(WHITE, DARK_BLUE);
			}
			if (  map[Y][X] == 2 ) // Если текущ я клетк  место пром х 
			{
				setcolor( WHITE, BLUE);

				printSymb(176, 3); 	
								
				setcolor( WHITE, BLUE);
				setcursor(_x, _y+1);
				printSymb(176, 3);

				setcolor(WHITE, DARK_BLUE);
			}

				_x += 3;		// Переход к следующей клетке
		}	// for(X = 0; X < 10; X++)
		
		_x = xDefault;	// Сбр сыв ем X
		_y += 2;			// Уст н влив ем Y н  новую строку
	}
}

/*--- Вывод текст  по центру ---*/
void printCenter(char *Text, int Y)
{
	int X = ( 40 - ( strlen(Text) / 2 ));

	setcursor(X, Y);
	cout << Text;
}

bool inputName(int X, int Y)
{
	int i = 0;
	setcursor(X, Y);	
	printSymb('_', 16);
	setcursor(X, Y);

    char nickname[17];

	while(true)
	{
        nickname[i] = getch();
		
		if( GetAsyncKeyState(VK_ESCAPE) )
            return false;					// Если нажата ESC, то вернуться в гл вное меню

        if( nickname[i] == 13 )
		{
            nickname[i] = '\0';
			break;
		}
        else if( nickname[i] == 8)
		{
			if( i > 0 )
			{
				cout << "\b_\b";
				i--;
			}
		}
		else if( i < 16)
		{
            cout << nickname[i];
			i++;
		}		
	}

		
	
    if( !nickname[0])
        strcpy(nickname, "Unknown");

    p1.nickname = nickname;

	return true;
}

int Player::atackCPU(Player *pl)		
{
	bool again = false;		// Повторн я ли  т к 
    bool destr = false;		// Уничтожен ли корабль
    int X, Y;				// Позиция в массиве
    int parts = 0;			// Количество частей текущего корабля
					// Требуется для вывод  сообщения 

	bool remained = false;	
    int _x, _y;				// Координаты для  т ки не т ков нной в основнов
	
	HCHANNEL damageSnd = BASS_SampleGetChannel			// Звук поп д ния
		(BASS_SampleLoad(false, "sounds/damaged.mp3",	
		NULL, NULL, 2, 0 ),
		false);

	HCHANNEL missSnd = BASS_SampleGetChannel			// Звук пром х 
		(BASS_SampleLoad(false, "sounds/miss.mp3",	
		NULL, NULL, 2, 0 ),
		false); 

	bool incr;
	bool XorY;

	while( true )		// Общий цикл
	{		
		if( p1.cpu )
			pl->printMap();
		
        if( !again || destr)	// Если это не повторн я  т к  или корабль уничтожен
		{
			do
			{
				incr = rand()%10 % 2;		// Инкрементиров ние или декрементиров ние
				XorY = rand()%10 % 2;		// X или Y. если true, то X

				X = rand()%10;
				Y = rand()%10;
				
				if(pl->map[Y][X] == 0)
				{
					if(
					(pl->map[Y+1][X] != 1) ||
					(pl->map[Y-1][X] != 1) ||
					(pl->map[Y][X+1] != 1) ||
					(pl->map[Y][X-1] != 1))
						break;
				}
				else if(pl->map[Y][X] != 1 || pl->map[Y][X] != 2);
						break;
				 
			} while (true);	// Поиск свободной обл сти		
		}
        else		// Если это повторн я  т к  по неуничтоженному кораблю
		{
			while(true)	// Определение мест 
			{
				
                /*--- Проверка н  выход з  массив ---*/
				
				if(incr)
				{
					if( X == 9 && X == Y)
						destr = true;
					
				}
				else
				{
					if( X == 0 && X == Y)
						destr = true;
				}
				if( XorY )		// Если X
				{
					if( incr && X == 9)	// Если инкремент недопустим
						incr = false;	// то сдел ть декрементом
					
					if( !incr && X == 0) // Если декремент недопустим
						incr = true;	// то сдел ть инкрементом
				}
				else			// Если Y
				{
					if( incr && Y == 9)	// Если инкремент недопустим
						incr = false;	// то сдел ть декрементом

					if( !incr && Y == 0) // Если декремент недопустим
						incr = true;	// то сдел ть инкрементом
				}
				
				/*- Выбор следующей точки для  т ки -*/
				if( pl->map[Y+1][X] == 3 || pl->map[Y-1][X] == 3)	
				{
					XorY = false;

					if( pl->map[Y+1][X] == 3)
					{
						incr = true;						
					}
					else
					{
						incr = false;
					}
					
				}											
				if( pl->map[Y][X+1] == 3 || pl->map[Y][X-1] == 3)
				{
					XorY = true;

					if( pl->map[Y][X+1] == 3)
					{
						incr = true;
					}
					else 
					{
						incr = false;
					}
				}



				if(remained == true && 
					(pl->map[Y+1][X] != 3) &&
					(pl->map[Y-1][X] != 3) &&
					(pl->map[Y][X+1] != 3) &&
					(pl->map[Y][X-1] != 3))
				{
					X = _x;
					Y = _y;			

					if( (pl->map[Y+1][X] != 3) &&
						(pl->map[Y-1][X] != 3) &&
						(pl->map[Y][X+1] != 3) &&
						(pl->map[Y][X-1] != 3))
						remained = false;

					break;
				}

				// Если вокруг только не подходящие для  т ки клетки, то иск ть другое место 
				if(( !remained &&
					(pl->map[Y+1][X] != 3) &&
					(pl->map[Y-1][X] != 3) &&
					(pl->map[Y][X+1] != 3) &&
					(pl->map[Y][X-1] != 3)))
				{
					destr = true;
					break;
				}

			/*-- Ат ков н  ли эт  зон  р нее--*/
                // Если не  т ков н , то завершить цикл и позволить  т ков ть место
			
				if (pl->map[Y+1][X] == 3)
				{
					incr = true;
					XorY = false;
				}
				if (pl->map[Y-1][X] == 3)
				{
					incr = false;
					XorY = false;
				}
				if (pl->map[Y][X+1] == 3)
				{
					incr = true;
					XorY = true;
				}
				if (pl->map[Y][X-1] == 3)
				{
					incr = false;
					XorY = true;
				}

				if( incr && XorY)		// Инкрементиров ние по X
					if(  pl->map[Y][X+1] == 3 )
					{
						if(pl->map[Y][X-1] == 3)
						{
							remained = true;
							_x = X-1;
							_y = Y;
						}
					
						X++;
						break;
					}
				if( !incr && XorY)		// Декрементиров ние по X
					if( pl->map[Y][X-1] == 3 )
					{
						if(pl->map[Y][X+1] == 3)
						{
							remained = true;
							_x = X+1;
							_y = Y;
						}
					
						X--;
						break;
					}
				if( !incr && !XorY)		// Декрементиров ние по Y
					if( pl->map[Y-1][X] == 3 )
					{
						if(pl->map[Y+1][X] == 3)
						{
							remained = true;
							_x = X;
							_y = Y+1;
						}
					
						Y--;
						break;
					}
				if( incr && !XorY)		// Инкрементиров ние по Y
					if( pl->map[Y+1][X] == 3 )
					{
						if(pl->map[Y-1][X] == 3)
						{
							remained = true;
							_x = X;
							_y = Y-1;
						}
					
						Y++;
						break;
					}

			}
		}
        /*- "Атака " -*/
		
		if(pl->map[Y][X] == 0)
		{
			Sleep(delay);
			if (sounds)			// +ёыш чтєъш тъы│ўхэv
				BASS_ChannelPlay(missSnd, false);

			pl->map[Y][X] = 2;
			scrChange(false);

			return pl->remain;
		}
		if(pl->map[Y][X] == 3)
		{
			Sleep(delay);
			destr = false;
			if (sounds)			// +ёыш чтєъш тъы│ўхэv
				BASS_ChannelPlay(damageSnd, true);

			pl->map[Y][X] = 1;
			scrChange(true);
			
            pl->remain--;		// Декриминтиров ть оставшееся количество частей
            if( !pl->remain)	// Если не ост лось больше кораблей,
				return pl->remain;	// То вернуть ноль
			
			again = true;

            //--- Проверка уничтожен ли корабль //
	
            /*- Если вокруг корабля не видно -*/
			if( remained == false && 
				((Y < 9) && (  pl->map[Y+1][X] != 3)) &&  // Контроль выход  з  
                ((Y > 0) && (  pl->map[Y-1][X] != 3)) &&  // пределы массив
				((X < 9) && (  pl->map[Y][X+1] != 3)) &&  // Является ли одиночным
				((X > 0) &&	(  pl->map[Y][X-1] != 3)) )
			{
					destr = true;	// То предположить что он уничтожен
			}
			
			if( ((Y < 9) && pl->map[Y+1][X] == 3) ||  
                ((Y > 0) && pl->map[Y-1][X] == 3) ||  // Если вокруг есть часть корабля
				((X < 9) && pl->map[Y][X+1] == 3) ||  
				((X > 0) && pl->map[Y][X-1] == 3) )
                    destr = false;					// зн чит корабль не уничтожен


		// Определение положения
            /*--- Проверка н  выход з  массив ---*/
			
			

			//-----
			if( pl->map[Y+1][X] == 3 || pl->map[Y-1][X] == 3)	
			{
				XorY = false;

				if( pl->map[Y+1][X] == 3)
					incr = true;
				if( pl->map[Y-1][X] == 3)
					incr = false;

				
			}											
			if( pl->map[Y][X+1] == 3 || pl->map[Y][X-1] == 3)
			{
				XorY = true;

				if( pl->map[Y][X+1] == 3)
					incr = true;
				if( pl->map[Y][X-1] == 3)
					incr = false;

			}
            // Если кр й корабля
			if (incr && XorY)
				if (pl->map[Y][X+1] != 3 && !remained)
                    destr = true;				// Если это кр й корабля, то иск ть другое место для  т ки
			if (!incr && XorY)
				if (pl->map[Y][X-1] != 3 && !remained)
					destr = true;
			if (incr && !XorY)
				if (pl->map[Y+1][X] != 3 && !remained)
					destr = true;
			if (!incr && !XorY)
				if (pl->map[Y-1][X] != 3 && !remained)
					destr = true;
					
			
		}
		pl->printMap();
	}
}

int Player::atackHum(Player *pl)	// Возвр щ ет количество кор белй противник 
{	
    Coord coord;    // Координаты для атаки
	coord.ESC = false;
	int i = 0;		// Выбор внутриигрового меню
	
	
	HCHANNEL damageSnd = BASS_SampleGetChannel			// Получение дискриптор 
		(BASS_SampleLoad(false, "sounds/damaged.mp3",	// к н л  
		NULL, NULL, 2, 0 ),
		false);

	HCHANNEL missSnd = BASS_SampleGetChannel			// Получение дискриптор 
		(BASS_SampleLoad(false, "sounds/miss.mp3",	// к н л 
		NULL, NULL, 2, 0 ),
		false); 

	HCHANNEL alreadyAtacked = BASS_SampleGetChannel		// Звук ошибки.
		(BASS_SampleLoad(false, "sounds/already_atacked.mp3",
		NULL, NULL, 2, 0 ),
		false);

    /*-------- Ввод Координат --------*/
	while(true)
	{
		i = 0;
		setcolor(WHITE, BLACK);
		setcursor(0, 24);
		printSymb(' ', 80);
		setcursor(0, 0);
        printCenter("Введите координаты для атаки ___\b\b\b", 24);
        coord = coord_input();
		if( coord.ESC == true)
		{
			return 50;	// Послать соответствующий сигнал
		}	

        /*-----Проверка карты по введенным Координат м -------*/

		if(	pl->map[coord.y][coord.x] == 1 ||	
			pl->map[coord.y][coord.x] == 2)// Если это место  т ков лось р нее
		{
			if( sounds ) // +ёыш чтєъш тъы│ўхэv			
				BASS_ChannelPlay(alreadyAtacked, false);
		}
		else if( pl->map[coord.y][coord.x]== 0 ) 	// Если пром х
		{
			if (sounds)			// +ёыш чтєъш тъы│ўхэv
				BASS_ChannelPlay(missSnd, false);
			pl->map[coord.y][coord.x] = 2;

			scrChange(false);		// Изменение счет   т кующего
			pl->printMap();
			return pl->remain;
		}
		else						// Если поп д ние
		{
			scrChange(true);
            if (sounds)			// Если звуки включены
				BASS_ChannelPlay(damageSnd, true);

			pl->map[coord.y][coord.x] = 1;
			pl->remain--;
			pl->printMap();
			if( !pl->remain)
				return pl->remain;
		}
	}
}

/*- Внутриигровое меню  -*/
int ingameMenu()
{
	int X, Y;
	int move = 0, choose = -1;
	
	mkFrame(8, 32, 24, 11);	// Созд ние р мки(фрейм )
	
	char *_menu[] =
	{
		"Вернуться в игру",
        "Сохранить игру",
        "Загрузить игру",
        "Вернуться в главное меню",
		"Выйти из игры"
	};
	while(choose < 0)
	{
		setcolor(WHITE, BLACK);
		
		for(int i = 0; i < 5; i++)
			printCenter(_menu[i], i+12);
		
		setcolor(WHITE,GRAY);
		printCenter(_menu[move], move + 12);
		// Предотвр щение ре кции прогр ммы н  удержив ние кл виш
		while(GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || 
			  GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_ESCAPE));
		getch();
		if(GetAsyncKeyState(VK_ESCAPE))
		{
			screen();
            return 1;					// Если нажатаESC, вернуться в игру
		}
		if(GetAsyncKeyState(VK_RETURN))
		{
			choose = move;
			if( choose == 3)
				return 0;		// Возвр щение в гл вное меню
		
		}
		if(GetAsyncKeyState(VK_DOWN))
		{
			if(move < 4)
				move++;
			else
				move = 0;
		}
		if(GetAsyncKeyState(VK_UP))
		{
			if( move > 0)
				move--;
			else
				move = 4;
		}

		if( choose >= 0)		
			break;
		
	}
	/*--      Выбор     -*/
	switch(choose)
	{
	case 1:
        save();			// Сохранение игры
		break;
	case 2:
        load( false );			// Загрузка игры
		break;
		
	case 4:
		exit(0);		// Выход из игры
	}

	screen(); // Восст новление игры перед выходом из функции	
	return 1;
}

/*- Сохр нение игры -*/
void save()
{
	while(GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_ESCAPE));

	int move = 0;	// Перемещение по меню
	int choise = -1;
	char new_name[23];
	ifstream namesv0 ("save/save0.sav");
	ifstream namesv1 ("save/save1.sav");
	ifstream namesv2 ("save/save2.sav");
	ifstream namesv3 ("save/save3.sav");

	char svname[4][23];
	
	namesv0 >> svname[0];
	namesv1 >> svname[1];
	namesv2 >> svname[2];
	namesv3 >> svname[3];

	mkFrame (8, 32, 
			22, 14);

	setcursor(24, 15);
    cout << "Выберите слот для сохранения";
	while(choise < 0)
	{

		for(int i = 0; i < 4; i++)
		{
			setcolor(WHITE,BLACK);
			setcursor(25, i+17);

			if( !strcmp("none", svname[i]))
                cout << "Сохранение отсутствует";
			else
			{
				for(int j = 0; svname[i][j]; j++)
					if( svname[i][j] == '_')
						cout << ' ';
					else 
						cout << svname[i][j];
			}
		}

		setcursor(25, move+17);
		setcolor(WHITE, GRAY);
		
		if( !strcmp("none", svname[move]))
            cout << "Сохранение отсутствует";
		else
		{
			for(int j = 0; svname[move][j]; j++)
				if( svname[move][j] == '_')
					cout << ' ';
				else 
					cout << svname[move][j];
		}

		getch();
		if (GetAsyncKeyState(VK_DOWN))
		{
			if (move < 3)
				move++;
			if (move == 3)
				move = 0;
		}
		if (GetAsyncKeyState(VK_UP))
		{
			if (move == 0)
				move = 3;
			else
				move--;
		}
		if (GetAsyncKeyState(VK_RETURN))
		{
			choise = move;
			setcolor(WHITE, BLACK);
			setcursor(25, move + 17);
			printSymb('_', 22);

			int i = 0;
			setcursor(25, move + 17);
			while(true)
			{
				new_name[i] = getch();
				
				if( new_name[i] == 13 && i <= 22)
					break;
				else if( new_name[i] == 8)
				{
					if( i > 0 )
					{
						cout << "\b_\b";
						i--;
					}
				}
				else if( i < 22)
				{
					cout << new_name[i];
					i++;
					
				}		
			}

		}
		if (GetAsyncKeyState(VK_ESCAPE))
			return;

		
		while(GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || 
			GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_ESCAPE));
	}

	// Получение имени ф йл 
	char filename[15];
	strcpy(filename, "save/save");
	filename[9] = choise + 48;
	filename[10] ='\0';
	strcat(filename, ".sav");

	ofstream sav (filename);

	if (!sav)
	{
        MessageBoxA(NULL, "╬°шсър ёюїЁрэхэш ", "╬°√яър ", 0);
		return;
	}

	/*----- Сохр нение ----*/
	for(int i = 0; new_name[i]; i++)
		if( new_name[i] == ' ')		// З мен  Пробел  н  '_' с целью возможности сохр нения с пробелом
			sav << '_';
		else 
			sav << new_name[i];

	//p1
	sav	<< p1.nickname << ' ' << p1.score << ' ' << p1.damaged << ' ' << p1.miss << endl;
	for(int i = 0; i < 10; i++)
	{
		for( int j = 0; j < 10; j++)
			sav << p1.map[i][j] << ' ';
		sav << endl;
	}
	sav << endl << endl;

	//p2
	sav	<<  p2.score << ' ' << p2.damaged << ' ' << p2.miss << endl;
	for(int i = 0; i < 10; i++)
	{
		for( int j = 0; j < 10; j++)
			sav << p2.map[i][j] << ' ';
		sav << endl;
	}	

	mkFrame(3, 15, 32, 10);
	setcursor(34, 11);
	cout << "СОХРАНЕНО";
	getch();
}

/*- Созд ние р мки -*/
void mkFrame(int height, int width, int X, int Y)
{
	setcolor(WHITE,BLACK);
	setcursor(X, Y);

	cout << (char) 218; printSymb(196, width-2); cout << (char) 191;

    for(int i = 0; i < height-1;i++)
	{
		setcursor(X, ++Y);
		cout << (char) 179; printSymb(' ', width-2); cout << (char)179;
	}
	setcursor(X, Y++);
	cout << (char) 192; printSymb(196, width-2); cout << (char) 217;
}

/*- Восст новление\вывод экр н  -*/
void screen()
{
	int X, Y;
	/*- Рисуем фон -*/
	setcursor(0, 0);
	setcolor(DARK_GREEN, BLACK);
	printSymb(176, 80 * 25);
	setcursor(0, 0);

    /*- Рисуем Координатные обозн чения -*/
	setcolor(WHITE, GRAY);

	X = 4, Y = 3;

	setcursor(X, Y);
	for(int i = 0; i < 10; i++)
	{
		cout << "  ";
		setcursor(X + 70, Y);
		cout << "  ";
		setcursor(X, ++Y);

		cout << ( i < 9 ? " " : "") << i+1;
		setcursor(X + 70, Y);
		cout << i+1 << ( i < 9 ? " " : "");
		setcursor(X, ++Y);

	}
	X = 6; Y = 2;

	setcursor(X, Y);
	for( int i = 0; i < 10; i++)
	{
		cout << ' ' << (char) (65 + i) << ' ';
		setcursor(X + 38, Y);
		cout << ' ' << (char) (65 + i) << ' ';

		X += 3;
		setcursor(X, Y);
	}
	
    /*- Рисуем карты -*/
	p1.printMap();
	p2.printMap();

	/*- Дополнительные н дписи -*/
	setcolor(WHITE, BLACK);
	setcursor( 0, 0);
	printSymb(' ', 80);
	
	if( !p1.cpu )
		printCenter("В ш ход", 0);
		
	setcursor(0, 24);
	printSymb(' ', 80);
	setcursor(0, 0);

	// Вывод результ тов
	setcursor(0, 1);
    cout << "Очки: " << p1.score << " Попаданий: " << p1.damaged << " Промахов: " << p1.miss;
	setcursor(43, 1);
    cout << "Очки: " << p2.score << " Попаданий: " << p2.damaged << " Промахов: " << p2.miss;

	setcursor(20 - p1.nickname.length(), 23);
	cout << p1.nickname;
	setcursor(60 - p2.nickname.length(), 23);
	if( !p1.cpu)
        printCenter("Введите координаты для атаки ___\b\b\b", 24);
}

/*- Загрузка игры -*/
bool load(bool from_menu)
{
	while(GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_ESCAPE));

	loaded = true;		// Ук зыв ем что игр  з гружен 

	ifstream save0("save/save0.sav");
	ifstream save1("save/save1.sav");
	ifstream save2("save/save2.sav");
	ifstream save3("save/save3.sav");

	char svname[4][23];
	int move = 0;

	save0 >> svname[0];
	save1 >> svname[1];
	save2 >> svname[2];
	save3 >> svname[3];

	int choise = -1;
	mkFrame (8, 32, 
		22, 14);

retry:
	setcolor(WHITE, BLACK);
	setcursor(24, 15);
    cout << "    Выберите сохранение";
	while(choise < 0)
	{

		for(int i = 0; i < 4; i++)
		{
			setcolor(WHITE,BLACK);
			setcursor(25, i+17);

			if( !strcmp("none", svname[i]))
                cout << "Сохранение отсутствует";
			else
			{
				for(int j = 0; svname[i][j]; j++)
					if( svname[i][j] == '_')
						cout << ' ';
					else 
						cout << svname[i][j];
			}
		}

		setcursor(25, move+17);
		setcolor(WHITE, GRAY);

		if( !strcmp("none", svname[move]))
            cout << "Сохранение отсутствует";
		else
		{
			for(int j = 0; svname[move][j]; j++)
				if( svname[move][j] == '_')
					cout << ' ';
				else 
					cout << svname[move][j];
		}

		getch();
		if (GetAsyncKeyState(VK_DOWN))
		{
			if (move < 3)
				move++;
			else if (move == 3)
				move = 0;
		}
		if (GetAsyncKeyState(VK_UP))
		{
			if (move == 0)
				move = 3;
			else
				move--;
		}
		if (GetAsyncKeyState(VK_RETURN))
			choise = move;
		
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			if( from_menu )
				return false;
			else
			{
				screen();
				return false;
			}
		}
	
		while( GetAsyncKeyState(VK_RETURN)  || GetAsyncKeyState(VK_ESCAPE) ||
			   GetAsyncKeyState(VK_UP)		|| GetAsyncKeyState(VK_DOWN));
	}
	char nickname[17];
	char filename[15];

	strcpy(filename, "save/save");
	filename[9] = choise + 48;
	filename[10]= '\0';
	strcat(filename, ".sav");

	ifstream check (filename);
	ifstream loading (filename);	// filename более не требуется

	check >> nickname;
	if( strcmp("none", nickname) )
	{
		loading >> filename;	// Пропуск ем имя сохр нения.
		//p1
		loading	>> p1.nickname >>p1.score >>p1.damaged >>p1.miss;
		for(int i = 0; i < 10; i++)
		{
			for( int j = 0; j < 10; j++)
				loading >> p1.map[i][j];
		}

		//p2
		p1.cpu = false;
		p2.cpu = true;
		loading	>>  p2.score >>p2.damaged >>p2.miss;
		for(int i = 0; i < 10; i++)
		{
			for( int j = 0; j < 10; j++)
				loading >> p2.map[i][j];
		}	

		if ( from_menu)
			screen();

		return true;
	}
	else
	{
		choise = -1;
		goto retry;
	}
}

/*-  Загрузка б зы пользов телей -*/
void load_userBase()
{
	ifstream uBase ("data/users.dat");
	int i = 0;

	for(int i = 0; !uBase.eof(); i++)
	{
		uBase >> userBase[i].nickname;

		if( !userBase[i].nickname[0] )
			break;		// Если ф йл пуст то не проверять
		
		uBase >> userBase[i].wins >> userBase[i].lose 
			  >> userBase[i].rank >> userBase[i].win2increasing;
		userBase[i].occupied = true;
	}
}

/*- Вставка в б зу нового пользов теля, или пр вк  результ тов ст рого -*/
void put2base(bool win)
{
	int i = 0;
    /*- Проверка н  уместность сохр нения -*/
	if( !strcmp("Unknown", p1.nickname.c_str()))
		return;							// Если игрок не предст вился

	/*- Поиск пользов теля в б зе -*/
	for( ; ; i++)
	{
		if( !strcmp(p1.nickname.c_str(), userBase[i].nickname))
			break;

		if( !userBase[i].occupied )		// Если н йден  не з нят я обл сть
			break;
	}

	/*- Сохр нение пользов теля -*/
	strcpy(userBase[i].nickname, p1.nickname.c_str());
	userBase[i].occupied = true;
	
	if( win)
	{
		setcolor(GREEN, BLACK);

		++ userBase[i].wins;
		-- userBase[i].win2increasing;

		if ( userBase[i].win2increasing < 0)		// Если побед дост точно чтобы "повысить"
		{
			printCenter("Вы получили новое зв ние!", 15);

			++ userBase[i].rank;
			userBase[i].win2increasing = 5;
		}

		setcursor(12, 16);
        cout << "Ваше текущее звание: " << ranks[ userBase[i].rank ];
		setcursor(12, 17);
        cout << "Осталось " << userBase[i].win2increasing << " побед до следующего звания";
        printCenter("Удачи в будущих битвах!", 20);
	}
	else
	{
		setcolor(RED, BLACK);
		++ userBase[i].lose;

		if( userBase[i].win2increasing < 5)		
			++ userBase[i].win2increasing;

		setcursor(12, 16);
        cout << "Ваше текущее звание: " << ranks[ userBase[i].rank ];
		setcursor(12, 17);
		cout << "Ост лось " << userBase[i].win2increasing << " побед до следующего зв ния";

        printCenter("Удачи в следующий р з.", 20);

	}

	save_userBase();
} 

/*- Сохр нение б зы пользов телей в ф йл -*/
void save_userBase()
{
	ofstream uBase("data/users.dat");

	for (int i = 0; userBase[i].occupied; i++)
	{
		uBase << userBase[i].nickname << "\t\t"
			  << userBase[i].wins << '\t'
			  << userBase[i].lose << '\t' << userBase[i].rank << '\t'
			  << userBase[i].win2increasing << endl;
	}
}
/*- Ст тус игрок  н  момент оконч ния игры -*/
void playerState( bool win )
{
	setcursor(0, 0);
	setcolor(GREEN, BLACK);
	printSymb(' ', 80 * 25);
	setcursor(0, 0);

	if ( win )
	{
        printCenter("Поздравления!", 11);
		printCenter("Вы победитель!", 12);

		put2base(true);

		if( p1.score > hslist[5].score )	// Если результ т рекордный
		{
            /*- Поиск позиции для вставки в список */
			int i;
			for (i = 0; i < 6; i++)
				if( hslist[i].score <= p1.score )
					break;
			
			for( int j = 0; j < i; j++)  // Смещение нижестоящих 
				hslist[j] = hslist[j+1];
			
			strcpy(hslist[i].nickname, p1.nickname.c_str()); // Помещение в список
			hslist[i].score = p1.score;
			hslist[i].record = true;

			getch();
			records();
		}

	}
	else
	{
		setcolor(RED, BLACK);
        printCenter("Вы проиграли", 11);
		put2base(false);
	}

	
	getch();
}


/*- Вывод всех пользов телей -*/
void showUsers()
{
	int start_pos = 0;		// Ст ртов я позиция для вывод 
	int Y;
	/*- З головок -*/
	setcolor(WHITE, BLACK);
	setcursor(0, 0);
	printSymb(' ', 80);
	printCenter("Пользователи когда либо игравшие в эту игру", 0);

	/*- Рисов ние т блицы -*/
	mkFrame(24, 80, 0, 1);
	setcursor(0, 0);
	
    /*- Проверка количеств  -*/
    if( !userBase[0].occupied )			// Если б з  пуст
	{
		while(!GetAsyncKeyState(VK_ESCAPE))
		{
			printCenter("База пользователей пуста. Может вы станете первым?", 4);
			getch();
		}
		return;
	}

	while(true)
	{
		Y = 4;
		for(int i = 0; i < 20; i++)
		{
			setcursor(6, 2);
			setcolor(WHITE, BLACK);
            cout << "Никнейм\t\tПобед\tПоражений\tЗвание\tПобед до повышения";

			if( !userBase[i+start_pos].occupied)
				break;

			setcursor(6, Y++);
			setcolor(WHITE, BLACK);
			cout << userBase[i+start_pos].nickname;

			if( strlen(userBase[i+start_pos].nickname) > 8)
				cout << '\t';
			else
				cout << "\t\t";
	
			setcolor(GREEN, BLACK);
			cout << userBase[i+start_pos].wins << '\t';
			setcolor(RED, BLACK);
			cout << userBase[i+start_pos].lose << "\t\t";
			setcolor(YELLOW, BLACK);
			cout << ranks [userBase[i+start_pos].rank] << '\t' << userBase[i+start_pos].win2increasing << endl;
		}

		for( ; Y < 24; ++Y)
		{
			setcursor( 6, Y);
			printSymb(' ', 70);
		}
		
        /* Вывод предложений нажатия кл виш */

        if( start_pos )			// Если нажатие PG_UP допустимо
		{	
			setcursor( 73 , 1);
			setcolor(YELLOW, BLACK);
			cout << "PG UP";
			setcolor(WHITE, BLACK);
		}
		else
		{
			setcursor( 73 , 1);
			printSymb(196, 5);
		}
		if( userBase[start_pos + 20].occupied )
		{
			setcursor( 72 , 24);
			setcolor(YELLOW, BLACK);
			cout << "PG DOWN";
			setcolor(WHITE, BLACK);
		}
		else
		{
			setcursor( 72 , 24);
			printSymb(196, 7);
		}
        /* Перехв т нажатия кл виш */
        getch();							// Ожид ние нажатия

		if(GetAsyncKeyState(VK_PRIOR))		// Page UP
		{
			if (start_pos)
				start_pos -= 20;
		}

		if(GetAsyncKeyState(VK_NEXT))		// Page DOWN
		{
			if (userBase[start_pos + 20].occupied)
				start_pos += 20;
		}

		if(GetAsyncKeyState(VK_ESCAPE))
			return;


		while(GetAsyncKeyState(VK_ESCAPE) || GetAsyncKeyState(VK_NEXT) ||
			  GetAsyncKeyState(VK_PRIOR));
		
	}
}


/*- Н строки -*/
void settings()
{
	while(GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_ESCAPE));

	bool change = false;
	int Y = 7, move = 0;
	ifstream set("data/settings.dat");

	setcursor( 0, 0);
	setcolor(WHITE, BLACK);
	printSymb(' ', 80 * 25);
	
	/*- Оформление -*/
	printCenter("Настройка звука", 3);
	setcursor(0, 4);
	printSymb(196, 80);

	printCenter("Настройка игры", 10);
	setcursor(0, 11);
	printSymb(196, 80);
	
	bool musicOn;
	bool soundsOn;
	float new_delay;

	set >> musicOn >> soundsOn >> new_delay;

	while(true)
	{
		setcolor(WHITE, BLACK);

		setcursor(6, 7);
        cout << "Музыка " << (musicOn ? "ВКЛ " : "ВЫКЛ");
		setcursor(6, 8);		
		cout << "Звуки " << (soundsOn ? "ВКЛ " : "ВЫКЛ");
		setcursor(6, 12);
		cout.precision(2);
        cout << "Задержка между атаками: " <<  new_delay / 1000 << " сек.";
        setcursor(6, 13);
        cout << "Сбросить все результаты и настройки";

		// Выделение выбр нного пункт 
		setcolor(WHITE, GRAY);
		if( move == 0)
		{
			setcursor(6, 7);
            cout << "Музыка " << (musicOn ? "ВКЛ" : "ВЫКЛ");
		}
		if( move == 1)
		{
			setcursor(6, 8);
			cout << "Звуки " << (soundsOn ? "ВКЛ" : "ВЫКЛ");
		}
		if( move == 2)
		{
			setcursor(6, 12);
            cout << "Задержка между атаками: " << new_delay / 1000 << " сек.";
		}
        if( move == 3)
        {
            setcursor(6, 13);
            cout << "Сбросить все результаты и настройки";
        }
        // Перехв т кл виш и обр ботк  нажатий кл виш
		getch();
		
		if( GetAsyncKeyState(VK_UP) )
		{
			if( move == 0) 
                move = 3;
			else
				move--;
		}

		if( GetAsyncKeyState(VK_DOWN) )
		{
            if( move == 3)
				move = 0;
			else
				move++;
		}
		
		if( GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT))
		{

			if ( move == 0)
            {
				if ( musicOn ) musicOn = false;
				else musicOn = true;
                change = true;
            }
            else if(move == 1)
            {
				if ( soundsOn ) soundsOn = false;
				else soundsOn = true;

                change = true;
            }
            else if( move == 2)
			{
				setcursor(6, 12);
				setcolor(WHITE, BLACK);
				printSymb(' ', 60);
				setcolor(WHITE, GRAY);

				setcursor(6, 12);
                cout << "Введите новое значение: ";
				cin >> new_delay;
				new_delay *= 1000;

                change = true;
			}				
            else if( move == 3)
            {
                while( true)
                {
                    mkFrame(  3, strlen( "Вы уверены? y/n  "),
                              40 - (strlen( "Вы уверены? y/n  ") / 2),
                              10);
                    printCenter( "Вы уверены? y/n", 11);
                    setcursor( 80, 20);

                    char answer = getch();

                    if( answer == 'y' || GetAsyncKeyState(VK_RETURN))
                    {
                        clearAll();
                        change = true;

                        break;
                    }
                    else if (answer == 'n')
                        break;
                }
                move = 0;
                drawSettingWindow();
            }
			
		}
		
		if( GetAsyncKeyState(VK_ESCAPE) )
		{
			if( change )
			{
				ofstream saveSet("data/settings.dat");

				saveSet << musicOn << ' ' << soundsOn << ' ' << new_delay;
			
				mkFrame(4, 29, 25, 11);
				setcursor(27, 12);
                cout << "Перезапустите игру, чтобы ";
				setcursor(27, 13);
				cout << "изменения вступили в силу ";
				getch();

			}
			while( GetAsyncKeyState(VK_ESCAPE) );
			return;
		}
		while( GetAsyncKeyState(VK_RETURN)  || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT) ||
			GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN));
	}	
}
/*- Рекорды -*/
void records()
{
	while(GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_ESCAPE));

	ofstream hs("data/highscore.dat");
	int Y = 10;
	// Укр шения
	setcolor(WHITE, BLACK);
	setcursor(0, 0);
	printSymb(' ', 80 * 25);
	setcursor(0 , 0);

    printCenter("Лучшие результаты", 3);
	setcursor(0, 5);
	printSymb(196, 80);

	setcursor(0, 20);
	printSymb(196, 80);

	// Вывод результ тов

	for (int i = 0; i < 6; i++)
	{
		setcursor(6, Y++);

		if( hslist[i].record )
			setcolor(GREEN, BLACK);

		cout << hslist[i].nickname << '\t';

		if( strlen(hslist[i].nickname) > 8)
			cout << '\t';
		cout << hslist[i].score;

		if( hslist[i].record )
		{
			setcolor(WHITE, BLACK);
			hslist[i].record = false;
		}
	}

	while(true)
	{
		getch();
		if(GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_ESCAPE))
		{
			for (int i = 0; i < 6; i++)
				hs << hslist[i].nickname << ' ' << hslist[i].score << endl;

			return;
		}
	}
}

/*- ╬ яЁюуЁрььх -*/
void about()
{
	while( GetAsyncKeyState(VK_ESCAPE) || GetAsyncKeyState(VK_RETURN));

	setcursor(0, 0);
	printSymb(' ', 80 * 25);
	setcursor(32, 2);
	setcolor(BLUE, BLACK);
	cout << "Sea";
	setcolor(RED, BLACK);
	cout << "Battle ";
	setcolor(YELLOW, BLACK);
	cout << "v 1.0.0";
	
	setcursor(1, 4);
    cout << "Всем без исключения известная, и, возможно, любимая игра. Ранее играли мы на";
	setcursor(1, 5);	
    cout << "бумажках называя друг другу координаты для атаки. Времена далеко не ушли, и";
	setcursor(1, 6);
    cout << "некоторые еще сидят на уроках в период отсутствия учителя и занимаются";
	setcursor(1, 7);
    cout << "этой незатейливой игрой. Эта реализация сначала была просто заданием, практикой";
	setcursor(1, 8);
    cout << "для меня как программиста. Учащий, на то время, меня человек говорил что это";
	setcursor(1, 9);
    cout << "переход на новый уровень, и был прав: Ранее мои программы вмещались отсилу в";
	setcursor(1, 10);
    cout << "сотню строк, а эта игра вошла в 3000 (!) строк. И это не предел. Ведь эта";
	setcursor(1, 11);
    cout << "версия слишком ограничена и требует доработки, и реализации моих идей. Не";
	setcursor(1, 12);
    cout << "думаю что пройдет очень много времени прежде чем я встрою сетевой режим. ";
	setcursor(1, 13);
    cout << "Период разработки был нтересным и, признаюсь, немного ленивым";
	setcursor(1, 14);
    cout << ". Я познал новое, ранее неизведанное. Но довольно лирики.";
	setcursor(1, 16);
    cout << "На мой взгляд удобнее всего играть в эту игру держа одну руку на основной";
	setcursor(1, 17);
    cout << "клавиатуре, а другую на цифровой. В меню настроек время задержки можно";
	setcursor(1, 18);
    cout << "устанавливать дробное. Всё перемещение по меню осуществляется нажатиями";
	setcursor(1, 19);
    cout << "стрелок, Enter, Esc. И если в игре вы не можете ввести букву для атаки";
	setcursor(1, 20);
    cout << "то это не баг, а смените расскладку на английскую :)";
	setcursor(1, 21);
    cout << "Удачи!";
	
    setcursor(1, 24);
	setcolor(GRAY, BLACK);
    cout << "Иван Сидельник AKA Cydeamon\tmailto: cydeamon@gmail.com\t\t2012|07";

	setcolor(WHITE, BLACK);
	setcursor(0, 0);
	getch();
    if(GetAsyncKeyState(0x42)) // Если пользователь нажал 'B', то вывести пасхалку
		BlackMesa();
}

void BlackMesa()
{
	while(GetAsyncKeyState(42));
	
    system("cls"); // Очистка консоли

	ifstream BM ("data/blackmesa.dat");
	char ch;

	while( !BM.eof() )
	{
		BM >> ch;
		if(ch == '_')
			cout << ' ';
		else if( ch == '|')
			cout << endl;
		else
			cout << ch;
	}

    printCenter("Нажмите ESC для выхода", 23);
	
	while(true)
	{
		getch();
		if(GetAsyncKeyState(VK_ESCAPE))
			break;
	}

}

Coord coord_input()
{
    Coord coord;
    char txtCoord[4];
    int i = 0;

    while( true )
    { 
        txtCoord[i] = getch();
	
		if(GetAsyncKeyState(VK_ESCAPE))
		{		
            if( !ingameMenu() )
            {
                coord.ESC = true;
                return coord;
            }
        }
        if( i > 0 && txtCoord[i] == '\b')
        {
            cout << "\b_\b";
            i--;
			continue;
        }

        if( i > 1 && txtCoord[i] == 13)
            break;

        switch(i)
        {
        case 0:

            if(txtCoord[i] >= 'a' && txtCoord[i] <= 'k')
            {
                txtCoord[i] -= 'a';
                txtCoord[i] += 'A';
            }
            if(txtCoord[i] >= 'A' && txtCoord[i] <= 'K')
            {
                cout << txtCoord[i];
                i++;
            }

        case 1:

            if((txtCoord[i] >= '1' && txtCoord[i] <= '9'))
           {
                cout << txtCoord[i];
                i++;
            }
        case 2:

            if( txtCoord[i-1] == '1' && txtCoord[i] == '0' )
            {
                cout << txtCoord[i];
                i++;
            }

        }   // switch

    } // while

    coord.x = txtCoord[0] - 'A';

    if (txtCoord[1] == '1' && txtCoord[2] == '0')
        coord.y = 9;
    else
        coord.y = txtCoord[1] - '1';

    return coord;
}

void clearAll()
{
    ofstream save1       ("save/save0.sav");
    ofstream save2       ("save/save1.sav");
    ofstream save3       ("save/save2.sav");
    ofstream save4       ("save/save3.sav");

    ofstream highscore   ("data/highscore.dat");
    ofstream settings    ("data/settings.dat" );
    ofstream users       ("data/users.dat"    );

    save1 << "none";
    save2 << "none";
    save3 << "none";
    save4 << "none";

    highscore << "none 0" << endl
              << "none 0" << endl
              << "none 0" << endl
              << "none 0" << endl
              << "none 0" << endl
              << "none 0" << endl;

    settings << "1 1 500";
    users    << "";

}

void drawSettingWindow()
{
    while(GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_ESCAPE));

    bool change = false;
    int Y = 7, move = 0;
    ifstream set("data/settings.dat");

    setcursor( 0, 0);
    setcolor(WHITE, BLACK);
    printSymb(' ', 80 * 25);

    /*- Оформление -*/
    printCenter("Настройка звука", 3);
    setcursor(0, 4);
    printSymb(196, 80);

    printCenter("Настройка игры", 10);
    setcursor(0, 11);
    printSymb(196, 80);

    bool musicOn;
    bool soundsOn;
    float new_delay;

    set >> musicOn >> soundsOn >> new_delay;
}
