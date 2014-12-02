#pragma once

#define OBJECT	void*

enum ComponentType
{
	Uninitialized,
	Transfrom,
	MeshRenderer,
	ScriptObject,
	Material,
	Animator
};

struct Component
{
	ComponentType m_Type;
	OBJECT        m_Object;
	Component*	  m_Component;
};