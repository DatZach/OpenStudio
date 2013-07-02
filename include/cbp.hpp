/*
 *	cbp.hpp
 *	Code::Blocks Project
 */

#ifndef __CPB_HPP
#define __CBP_HPP

namespace Ide
{
	class ProjectBase;
	
	class ProjectCbp : public ProjectBase
	{
	private:
	
	public:
		ProjectCbp();
		
		bool Load(const std::string& filename);
		bool Save(const std::string& filename);
	};
}

#endif
