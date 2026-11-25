Recharge_management_system__
Mobile Recharge System in C

Problem Statement:
- Manual recharge logs are slow and error-prone.
- Tracking past transactions and balances is difficult.
- Manual GST calculation delays customer billing.
- Unvalidated inputs lead to duplicate or invalid records.

Project Objectives:
- Automate customer registration and recharge workflows.
- Store records permanently using binary files.
- Provide instant balance enquiry and transaction logs.
- Generate itemized receipts with automatic 18% GST.

Proposed Solution:
- 8-Option Menu: Simple, loop-driven console interface.
- Dual Binary Files:
- customers.dat for profiles and history.dat for logs.
- Input Validation: Enforces 10-digit numbers starting with 6-9.
- Duplicate Check: Prevents re-registering existing mobile numbers.

Novelty of the Code
- Auto-Increment IDs: Scans records to assign unique IDs from 1000.
- In-Place Updates: Uses fseek() to edit balance without rewriting the file.
- Smart Tax Split: Reverse-calculates base plan cost and 18% GST.
- Custom Safe Input: readline() handles multi-word names cleanly.

Data & Memory Handling:
- Structures: struct customer and struct history group user data.
- Pointers: Pass structs by reference (&temp) to update values directly.
- String Functions: strcmp(), strcpy(), strlen(), and strcspn().

File I/O & Program Flow:
- Binary File Operations: fopen(), fread(), fwrite(), and fseek().
- Modular Design: 9 focused functions for clean, readable code.
- Control Structures: switch-case menu routing and validation loops.
  
Challenges Faced & Solutions:

Challenge 1: fread() & fwrite() Syntax*
Issue: Confusion with parameter order — passing struct address (&temp), sizeof(struct customer), item count (1), and file pointer (*fp).
Fix: Standardized binary read/write blocks using exact struct sizes and fseek() offsets.

Challenge 2: readline() Function
Issue: Leftover newline (\n) from scanf() caused fgets() to skip input or break strcmp().
Fix: Added getchar() to clear the buffer and strcspn() to strip trailing newlines.

 The project is submitted by MURUGA DHARSHINI T. This project has been done by me. The file handling concepts and syntax are learned with the help of AI and use it in project.
       
