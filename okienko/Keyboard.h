#pragma once
#include <bitset>
#include <queue>
class Keyboard
{
	
	std::bitset<256> keys;
	std::queue<char> charBuffer;
public:
	std::string readCharBuffer();
	void setKey(char key);
	bool isKeyPressed(char key);
	void unsetKey(char key);
};

