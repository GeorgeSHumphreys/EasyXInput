// Copyright (c) 2023 George Humphreys
#pragma once
#include <functional>


namespace EXI
{
	class ControllerButton;
	class ControllerAxis;
	class ControllerTrigger;

	typedef std::function<void(ControllerButton*)> ControllerButtonDelegate;
	typedef std::function<void(ControllerAxis*)> ControllerAxisDelegate;
	typedef std::function<void(ControllerTrigger*)> ControllerTriggerDelegate;

	class ControllerCallbackBase
	{
	public:
		void Bind() { m_bound = true; }

		void Clear() { m_bound = false; }

		bool IsBound() { return m_bound; }

	protected:
		bool m_bound{ false };
	};

	class ControllerButtonCallback : public ControllerCallbackBase
	{
	public:
		template<class OwningObject, class FunctionRef>
		void Bind(OwningObject* owningObj, FunctionRef funcRef);

		void Clear() 
		{ 
			ControllerCallbackBase::Clear();
			m_callback = {}; 
		};

		ControllerButtonDelegate m_callback;
	};

	class ControllerAxisCallback : public ControllerCallbackBase
	{
	public:

		template<class OwningObject, class FunctionRef>
		void Bind(OwningObject* owningObj, FunctionRef funcRef);

		void Clear()
		{
			ControllerCallbackBase::Clear();
			m_callback = {};
		};

		ControllerAxisDelegate m_callback;
	};

	class ControllerTriggerCallback : public ControllerCallbackBase
	{
	public:

		template<class OwningObject, class FunctionRef>
		void Bind(OwningObject* owningObj, FunctionRef funcRef);

		void Clear()
		{
			ControllerCallbackBase::Clear();
			m_callback = {};
		};

		ControllerTriggerDelegate m_callback;
	};


	template<class OwningObject, class FunctionRef>
	inline void ControllerButtonCallback::Bind(OwningObject* owningObj, FunctionRef funcRef)
	{
		ControllerCallbackBase::Bind();

		m_callback = std::bind(funcRef, owningObj, std::placeholders::_1);
	}

	template<class OwningObject, class FunctionRef>
	inline void ControllerAxisCallback::Bind(OwningObject* owningObj, FunctionRef funcRef)
	{
		ControllerCallbackBase::Bind();

		m_callback = std::bind(funcRef, owningObj, std::placeholders::_1);
	}

	template<class OwningObject, class FunctionRef>
	inline void ControllerTriggerCallback::Bind(OwningObject* owningObj, FunctionRef funcRef)
	{
		ControllerCallbackBase::Bind();

		m_callback = std::bind(funcRef, owningObj, std::placeholders::_1);
	}
}