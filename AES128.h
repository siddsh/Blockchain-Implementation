#pragma once

#include <iostream>
#include <bitset>
#include <sstream>
#include <string>
#include <unordered_map>

std::string AESencrypt(std::string iv, std::string pt);

std::string AESdecrypt(std::string iv, std::string ct);