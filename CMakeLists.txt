cmake_minimum_required(VERSION 3.19)
project(DecentralizedComputing)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-fpermissive -std=c++0x")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.77.0 COMPONENTS regex)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(DecentralizedComputing main.cpp stdafx.cpp stdafx.h bigint.cpp bigint.h entry.cpp entry.h SortedDoublyLinkedListIterator.cpp SortedDoublyLinkedListIterator.h SortedDoublyLinkedList.cpp SortedDoublyLinkedList.h PrimeNumberLibrary.cpp PrimeNumberLibrary.h PendingPrimeCalculation.cpp PendingPrimeCalculation.h PrimeHelpers.cpp PrimeHelpers.h)
target_link_libraries(DecentralizedComputing ${Boost_LIBRARIES})
