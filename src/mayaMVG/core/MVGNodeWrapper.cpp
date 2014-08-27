#include "mayaMVG/core/MVGNodeWrapper.h"
#include "mayaMVG/maya/MVGMayaUtil.h"
#include <maya/MGlobal.h>
#include <maya/MFnDagNode.h>
#include <maya/MSelectionList.h>

namespace mayaMVG {

MVGNodeWrapper::MVGNodeWrapper()
{
}

MVGNodeWrapper::MVGNodeWrapper(const std::string& name)
{
	if(name.empty())
		return;
	MVGMayaUtil::getDagPathByName(name.c_str(), _dagpath);
	if(_dagpath.apiType() == MFn::kTransform)
		_dagpath.extendToShape();
}

MVGNodeWrapper::MVGNodeWrapper(const MString& name)
{
	if(name.length() == 0)
		return;
	MVGMayaUtil::getDagPathByName(name, _dagpath);
	if(_dagpath.apiType() == MFn::kTransform)
		_dagpath.extendToShape();
}

MVGNodeWrapper::MVGNodeWrapper(const MDagPath& dagPath)
	: _dagpath(dagPath)
{
	if(_dagpath.apiType() == MFn::kTransform)
		_dagpath.extendToShape();
}

MVGNodeWrapper::~MVGNodeWrapper()
{
}

bool MVGNodeWrapper::isValid() const
{
	return _dagpath.isValid();
}

void MVGNodeWrapper::select() const
{
	MSelectionList list;
	list.add(_dagpath);
	MGlobal::setActiveSelectionList(list);
}

const MDagPath& MVGNodeWrapper::getDagPath() const
{
	return _dagpath;
}

std::string MVGNodeWrapper::getName() const
{
	MFnDagNode fn(_dagpath.transform()); // return the transform name
	return fn.name().asChar();
}

void MVGNodeWrapper::setName(const std::string& name)
{
	MFnDagNode fn(_dagpath.transform()); // rename the transform node
	fn.setName(name.c_str());
}

} // namespace
