/*Clase implementada en el h porque al ser template y estar en el primer
proyecto que se compila, al compilarse nadie la llama y no genera ninguna
instancia. Deben ser los otros proyectos los que generen las distintas
instancias de singleton.*/

#pragma once
#ifndef __UTILS_SINGLETON
#define __UTILS_SINGLETON

#include <memory>
#include <typeinfo>
#include <iostream>

namespace me {
	
	template<class T>
	/**
	Ensures there is only one instance of a class, and offers global access to it.
	@tparam T is the class made a singleton
	*/
	class Singleton {
	private:
		//The only instance of class T
		static std::unique_ptr<T> mInstance;
		
	protected:
		Singleton() {};

	public:
		Singleton<T>& operator=(const Singleton<T>& o) = delete;
		Singleton(const Singleton<T>& o) = delete;
		virtual ~Singleton() {}

		/**
		Constructs the instance of class T.
		@tparam Arguments to pass to class T constructor.
		*/
		template<typename ...Targs>
		static T* init(Targs &&...args) {
			if (mInstance.get() == nullptr) {
				mInstance.reset(new T(std::forward<Targs>(args)...));
#ifdef _DEBUG
				std::cout << "Singleton: Instance of " << typeid(T).name() << " created.\n";
			}
			else {
				std::cout << "Singleton error: There already is an instance of class " << typeid(T).name() << ".\n";
#endif
			}
			return mInstance.get();
		}

		/**
		Returns the class T instance. If it does not exits, creates it with
		the default constructor and returns it.
		@return Reference to the only instance of class T.
		*/
		static T* instance() {
			if (mInstance.get() == nullptr)
				return init();
			return mInstance.get();
		}
	};

	template<class T>
	std::unique_ptr<T> Singleton<T>::mInstance;
}

#endif