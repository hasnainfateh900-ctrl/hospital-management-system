# Hospital Management System (Console Application)

A C++ console application modeling basic hospital workflows with people, doctors, nurses, patients, appointments, and visit history.

## Features in the current code

- Register a patient
- Schedule appointments
- Record visits and view patient history
- View follow-up appointments
- Manage doctor availability slots
- Save and reload records from a local text file

## Concepts demonstrated

- Object-oriented programming and inheritance
- Multiple classes split across header/source files
- Vectors and basic record serialization
- File input/output
- Menu-driven command-line interaction

## Build

Requires CMake 3.16+ and a C++17 compiler.

```bash
cmake -S . -B build
cmake --build build
```

Run the generated executable from the build output directory. The app currently reads/writes `hospital_db.txt` relative to the working directory.

## Important privacy and correctness notes

This is an educational prototype, not a real clinical system. Do not enter real patient or insurance information. The local text-file format is not encrypted and is not suitable for sensitive records.

Before using this as a flagship internship project, improve and test:
- Input validation and duplicate-ID handling
- Safe parsing of malformed database lines
- Consistent appointment/doctor-slot validation
- Automated unit tests
- Separation of persistence from business logic
- Error reporting when saving fails
- A sample-data generator rather than committing real records

## Roadmap

1. Add tests for patient registration, scheduling, and persistence.
2. Replace raw pointers in loading logic with safer ownership patterns.
3. Add a structured repository/data-access layer.
4. Add a database backend and documented schema.
5. Add screenshots or a short demo GIF after the application has been run and verified.
