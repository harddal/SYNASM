# SYNASM
![alt text](https://i.imgur.com/0X192sZ.png)

SYNASM - An assembler for Synergy's 29 bit computer in The Powder Toy.

Link to forum thread: http://powdertoy.co.uk/Discussions/Thread/View.html?Thread=19974&PageNum=0

Note that there is no built in detection for syntax errors so it may crash if there are any. I don't plan on improving this project as its use scope is limited.

Files:

    Main.cpp - Main source file
    
    LookupTable.h - Tables for converted values to binary
    
    Utility.h - Header for Utility.cpp
    
    Utility.cpp - Contains functions to convert instructions and arguments to binary
    
    adder.asm - Example assembly program, asks for two numbers, adds them, displays the result. Uses DCO strings.
    
    SYNASM.exe - Compiled .exe of the assembler if you do not wish to compile yourself. Requires MSVC++ 2013 redist
                 You can get it here: http://www.microsoft.com/en-us/download/details.aspx?id=40784

    SYNASM.xml - Adds syntax highlighting for SYNASM to Notepad++.
  
Features:

    Support for all 31 of the instructions
    
    Can use strings for DCO
    
    Being assembly, it's easier to write than straight binary
  
Instructions for use:

    Format: [CMD] [ARGA], [ARGB]
    
    It is important that there is whitespace between the [CMD] [ARGA], [ARGB].
    
    So writing 10 to RAM1 would be:
        DB 0x1, 0xA
 
    Numbers in the assembly are in hex to shorten it up. For commands without an ARGB you type NUL:
        DIR 0x1, NUL
 
    You can also use EAX and EBX to specify registers 1 and 2:
        ADD EAX, EBX
 
    It also supports code commenting with the semicolon:
        IIP EAX, NUL ;Get number from user input to register 1
    
    The new string support allows you to use DCO like this:
        DCO "@I AM A STRING"
    
    When using DCO strings can be pretty much any length, but some rules must be followed:
        The first character of every string must be @ to tell the assembler it is a string (will fix in future)
        All letters you write must be in UPPER case (Except escape characters).
        Currently commas are not supported in strings.
        
    The DCO supports escape sequences in strings:
        DCO "@LINE 1 nLINE 2"
    
    This will print "LINE 1" on the first line and "LINE 2" on the second line.
    
    The three jump commands have been added (JE, JNE, JMP). To use:
        JMP X, Y
        
    So to make an unconditonal jump to ROM 1x1:
        JMP 0x1, 0x1
    
    The escape characters are:
        b - Blows up the computer
        n - Enter/new line
        e - CONFIRM button
        c - Clear screen
        f - Filler byte for DCO


Use the included Lua file to load the binary program into TPT (might be currently broken in the newest versions of TPT ? but I am working on it).

Credit to Procybit for a guide on how to calculate the JMP commands: https://tpt.io/.320432
