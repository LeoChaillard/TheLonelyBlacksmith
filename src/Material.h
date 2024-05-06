#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <map>

class Material
{
public:
	enum Value
	{
		UNSPECIFIED,
		BASIC,
		WOOD,
		STONE,
		IRON
	};

	Material() = default;
	Material(Value _material) : value(_material)
	{
	}

	bool operator==(Material _material) const
	{
		return value == _material.value;
	}

	bool operator!=(Material _material) const
	{
		return value != _material.value;
	}

	bool operator<(Material _material) const
	{
		return value < _material.value;
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
	std::map<Value, std::string> toString = { {Value::BASIC, "Basic"},
											  {Value::WOOD, "Wood"},
												{Value::STONE, "Stone"},
												{Value::IRON, "Iron"} };
};


#endif // MATERIAL_H