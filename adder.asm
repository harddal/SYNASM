DB 0x1, 0xA
LD 0x1, EAX
DCO "@INPUT FIRST NUMBER "
IIP EAX, NUL
DB 0x1, 0xB
LD 0x1, EAX
DCO "@nnINPUT SECOND NUMBER "
IIP EAX, NUL
LD 0xA, EAX
LD 0xB, EBX
ADD EAX, EBX
DCO "@nnRESULT "
DIR EAX, NUL