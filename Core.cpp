#include<iostream>
#include <sys/types.h>
#include <vector>
#include <fstream>

namespace Core
{
    template<typename T>
	void encode(std::vector<int8_t>* buffer, int16_t* iterator,T value)
	{
		for (unsigned i = 1; i <= sizeof(T); ++i)
		{
			(*buffer)[(*iterator)++] = value >> 8 * (sizeof (T) - i);
		}
	}

}

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
//        Core::encode<std::string>(buffer, iterator, name);
    }
}

namespace Core
{
	namespace Util
	{
        void save(const char* file,std::vector<int8_t> buffer)
        {
            std::ofstream out;
            out.open(file);

            for(unsigned i = 0; i < buffer.size(); ++i)
            {
                out << buffer[i];
            }
            out.close();
        }
        void retrieveNsave(ObjectModel::Root* r)
        {

            int16_t iterator = 0;
            std::vector<int8_t> buffer(r->getSize());
            std::string name = r->getName().substr(0,r->getName().length()).append(".ttc");
            r->pack(&buffer, &iterator);
            save(name.c_str(), buffer);

        }


	}
}

