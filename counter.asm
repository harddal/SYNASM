DB 1h, 0h  ; Set RAM1 to 0
LD 1h, EAX  ; Load RAM1 into register 1
DCO "@COUNTER "
INC EAX, NUL ; Increment the value in register 1
DIR EAX, NUL ; Display the value of register 1
DCO "@, "
JMP 7h, 5h ; Jump to line 5 (DCO makes line 4 line 5)
