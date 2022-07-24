#ifndef LIB_UTILS_EXPORTS
#define LIB_UTILS_EXPORTS
#endif // !LIB_UTILS_EXPORTS

#include "geoObject.h"


GeoObject::GeoObject()
{
	mObjectType = G_OBJECT_TYPE_DEFUAL;
	mObjectTag = G_OBJECT_TYPE_DEFUAL;
	mObjectName.assign(G_OBJECT_NAME);

}

/**
* @brief 返回对象类型，对象类型是一个字符，
* @return 对应对象类型表中的值
*/
GeoObject::GeoObject(
					char * name = G_OBJECT_NAME,
					geoUInt16 type = G_OBJECT_TYPE_DEFUAL,
					geoUInt16 tag = G_OBJECT_TYPE_DEFUAL
					)
{
	mObjectType = type;
	mObjectTag = tag;
	mObjectName.assign(name);

}
GeoObject::~GeoObject()
{


}

geoStdString GeoObject::toString()
{
	return mObjectName;
}

 void	GeoObject::setClassName( geoStdString cname)
{
	mObjectName = cname;
}

const geoUInt16	GeoObject::getType()
{
	return 0;
}
void	GeoObject::setType(geoUInt16 type)
{
	mObjectType = type;
}
geoVoid		GeoObject::dump()
{

}