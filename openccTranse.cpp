#pragma once
#include "openccTranse.h"
std::string openccTranse:: convertText(const std::string text)
{
	const std::string& converted = converter->Convert(text);
	return converted;
};