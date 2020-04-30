/* �����������  ��������� OEM866 ����� ��������  ��� IBM866, CP866, csIBM866 */

#include "declarations.h"

#pragma comment( lib, "bass" )		// ������祭�� ��㪮��� ������⥪� Bass
#pragma comment( lib, "User32.lib")
/*----------- ������ -------------------------------------*/


void Player::scrChange(bool hit)	// ��������� ��� ��ப�
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

void Player::generateMap()		// �����஢���� �����
{
    int Y, X;		// ���� � ���ᨢ� ��� ��⠢�� ��ࠡ��
    int parts;		// ������⢮ ��⥩
    int count;		// ���稪 ��� ���ਬ��� parts
    bool horiz;		// ��ਧ��⠫쭮
	
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
		} while( map[Y][X] == 3);	// ���� ᢮������ ���⪨

		if ((( Y < 9) && (map[Y+1][X] == 3) ) ||	
            (( Y > 0) && (map[Y-1][X] == 3) ) ||	 // ����� �� ��⠭����� ����� ��ࠡ��?
			(( X < 9) && (map[Y][X+1] == 3) ) ||	
			(( X > 0) && (map[Y][X-1] == 3) ))		
		{ 
			c--;
			continue;
		}
		
        //--------------- ��⠢�� ��ࠡ��� � �����-------------------*/
		
        int i;			// ��� �஢�ન ������ ��㣨� ��ࠡ���
		horiz = rand()%2;	// ��।������ ���������

		if( horiz )			
		{
			if( (parts + X) > 9 )
			{	c--; continue; }
		}
		else
		{
			if( (parts + Y) > 9 )
			{	c--; continue; }
        }							// �஢�ઠ �� "����⨬����"

        bool success = true;	// �஢�ઠ �ᯥ譮�� �����襭�� ᫥���饣� 横��
		for( i = 0; i < (parts + 1); i++ )	// ��� �㦤� �஢����� �᫨ parts = 0
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
        if ( !success)			// �᫨ �஢�ઠ ���  ��� 筮
		{ c--; continue; }		// �� �� �� ����� ����
			
        // �᫨ �� �஢�ન ��諨 �ᯥ譮, � ����� � ᯮ������ ��ࠡ�� �  ����
		for(i = 0; i <= parts; i++)
		{
			if( horiz ) 
				map[Y][X+i] = 3;
			else
				map[Y+i][X] = 3;
		}
		count++;

        if( count == 4 - parts )	// �᫨ �뢥���� ���� �筮� ������⢮ ��ࠡ���
		{							// ⥪�饣� ⨯ , �...
			count = 0;				
            parts++;				// ...ᬥ���� ⨯ ��ࠡ��
		}
	}
}


int color(Color Text, Color Background)					// ����祭�� �᫠, ᮮ⢥�����饣� 㪠������
{    return (Background * 16) + Text; }					// 梥�� ⥪�� � 䮭�

/*- �������� ����� ��ப� -*/
bool Player::createMap()
{
    int X, Y;	// X � Y �������� ��室��� �� ࠬ�� X � Y
    int arrX, arrY;	// ���� � ���ᨢ� ������饥�� �� ��㫥 (X - X)/3, � Y ������� �� 2
    int parts =1;// ������⢮ ��⥩ ��ࠡ���, ����� ������ �뢮����� � �����(� 横��) ������
    int count;	// �� ��� ��।������ ���⨣��� �� ��࠭�祭�� parts'���㡭�� ��ࠡ���
    int ships=0;// ������⢮ ��ࠡ���

    bool ok;	// ��������� �� ⥪��� ������
    bool horiz = true; // ���������, �᫨ true - ��ਧ��⠫쭮
    setcursor(x, y);   // ��⠭�������� ����� � ���� ���孨� 㣮�.
	setcolor(WHITE, DARK_BLUE);

	X = x; Y = y;
    arrX = (X - x) / 3;		// �८�ࠧ������ ����樨 � ���᮫� � ������ � ���ᨢ�
	arrY = (Y - y) / 2;
	count = 0;

/*-- �ᯮ����⥫�� ������ --*/
	setcursor(0, 0);
	setcolor(WHITE,BLACK);
	for(int i = 0; i < 80; i++)
		cout << ' ';

    printCenter("����⠭���� ��ࠡ���", 0);
	setcursor(0, 24);
	for(int i = 0; i < 80; i++)
		cout << ' ';
	setcursor(0, 0);
	setcursor(0, 24);
    cout << " �஡�� - ����� ���������, " << (char) 24 << (char) 25 << (char) 26 << (char) 27
         << " - ��६�饭�� ��ࠡ��, Enter - ����� ������";
	for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)	// ����  ���ᨢ
			map[i][j] = 0;

/*-- � ��� ����  ��ࠡ��� --*/
	while( ships < 10)
	{	
        printMap();	// ������塞 �뢮� �����
		setcursor(X, Y);
		ok = true;
    /*---- �஢�ઠ �  ��室 �  �� ���� ���ᨢ  -*/
		if( horiz) 
		{
			if( ((X - x) / 3) + (parts-1) <= 9)
			{
				for( int i = 0; i < parts; i++)
				{
					if( ((arrY > 0) && map[arrY-1][arrX + i] == 3) ||	
						((arrY < 9) && map[arrY+1][arrX + i] == 3) ||
                        ( map[arrY][arrX + i] == 3))// �᫨ ����⨫ �� ���� ��ࠡ��
						ok = false;					// � ����� :) 11:03 25.07.12 � � ��襬 � ��஥���
					
                    // �஢�ઠ ���� �� � ��� �� � ��ࠡ��
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

            if( ok )		// �᫨ ��㣨� ��ࠡ��� �� � �諮��
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
                else		// �᫨ ����⨫ �� �訡� , �� ��ࠡ�� ����� ���� �  ����
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
                        ( map[arrY + i][arrX] == 3))// �᫨ ����⨫ �� ���� ��ࠡ��
						ok = false;					// � ����� 
					
                    // �஢�ઠ ���� �� � ��� �� � ��ࠡ��
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

            if( ok )		// �᫨ ��㣨� ��ࠡ��� �� � 諮��
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
                else		// �᫨ ����⨫ �� �訡� , �� ��ࠡ�� ����� ���� �  ����
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

        /*---------�஢�ઠ ������� �� ��� -----------*/
		
		while(  GetAsyncKeyState(VK_UP)		|| GetAsyncKeyState(VK_DOWN) ||
				GetAsyncKeyState(VK_RIGHT)  || GetAsyncKeyState(VK_LEFT) ||
				GetAsyncKeyState(VK_ESCAPE) || GetAsyncKeyState(VK_RETURN)||
                GetAsyncKeyState(VK_SPACE) ); // ���� �� 㤥ন�����
		getch();

        if( GetAsyncKeyState(VK_UP) )		// �᫨ ����� ������ "�����"
		{
			if( arrY > 0)
			{
				Y -= 2;	// ���ਬ���஢ ��� �� ���᮫�
                --arrY;	// ���ਬ���஢ ��� �� ���ᨢ�
			}
		}
        if( GetAsyncKeyState(VK_DOWN) )		// �᫨ ����� ������ "����"
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
        if( GetAsyncKeyState(VK_LEFT) )		// �᫨ ����� ������ "�����"
		{
			if( arrX> 0)
			{
				X -= 3;
				--arrX;
			}
		}
        if( GetAsyncKeyState(VK_RIGHT) )	// �᫨ ����� ������ "��� ��"
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

        if( GetAsyncKeyState(VK_ESCAPE) ) // �᫨ ����� ������ [ESC]
		{
			return 0;
		}

        if( GetAsyncKeyState(VK_RETURN) ) // �᫨ ����� ������ Enter
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
		
    /*----- �����祭�� ��⥩ ��ࠡ��� ---*/
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
	consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);	// ����祭�� ���  �뢮�  ���᮫�
	srand(time(0));

	if (HIWORD(BASS_GetVersion())!=BASSVERSION) 
	{
        MessageBoxA (NULL, "������ ������ BASS.", "������", 0);	// �஢�ઠ ᮮ⢥��⢨� ���ᨨ
        return 1;
	}

	if( !BASS_Init(-1, 44100, BASS_DEVICE_3D, 0, NULL))
	{
        MessageBoxA(NULL, "������ ������������� BASS", "������", 0);
		return 1;
	}

	HSTREAM menuMusic = BASS_StreamCreateFile( false, "sounds/menu.mp3", 0, 0, // ���� ���
							BASS_SAMPLE_LOOP);						// ���ਯ��  ��⮪ 

    if( !menuMusic )
	{
         MessageBoxA(NULL, "������ �������  ����������� ������", "������", NULL);
		exit(1);
    }

    /*- ����ᥭ�� ������ � ������ -*/
	ifstream in ("data/ranks.dat");

    for(int i = 0; !in.eof(); i++)
    {
        in >> ranks[i];

        for(int j = 0; ranks[i][j] ; j++)
            if(ranks[i][j] == '_')
               ranks[i][j]  = ' ';
    }
    /*- ����㧪� � �� ���짮� ⥫�� */
	load_userBase();
	
    /*- ����㧪� � ��஥� -*/
	ifstream set ("data/settings.dat");
	set >> music >> sounds >> delay;

    /*- ����㧪� ४�म� -*/
	ifstream hs ("data/highscore.dat");

	for(int i = 0; i < 6; i++)
	{
		hs >> hslist[i].nickname >> hslist[i].score;
	}
	
    if ( !music )				// �᫨ � ����ன��� 㪠���� �� ��몠 �� ������ �����
        alreadyPlay = true;		// �� ᤥ���� ⠪ �⮡� ��� �� ��ࠫ�

	if( !alreadyPlay )							// �᫨ �� ���ந��������
	{
		alreadyPlay = true;	
        BASS_ChannelPlay(menuMusic, true);		// ��砫� ���ந��������
	}

	while(true)
	{
        menu();	// � 横�� ��� ��� ⮣� �⮡� � ��� �������� � ����
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
    ifstream menu ("data/menu_image.dat");	// ���� � ���孨� � ������ �ᥢ������᪨�
	int X, Y;								// ⥪�⮬
	char menuPart;
	
    HSTREAM menuMusic = BASS_StreamCreateFile( false, "sounds/menu.mp3", 0, 0, // ��������
                        BASS_SAMPLE_LOOP);						// ���ਯ�� ��⮪
	
		

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
    printSymb(196, 80);		// ��ᮢ ��� ���孥� ���
	
	/*----- ����  業��  �� ����� 饭�� �� ��㣮� �㭪樨 --*/
	setcursor(0, 8);

	for(int i = 0; i < 80 * 9; i++)
		cout << ' ';
	
    // ��ᮢ ��� ������ ���
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
        }							// ��ᮢ ��� ������ ���
	}
	setcursor(0, 0);	// ��� ������ ᬥ饭�� ���᮫�


    setcolor(GRAY, BLACK);		// ��⠭���� 梥�
	setcursor(20, 7);			

	cout << (char) 194; printSymb(196, 40); cout << (char) 194;

	X = 20; Y = 7;
	for( int i = 0; i < 9; i++)				// ��ᮢ ��� �।���
	{
		setcursor(X, ++Y);
		cout << (char) 179; printSymb(' ', 40); cout << (char) 179;
	}

	setcursor(X, ++Y);
	cout << (char) 193; printSymb(196, 40); cout << (char) 193;

	/*----------------------- ����  ----------------------------*/
               /*--- ��६�饭�� �� �㭪⠬ ---*/

	setcolor(WHITE, BLACK);
    int choise;		// �롮� �㭪� ����
	int move = 0;	// ��६�饭�� �� ����

    HCHANNEL sound = BASS_SampleGetChannel              // ����祭�� ���ਯ��
        (BASS_SampleLoad(false, "sounds/select.mp3",	// ������
		NULL, NULL, 2, 0 ),
		false); 
	
	if( !sound )
	{
        MessageBoxA(NULL, "�訡�� ����祭�� ���ਯ�� ������", "��믪�", NULL);
		return;
	}

	char *Menu[] =
	{
        "����� ���",
        "����㧨�� ����",
        "���짮��⥫�",
        "����ன��",
		"������",
        "� �ணࠬ��",
		"��室"
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
							
                printCenter("����� ���",		Y);
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

                printCenter("����㧨�� ����",  Y);
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

                printCenter("���짮��⥫�",	   Y );
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

                printCenter("����ன��",	   Y );
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

				printCenter("������",		   Y);
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

                printCenter("� �ணࠬ��",	   Y);
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

				printCenter("��室",		   Y);
				setcolor(WHITE, BLACK);
			
				break;
			}
		}


		if( move < 6 )
		{
            if( GetAsyncKeyState(VK_DOWN) )	// �᫨ ����� �� ���  "����"
			{
				move++;
				
				setcolor(GRAY, BLACK);
				setcursor(20, Y);
				cout << (char) 179; printSymb(' ', 40); cout << (char) 179;
				
				setcolor(WHITE, BLACK);
				printCenter(Menu[Y-9], Y); 

				Y++;
				if (sounds)			// +��� ����� ������v
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
				if (sounds)			// +��� ����� ������v
					BASS_ChannelPlay(sound, true);
		}
		if( move > 0 )
		{
            if( GetAsyncKeyState(VK_UP) )		// �᫨ ����� �� ���  �����
			{
				move--;

				setcolor(GRAY, BLACK);
				setcursor(20, Y);
				cout << (char) 179; printSymb(' ', 40); cout << (char) 179;
				
				printCenter(Menu[Y-9], Y);
				setcolor(WHITE, BLACK);

				Y--;
				if (sounds)			// +��� ����� ������v
                    BASS_ChannelPlay(sound, true);	// �ந��뢠��� ���  �� ����⨨ �� ���
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
				if (sounds)			// +��� ����� ������v
					BASS_ChannelPlay(sound, true);
			}	
		

        if( GetAsyncKeyState(VK_RETURN))	// ���室 � �㭪樨 �� ������ Enter
			choise = move;					

		while( GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) ||
			   GetAsyncKeyState(VK_RETURN));

		

		/*----- ���室 � ��� ���� �㭪樨 -----*/
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
				alreadyPlay = true;	// ��� �� �� �� �� ��� ��� ?
				if (load( true ))		// ��� �� �㭪�� � ��㧪� � � �� �� �� �맮� ���� �� ����
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

	BASS_Free();	// �᢮�������� ���ன�� 
	
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

		/*------- �롮� ०��  � ���� ����� ------*/
		int X, Y, _menu = 0, choise = -1;
		setcolor(WHITE, BLACK);

		X = 30; Y = 11;

		mkFrame(6, 20, X, Y);

		setcursor(32 , 12);
		cout << "�롥�� ०��: ";

		X = 34; Y = 14;
		while(choise < 0)
		{
			printCenter("������� vs CPU",		14);
			printCenter("CPU vs CPU",   15);

			switch(_menu)
			{
			case 0:

				setcolor(WHITE, GRAY);
				printCenter("������� vs CPU", 14);
				setcolor(WHITE, BLACK);

				break;

			case 1:
				setcolor(WHITE, GRAY);
				printCenter("CPU vs CPU", 15);
				setcolor(WHITE, BLACK);

				break;
			}
            /*------------  ������ �� ��� ---------*/
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

            if( GetAsyncKeyState(VK_ESCAPE) )		// �᫨ ���짮� ⥫� ��� ��� � ���� ����⨥� ESC
				return 2;

			if( GetAsyncKeyState(VK_RETURN) )
			{
				choise = _menu;					// �롮�
				mode = _menu+1;
			}
			while( GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) ||
				GetAsyncKeyState(VK_RETURN));

			if(choise < 0)
				getch();		
		}
		/*--------------- �롮� ०��  � ���� ����� ------*/
		switch(choise)
		{
		case 0:

			p2.cpu = true;

			X = 27; Y = 13;
			mkFrame(5, 22, X, Y);

			setcursor(29, 14);
            cout << "������ ��� ���";

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
	
/*------------- ���㥬 䮭--------------------------*/
	screen();

	if ( !loaded)
	{
		if( p1.cpu )
		{
			p1.generateMap();		// �᫨ ��� � ०�� "CPU vs CPU"
			strcpy((char *)p1.nickname.c_str(), "CPU1");
			strcpy((char *)p2.nickname.c_str(), "CPU2");
		}
		else
		{
			p2.generateMap(); 
			
            p2.printMap(); // ���㥬 ����� ��ண� ��ப

			if( !p1.createMap()	)
				return 2;		// ����� 饭�� � ����

			p1.printMap();
			strcat((char*)p2.nickname.c_str(), "CPU");	
		}

	}

	if( loaded || !p1.cpu)	//	���  祫����  ��⨢ CPU
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
            printCenter("��� 室", 0);

			// �뢮� १��� ⮢
			setcursor(0, 1);
            cout << "�窨: " << p1.score << " ���������: " << p1.damaged << " �஬�客: " << p1.miss;
			setcolor(DARK_GREEN, BLACK);
			cout << (char) 176;
			setcolor(WHITE, BLACK);

			setcursor(43, 1);
            cout << "�窨: " << p2.score << " ���������: " << p2.damaged << " �஬�客: " << p2.miss;
			setcolor(DARK_GREEN, BLACK);
			cout << (char) 176;
			setcolor(WHITE, BLACK);

			res = p1.atackHum(&p2);
			if ( !res )
			{
				win = true;
				break;
			}
			if ( res == 50)		// �᫨ � ����ਨ�஢�� ���� ��� �  ���� ��室  � ����
				return 2;		// � ������ ��� ����� �४� �� �믮������ �㭪�� Play � menu
			p2.y = 3;
			p2.printMap();

			if(p2.y != 3 )
				getch();

			
			setcursor(0, 0);
			setcolor(WHITE, BLACK);
			printSymb(' ', 80);
            printCenter("��� ��⨢����", 0);
					
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
		Player *winner;		// ������ ���������  (��, ���� ���� �� ����� :)
		while( true )
		{

			setcursor(0, 0);
			setcolor(WHITE, BLACK);
			printSymb(' ', 80);
			setcursor(36, 0);
			cout << "��� " << p1.nickname;

			setcursor(0, 1);
            cout << "�窨: " << p1.score << " ���������: " << p1.damaged << " �஬�客: " << p1.miss;
			
			
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
			cout << "��� " << p2.nickname;

			setcursor(43, 1);
            cout << "�窨: " << p2.score << " ���������: " << p2.damaged << " �஬�客: " << p2.miss;
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
		cout << winner->nickname << " �������";
		
		getch();
	}
}

/*---------- ���饭� � ��⠭���� �����  ---------*/
void setcursor(int X, int Y)
{
	cursorPos.X = X;
	cursorPos.Y = Y;

	SetConsoleCursorPosition(consoleOutput, cursorPos);
}

/* ----- � ��� ᨬ��� � ᪮�쪮 � � �뢥�� */
void printSymb(int symbol, int times = 1)
{
	for(times; times; times--)
		cout << (char) symbol ;
}

/*------ ��� �� ��� ��ࠡ��---------*/
/*type 
0 - �।��� ���� ��ࠡ��, 1 - � � �� ��ࠡ��, 2 - ����� ��ࠡ��, 3 - �������� ��ࠡ��
4 - ���०���� � �।��� ����, 5 - ���०������ � � �� ��ࠡ��, 6 - ���०����� ����� ��ࠡ��,
7 - ����⮦���� ������� ��ࠡ��
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
            {		// �� ���०���� � �।��� ���� ��ࠡ��
				printSymb(205, 3);
				setcursor(X, Y+1);
				printSymb(205, 3);
				
				break;
			}
        case 1:		// �� ���०������ � � �� ��ࠡ��
			{
				cout << (char) 213 << (char) 205 << (char) 205; 
				setcursor(X, Y+1);
				cout << (char) 212 << (char) 205 << (char) 205; 
				
				break;
			}
        case 2:		// �� ���०����� ����� ��ࠡ��
			{
				cout  << (char) 205 << (char) 205 << (char) 184 ; 
				setcursor(X, Y+1);
				cout  << (char) 205 << (char) 205 << (char) 190 ;
				
				break;
			}
        case 4:		// ���०���� � �।��� ���� ��ࠡ��
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
        case 5:		// ���०������ � � �� ��ࠡ��
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
	else	// �᫨ ���⨪ �쭮
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
	int xDefault = x;		// � � �� � ������ X;
		
	setcursor(x, y);

	for(Y = 0; Y < 10; Y++)
	{
		for(X = 0; X < 10; X++)
		{
			setcursor(_x, _y);
			
            /*- �᫨ ����  ����� ���०������ ���� ��ࠡ�� -*/
			if(  map[Y][X] == 1)
			{
				
				if( ((Y == 9) || (  map[Y+1][X] != 1 &&  map[Y+1][X] != 3 )) &&  // ����஫� ��室  �  
                    ((Y == 0) || (  map[Y-1][X] != 1 &&  map[Y-1][X] != 3 )) &&  // �।��� ���ᨢ
					((X == 9) || (  map[Y][X+1] != 1 &&  map[Y][X+1] != 3 )) &&  // ������� �� �������
					((X == 0) || (  map[Y][X-1] != 1 &&  map[Y][X-1] != 3 )) )
					printPart(7, true, _x, _y);

                /*----  �஢�ઠ �� �� Y ----*/
                if( ((Y < 9) && ( map[Y+1][X] == 3 ||  map[Y+1][X] == 1)) &&	// ���� �� �।��� �����
					((Y > 0) && ( map[Y-1][X] == 3 ||  map[Y-1][X] == 1)))	// �� ���⨪ �쭮� ��
					printPart(4, false, _x, _y);
				else
				{
                    /*- �஢�ઠ ���� ⥪�饩 ���⪨-*/
                    if ( (Y < 9) && (map[Y+1][X] == 3 ||  map[Y+1][X] == 1))	// ������� � � ��� ��ࠡ��?
						printPart(5, false, _x, _y);				

                    /*- �஢�ઠ ��� -*/
                    if ( (Y > 0) && (map[Y-1][X] == 3 ||  map[Y-1][X] == 1))	// ������� ���殬 ��ࠡ��?
						printPart(6, false, _x, _y);
				}
                /*--------�஢�ઠ �� �� X ------*/
                if( ( (X<9) && ( map[Y][X+1] == 3 ||  map[Y][X+1] == 1)) &&	// ���� �� �।��� �����
                    ( ( X ) && ( map[Y][X-1] == 3 ||  map[Y][X-1] == 1 )))	// �� ��ਧ��⠫쭮� ��?
					printPart(4, true, _x, _y);
				else
				{
                    if ( (X < 9) && ( map[Y][X+1] == 3 ||  map[Y][X+1] == 1))	// ������� � � ��� ��ࠡ��?
						printPart(5, true, _x, _y);				
					
                    if ( ( X ) && ( map[Y][X-1] == 3 ||  map[Y][X-1] == 1))	// ������� ���殬 ��ࠡ��?
						printPart(6, true, _x, _y);
				}

			}
            /*- �᫨ ����  ����� �� ���०������ ���� ��ࠡ�� -*/
			else	// if(
            if( mode == 2 || ! cpu )	// �᫨ ०�� "CPU vs CPU' ��� �뢮����� ����  ��ப
			{			
				if(  map[Y][X] == 3)
				{
                    /*----- �஢�ઠ �  �����筮��� -----*/

					if( ((Y == 9) || ( map[Y+1][X] != 1 &&  map[Y+1][X] != 3 )) && 
						((Y == 0) || ( map[Y-1][X] != 1 &&  map[Y-1][X] != 3 )) && 
						((X == 0) || ( map[Y][X-1] != 1 &&  map[Y][X-1] != 3 )) &&  // ������� �� �������
						((X == 9) || ( map[Y][X+1] != 1 &&  map[Y][X+1] != 3 )) )	
						printPart(3, true, _x, _y);

                    /*----  �஢�ઠ �� �� Y ----*/
				if( ((Y < 9) && (  map[Y+1][X] == 3 ||  map[Y+1][X] == 1)) &&		// ������� �� �।���
                    ((Y > 0) &&	(  map[Y-1][X] == 3 ||  map[Y-1][X] == 1)))		// �����
						printPart(0, false, _x, _y);
					else
					{
						if ( (Y < 9) && ( map[Y+1][X] == 3 ||  map[Y+1][X] == 1))	// ������� � � ���?
							printPart(1, false, _x, _y);	
						if ( ( Y ) && ( map[Y-1][X] == 3 ||  map[Y-1][X] == 1)) // ������� ���殬?
							printPart(2, false, _x, _y);

					}

                    /*- �஢�ઠ �� �� X ====-*/
					if( (( X > 0 ) && ( map[Y][X-1] == 3 ||  map[Y][X-1] == 1) ) && 
                        (( X < 9 ) && ( map[Y][X+1] == 3 ||  map[Y][X+1] == 1) ))	// ������� �� �।��� �����
						printPart(0, true, _x, _y);
					else
					{								
						if( ( X ) && ( map[Y][X-1] == 3 ||  map[Y][X-1] == 1))	
							printPart(2, true, _x, _y);

						if( ( X < 9 ) && ( map[Y][X+1] == 3 ||  map[Y][X+1] == 1)	) // ����஫� ��室  �  �।��� 
                            printPart(1, true, _x, _y);						// ���ᨢ
					}									
					
				
				} // if(  map[Y][X] == 3)
				if ( ! map[Y][X] ) // �᫨ ⥪�� � ����  ���� 
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
			if (  map[Y][X] == 2 ) // �᫨ ⥪�� � ����  ���� �஬ � 
			{
				setcolor( WHITE, BLUE);

				printSymb(176, 3); 	
								
				setcolor( WHITE, BLUE);
				setcursor(_x, _y+1);
				printSymb(176, 3);

				setcolor(WHITE, DARK_BLUE);
			}

				_x += 3;		// ���室 � ᫥���饩 ���⪥
		}	// for(X = 0; X < 10; X++)
		
		_x = xDefault;	// ��� �� �� X
		_y += 2;			// ��� � ���� �� Y �  ����� ��ப�
	}
}

/*--- �뢮� ⥪��  �� 業��� ---*/
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
            return false;					// �᫨ ����� ESC, � �������� � �� ���� ����

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
	bool again = false;		// ����� � ��  � � 
    bool destr = false;		// ����⮦�� �� ��ࠡ��
    int X, Y;				// ������ � ���ᨢ�
    int parts = 0;			// ������⢮ ��⥩ ⥪�饣� ��ࠡ��
					// �ॡ���� ��� �뢮�  ᮮ�饭�� 

	bool remained = false;	
    int _x, _y;				// ���न���� ���  � �� �� � ��� ���� � �᭮����
	
	HCHANNEL damageSnd = BASS_SampleGetChannel			// ��� ��� � ���
		(BASS_SampleLoad(false, "sounds/damaged.mp3",	
		NULL, NULL, 2, 0 ),
		false);

	HCHANNEL missSnd = BASS_SampleGetChannel			// ��� �஬ � 
		(BASS_SampleLoad(false, "sounds/miss.mp3",	
		NULL, NULL, 2, 0 ),
		false); 

	bool incr;
	bool XorY;

	while( true )		// ��騩 横�
	{		
		if( p1.cpu )
			pl->printMap();
		
        if( !again || destr)	// �᫨ �� �� ����� �  � �  ��� ��ࠡ�� 㭨�⮦��
		{
			do
			{
				incr = rand()%10 % 2;		// ���६���஢ ��� ��� ���६���஢ ���
				XorY = rand()%10 % 2;		// X ��� Y. �᫨ true, � X

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
				 
			} while (true);	// ���� ᢮������ ��� ��		
		}
        else		// �᫨ �� ����� �  � �  �� ��㭨�⮦������ ��ࠡ��
		{
			while(true)	// ��।������ ���� 
			{
				
                /*--- �஢�ઠ �  ��室 �  ���ᨢ ---*/
				
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
				if( XorY )		// �᫨ X
				{
					if( incr && X == 9)	// �᫨ ���६��� �������⨬
						incr = false;	// � ᤥ� �� ���६��⮬
					
					if( !incr && X == 0) // �᫨ ���६��� �������⨬
						incr = true;	// � ᤥ� �� ���६��⮬
				}
				else			// �᫨ Y
				{
					if( incr && Y == 9)	// �᫨ ���६��� �������⨬
						incr = false;	// � ᤥ� �� ���६��⮬

					if( !incr && Y == 0) // �᫨ ���६��� �������⨬
						incr = true;	// � ᤥ� �� ���६��⮬
				}
				
				/*- �롮� ᫥���饩 �窨 ���  � �� -*/
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

				// �᫨ ����� ⮫쪮 �� ���室�騥 ���  � �� ���⪨, � �� �� ��㣮� ���� 
				if(( !remained &&
					(pl->map[Y+1][X] != 3) &&
					(pl->map[Y-1][X] != 3) &&
					(pl->map[Y][X+1] != 3) &&
					(pl->map[Y][X-1] != 3)))
				{
					destr = true;
					break;
				}

			/*-- �� ��� �  �� ��  ���  � ���--*/
                // �᫨ ��  � ��� � , � �������� 横� � ���������  � ��� �� ����
			
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

				if( incr && XorY)		// ���६���஢ ��� �� X
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
				if( !incr && XorY)		// ���६���஢ ��� �� X
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
				if( !incr && !XorY)		// ���६���஢ ��� �� Y
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
				if( incr && !XorY)		// ���६���஢ ��� �� Y
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
        /*- "�⠪� " -*/
		
		if(pl->map[Y][X] == 0)
		{
			Sleep(delay);
			if (sounds)			// +��� ����� ������v
				BASS_ChannelPlay(missSnd, false);

			pl->map[Y][X] = 2;
			scrChange(false);

			return pl->remain;
		}
		if(pl->map[Y][X] == 3)
		{
			Sleep(delay);
			destr = false;
			if (sounds)			// +��� ����� ������v
				BASS_ChannelPlay(damageSnd, true);

			pl->map[Y][X] = 1;
			scrChange(true);
			
            pl->remain--;		// ���ਬ���஢ �� ��⠢襥�� ������⢮ ��⥩
            if( !pl->remain)	// �᫨ �� ��� ���� ����� ��ࠡ���,
				return pl->remain;	// �� ������ ����
			
			again = true;

            //--- �஢�ઠ 㭨�⮦�� �� ��ࠡ�� //
	
            /*- �᫨ ����� ��ࠡ�� �� ����� -*/
			if( remained == false && 
				((Y < 9) && (  pl->map[Y+1][X] != 3)) &&  // ����஫� ��室  �  
                ((Y > 0) && (  pl->map[Y-1][X] != 3)) &&  // �।��� ���ᨢ
				((X < 9) && (  pl->map[Y][X+1] != 3)) &&  // ������� �� �������
				((X > 0) &&	(  pl->map[Y][X-1] != 3)) )
			{
					destr = true;	// �� �।�������� �� �� 㭨�⮦��
			}
			
			if( ((Y < 9) && pl->map[Y+1][X] == 3) ||  
                ((Y > 0) && pl->map[Y-1][X] == 3) ||  // �᫨ ����� ���� ���� ��ࠡ��
				((X < 9) && pl->map[Y][X+1] == 3) ||  
				((X > 0) && pl->map[Y][X-1] == 3) )
                    destr = false;					// �� �� ��ࠡ�� �� 㭨�⮦��


		// ��।������ ���������
            /*--- �஢�ઠ �  ��室 �  ���ᨢ ---*/
			
			

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
            // �᫨ �� � ��ࠡ��
			if (incr && XorY)
				if (pl->map[Y][X+1] != 3 && !remained)
                    destr = true;				// �᫨ �� �� � ��ࠡ��, � �� �� ��㣮� ���� ���  � ��
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

int Player::atackHum(Player *pl)	// ����� � �� ������⢮ ��� ���� ��⨢��� 
{	
    Coord coord;    // ���न���� ��� �⠪�
	coord.ESC = false;
	int i = 0;		// �롮� ����ਨ�஢��� ����
	
	
	HCHANNEL damageSnd = BASS_SampleGetChannel			// ����祭�� ���ਯ�� 
		(BASS_SampleLoad(false, "sounds/damaged.mp3",	// � � �  
		NULL, NULL, 2, 0 ),
		false);

	HCHANNEL missSnd = BASS_SampleGetChannel			// ����祭�� ���ਯ�� 
		(BASS_SampleLoad(false, "sounds/miss.mp3",	// � � � 
		NULL, NULL, 2, 0 ),
		false); 

	HCHANNEL alreadyAtacked = BASS_SampleGetChannel		// ��� �訡��.
		(BASS_SampleLoad(false, "sounds/already_atacked.mp3",
		NULL, NULL, 2, 0 ),
		false);

    /*-------- ���� ���न��� --------*/
	while(true)
	{
		i = 0;
		setcolor(WHITE, BLACK);
		setcursor(0, 24);
		printSymb(' ', 80);
		setcursor(0, 0);
        printCenter("������ ���न���� ��� �⠪� ___\b\b\b", 24);
        coord = coord_input();
		if( coord.ESC == true)
		{
			return 50;	// ��᫠�� ᮮ⢥�����騩 ᨣ���
		}	

        /*-----�஢�ઠ ����� �� �������� ���न��� � -------*/

		if(	pl->map[coord.y][coord.x] == 1 ||	
			pl->map[coord.y][coord.x] == 2)// �᫨ �� ����  � ��� ���� � ���
		{
			if( sounds ) // +��� ����� ������v			
				BASS_ChannelPlay(alreadyAtacked, false);
		}
		else if( pl->map[coord.y][coord.x]== 0 ) 	// �᫨ �஬ �
		{
			if (sounds)			// +��� ����� ������v
				BASS_ChannelPlay(missSnd, false);
			pl->map[coord.y][coord.x] = 2;

			scrChange(false);		// ��������� ���   � ���饣�
			pl->printMap();
			return pl->remain;
		}
		else						// �᫨ ��� � ���
		{
			scrChange(true);
            if (sounds)			// �᫨ ��㪨 ����祭�
				BASS_ChannelPlay(damageSnd, true);

			pl->map[coord.y][coord.x] = 1;
			pl->remain--;
			pl->printMap();
			if( !pl->remain)
				return pl->remain;
		}
	}
}

/*- ����ਨ�஢�� ����  -*/
int ingameMenu()
{
	int X, Y;
	int move = 0, choose = -1;
	
	mkFrame(8, 32, 24, 11);	// ���� ��� � ���(�३� )
	
	char *_menu[] =
	{
		"�������� � ����",
        "���࠭��� ����",
        "����㧨�� ����",
        "�������� � ������� ����",
		"��� �� ����"
	};
	while(choose < 0)
	{
		setcolor(WHITE, BLACK);
		
		for(int i = 0; i < 5; i++)
			printCenter(_menu[i], i+12);
		
		setcolor(WHITE,GRAY);
		printCenter(_menu[move], move + 12);
		// �।��� 饭�� � �樨 �ண� ��� �  㤥ন� ��� �� ���
		while(GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || 
			  GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_ESCAPE));
		getch();
		if(GetAsyncKeyState(VK_ESCAPE))
		{
			screen();
            return 1;					// �᫨ �����ESC, �������� � ����
		}
		if(GetAsyncKeyState(VK_RETURN))
		{
			choose = move;
			if( choose == 3)
				return 0;		// ����� 饭�� � �� ���� ����
		
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
	/*--      �롮�     -*/
	switch(choose)
	{
	case 1:
        save();			// ���࠭���� ����
		break;
	case 2:
        load( false );			// ����㧪� ����
		break;
		
	case 4:
		exit(0);		// ��室 �� ����
	}

	screen(); // ����� �������� ���� ��। ��室�� �� �㭪樨	
	return 1;
}

/*- ���� ����� ���� -*/
void save()
{
	while(GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_ESCAPE));

	int move = 0;	// ��६�饭�� �� ����
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
    cout << "�롥�� ᫮� ��� ��࠭����";
	while(choise < 0)
	{

		for(int i = 0; i < 4; i++)
		{
			setcolor(WHITE,BLACK);
			setcursor(25, i+17);

			if( !strcmp("none", svname[i]))
                cout << "���࠭���� ���������";
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
            cout << "���࠭���� ���������";
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

	// ����祭�� ����� � �� 
	char filename[15];
	strcpy(filename, "save/save");
	filename[9] = choise + 48;
	filename[10] ='\0';
	strcat(filename, ".sav");

	ofstream sav (filename);

	if (!sav)
	{
        MessageBoxA(NULL, "������ ��������� ", "������ ", 0);
		return;
	}

	/*----- ���� ����� ----*/
	for(int i = 0; new_name[i]; i++)
		if( new_name[i] == ' ')		// � ���  �஡��  �  '_' � 楫�� ���������� ��� ����� � �஡����
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
	cout << "���������";
	getch();
}

/*- ���� ��� � ��� -*/
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

/*- ����� ��������\�뢮� �� �  -*/
void screen()
{
	int X, Y;
	/*- ���㥬 䮭 -*/
	setcursor(0, 0);
	setcolor(DARK_GREEN, BLACK);
	printSymb(176, 80 * 25);
	setcursor(0, 0);

    /*- ���㥬 ���न���� ����� 祭�� -*/
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
	
    /*- ���㥬 ����� -*/
	p1.printMap();
	p2.printMap();

	/*- �������⥫�� � ���� -*/
	setcolor(WHITE, BLACK);
	setcursor( 0, 0);
	printSymb(' ', 80);
	
	if( !p1.cpu )
		printCenter("� � 室", 0);
		
	setcursor(0, 24);
	printSymb(' ', 80);
	setcursor(0, 0);

	// �뢮� १��� ⮢
	setcursor(0, 1);
    cout << "�窨: " << p1.score << " ���������: " << p1.damaged << " �஬�客: " << p1.miss;
	setcursor(43, 1);
    cout << "�窨: " << p2.score << " ���������: " << p2.damaged << " �஬�客: " << p2.miss;

	setcursor(20 - p1.nickname.length(), 23);
	cout << p1.nickname;
	setcursor(60 - p2.nickname.length(), 23);
	if( !p1.cpu)
        printCenter("������ ���न���� ��� �⠪� ___\b\b\b", 24);
}

/*- ����㧪� ���� -*/
bool load(bool from_menu)
{
	while(GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_ESCAPE));

	loaded = true;		// �� �� �� �� ���  � ��㦥� 

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
    cout << "    �롥�� ��࠭����";
	while(choise < 0)
	{

		for(int i = 0; i < 4; i++)
		{
			setcolor(WHITE,BLACK);
			setcursor(25, i+17);

			if( !strcmp("none", svname[i]))
                cout << "���࠭���� ���������";
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
            cout << "���࠭���� ���������";
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
	ifstream loading (filename);	// filename ����� �� �ॡ����

	check >> nickname;
	if( strcmp("none", nickname) )
	{
		loading >> filename;	// �ய�� �� ��� ��� �����.
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

/*-  ����㧪� � �� ���짮� ⥫�� -*/
void load_userBase()
{
	ifstream uBase ("data/users.dat");
	int i = 0;

	for(int i = 0; !uBase.eof(); i++)
	{
		uBase >> userBase[i].nickname;

		if( !userBase[i].nickname[0] )
			break;		// �᫨ � �� ���� � �� �஢�����
		
		uBase >> userBase[i].wins >> userBase[i].lose 
			  >> userBase[i].rank >> userBase[i].win2increasing;
		userBase[i].occupied = true;
	}
}

/*- ��⠢�� � � �� ������ ���짮� ⥫�, ��� �� ��  १��� ⮢ �� ண� -*/
void put2base(bool win)
{
	int i = 0;
    /*- �஢�ઠ �  㬥�⭮��� ��� ����� -*/
	if( !strcmp("Unknown", p1.nickname.c_str()))
		return;							// �᫨ ��ப �� �।�� �����

	/*- ���� ���짮� ⥫� � � �� -*/
	for( ; ; i++)
	{
		if( !strcmp(p1.nickname.c_str(), userBase[i].nickname))
			break;

		if( !userBase[i].occupied )		// �᫨ � ����  �� � ��� � ��� ���
			break;
	}

	/*- ���� ����� ���짮� ⥫� -*/
	strcpy(userBase[i].nickname, p1.nickname.c_str());
	userBase[i].occupied = true;
	
	if( win)
	{
		setcolor(GREEN, BLACK);

		++ userBase[i].wins;
		-- userBase[i].win2increasing;

		if ( userBase[i].win2increasing < 0)		// �᫨ ����� ���� �筮 �⮡� "�������"
		{
			printCenter("�� ����稫� ����� �� ���!", 15);

			++ userBase[i].rank;
			userBase[i].win2increasing = 5;
		}

		setcursor(12, 16);
        cout << "��� ⥪�饥 ������: " << ranks[ userBase[i].rank ];
		setcursor(12, 17);
        cout << "��⠫��� " << userBase[i].win2increasing << " ����� �� ᫥���饣� ������";
        printCenter("���� � ����� ��⢠�!", 20);
	}
	else
	{
		setcolor(RED, BLACK);
		++ userBase[i].lose;

		if( userBase[i].win2increasing < 5)		
			++ userBase[i].win2increasing;

		setcursor(12, 16);
        cout << "��� ⥪�饥 ������: " << ranks[ userBase[i].rank ];
		setcursor(12, 17);
		cout << "��� ���� " << userBase[i].win2increasing << " ����� �� ᫥���饣� �� ���";

        printCenter("���� � ᫥���騩 � �.", 20);

	}

	save_userBase();
} 

/*- ���� ����� � �� ���짮� ⥫�� � � �� -*/
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
/*- �� ��� ��ப  �  ������ ����� ��� ���� -*/
void playerState( bool win )
{
	setcursor(0, 0);
	setcolor(GREEN, BLACK);
	printSymb(' ', 80 * 25);
	setcursor(0, 0);

	if ( win )
	{
        printCenter("����ࠢ�����!", 11);
		printCenter("�� ������⥫�!", 12);

		put2base(true);

		if( p1.score > hslist[5].score )	// �᫨ १��� � ४�भ�
		{
            /*- ���� ����樨 ��� ��⠢�� � ᯨ᮪ */
			int i;
			for (i = 0; i < 6; i++)
				if( hslist[i].score <= p1.score )
					break;
			
			for( int j = 0; j < i; j++)  // ���饭�� ��������� 
				hslist[j] = hslist[j+1];
			
			strcpy(hslist[i].nickname, p1.nickname.c_str()); // ����饭�� � ᯨ᮪
			hslist[i].score = p1.score;
			hslist[i].record = true;

			getch();
			records();
		}

	}
	else
	{
		setcolor(RED, BLACK);
        printCenter("�� �ந�ࠫ�", 11);
		put2base(false);
	}

	
	getch();
}


/*- �뢮� ��� ���짮� ⥫�� -*/
void showUsers()
{
	int start_pos = 0;		// �� �⮢ � ������ ��� �뢮� 
	int Y;
	/*- � ������� -*/
	setcolor(WHITE, BLACK);
	setcursor(0, 0);
	printSymb(' ', 80);
	printCenter("���짮��⥫� ����� ���� ��ࠢ訥 � ��� ����", 0);

	/*- ��ᮢ ��� � ����� -*/
	mkFrame(24, 80, 0, 1);
	setcursor(0, 0);
	
    /*- �஢�ઠ �������  -*/
    if( !userBase[0].occupied )			// �᫨ � �  ����
	{
		while(!GetAsyncKeyState(VK_ESCAPE))
		{
			printCenter("���� ���짮��⥫�� ����. ����� �� �⠭�� ����?", 4);
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
            cout << "�������\t\t�����\t��ࠦ����\t������\t����� �� ����襭��";

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
		
        /* �뢮� �।������� ������ �� ��� */

        if( start_pos )			// �᫨ ����⨥ PG_UP �����⨬�
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
        /* ���� � ������ �� ��� */
        getch();							// ���� ��� ������

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


/*- � ��ப� -*/
void settings()
{
	while(GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_ESCAPE));

	bool change = false;
	int Y = 7, move = 0;
	ifstream set("data/settings.dat");

	setcursor( 0, 0);
	setcolor(WHITE, BLACK);
	printSymb(' ', 80 * 25);
	
	/*- ��ଫ���� -*/
	printCenter("����ன�� ��㪠", 3);
	setcursor(0, 4);
	printSymb(196, 80);

	printCenter("����ன�� ����", 10);
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
        cout << "��몠 " << (musicOn ? "��� " : "����");
		setcursor(6, 8);		
		cout << "��㪨 " << (soundsOn ? "��� " : "����");
		setcursor(6, 12);
		cout.precision(2);
        cout << "����প� ����� �⠪���: " <<  new_delay / 1000 << " ᥪ.";
        setcursor(6, 13);
        cout << "������ �� १����� � ����ன��";

		// �뤥����� ��� ����� �㭪� 
		setcolor(WHITE, GRAY);
		if( move == 0)
		{
			setcursor(6, 7);
            cout << "��몠 " << (musicOn ? "���" : "����");
		}
		if( move == 1)
		{
			setcursor(6, 8);
			cout << "��㪨 " << (soundsOn ? "���" : "����");
		}
		if( move == 2)
		{
			setcursor(6, 12);
            cout << "����প� ����� �⠪���: " << new_delay / 1000 << " ᥪ.";
		}
        if( move == 3)
        {
            setcursor(6, 13);
            cout << "������ �� १����� � ����ன��";
        }
        // ���� � �� ��� � ��� ���  ����⨩ �� ���
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
                cout << "������ ����� ���祭��: ";
				cin >> new_delay;
				new_delay *= 1000;

                change = true;
			}				
            else if( move == 3)
            {
                while( true)
                {
                    mkFrame(  3, strlen( "�� 㢥७�? y/n  "),
                              40 - (strlen( "�� 㢥७�? y/n  ") / 2),
                              10);
                    printCenter( "�� 㢥७�? y/n", 11);
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
                cout << "��१������ ����, �⮡� ";
				setcursor(27, 13);
				cout << "��������� ���㯨�� � ᨫ� ";
				getch();

			}
			while( GetAsyncKeyState(VK_ESCAPE) );
			return;
		}
		while( GetAsyncKeyState(VK_RETURN)  || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT) ||
			GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN));
	}	
}
/*- ������ -*/
void records()
{
	while(GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_ESCAPE));

	ofstream hs("data/highscore.dat");
	int Y = 10;
	// ��� 襭��
	setcolor(WHITE, BLACK);
	setcursor(0, 0);
	printSymb(' ', 80 * 25);
	setcursor(0 , 0);

    printCenter("���訥 १�����", 3);
	setcursor(0, 5);
	printSymb(196, 80);

	setcursor(0, 20);
	printSymb(196, 80);

	// �뢮� १��� ⮢

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

/*- � ��������� -*/
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
    cout << "�ᥬ ��� �᪫�祭�� �����⭠�, �, ��������, ���� ���. ����� ��ࠫ� �� ��";
	setcursor(1, 5);	
    cout << "�㬠���� ���뢠� ��� ���� ���न���� ��� �⠪�. �६��� ������ �� �諨, �";
	setcursor(1, 6);
    cout << "������� �� ᨤ�� �� �ப�� � ��ਮ� ������⢨� ��⥫� � ����������";
	setcursor(1, 7);
    cout << "�⮩ ����⥩����� ��ன. �� ॠ������ ᭠砫� �뫠 ���� ��������, �ࠪ⨪��";
	setcursor(1, 8);
    cout << "��� ���� ��� �ணࠬ����. ��騩, �� � �६�, ���� 祫���� ����ਫ �� ��";
	setcursor(1, 9);
    cout << "���室 �� ���� �஢���, � �� �ࠢ: ����� ��� �ணࠬ�� ���頫��� ��ᨫ� �";
	setcursor(1, 10);
    cout << "��� ��ப, � �� ��� ��諠 � 3000 (!) ��ப. � �� �� �।��. ���� ��";
	setcursor(1, 11);
    cout << "����� ᫨誮� ��࠭�祭� � �ॡ�� ��ࠡ�⪨, � ॠ����樨 ���� ����. ��";
	setcursor(1, 12);
    cout << "�㬠� �� �ன��� �祭� ����� �६��� �०�� 祬 � ����� �⥢�� ०��. ";
	setcursor(1, 13);
    cout << "��ਮ� ࠧࠡ�⪨ �� ����� �, �ਧ�����, ������� ������";
	setcursor(1, 14);
    cout << ". � ������ �����, ࠭�� ������������. �� �����쭮 ��ਪ�.";
	setcursor(1, 16);
    cout << "�� ��� ����� 㤮���� �ᥣ� ����� � ��� ���� ��ঠ ���� ��� �� �᭮����";
	setcursor(1, 17);
    cout << "���������, � ����� �� ��஢��. � ���� ����஥� �६� ����প� �����";
	setcursor(1, 18);
    cout << "��⠭�������� �஡���. ��� ��६�饭�� �� ���� �����⢫���� �����ﬨ";
	setcursor(1, 19);
    cout << "��५��, Enter, Esc. � �᫨ � ��� �� �� ����� ����� �㪢� ��� �⠪�";
	setcursor(1, 20);
    cout << "� �� �� ���, � ᬥ��� ��᪫���� �� ��������� :)";
	setcursor(1, 21);
    cout << "����!";
	
    setcursor(1, 24);
	setcolor(GRAY, BLACK);
    cout << "���� �����쭨� AKA Cydeamon\tmailto: cydeamon@gmail.com\t\t2012|07";

	setcolor(WHITE, BLACK);
	setcursor(0, 0);
	getch();
    if(GetAsyncKeyState(0x42)) // �᫨ ���짮��⥫� ����� 'B', � �뢥�� ���堫��
		BlackMesa();
}

void BlackMesa()
{
	while(GetAsyncKeyState(42));
	
    system("cls"); // ���⪠ ���᮫�

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

    printCenter("������ ESC ��� ��室�", 23);
	
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

    /*- ��ଫ���� -*/
    printCenter("����ன�� ��㪠", 3);
    setcursor(0, 4);
    printSymb(196, 80);

    printCenter("����ன�� ����", 10);
    setcursor(0, 11);
    printSymb(196, 80);

    bool musicOn;
    bool soundsOn;
    float new_delay;

    set >> musicOn >> soundsOn >> new_delay;
}
