#ifndef _UTILS_H
#define _UTILS_H

#include <thread>
#include <iostream>

void printThread(void)
{
    std::thread::id this_id = std::this_thread::get_id();
    std::cout << "thread " << this_id << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
}

void sleepThread(void)
{
    std::chrono::milliseconds timeToSleep(100);
    std::this_thread::sleep_for(timeToSleep);
}

#endif