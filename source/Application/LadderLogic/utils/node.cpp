#include "node.h"

node::node(std::string name, std::string pass) : User(std::move(name), std::move(pass))
{
}