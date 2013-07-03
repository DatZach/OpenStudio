/*
 *	project.hpp
 *	Project Serializer
 */

#ifndef __PROJECT_HPP
#define __PROJECT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <vsproj.hpp>
#include <cbp.hpp>

namespace Ide
{
	class Project
	{
	private:
	
	public:
		Project();
		
		bool Load(const std::string& filename);
		bool Save(const std::string& filename);
	};
	
	class ProjectBase
	{
	private:
		std::vector<std::string> sourceFiles;
		
	public:
		ProjectBase();
		
		virtual bool Load(const std::string& filename) = 0;
		virtual bool Save(const std::string& filename) = 0;
	};
}

#endif
