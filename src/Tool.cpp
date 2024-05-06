#include "Tool.h"

Tool::Tool()
	: 
	toolType(ToolType::UNSPECIFIED),
	material(Material::UNSPECIFIED)
{
}

Tool::Tool(ToolType _toolType, Material _material)
	: toolType(_toolType),
	material(_material)
{
}

bool Tool::operator==(const Tool& _tool) const
{
	return _tool.material == material && _tool.toolType == toolType;
}

bool Tool::operator<(const Tool& _tool) const
{
	return std::tie(material, toolType) < std::tie(_tool.material, _tool.toolType);
}

ToolType Tool::GetToolType() const
{
	return toolType;
}

Material Tool::GetMaterial() const
{
	return material;
}