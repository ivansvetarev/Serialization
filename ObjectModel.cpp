#include <iostream>
#include "Core.cpp"
#include <vector>

namespace ObjectModel
{
	//declaration
	enum class Wrapper : int8_t
	{

		ARRAY = 1,
		PRIMITIVE,
		STRING,
		OBJECT
	};

	enum class Type : int8_t
	{
		I8	= 1,
		I16,
		I32,
		I64,

		U8,
		U16,
		U32,
		U64,

		FLOAT,
		DOUBLE,

		BOOL
	};

    //	abstract
    class Root
	{
	protected:
		std::string name;
		int16_t nameLength;
		int8_t wrapper;
		int32_t size;
		int8_t type;
	protected:
        //way to do an abstract class
		Root();
	public:
		int32_t getSize();
		void setName(std::string);
		std::string getName();
		virtual void pack(std::vector<int8_t>*, int16_t*);

	};



	class Primitive : public Root
	{
	private:
		int8_t type = 0;
		std::vector<int8_t>* data = nullptr;
	private:
		Primitive();
	public:
        static Primitive* create(std::string, Type, int32_t);
        void pack(std::vector<int8_t>*, int16_t*);
	};

	class Array : public Root
	{

	};

	class Object : public Root
	{

	};

	//definitions
	Root::Root()
		:
		name("unknown"),
		wrapper(0),
		nameLength(0),
		size(sizeof nameLength + sizeof wrapper  + sizeof size){}
	void Root::setName(std::string name)
	{
		this->name = name;
		nameLength = (int16_t)name.length();
		size += nameLength;
	}

    //abstract
    void Root::pack(std::vector<int8_t>* vector, int16_t* intd){}

	int32_t Root::getSize()
	{
		return size;
	}

	std::string Root::getName()
	{
		return name;
	}
	Primitive::Primitive()
	{
    	size += sizeof type;
	}
	Primitive* Primitive::create(std::string name, Type type, int32_t value)
	{
        Primitive* p = new Primitive();
		p->setName(name);    // Incapsulation
		p->wrapper = static_cast<int8_t>(Wrapper::PRIMITIVE);
		p->type = static_cast<int8_t>(type);
		p->data = new std::vector<int8_t>(sizeof value);

		int16_t iterator = 0;
		Core::encode(p->data, &iterator, value);

		return p;
	}

    void Primitive::pack(std::vector<int8_t>*, int16_t* )
    {

    }
}


