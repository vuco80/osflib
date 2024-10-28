#ifndef OSFLIB_BASE_H
#define OSFLIB_BASE_H

#include "Defines.h"

namespace osflib {
	
	class ResourceBase {
	public:
		ResourceBase(Id id) : m_Id(id), m_InstanceId(++m_NextInstanceId) {}
		virtual ~ResourceBase() {}
		
		Id GetId() const { return m_Id; }
		Id GetInstanceId() const { return m_InstanceId; }
		
	private:
		Id m_Id;
		Id m_InstanceId;
		static Id m_NextInstanceId;
	};
	
	template<typename T>
	class Visitor {
	public:
		Visitor(){}
		virtual ~Visitor(){}
		
		virtual void Visit(const T& element) = 0;
	};
}

#endif