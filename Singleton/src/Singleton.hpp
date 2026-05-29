/*+==========================================================================
* File : Singleton.h
* Author : ryuu3160
* Date : 2024/07/27
* Note : mozc style singleton template class
* 
* (C) 2024 ryuu3160. All Rights Reserved.
=============================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include "SingletonController.hpp"
#include <mutex>

// ==============================
// Define
// ==============================
#if defined(_MSC_VER)
#define CPP_STD _MSVC_LANG
#else
#define CPP_STD __cplusplus
#endif

#if CPP_STD >= 202002L
#define TEMPLATE template<typename T> requires std::is_class_v<T>
#define MEMBER_VARIABLE static inline std::once_flag m_onceFlag; \
                        static inline T *m_instance = nullptr;
#define MEMBER_VARIABLE_DECLARATION
#elif CPP_STD >= 201703L
#define TEMPLATE template<typename T, typename = std::enable_if_t<std::is_class<T>::value>>
#define MEMBER_VARIABLE static inline std::once_flag m_onceFlag; \
                        static inline T *m_instance = nullptr;
#define MEMBER_VARIABLE_DECLARATION
#else
#define TEMPLATE template<typename T, typename = std::enable_if_t<std::is_class<T>::value>>
#define MEMBER_VARIABLE static std::once_flag m_onceFlag; \
                        static T *m_instance;
#define MEMBER_VARIABLE_DECLARATION \
    template <typename T, typename U> std::once_flag Singleton<T, U>::m_onceFlag; \
    template <typename T, typename U> T *Singleton<T, U>::m_instance = nullptr;
#endif

/**
 * @brief SingletonTemplateClass
 * @tparam T Class to be made singleton
 */
TEMPLATE
class Singleton
{
public:

    /**
	 * @brief Get the instance of the singleton class
	 * @return Reference to the instance of the singleton class
     */
    static T &GetInstance()
    {
		// if the instance is not created, create it
        if(m_instance == nullptr)
            std::call_once(m_onceFlag, create);

        return *m_instance;
    }

protected:
	// default constructor and destructor
    Singleton() = default;
    virtual ~Singleton() = default;

    // copy and assignment prohibited
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

    /**
     * @brief Create the instance
     */
    static void create()
    {
        m_instance = new T;
        SingletonController::AddController(&Singleton<T>::destroy);
    }
    /**
	 * @brief Destroy the instance of the singleton class
     */
    static void destroy()
    {
        delete m_instance;
        m_instance = nullptr;
    }

    MEMBER_VARIABLE
};

MEMBER_VARIABLE_DECLARATION
