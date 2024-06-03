#include "lab4.h"
#include <stdint.h>
#include <stdio.h>

// Assume that the least significant 11 bits of instBits
// contain the instruction bits [31-21].
// Set the output signals as follows:
//  outputSignals.Reg2Loc = 1;
void setControl(uint64_t instBits, ControlSignals& outputSignals) {
  if(instBits ==  0b10001011000  ) {   //ADD

    outputSignals.Reg2Loc = 0;
    outputSignals.ALUSrc = 0;
    outputSignals.MemtoReg = 0;
    outputSignals.RegWrite = 1;
    outputSignals.MemRead = 0;
    outputSignals.MemWrite = 0;
    outputSignals.Branch = 0;
    outputSignals.ALUOp = 0b10;

   }
   else if(instBits == 0b11001011000 || instBits == 0b10101010000){ //  SUB or ORR
    outputSignals.Reg2Loc = 0;
    outputSignals.ALUSrc = 0;
    outputSignals.MemtoReg = 0;
    outputSignals.RegWrite = 1;
    outputSignals.MemRead = 0;
    outputSignals.MemWrite = 0;
    outputSignals.Branch = 0;
    outputSignals.ALUOp = 0b10;
   }
 

 else if(instBits == 0b11111000010){   //LDUR
   // outputSignals.Reg2loc = 0;
    outputSignals.ALUSrc = 1;
    outputSignals.MemtoReg = 1;
    outputSignals.RegWrite = 1;
    outputSignals.MemRead = 1;
    outputSignals.MemWrite = 0;
    outputSignals.Branch = 0;
    outputSignals.ALUOp = 00;

}    

 else  if(instBits == 0b11111000000 ){   //STUR
    outputSignals.Reg2Loc = 1;
    outputSignals.ALUSrc = 1;
    //outputSignals.MemtoReg = 1;
    outputSignals.RegWrite = 0;
    outputSignals.MemRead = 0;
    outputSignals.MemWrite = 1;
    outputSignals.Branch = 0;
    outputSignals.ALUOp = 0b00;

} 

 else if(instBits ==  0b10010001000  ) {   //ADDI

    outputSignals.Reg2Loc = 0;
    outputSignals.ALUSrc = 0;
    outputSignals.MemtoReg = 0;
    outputSignals.RegWrite = 1;
    outputSignals.MemRead = 0;
    outputSignals.MemWrite = 0;
    outputSignals.Branch = 0;
    outputSignals.ALUOp = 0b10;

 }

else if(instBits ==  0b11010001000  ) {   //SUBI

    outputSignals.Reg2Loc = 0;
    outputSignals.ALUSrc = 0;
    outputSignals.MemtoReg = 0;
    outputSignals.RegWrite = 1;
    outputSignals.MemRead = 0;
    outputSignals.MemWrite = 0;
    outputSignals.Branch = 0;
    outputSignals.ALUOp = 0b10;
}

else if((instBits >> 3) == 0b10110100  ) {   //cbz

    outputSignals.Reg2Loc = 1;
    outputSignals.ALUSrc = 0;
   // outputSignals.MemtoReg = 0;
    outputSignals.RegWrite = 0;
    outputSignals.MemRead = 0;
    outputSignals.MemWrite = 0;
    outputSignals.Branch = 1;
    outputSignals.ALUOp = 0b01;
}
}



// Assume that the lower 32-bits of instBits contain the instruction.
// Return the appropraite sign extended version of the embedded
// immediate, based on the instruction type.
uint64_t getExtendedBits(uint64_t instBits) {
  uint64_t returnVal = 0;
  uint64_t first = 1;


  if((instBits >> 21) == 0b11111000000) {    //STUR
    
     if(instBits & (first  << 20 )){
      returnVal = (((instBits >> 12) & 0x1FF) | 0XFFFFFFFFFFFFFF00);

     }
     else{
       returnVal = ((instBits >> 12) & 0x1FF);

     }
     
  }

 else if((instBits >> 21) == 0b11111000010) {    //LdUR
    
     if(instBits & (first  << 20 )){
      returnVal = (((instBits >> 12) & 0x1FF) | 0XFFFFFFFFFFFFFF00);

     }
     else{
       returnVal = ((instBits >> 12) & 0x1FF);

     }
     
  }

 else if((instBits >> 22) == 0b1001000100) {    //ADDI
    printf("Is this working?");
    uint64_t uimm = (instBits >> 10) & 0xfff;
    if(uimm & 0x800)
      returnVal = uimm | 0xfffffffffffff000;
    else
      returnVal = uimm;
    //  if(instBits & (first  << 21 )){
    //   returnVal = (((instBits >> 10) & 0xFFF) | 0XFFFFFFFFFFFFF000);

    //  }
    //  else{
    //    returnVal = ((instBits >> 10) & 0xFFF);

    //  }
     
  }


  else if((instBits >> 22) == 0b1101000100 ) {    //subI
    
     if(instBits & (first  << 21 )){
      returnVal = (((instBits >> 10) & 0xFFF) | 0XFFFFFFFFFFFFFF00);

     }
     else{
       returnVal = ((instBits >> 10) & 0xFFF);

     }
     
  }

  else if((instBits >> 24) ==  0b10110100 ) {    //CBZ
    
     if(instBits & (first  << 23 )){
      returnVal = (((instBits >> 5) & 0xFFF) | 0XFFFFFFFFFFFFFF00);

     }
     else{
       returnVal = ((instBits >> 5 & 0xFFF));

     }
     
  }


  return returnVal;
}


