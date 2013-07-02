/*
 *	cbp.cpp
 *	Code::Blocks Project
 */

#include <project.hpp>
#include <cbp.hpp>

namespace Ide
{
	ProjectCbp::ProjectCbp()
		: ProjectBase()
	{
	
	}
	
	bool ProjectCbp::Load(const std::string& filename)
	{
		return false;
	}
	
	bool ProjectCbp::Save(const std::string& filename)
	{
		return false;
	}
}
