#pragma once

/// Enumeration of data types that can be stored as properties.
enum PropertyDataType
{
	/// Float data.
	PropertyDataTypeFloat,
	/// Integer data.
	PropertyDataTypeInt,
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


class Property
{
public:
	Property() {};
	~Property() {};

	PropertyDataType mDataType;
	std::string mName;


	template<typename T>
	void BindUniform(unsigned int programID, std::string name, T value)
	{
		if (std::is_same<int, T>::value)
		 {
			 printf("SetUniformValue type = int \n");
		 }
		 return true;
	}
};

