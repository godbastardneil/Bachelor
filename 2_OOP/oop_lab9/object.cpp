#include "object.h"

unsigned int object::count = 0;

object::object() { ++count; } // конструктор

object::~object() { --count; }

unsigned int object::Count() { return count; }

