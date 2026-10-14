cmake_minimum_required(VERSION 3.16)
project(HospitalManagementSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(hospital_management
    main.cpp
    Hospital.cpp
    Doctor.cpp
    Nurse.cpp
    Patient.cpp
    Person.cpp
    Visit.cpp
)

if(MSVC)
    target_compile_options(hospital_management PRIVATE /W4)
else()
    target_compile_options(hospital_management PRIVATE -Wall -Wextra -Wpedantic)
endif()
