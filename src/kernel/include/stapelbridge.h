#include <stdint.h>

typedef struct {
  void* central_memory;
  void* stack;
  void* call_stack;
  uint64_t instruction_pointer;
  uint64_t stack_pointer;
  uint64_t call_stack_pointer;
} __attribute__((packed)) StapelMultitaskingInstance;

StapelMultitaskingInstance* insert_stapel_cardridge(void* memoryregion);
int handle_next_instruction(StapelMultitaskingInstance* cv);
void load_stapel_tutorial();
