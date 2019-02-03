#include "stdafx.h"
#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <windows.h>
#include <conio.h>

using namespace std;


class cell
{
public:
	bool mine,check;
	char mean;
	int mass;
};
class field
{
public:
	//создаём поле
	cell * * pole;
	void CreateField(int height,int length)
	{
		pole = new cell*[height];
		for (size_t i = 0; i < height; i++)
		{
			pole[i] = new cell[length];
		};
		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < length; j++)
			{
				pole[i][j].mass = -1;

			}
		}
		cout << "massiv sozdan\n";
	};
	//расставляем мины{pole[i][j].mass=9} и заливаем остальные квадраты значениями {0..8}
	void InitMines(int height, int length,int y,int x)
	{
		int mines;
		mines = round((height*length)*0.21);
		//mines = 1;
		srand(static_cast<unsigned int>(time(0)));
		//--------------------------------------------------------расставляем мины, заполняем остальное"-1"
		pole[y][x].mass = 0;
		if ((y > 0) && (x > 0) && (y < height-1) && (x < length-1))
		{
			pole[y - 1][x - 1].mass = 0;
			pole[y - 1][x].mass = 0;
			pole[y - 1][x + 1].mass = 0;
			pole[y][x + 1].mass = 0;
			pole[y + 1][x + 1].mass = 0;
			pole[y + 1][x].mass = 0;
			pole[y + 1][x - 1].mass = 0;
			pole[y][x - 1].mass = 0;
		}
		if ((y == 0) && (x > 0) && (x < length))
		{
			pole[y][x + 1].mass = 0;
			pole[y + 1][x + 1].mass = 0;
			pole[y + 1][x].mass = 0;
			pole[y + 1][x - 1].mass = 0;
			pole[y][x - 1].mass = 0;

		}
		if ((x > 0) && (y == height - 1) && (x < length - 1))
		{
			pole[y - 1][x - 1].mass = 0;
			pole[y - 1][x].mass = 0;
			pole[y - 1][x + 1].mass = 0;
			pole[y][x + 1].mass = 0;
			pole[y][x - 1].mass = 0;
		}
		if ((y > 0) && (x == 0) && (y < height - 1))
		{
			
			pole[y - 1][x].mass = 0;
			pole[y - 1][x + 1].mass = 0;
			pole[y][x + 1].mass = 0;
			pole[y + 1][x + 1].mass = 0;
			pole[y + 1][x].mass = 0;

		}
		if ((y > 0) && (x > 0) && (y < height - 1) && (x == length - 1))
		{
			pole[y - 1][x - 1].mass = 0;
			pole[y - 1][x].mass = 0;
			pole[y + 1][x].mass = 0;
			pole[y + 1][x - 1].mass = 0;
			pole[y][x - 1].mass = 0;
		}
		if ((x == 0) && (y == 0))
		{
			pole[0][1].mass = 0;
			pole[1][1].mass = 0;
			pole[1][0].mass = 0;
		}
		if ((x == 0) && (y == height-1))
		{
			pole[height-2][0].mass = 0;
			pole[height-2][1].mass = 0;
			pole[height-1][1].mass = 0;
		}
		if ((x == length-1) && (y == height-1))
		{
			pole[height-2][length-1].mass = 0;
			pole[height-2][length-2].mass = 0;
			pole[height-1][length-2].mass = 0;
		}
		if ((x == length-1) && (y == 0))
		{
			pole[0][length-2].mass = 0;
			pole[1][length-2].mass = 0;
			pole[1][length-1].mass = 0;
		}

		while (mines > 0)
		{
			
			for (size_t i = 0; i < height; i++)
			{
				for (size_t j = 0; j < length; j++)
				{
					if (mines == 0) break;
					if ((rand() % 100 < 21) && (pole[i][j].mass != 9)&& (pole[i][j].mass != 0))
					{
						pole[i][j].mass = 9;
						mines--;
					}
					else
					{
						if ((i > height*0.95)  && (rand() % 100 < 40) && (pole[i][j].mass != 0))
						{
							pole[i][j].mass = 9;
							mines--;
						}
					}
					
					
				}
			}
		}

		//расставляем число мин у внутреннего квадрата
		for (size_t i = 1; i < height - 1; i++)
		{
			for (size_t j = 1; j < length - 1; j++)
			{
				if (pole[i][j].mass <=0)
				{
					int mines = 0;

					if (pole[i - 1][j - 1].mass == 9) mines++;
					if (pole[i - 1][j].mass == 9) mines++;
					if (pole[i - 1][j + 1].mass == 9) mines++;
					if (pole[i][j + 1].mass == 9) mines++;
					if (pole[i + 1][j + 1].mass == 9) mines++;
					if (pole[i + 1][j].mass == 9) mines++;
					if (pole[i + 1][j - 1].mass == 9) mines++;
					if (pole[i][j - 1].mass == 9) mines++;
					pole[i][j].mass = mines;

				}
			}
		}
		//инициализируем края
		for (size_t j = 1; j < length - 1; j++)
		{
			if (pole[0][j].mass <= 0)
			{
				int mines = 0;
				if (pole[0][j + 1].mass == 9) mines++;
				if (pole[1][j + 1].mass == 9) mines++;
				if (pole[1][j].mass == 9) mines++;
				if (pole[1][j - 1].mass == 9) mines++;
				if (pole[0][j - 1].mass == 9) mines++;
				pole[0][j].mass = mines;

			}
		}
		for (size_t j = 1; j < length - 1; j++)
		{
			if (pole[height - 1][j].mass <= 0)
			{
				int mines = 0;
				if (pole[height - 2][j - 1].mass == 9) mines++;
				if (pole[height - 2][j].mass == 9) mines++;
				if (pole[height - 2][j + 1].mass == 9) mines++;
				if (pole[height - 1][j + 1].mass == 9) mines++;
				if (pole[height - 1][j - 1].mass == 9) mines++;
				pole[height - 1][j].mass = mines;

			}
		}
		for (size_t i = 1; i < height - 1; i++)
		{
			if (pole[i][0].mass <= 0)
			{
				int mines = 0;

				if (pole[i - 1][0].mass == 9) mines++;
				if (pole[i - 1][1].mass == 9) mines++;
				if (pole[i][1].mass == 9) mines++;
				if (pole[i + 1][1].mass == 9) mines++;
				if (pole[i + 1][0].mass == 9) mines++;

				pole[i][0].mass = mines;

			}
		}
		for (size_t i = 1; i < height - 1; i++)
		{
			if (pole[i][length - 1].mass <= 0)
			{
				int mines = 0;

				if (pole[i - 1][length - 1].mass == 9) mines++;
				if (pole[i - 1][length - 2].mass == 9) mines++;
				if (pole[i][length - 2].mass == 9) mines++;
				if (pole[i + 1][length - 2].mass == 9) mines++;
				if (pole[i + 1][length - 1].mass == 9) mines++;

				pole[i][length - 1].mass = mines;

			}
		}
		//инициализируем углы
		if (pole[0][0].mass <= 0)
		{
			int mines = 0;

			if (pole[0][1].mass == 9) mines++;
			if (pole[1][1].mass == 9) mines++;
			if (pole[1][0].mass == 9) mines++;
			pole[0][0].mass = mines;
		}
		if (pole[0][length - 1].mass <= 0)
		{
			int mines = 0;

			if (pole[0][length - 2].mass == 9) mines++;
			if (pole[1][length - 2].mass == 9) mines++;
			if (pole[1][length - 1].mass == 9) mines++;
			pole[0][length - 1].mass = mines;
		}
		if (pole[height - 1][0].mass <= 0)
		{
			int mines = 0;

			if (pole[height - 2][1].mass == 9) mines++;
			if (pole[height - 2][1].mass == 9) mines++;
			if (pole[height - 1][0].mass == 9) mines++;
			pole[height - 1][0].mass = mines;
		}
		if (pole[height - 1][length - 1].mass <= 0)
		{
			int mines = 0;

			if (pole[height - 2][length - 1].mass == 9) mines++;
			if (pole[height - 2][length - 2].mass == 9) mines++;
			if (pole[height - 1][length - 2].mass == 9) mines++;
			pole[height - 1][length - 1].mass = mines;
		}
		
	}
	//расставляем игровое поле
	void InitField(int height,int length)
	{
		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < length; j++)
			{
				pole[i][j].mean = 'O';
				pole[i][j].mine = false;
				pole[i][j].check = false;
			}
		};
		
	}
	//выводим поле в консоль
	void ShowField(int a, int b) 
	{
		for (size_t i = 0; i < a; i++)
		{
			for (size_t j = 0; j < b; j++)
			{
				if (!pole[i][j].mine)
				{
					if (pole[i][j].check)
					{
						cout << 'F'<<' ';
					}
					else
					{
						cout << pole[i][j].mean << ' ';
					}
				}
				else
				{
					if (pole[i][j].mass == 9)
					{
						cout << 'X' << ' ';
					}
					else
					{
						if (pole[i][j].mass == 0)
						{
							cout << '_' << ' ';
						}
						else
						{
							cout << pole[i][j].mass << ' ';
						}
					}
				
				}
				
			};
			cout << '\n';
		};
	
	}
	//открываем пустые поля
	void OpenFreeCells(int y,int x,int height,int length)
	{
		if ((y>0)&&(y<height-1) && (x>0) && (x<length-1))
		{
			if(pole[y - 1][x - 1].mass!=9) pole[y - 1][x - 1].mine = true;
			if (pole[y - 1][x].mass != 9) pole[y - 1][x].mine = true;
			if (pole[y - 1][x + 1].mass != 9) pole[y - 1][x + 1].mine = true;
			if (pole[y][x + 1].mass != 9) pole[y][x + 1].mine = true;
			if (pole[y + 1][x + 1].mass != 9) pole[y + 1][x + 1].mine = true;
			if (pole[y + 1][x].mass != 9) pole[y + 1][x].mine = true;
			if (pole[y + 1][x - 1].mass != 9) pole[y + 1][x - 1].mine = true;
			if (pole[y][x - 1].mass != 9) pole[y][x - 1].mine = true;
			pole[y][x].check = true;
		};
		if ((y==height - 1) && (x>0) && (x<length - 1))
		{
			
			if (pole[y - 1][x - 1].mass != 9) pole[y - 1][x - 1].mine = true;
			if (pole[y - 1][x].mass != 9) pole[y - 1][x].mine = true;
			if (pole[y - 1][x + 1].mass != 9) pole[y - 1][x + 1].mine = true;
			if (pole[y][x + 1].mass != 9) pole[y][x + 1].mine = true;
			if (pole[y][x - 1].mass != 9) pole[y][x - 1].mine = true;
			pole[y][x].check = true;
		};
		if ((y==0) && (x>0) && (x<length - 1))
		{
			
			if (pole[y][x + 1].mass != 9)pole[y][x + 1].mine = true;
			if (pole[y + 1][x + 1].mass != 9)pole[y + 1][x + 1].mine = true;
			if (pole[y + 1][x].mass != 9)pole[y + 1][x].mine = true;
			if (pole[y + 1][x - 1].mass != 9)pole[y + 1][x - 1].mine = true;
			if (pole[y][x - 1].mass != 9)pole[y][x - 1].mine = true;
			pole[y][x].check = true;
		};
		if ((y>0) && (y<height - 1) && (x==0))
		{
			
			if (pole[y - 1][x].mass != 9)pole[y - 1][x].mine = true;
			if (pole[y - 1][x + 1].mass != 9)pole[y - 1][x + 1].mine = true;
			if (pole[y][x + 1].mass != 9)pole[y][x + 1].mine = true;
			if (pole[y + 1][x + 1].mass != 9)pole[y + 1][x + 1].mine = true;
			if (pole[y + 1][x].mass != 9)pole[y + 1][x].mine = true;
			pole[y][x].check = true;
		};
		if ((y>0) && (y<height - 1) && (x==length - 1))
		{
			
			if (pole[y - 1][x - 1].mass != 9)pole[y - 1][x - 1].mine = true;
			if (pole[y - 1][x].mass != 9)pole[y - 1][x].mine = true;
			if (pole[y + 1][x].mass != 9)pole[y + 1][x].mine = true;
			if (pole[y + 1][x - 1].mass != 9)pole[y + 1][x - 1].mine = true;
			if (pole[y][x - 1].mass != 9)pole[y][x - 1].mine = true;
			pole[y][x].check = true;
		};
		if ((x == 0) && (y == 0))
		{
			if (pole[0][1].mass != 9)pole[0][1].mine = true;
			if (pole[1][1].mass != 9)pole[1][1].mine = true;
			if (pole[1][0].mass != 9)pole[1][0].mine = true;
			pole[y][x].check = true;
		}
		if ((x == 0) && (y == height - 1))
		{
			if (pole[height - 2][0].mass != 9)pole[height - 2][0].mine = true;
			if (pole[height - 2][1].mass != 9)pole[height - 2][1].mine = true;
			if (pole[height - 1][1].mass != 9)pole[height - 1][1].mine = true;
			pole[y][x].check = true;
		}
		if ((x == length - 1) && (y == height - 1))
		{
			if (pole[height - 2][length - 1].mass != 9)pole[height - 2][length - 1].mine = true;
			if (pole[height - 2][length - 2].mass != 9)pole[height - 2][length - 2].mine = true;
			if (pole[height - 1][length - 2].mass != 9)pole[height - 1][length - 2].mine = true;
			pole[y][x].check = true;
		}
		if ((x == length - 1) && (y == 0))
		{
			if (pole[0][length - 2].mass != 9)pole[0][length - 2].mine = true;
			if (pole[1][length - 2].mass != 9)pole[1][length - 2].mine = true;
			if (pole[1][length - 1].mass != 9)pole[1][length - 1].mine = true;
			pole[y][x].check = true;
		}
		
	}
	//проверяем, пусто ли поле
	void IsNull(int y, int x, int height, int length)
	{
		if (pole[y][x].check == false)
		{
			if (pole[y][x].mass == 0)
			{
				OpenFreeCells(y, x, height, length);
				if ((y > 0) && (y < height - 1) && (x > 0) && (x < length - 1))
				{
					IsNull(y - 1, x - 1, height, length);
					IsNull(y - 1, x, height, length);
					IsNull(y - 1, x + 1, height, length);
					IsNull(y, x + 1, height, length);
					IsNull(y + 1, x + 1, height, length);
					IsNull(y + 1, x, height, length);
					IsNull(y + 1, x - 1, height, length);
					IsNull(y, x - 1, height, length);
				};
				if ((y == height - 1) && (x > 0) && (x < length - 1))
				{
					IsNull(y - 1, x - 1, height, length);
					IsNull(y - 1, x, height, length);
					IsNull(y - 1, x + 1, height, length);
					IsNull(y, x + 1, height, length);
					IsNull(y, x - 1, height, length);
				};
				if ((y == 0) && (x > 0) && (x < length - 1))
				{
					IsNull(y, x + 1, height, length);
					IsNull(y + 1, x + 1, height, length);
					IsNull(y + 1, x, height, length);
					IsNull(y + 1, x - 1, height, length);
					IsNull(y, x - 1, height, length);
				};
				if ((y > 0) && (y < height - 1) && (x == 0))
				{
					IsNull(y - 1, x, height, length);
					IsNull(y - 1, x + 1, height, length);
					IsNull(y, x + 1, height, length);
					IsNull(y + 1, x + 1, height, length);
					IsNull(y + 1, x, height, length);
				};
				if ((y > 0) && (y < height - 1) && (x == length - 1))
				{
					IsNull(y - 1, x - 1, height, length);
					IsNull(y - 1, x, height, length);
					IsNull(y + 1, x, height, length);
					IsNull(y + 1, x - 1, height, length);
					IsNull(y, x - 1, height, length);
				};
				if ((x == 0) && (y == 0))
				{
					IsNull(0, 1, height, length);
					IsNull(1, 1, height, length);
					IsNull(1, 0, height, length);
				}
				if ((x == 0) && (y == height - 1))
				{
					IsNull(height - 2, 0, height, length);
					IsNull(height - 2, 1, height, length);
					IsNull(height - 1, 1, height, length);
				}
				if ((x == length - 1) && (y == height - 1))
				{
					IsNull(height - 2, length - 1, height, length);
					IsNull(height - 2, length - 2, height, length);
					IsNull(height - 1, length - 2, height, length);
				}
				if ((x == length - 1) && (y == 0))
				{
					IsNull(0, length - 2, height, length);
					IsNull(1, length - 2, height, length);
					IsNull(1, length - 1, height, length);
				}
				
			}
			pole[y][x].check = true;
		}
	}
	//подсчитываем кол-во проверенных полей
	bool IsFIeldChecked(int height, int length)
	{
		int c=0;
		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < length; j++)
			{
				if (pole[i][j].check) c++;
			}
		}
		cout << "\nChecked:" << c;
		return c == (height*length);
	}
};

int main()
{
	cout << "\nvvedite dlinu polya:";
	int length;
	cin >> length;
	cout << "\nvvedite vysotu polya:";
	int height;
	cin >> height;
	//-----------------
	field field;
	field.CreateField(height, length);
	//field.InitMines(height, length);
	field.InitField(height, length);
	int x = length / 2, y = height / 2;
	//field.InitMines(height, length, y, x);
	field.pole[y][x].mean = '*';
	field.ShowField(height, length);
	//-----------------
	char c;
	bool start=true;
	int mines;
	mines = length * height*0.21;
	//mines = 1;
	while (true)
	{

		c = _getch();


		switch (c)
		{
		case 'a':
			if (x > 0)
				x--;
			field.pole[y][x].mean = '*';
			field.pole[y][x + 1].mean = 'O';

			break;
		case 'd':
			if (x < length - 1)
				x++;
			field.pole[y][x].mean = '*';
			field.pole[y][x - 1].mean = 'O';

			break;
		case 'w':
			if (y > 0)
				y--;
			field.pole[y][x].mean = '*';
			field.pole[y + 1][x].mean = 'O';

			break;
		case 's':
			if (y < height - 1)
				y++;
			field.pole[y][x].mean = '*';
			field.pole[y - 1][x].mean = 'O';

			break;
		case ' ':
			
			if (start)
			{
				field.InitMines(height, length,y,x);
				start = false;
			}
			
			

			field.IsNull(y, x,height,length);
			


			if (field.pole[y][x].mass == 9)
			{
				system("cls");
				field.pole[y][x].mean = '!';
				for (size_t i = 0; i < height; i++)
				{
					for (size_t j = 0; j < length; j++)
					{
						if (field.pole[i][j].mean == '!')
						{
							cout << field.pole[i][j].mean<<' ';
						}
						else
						{
							if ((!field.pole[i][j].mine) && (field.pole[i][j].check))
							{
								cout << 'F' << ' ';
							}
							else
							{
								switch (field.pole[i][j].mass)
								{
								case 0:
									cout << '_' << ' ';
									break;
								case 9:
									cout << 'X' << ' ';
									break;
								default:
									cout << field.pole[i][j].mass << ' ';
									break;
								}
							}
						}
					}
					cout << "\n";
				};
				cout << "\nFAIL!!!!!!";


				system("pause");
				return 0;
			}


			field.pole[y][x].mine = true;
			
			break;
		case 'f':
			
			field.pole[y][x].mean = 'F';
			mines--;
			field.pole[y][x].check = true;

			break;

		}
		system("cls");
		field.ShowField(height, length);

		cout << "\nmines:" << mines;
		if ((field.IsFIeldChecked(height, length)) && (mines == 0))
		{
			cout << "\n POBEDA!!!";
			system("pause");
			return 0;
		}
	};
	
	
	system("pause");
    return 0;
}

