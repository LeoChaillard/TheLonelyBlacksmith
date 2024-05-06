#ifndef TOOLTYPE_H
#define TOOLTYPE_H

#include <string>
#include <map>

class ToolType
{
public:
	enum Value
	{
		UNSPECIFIED,
		PICKAXE,
		AXE,
		HAMMER,
		FORGE		
	};

	ToolType() = default;
	ToolType(Value _tooltype) : value(_tooltype) 
	{
	}

	bool operator==(ToolType _toolType) const 
	{ 
		return value == _toolType.value; 
	}

	bool operator!=(ToolType _toolType) const
	{
		return value != _toolType.value;
	}

	bool operator<(ToolType _toolType) const
	{
		return value < _toolType.value;
	}

	std::string ToString() const
	{
		if (value != Value::UNSPECIFIED)
		{
			return toString.at(value);
		}
		return "";
	}

private:
	Value value;
	std::map<Value, std::string> toString = { {Value::PICKAXE, "Pickaxe"},
											  {Value::AXE, "Axe"},
												{Value::HAMMER, "Hammer"}, 
												{Value::FORGE, "Forge"} };
};

#endif // TOOLTYPE_H