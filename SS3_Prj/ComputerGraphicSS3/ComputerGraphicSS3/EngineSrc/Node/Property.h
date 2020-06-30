#pragma once

#include "../Variant/variant.hpp"
#include "glm/glm.hpp"

/// Enumeration of data types that can be stored as properties.
enum PropertyDataType
{
	/// Float data.
	PropertyDataTypeFloat,
	/// Integer data.
	PropertyDataTypeInt,

	/// Integer data.
	PropertyDataTypeUInt,

	/// Boolean data.
	PropertyDataTypeBool,
	/// ColorRGBA data.
	PropertyDataTypeColor,
	/// Vector2 data.
	PropertyDataTypeVector2,
	/// Vector3 data.
	PropertyDataTypeVector3,
	/// Vector4 data.
	PropertyDataTypeVector4,
	/// Matrix3x3 data.
	PropertyDataTypeMatrix3x3,
	/// Matrix4x4 data.
	PropertyDataTypeMatrix4x4,
	/// String data.
	PropertyDataTypeString,
	/// Pointer data.
	PropertyDataTypePointer,
	/// Resource data.
	PropertyDataTypeResource,
	/// SRTValue2D data.
	PropertyDataTypeSRT2D,
	/// SRTValue3D data.
	PropertyDataTypeSRT3D
};

typedef mpark::variant<int, unsigned int, float, glm::vec2, glm::vec3, glm::mat4> PROPERTY_TYPE;



class MaterialProperty
{
public:

	std::string mUniformName;
	PropertyDataType mDataType;
	PROPERTY_TYPE mValue;

	MaterialProperty(std::string uniformName, PropertyDataType dataType, PROPERTY_TYPE value)
		:mUniformName(uniformName)
		, mDataType(dataType)
		, mValue (value)
	{
	}

	~MaterialProperty() {};
};






