#ifndef TOOL_H
#define TOOL_H

#include "ToolType.h"
#include "Material.h"
#include "Resource.h"

class Tool
{
public:
protected:
private:
	ToolType toolType;
	Material material;
public:
	Tool();
	Tool(ToolType _toolType, Material _material);
	~Tool() = default;
	
	bool operator==(const Tool& _tool) const;
	bool operator<(const Tool& _tool) const;
	ToolType GetToolType() const;
	Material GetMaterial() const;
protected:
private:
};

#endif // TOOL_H

