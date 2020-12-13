#include <iostream>
#include <memory>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
constexpr int WIDTH = 1000, HEIGHT = 720, R = 25;
using namespace std;
std::shared_ptr<SDL_Texture> icon;
std::shared_ptr<SDL_Texture> icon2;
std::shared_ptr<SDL_Texture> Make_icon(SDL_Renderer *renderer, const char *name)
{

	std::shared_ptr<SDL_Texture> picture = std::shared_ptr<SDL_Texture>(
			IMG_LoadTexture(renderer, name),
			SDL_DestroyTexture);
	if(picture == nullptr)
	{
		std::cerr << "�� ����������� ��������" <<
		SDL_GetError()<<std::endl;
		return nullptr;
	}
	return picture;
}


void DrawCircle(SDL_Renderer * ren, int x, int y, int r, int X, int Y)
{
            int delta = 1 - 2 * r;
            int error = 0;
            SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);

            while(y >= 0)
            {
                SDL_RenderDrawPoint(ren, X + x, Y + y);
                SDL_RenderDrawPoint(ren, X + x, Y - y);
                SDL_RenderDrawPoint(ren, X - x, Y + y);
                SDL_RenderDrawPoint(ren, X - x, Y - y);
                error = 2 * (delta + y) - 1;
                if (delta < 0 and error <= 0)
                {
                    ++x;
                  delta += 2 * x + 1;
                    continue;
                }
                if (delta > 0 and error > 0)
                {
                    --y;
                    delta -= 2 * y + 1;
                    continue;
                }
                ++x;
                --y;
                delta += 2 * (x - y);
            }
}
int main(int, char **)
{
    std::cout << "������ ������ ���������" << std::endl;
    SDL_Init(SDL_INIT_EVERYTHING);
    auto win = std::shared_ptr<SDL_Window>(
            SDL_CreateWindow("Home",
                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                    WIDTH, HEIGHT,
                    SDL_WINDOW_SHOWN),
            SDL_DestroyWindow);
    if (win == nullptr) {
        std::cerr << "������ ��� �������� ����: " <<
                SDL_GetError() << std::endl;
        return 1;
    }
    auto ren = std::shared_ptr<SDL_Renderer>(
            SDL_CreateRenderer(win.get(), -1,
                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
            SDL_DestroyRenderer);
    if (ren == nullptr) {
        std::cerr << "������ ��� �������� ���������: " <<
                SDL_GetError() << std::endl;
        return 1;
    }


	bool f = true;
	int icon_x = 640, icon_y = 90;// ���������� ��� ��������� ������ � ����
	bool f2 = true;
	int icon_x2 = 500, icon_y2 = 600;// ���������� ��� �������� ������ �� ����� ��������

	auto keys = SDL_GetKeyboardState(nullptr);

    SDL_Event event;
    bool finish = false;
    // �������� ���� ���������
    while (not finish)
    {
        // ���� ��������� �������
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                finish = true;
        }
        //����
        SDL_SetRenderDrawColor(ren.get(), 168, 209, 255, 1);
        SDL_RenderClear(ren.get());
        //�����
        SDL_Rect r { 0, 525, WIDTH, 220 };
        SDL_SetRenderDrawColor(ren.get(), 28, 22, 12, 1);
        SDL_RenderFillRect(ren.get(), &r);
        //�����
        for (int i = 20; i < WIDTH; i += 100) {
        	SDL_SetRenderDrawColor(ren.get(), 0, 0, 0, 1);
            SDL_Rect r1 { i, 450, 50, 100 };
            SDL_RenderFillRect(ren.get(), &r1);
            SDL_Rect r2 { i + 50, 490, 50, 20 };
            SDL_RenderFillRect(ren.get(), &r2);
            SDL_SetRenderDrawColor(ren.get(), 0, 0, 0, 1);
            for (double x1 = i + 25, x2 = i + 25,  y = 425; y < 450; --x1, ++x2, y++)
            { SDL_RenderDrawLine(ren.get(), x1, y, x2, y);
            } }
        //���
        SDL_Rect r1 { WIDTH / 2 - 150, 200, 430, 430 };
        SDL_SetRenderDrawColor(ren.get(), 117, 16, 16, 1);
        SDL_RenderFillRect(ren.get(), &r1);
        //����
        SDL_Rect r2 { WIDTH / 2 + 25, 200 + 150, 100, 100 };
        SDL_SetRenderDrawColor(ren.get(), 193, 245, 242, 1);
        SDL_RenderFillRect(ren.get(), &r2);

        SDL_SetRenderDrawColor(ren.get(), 54, 40, 21, 1);
        SDL_RenderDrawLine(ren.get(), WIDTH / 2 + 75, 350, WIDTH / 2 + 75, 450);

        SDL_SetRenderDrawColor(ren.get(), 54, 40, 21, 1);
        SDL_RenderDrawLine(ren.get(), WIDTH / 2 + 25, 400, WIDTH / 2 + 125, 400);

        //�����
        SDL_Rect r3 { WIDTH / 2 + 175, 130, 30, 60 };
        SDL_SetRenderDrawColor(ren.get(), 117, 16, 16, 1);
        SDL_RenderFillRect(ren.get(), &r3);
        //�����
        SDL_SetRenderDrawColor(ren.get(), 245, 223, 223, 1);
        for (double x1 = WIDTH / 2 + 65, x2 =WIDTH / 2 + 65,  y = 100; y < 200; x1 -= 2.15, x2 += 2.15, y++) {
            SDL_RenderDrawLine(ren.get(), x1, y, x2, y);
        }
        //�����
        SDL_Rect r4 { WIDTH / 2 + 38 , 500, 75, 130 };
        SDL_SetRenderDrawColor(ren.get(), 245, 223, 223, 1);
        SDL_RenderFillRect(ren.get(), &r4);
        //�����
        SDL_SetRenderDrawColor(ren.get(), 57, 99, 24, 1);
        for(int i = 0; i <= 25; i += 25)
            for (int x = 15 + i,  y1 = HEIGHT - i, y2 = HEIGHT - (i+50) ; x < WIDTH - 15; x += 50 )
                SDL_RenderDrawLine(ren.get(), x, y1, x, y2);

        //����������
        DrawCircle(ren.get(), 0, R, R, WIDTH / 2 + 65, 150);


		//� ����
		if (f)
			icon = Make_icon(ren.get(), "list.png");
		else
			icon = Make_icon(ren.get(), "list_l.png");

		if(keys[SDL_SCANCODE_RIGHT] and icon_x < WIDTH - 100){ icon_x += 3; f = true;}//��� � ����� ����� 8 ��� �������� ������
		if(keys[SDL_SCANCODE_LEFT] and icon_x > 0 ){ icon_x -= 3; f = false;}
		if(keys[SDL_SCANCODE_UP] and icon_y > 0){ icon_y -= 3; }
		if(keys[SDL_SCANCODE_DOWN] and icon_y < HEIGHT - 50){ icon_y += 3; }

		if(icon == nullptr) return 1;
		SDL_Rect icon_rect {icon_x, icon_y, 100, 105};
		SDL_RenderCopy(ren.get(), icon.get(), nullptr, &icon_rect);

		//�� �����
		if(icon_x2 < WIDTH - 150 and f2){
			icon2 = Make_icon(ren.get(), "ezhik.png");
			icon_x2 += 2;//������
		}
		else f2 = false;
		if(icon_x2 > 0 and !f2){
			icon2 = Make_icon(ren.get(), "ezhik_l.png");
			icon_x2 -= 2;//�����
		}
		else f2 = true;

		if(icon2 == nullptr) return 1;
		SDL_Rect icon_rect2 {icon_x2, icon_y2, 150, 150};
		SDL_RenderCopy(ren.get(), icon2.get(), nullptr, &icon_rect2);

        SDL_RenderPresent(ren.get());
        }
        /*
         * ������� �����������:
         * 1 ����� (��������) - �����, ���������� �������� ������������.
         * 2 ����� (������) - �����, � ������� �������������� ���������� �����������.
         *
         */
        std::cout << "�����" << std::endl;
        return 0;
}

