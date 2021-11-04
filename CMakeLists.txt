cmake_minimum_required(VERSION 3.0.0)
project(main VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(includes)

add_executable(main
    includes/functions.cpp
    includes/functions.hpp
    includes/hash.cpp
    includes/hash.hpp
    includes/includes.hpp

    includes/classes/block_class.cpp
    includes/classes/block_class.hpp
    includes/classes/blockchain_class.cpp
    includes/classes/blockchain_class.hpp
    includes/classes/transaction_class.cpp
    includes/classes/transaction_class.hpp
    includes/classes/user_class.cpp
    includes/classes/user_class.hpp
    main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
