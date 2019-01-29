#pragma once
#include <Source/Common.h>

namespace KidClone {

template<typename... TArgs>
class Event;

class EventHandler {
public:
	struct Base {
		virtual ~Base() = default;
	};

public:
	EventHandler() = default;
	EventHandler(const EventHandler&) = delete;
	EventHandler(EventHandler&& other) {
		std::swap(m_ptr, other.m_ptr);
	}

	auto operator=(const EventHandler&)->EventHandler& = delete;
	auto operator=(EventHandler&& other)->EventHandler& {
		m_ptr.reset();
		std::swap(m_ptr, other.m_ptr);
	}

	template<typename T>
	auto operator=(T&& l)->EventHandler& {
		m_ptr.reset(new T(std::move(l)));
		return *this;
	}

	inline operator bool() { return bool(m_ptr); }

	template<typename H, typename... Args>
	auto setFunction(Event<Args...>& theEvent, H Handler)->void {
		m_ptr.reset(new typename Event<Args...>::Listener(theEvent, Handler));
	}

private:
	unique_ptr<Base> m_ptr;
};

template<typename... TArgs>
class Event : private shared_ptr<Event<TArgs...>*> {
public:
	using Handler = function<void(TArgs...)>;

private:
	using ListenerList = list<Handler>;
	using Iterator = typename ListenerList::iterator;

public:
	class Listener : public EventHandler::Base {
		friend Event;

		Listener(const Event& ev, Handler f) {
			observe(ev, f);
		}

	public:
		Listener() = default;
		Listener(const Listener& other) = delete;
		Listener(Listener&& other) {
			m_event = other.m_event;
			m_it = other.m_it;
			other.m_event.reset();
		}
		~Listener() {
			reset();
		}

		auto operator=(const Listener& other)->Listener& = delete;
		auto operator=(Listener&& other)->Listener& {
			reset();
			m_event = other.m_event;
			m_it = other.m_it;
			other.m_event.reset();
			return *this;
		}

		inline operator bool() const { return !m_event.expired(); }

		auto observe(const Event& ev, Handler h)->void {
			reset();
			m_event = ev;
			m_it = ev.addHandler(h);
		}
		auto reset()->void {
			if (!m_event.expired())
				(*m_event.lock())->removeHandler(m_it);
			m_event.reset();
		}

	private:
		weak_ptr<Event*> m_event;
		typename ListenerList::iterator m_it;
	};

	friend Listener;

	Event() : shared_ptr<Event*>(std::make_shared<Event*>(this))
	{ }
	Event(const Event&) = delete;
	Event(Event&&) = default;

	auto operator=(const Event&)->Event& = delete;
	auto operator=(Event&&)->Event& = default;
	auto operator()(TArgs... args) const {
		return notify(std::forward<TArgs>(args)...);
	}

	auto connect(Handler h) const {
		return addHandler(h);
	}
	auto disconnect(Iterator it) const {
		removeHandler(it);
	}
	auto notify(TArgs&&... args) const {
		for (auto& f : m_listeners) {
			f(std::forward<TArgs>(args)...);
		}
	}
	auto numHandlers() const {
		return m_listeners.size();
	}
	auto listen(Handler h) const {
		return Listener(*this, h);
	}

private:
	auto addHandler(Handler fn) const {
		return m_listeners.insert(m_listeners.end(), fn);
	}
	auto removeHandler(Iterator it) const {
		m_listeners.erase(it);
	}

private:
	mutable ListenerList m_listeners;
};

} // namespace KidClone
