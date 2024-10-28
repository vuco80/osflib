#ifndef OSFLIB_BASE_H
#define OSFLIB_BASE_H

#include "Defines.h"

namespace osflib {
	
	class ResourceBase {
	public:
		ResourceBase(Id id) : m_Id(id) {}
		virtual ~ResourceBase() {}
		
		int GetId() const { return m_Id; }
	private:
		Id m_Id;
	};
	
}

#endif