#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#include "ObjectModel.cpp"
#include "EventSystem.cpp"


using namespace ObjectModel;
using namespace EventSystem;

int main(int argc, char** argv)
{
	int32_t foo = 5;
	Primitive* p = Primitive::create("int32", Type::I32, foo);
    std::cout << "Well done" << std::endl;    

#if 0
	System Foo("Foo");
	Event* e = new KeyboardEvent('a', true, false);

	Foo.addEvent(e);

	KeyboardEvent* kb = static_cast<KeyboardEvent*>(Foo.getEvent());
	
    Foo.serialize();

    return 0;
#endif
}
