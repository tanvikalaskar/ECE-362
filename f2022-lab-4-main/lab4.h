#ifndef LAB4H_
#define LAB4H_

#include <stdint.h>

// Assume that only the LSB of the 64-bit values
// are used to store the value of the control signal.
// Since this is a C-simulator and not a real piece of hardware
// wasting space on making all the types 64-bits is not a important
// but lets us keep the software flexible.
struct ControlSignals {
  uint64_t Reg2Loc;
  uint64_t Branch;
  uint64_t MemRead;
  uint64_t MemtoReg;
  uint64_t ALUOp;
  uint64_t MemWrite;
  uint64_t ALUSrc;
  uint64_t RegWrite;
};

extern void setControl(uint64_t instBits, ControlSignals& outputSignals);
extern uint64_t getExtendedBits(uint64_t instBits);

#endif
