#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "print_header.h"

int map_segment_section(FILE* fp)
{
	char* buf = (char*)malloc(str_table_size);
	fseek(fp, str_table_off, SEEK_SET);
	fread(buf, 1, str_table_size, fp);

	printf("Mapping Segment to Sections:\n");
	for (int i = 0; i < ph_num; i++)
	{
		printf("[%d] ", i);
		
		fseek(fp, ph_off + i*56, SEEK_SET);
		fseek(fp, 8, SEEK_CUR);
		fread(&p_offset, 1, 8, fp);
		fseek(fp, 16, SEEK_CUR);
		fread(&p_filesz, 1, 8, fp);
		uint64_t p_start = p_offset;
		uint64_t p_end = p_offset + p_filesz;
		
		uint64_t s_start, s_end;
		uint32_t s_name;
		uint64_t s_off, s_size;

		for (int j = 0; j < sh_num; j++)
		{
			fseek(fp, j*64 + sh_off, SEEK_SET);
			
			fread(&s_name, 1, 4, fp);
			fseek(fp, 20, SEEK_CUR);
			fread(&s_off, 1, 8, fp);
			fread(&s_size, 1, 8, fp);
			s_start = s_off;
			s_end = s_off + s_size;
			if (s_start >= p_start && s_end <= p_end)
			{
				while (buf[s_name] != 0)
				{
					printf("%c", buf[s_name]);
					s_name++;
				}
				printf(" ");
			}
		}
		printf("\n");
	}
	free(buf);
	return 0;
}
