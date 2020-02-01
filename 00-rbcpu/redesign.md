Some good redesign plans for my CPU.

Rather than focusing on the hardware, let's focus on the instruction
set programmer interface.  The advent of RISC architectures with no
processor condition code flags means that I shouldn't assume compute
instructions should set flags by default.  Rather, just as there are
separate instructions to explicitly read flags or ignore them, there
should also be separate instructions to explicitly set flags or not
set them at all, and which ones.

Basic Instructions.

```
Flags:
Z = Zero
N = Sign (negative)
C = Carry
V = Overflow

Registers:
AL, AH
BL, BH

LD
ST

NOT
AND
OR
XOR

SHL
SHR
ASR
ROL
ROR

INC
CAR
DEC
BOW

ADD
ADC
SUB
SBC

BIT
CMP

BZ
BNZ
BN
BNN
BC
BNC
BV
BNV

BA
BAE
BB
BBE

BG
BGE
BL
BLE

JMP
```

Yeah, something like that.  No matter how many times I do this, it
always seems to need to have room for improvement.
