/*
 *	project.cpp
 *	Project Serializer
 */

#include <project.hpp>

namespace Ide
{
	Project::Project()
	{
	
	}
	
	bool Project::Load(const std::string& filename)
	{
		return false;
	}
	
	bool Project::Save(const std::string& filename)
	{
		return false;
	}
	
	ProjectBase::ProjectBase()
		: sourceFiles()
	{
	
	}
}
