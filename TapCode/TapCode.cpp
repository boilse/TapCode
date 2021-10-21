#include <iostream>
#include <vector>

std::vector < std::vector < std::vector<char> >> plSqr
{
	{{'a','A'}, {'b','B'}, {'c','C','k','K'}, {'d','D'}, {'e','E'}},
	{{'f','F'}, {'g','G'}, {'h','H'}, {'i','I'}, {'j','J'}},
	{{'l','L'}, {'m','M'}, {'n','N'}, {'o','O'}, {'p','P'}},
	{{'q','Q'}, {'r','R'}, {'s','S'}, {'t','T'}, {'u','U'}},
	{{'v','V'}, {'w','W'}, {'x','X'}, {'y','Y'}, {'z','Z'}}
};

class vec2d
{
private:
	int m_x;
	int m_y;

public:
	//Constructor
	vec2d(int x = 0, int y = 0) : m_x(x), m_y(y)
	{

	}
	//getters
	int getX() const { return m_x; }
	int getY() const { return m_y; }
	//setters
	void setX(int x = 0) { m_x = x; }
	void setY(int y = 0) { m_y = y; }
	void reset() { m_x = 0; m_y = 0; }
	//funcs
	void addX(int a) { m_x += a; }
	void addY(int a) { m_y += a; }
	//friends
	friend std::ostream& operator<<(std::ostream& os, const vec2d* vctd);
};

std::ostream& operator<<(std::ostream& os, const vec2d* vctd)
{
	return os << vctd->getX() << ' ' << vctd->getY() << '\n';
}

std::vector<vec2d*> hmDots(std::string inStr)
{

	std::vector<vec2d*> fout;
	for (auto smth : inStr)
		fout.push_back(new vec2d());

	int n(0);
	bool fl(0);
	for (auto sym : inStr)
	{
		int i{};
		for (auto prt : plSqr)
		{
			int y{};
			for (auto tps : prt)
			{
				for (auto chr : tps)
				{
					if (chr == sym)
					{
						fout[n]->setX(i);
						fout[n]->setY(y);
						fl = 1;
						break;
					}
				}
				if (fl) break;
				y++;
			}
			if (fl) break;
			i++;
		}
		fout[n]->addX(1);
		fout[n]->addY(1);
		n++;
		fl = 0;
	}

	return fout;
}

std::string strToDots(std::string inStr)
{
	std::vector<vec2d*> hmd = hmDots(inStr);
	std::string str{};
	for (auto chrs : hmd) {
		for (int i(1); i <= chrs->getX(); i++)
		{
			str.append(".");
		}
		str.append(" ");
		for (int y(1); y <= chrs->getY(); y++)
		{
			str.append(".");
		}
		str.append(" ");
	}
	str.pop_back();
	for (auto i : hmd) delete i;
	return str;
}

std::string dotsToStr(std::string inDots)
{
	vec2d* vctd = new vec2d();
	std::string str{};

	bool fl{ 1 };
	for (auto chr : inDots)
	{
		if (chr != ' ')
		{
			if (fl) vctd->addX(1);
			else vctd->addY(1);
			//if(chr == inDots.back()) 

		}
		else
		{

			//std::cout << fl;
			//vctd->addX(1);
			//vctd->addY(-1);
			//std::cout << vctd;
			//if(chr == inDots.back()) 

			if (!fl)
			{
				vctd->addX(-1);
				vctd->addY(-1);

				str.push_back(plSqr.at(vctd->getX()).at(vctd->getY()).at(0));

				if (chr != inDots.back())vctd->reset();

			}
			fl = !fl;
		}

		//std::cout << vctd;
	}
	//std::cout << vctd;
	vctd->addX(-1);
	vctd->addY(-1);

	str.push_back(plSqr.at(vctd->getX()).at(vctd->getY()).at(0));

	delete vctd;

	return str;
}

std::string toTap(std::string inStr)
{


	if (inStr.at(0) == '.')
	{
		return dotsToStr(inStr);
	}
	else
	{
		return strToDots(inStr);
	}

}

int main()
{
	std::cout << toTap(".... ... ... ..... . ..... ... ... .... ....");


}
