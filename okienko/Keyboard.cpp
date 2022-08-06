#include "Keyboard.h"

std::string Keyboard::readCharBuffer()
{
	std::string ret;
	
	while (!charBuffer.empty()) 
	{
		ret += charBuffer.back();
		charBuffer.pop();
	}

	return ret;
}

void Keyboard::setKey(char key)
{
	keys.set(key);
	charBuffer.push(key);
}

bool Keyboard::isKeyPressed(char key)
{
	return keys[key];
}

void Keyboard::unsetKey(char key)
{
	keys.set(key, false);
}
