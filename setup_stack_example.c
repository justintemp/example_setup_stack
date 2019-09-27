/* temp.c */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*****************************************************************************************
 * The purpose of this program is to show a toy example of storing 'ls' on the 'stack'
 *****************************************************************************************/

int main() {
  // Stack is an array of 100 bytes and grows toward address 0x00
  void* stack = malloc(100);

  // Stack pointer should point to the top of the stack
  // (But since nothing is on the stack yet, this is initially PHYS_BASE i.e. the bottom of the stack)
  // (Your job is to put the arguments onto the stack and then make sure the stack pointer points to the top of the stack)
  char* temp_ptr = (char*)stack;
  temp_ptr += 99;
  void** esp = malloc(1); // esp isn't really the stack pointer. It's a pointer to the stack pointer
  void* PHYS_BASE = (void*)temp_ptr;
  *esp = PHYS_BASE;

  // Assume that the stuff above can't be changed and that all pintos gives you access to is esp (which is of type void**)

  /***
   * "RULES" for working with esp
   * 1. Dereference esp once to change the stack pointer --> *esp is the stack pointer
   * 2. Dereference esp twice to change the actual value on the stack --> **esp is the value on the stack
   *    (The number of bytes you change from this double dereference is based on what you typecasted esp into)
   */

  // Store the first character
  // Note that *char_ptr is basically doing **esp but with proper typecasting
  char* char_ptr = (char*)(*esp); // Get the actual stack pointer and cast it to char* since you can't dereference void*
  char_ptr -= 1; // Move the actual stack pointer one byte up so we can push a value onto the stack
  *char_ptr = 0;  // Store the Null character. Note that this is not the same as character '0' i.e. 0x30

  // Store the second character
  char_ptr -= 1;
  *char_ptr = 's';

  // Store the third character
  char_ptr -= 1;
  *char_ptr = 'l';

  // Check the values on the stack.
  printf("char_ptr: %s\n\n", char_ptr);

  // Note that char_ptr is pointing to the top of the stack, but *esp is still at the bottom of the stack
  // This is because we altered the stack values using char_ptr, which was a copy of *esp and not the actual value
  printf("char_ptr address: 0x%.4x\n", char_ptr);
  printf("*esp address: 0x%.4x\n\n", *esp);

  // Store the first integer
  // Note that you have to typecast to an int* instead of char* to store integers because of endianess and such
  int* int_ptr = (int*)(char_ptr);
  int_ptr -= 1;
  *int_ptr = 420;

  // Check the values on the stack. Note that int_ptr is pointing to the top of the stack
  printf("int_ptr: %d\n\n", *int_ptr);

  // Move the stack pointer to the top of the stack
  *esp = int_ptr;

  // Note that the stack pointer (*esp) and int_ptr atre now both pointing to the top of the stack
  printf("int_ptr address: 0x%.4x\n", int_ptr);
  printf("*esp address: 0x%.4x\n", *esp);
}
