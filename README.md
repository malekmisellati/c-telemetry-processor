# C Telemetry Processor

## Overview

A C application that reads simulated device telemetry data from a file, validates incoming records, stores valid records in a dynamically allocated linked list, calculates statistics, detects abnormal readings, and generates a report.

The project demonstrates fundamental C programming and systems programming concepts, including file I/O, pointers, dynamic memory allocation, linked lists, input validation, and build automation.

## Objectives

- Read telemetry records from a text file.
- Parse and validate incoming device data.
- Skip records containing invalid values.
- Store valid records using a dynamically allocated linked list.
- Calculate average temperature, average voltage, and highest temperature.
- Detect abnormal readings using predefined thresholds and device status.
- Generate a telemetry report in an output file.
- Manage dynamically allocated memory and handle allocation failures.
- Automate compilation using a Makefile.

## Technologies

- C (C11)
- GCC
- GNU Make
- Standard C Libraries
- File I/O
- Dynamic Memory Allocation
- Linked Lists

## Project Structure

```text
c-telemetry-processor/
│
├── src/
│   └── main.c
│
├── data/
│   └── telemetry.txt
│
├── output/
│   └── telemetry_report.txt
│
├── Makefile
└── README.md
```

## Telemetry Data Format

The application reads comma-separated telemetry records from `data/telemetry.txt`.

Each record contains:

```text
device_id,temperature,voltage,status
```

Example:

```text
1001,24.5,3.3,1
1002,28.7,3.2,1
1003,85.2,3.4,1
```

Field descriptions:

- `device_id`: Unique device identifier.
- `temperature`: Device temperature in Celsius.
- `voltage`: Device voltage in volts.
- `status`: Device status (`1` = active, `0` = inactive).

## Validation Rules

Records are validated before being added to the linked list.

| Field | Validation |
|---|---|
| Device ID | Must be greater than 0 |
| Temperature | Must be between -40°C and 85°C |
| Voltage | Must be between 2.5V and 3.6V |
| Status | Must be 0 or 1 |

Invalid records are skipped and are not included in the statistics or report.

## Processing and Analysis

The application performs the following operations:

1. Reads telemetry records from the input file.
2. Parses and validates each record.
3. Stores valid records in a dynamically allocated linked list.
4. Calculates total records, average temperature, average voltage, and highest temperature.
5. Identifies abnormal readings based on predefined conditions:
   - High temperature: above 70°C.
   - Low voltage: below 2.8V.
   - Inactive device: status equals 0.
6. Writes valid records, statistics, and abnormal reading classifications to an output report.
7. Releases allocated memory before exiting.

## Building the Application

### Requirements

- GCC compiler
- GNU Make

### Compile

From the project root directory, run:

```bash
make
```

The Makefile compiles the application using:

- `-Wall`
- `-Wextra`
- `-std=c11`

The resulting executable is named `telemetry.exe`.

### Run

On Windows PowerShell:

```powershell
.\telemetry.exe
```

### Clean

To remove the compiled executable:

```bash
make clean
```

## Output

The application displays processed telemetry records, calculated statistics, and abnormal reading classifications in the terminal.

It also generates:

```text
output/telemetry_report.txt
```

The report contains:

- Valid telemetry records.
- Aggregate telemetry statistics.
- Abnormal reading detection results.

## Key Concepts Demonstrated

- C structures and data modeling.
- Pointers and pointer-to-pointer parameters.
- Dynamic memory allocation using `malloc()` and `free()`.
- Singly linked-list implementation and traversal.
- File handling using `fopen()`, `fgets()`, `fprintf()`, and `fclose()`.
- Input parsing and validation.
- Conditional logic and statistical calculations.
- Memory management and error handling.
- Compilation and build automation using GNU Make.
