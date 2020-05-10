#include <stdint.h>

uint64_t ph_off;
uint16_t ph_ent_size, ph_num;
uint32_t seg_type;
uint64_t p_offset, p_filesz;

uint64_t sh_off;
uint16_t sh_ent_size, sh_num, sh_strtab_index;
uint64_t str_table_off, str_table_size;

int section_header(FILE* fp);
int program_header(FILE* fp);
int map_segment_section(FILE* fp);
