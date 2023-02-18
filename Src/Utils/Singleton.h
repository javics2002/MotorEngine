/*Clase implementada en el h porque al ser template y estar en el primer
proyecto que se compila, al compilarse nadie la llama y no genera ninguna
instancia. Deben ser los otros proyectos los que generen las distintas
instancias de singleton.*/

#pragma once
#ifndef __UTILS_SINGLETON
#define __UTILS_SINGLETON

#include <memory>
#ifdef _DEBUG
#include <typeinfo>
#include <iostream>
#endif

namespace me {
	/**
	Ensures there is only one instance of a class, and offers global access to it.
	@tparam T is the class made a singleton
	*/
	template<class T>
	class Singleton {
	private:
		static std::unique_ptr<T> mInstance;
		
	protected:
		Singleton() {};

	public:
		Singleton<T>& operator=(const Singleton<T>& o) = delete;
		Singleton(const Singleton<T>& o) = delete;
		virtual ~Singleton() {}

		template<typename ...Targs>
		static T* init(Targs &&...args) {
			if (mInstance.get() == nullptr) {
				mInstance = std::make_unique<T>(std::forward<Targs>(args)...);
#ifdef _DEBUG
				std::cout << "Singleton: Instance of " << typeid(T).name() << " created.\n";
			}
			else {
				std::cout << "Singleton error: There already is an instance of class " << typeid(T).name() << ".\n";
#endif
			}
			return mInstance.get();
		}

		static T* instance() {
			if (mInstance.get() == nullptr)
				return init();
			return mInstance.get();
		}
	};
}

template<class T>
std::unique_ptr<T> me::Singleton<T>::mInstance;

#endif