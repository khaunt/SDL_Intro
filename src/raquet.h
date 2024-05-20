#include <iostream>
#include <array>
#include <string>

using namespace std;

struct raquet {
public:
	float width;
	float height;
	float x;
	float y;
	raquet(const int player_num);
	~raquet() {};
};

