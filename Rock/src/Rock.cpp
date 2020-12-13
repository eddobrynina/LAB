#include <iostream>
#include <string>
#include <random>
#include <sstream>

using namespace std;
std::random_device rd;
std::ranlux48 rnd { rd() };
std::uniform_int_distribution<> dist1 {15, 25};
std::uniform_int_distribution<> dist2 {1, 3};

int read_answer()
{
    int result;
    std::cout <<"вам нужно выбрать количество камней от 1 до 3" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::stringstream input_ss { input };
    input_ss >> result;
    bool f = input_ss.fail();
    while ( f || result < 1 || result > 3) {//обработка некоректного ввода используя строку
        std::cerr << "вы не поняли, вам можно брать количество камней от 1 до 3 камней. выберите количество еще раз: " << std::endl;
    	std::getline(std::cin, input);
    	std::stringstream input_ss { input };
        input_ss >> result;
        f = input_ss.fail();
    }
    return result;
}


int lvl_1(bool f)
{
	int d1 = dist1(rnd);
	std::cout << "всего " << d1 << " камней" << std::endl;
	int d2, a;
	bool f1;
	for (unsigned i=0; d1>0; ++i)
	{
		if( i%2 == 0 )
	    {
	        a = read_answer();
	        while (a > d1)
	        {
	        	std::cerr << "всего осталось " << d1 << " камней. сделайте другой выбор" << std::endl;
	        	a = read_answer();
	        }
	        std::cout << "осталось " <<(d1 - a) <<" камней " << std::endl;
	        d1 -= a;
	        f1 = true;
	    }
	    else
	    {
	    	d2 = dist2 (rnd);
	    	while (d2 > d1)
	    	{
	    		d2 = dist2 (rnd);
	    	}
	        std::cout << "компьютер взял камней - " << d2 << "  камней осталось- " << (d1-d2) << std::endl;
	        d1 -= d2;
	        f1 = false;
	    }
			if (d1 < 13 and f) return d1;
	    }
	if(f1) std::cout << "гейм овер. компьютер вин =(" << std::endl;
	else std::cout << "ваша победа =)" << std::endl;
	return 1;
}


void lvl_3(bool f, int ans)
{
	int d1 = ans;
	std::cout << "всего " << d1 << " камней" << std::endl;
	int d2, a;//Для рандомного хода компа
	bool f1;
	for (unsigned i=0; d1>0; ++i)
	{
		if(i%2 == 0)
	    {
	        a = read_answer();//Выбор пользователя сколько камней взять
	        while (a > d1)
	        {
	        	std::cerr << "всего осталось " << d1 << " камней. сделайте другой выбор!";
	        	a = read_answer();
	        }
	        std::cout << "осталось " <<(d1 - a) <<" камней " << std::endl;
	        d1 -= a;
	        f1 = true;
	    }

	    else
	    {
	        if( d1 % 4 == 2 )
			{
	    		d1 -= 1;
	    		std::cout << "компьютер взял камней - 1" << ". камней осталось: " << d1 << std::endl;
	    	}

	    	else if( d1 % 4 == 3 )
	    	{
	    		d1 -= 2;
	    		std::cout << "компьютер взял камней - 2" << ". камней осталось: " << d1 << std::endl;
	    	}

	    	else if( d1 % 4 == 0 )
	    	{
	    		d1 -= 3;
	    		std::cout << "компьютер взял камней - 3" << ". камней осталось: " << d1 << std::endl;
	    	}

	    	else
	    	{
	    		d2 = dist2 (rnd);
	    		while (d2 > d1)
	    		{
	    			d2 = dist2 (rnd);
	    		}
	    		d1 -= d2;
	    		std::cout << "Random choise - " << d2 << ". камней осталось: " << d1 << std::endl;
	    	}
	    	f1 = false;
	    }
	}
	if(f1) std::cout << "гейм овер. компьютер вин =(" << std::endl;
	else std::cout << "гейм овер. вы вин =)" << std::endl;
}


void lvl_2()
{
	bool f = true;
	int ans = lvl_1(f);
	lvl_3(f, ans);
}


int main()
{
	int choise;
	bool f = false;

	do
	{
		std::cout << "выберие уровень сложности игры : " << std::endl
				  << "1. Лекгий" << std::endl
				  << "2. Средний" << std::endl
			      << "3. Высокий" << std::endl
				  << "4. Выйти из игры" << std::endl;
		std::cin >> choise;
		while (std::cin.fail() or choise < 1 or choise > 4)
		{
				std::cerr << "Некорректный ввод. Попробуйте еще раз :" << std::endl;
		        if (std::cin.fail())
		        {
		            std::cin.clear();
		            std::cin.ignore(32767,'\n');
		        }
		        std::cin >> choise;
		    }
		std::cin.ignore(32767,'\n');

		switch(choise){
			case 1: {lvl_1(f); break;}
			case 2:	{lvl_2(); break;}
			case 3:	{lvl_3(f, dist1(rnd)); break;}

		}
	}while (choise != 4);

    return 0;
}
