#pragma once

#include "User.h"

class node : public User {
public:
				node *next = nullptr;

				node(std::string name, std::string pass);

};