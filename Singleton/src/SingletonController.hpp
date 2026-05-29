/*+===================================================================
* File : SingletonController.h
* Author : ryuu3160
* Date : 2024/07/27
* Note : mozc style singleton controller class
*
* (C) 2024 ryuu3160. All Rights Reserved.
===================================================================+*/
#pragma once

// ==============================
//	include
// ==============================
#include <mutex>
#include <vector>
#include <algorithm>

class SingletonController final
{
public:
	using ControllerFunc = void(*)();   // function pointer type for destroy functions

    /**
	 * @brief Register a destroy function for a singleton class
	 * @param In_Func Function pointer to the destroy function of the singleton class
     */
    static void AddController(_In_ ControllerFunc In_Func)
    {
        std::lock_guard<std::mutex> lock(GetMutex()); // Lock to prevent simultaneous access
        if (GetControllerCount() < GetControllerList().max_size())
        {
            GetControllerList().push_back(In_Func);
        }
    }

    /**
	 * @brief Call the registered destroy functions in reverse order to release the singleton instances
     */
    static void Release()
    {
        std::lock_guard<std::mutex> lock(GetMutex()); // Lock to prevent simultaneous access
        for(auto func = GetControllerList().rbegin(); func != GetControllerList().rend(); ++func)
        {
            (*func)();
		}
        GetControllerList().clear();
    }

private:
    static std::mutex &GetMutex()
    {
        static std::mutex g_mutex;
        return g_mutex;
    }
    static int &GetControllerCount()
    {
        static int g_nControllerCount = 0;
        return g_nControllerCount;
    }
    static std::vector<ControllerFunc> &GetControllerList()
    {
        static std::vector<ControllerFunc> g_ControllerList;
        return g_ControllerList;
    }
};