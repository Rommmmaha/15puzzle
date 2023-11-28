#include"raylib.h"
#include<string>
#include<ctime>
#include<vector>
void shuffle(std::vector<std::vector<int>>& arr)
{
	int n = arr.size();
	for (int a = 0; a < pow(n, 5); a++)
	{
		int ii = 0, jj = 0;
		for (; jj < n; jj++) { for (ii = 0; ii < n; ii++) { if (arr[jj][ii] == 0) { jj += n, ii += n; } } }
		jj -= n + 1, ii -= n + 1;
		int i = ii, j = jj, k = rand() % 4;
		switch (k)
		{
		case 0:
			if (i == 0)
				i++;
			else
				i--;
			break;
		case 1:
			if (i == n - 1)
				i--;
			else
				i++;
			break;
		case 2:
			if (j == 0)
				j++;
			else
				j--;
			break;
		case 3:
			if (j == n - 1)
				j--;
			else
				j++;
			break;
		default:
			break;
		}
		std::swap(arr[j][i], arr[jj][ii]);
	}
}
int main()
{
	srand(time(0));
	float tileSize = 150, fontSize = 50, n = 4, win = 0;
	bool restart = false;
	Vector2 screen{ tileSize * n + n + 1,tileSize * n + n + 1 };
	Color tile{ 255,150,100,255 }, backround{ 205,100,50,255 };
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(screen.x, screen.y, "15puzzle");
	std::vector<std::vector<int>> numbers;
	for (int i = 0; i < n; i++)
	{
		numbers.push_back({});
		for (int j = 0; j < n; j++) { numbers[i].push_back(1 + i * n + j); }
	}
	numbers[n - 1][n - 1] = 0;
	shuffle(numbers);
	for (; !WindowShouldClose();)
	{
		BeginDrawing();
		{
			ClearBackground(backround);
			if (IsKeyDown(KEY_SPACE)) { shuffle(numbers); }
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (numbers[j][i] != 0)
					{
						tile.a = fabs(n * n - numbers[j][i]) / (n * n - 1) * 155 + 100;
						DrawRectangle(1 + (tileSize + 1) * i, 1 + (tileSize + 1) * j, tileSize, tileSize, tile);
						int center = 1 + tileSize / 2 - fontSize / 2;
						DrawText(std::to_string(numbers[j][i]).c_str(), center + (tileSize + 1) * i, center + (tileSize + 1) * j, fontSize, WHITE);
					}
				}
			}
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				Vector2 mouse = GetMousePosition();
				int i = floorf(mouse.x / (tileSize + 1)), j = floorf(mouse.y / (tileSize + 1));
				for (; i >= n; i--) {}
				for (; i < 0; i++) {}
				for (; j >= n; j--) {}
				for (; j < 0; j++) {}

				//DrawCircle((i + 0.5) * tileSize, (j + 0.5) * tileSize, 20, BLUE);
				if (numbers[j][i] != 0)
				{
					int ii = 0, jj = 0;
					for (; jj < n; jj++)
					{
						for (ii = 0; ii < n; ii++)
						{
							if (numbers[jj][ii] == 0)
							{
								jj += n, ii += n;
							}
						}
					}
					jj -= n + 1, ii -= n + 1;
					//DrawCircle((ii + 0.5) * tileSize, (jj + 0.5) * tileSize, 20, WHITE);
					if (i == ii && abs(jj - j) == 1) { std::swap(numbers[j][i], numbers[jj][ii]); }
					if (j == jj && abs(ii - i) == 1) { std::swap(numbers[j][i], numbers[jj][ii]); }
					bool good = true;
					if (numbers[n - 1][n - 1] == 0)
					{
						for (int i = 0; i < n && good; i++)
							for (int j = 0; j < n && good; j++)
								if (!(i == n - 1 && j == n - 1) && good)
									good = numbers[i][j] == i * n + j + 1;
						win = good;
					}
				}
			}
			if (win > 0)
			{
				DrawText("You Won !", 10, 10, 40, WHITE);
				win -= GetFrameTime();
				restart = true;
			}
			else
			{
				//DrawText(std::to_string(int(1 / GetFrameTime())).c_str(), 10, 10, 40, RED);
				if (restart) { shuffle(numbers); restart = false; }
			}
		}
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
