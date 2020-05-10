#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "print_header.h"

int section_header(FILE* fp)
{
	if (!fp)
	{
		perror("open ELF file please.");
		exit(1);
	}

	fseek(fp, 40, SEEK_SET);
	int r = fread(&sh_off, 1, 8, fp);
	if (r != 8)
	{
		perror("read section header offset");
		exit(2);
	}
	printf("section header offset in file: %ld (0x%lx)\n", sh_off, sh_off);

	fseek(fp, 10, SEEK_CUR);
	r = fread(&sh_ent_size, 1, 2, fp);
	if (r != 2)
	{
		perror("read section header entry size");
		exit(2);
	}
	printf("section header entry size: %d\n", sh_ent_size);

	r = fread(&sh_num, 1, 2, fp);
	if (r != 2)
	{
		perror("read section header number");
		exit(2);
	}
	printf("section header number: %d\n", sh_num);

	r = fread(&sh_strtab_index, 1, 2, fp);
	if (r != 2)
	{
		perror("read section header string table index");
		exit(2);
	}
	printf("section header string table index: %d\n", sh_strtab_index);

	fseek(fp, sh_off + sh_strtab_index * sh_ent_size, SEEK_SET);
	fseek(fp, 24, SEEK_CUR);

	r = fread(&str_table_off, 1, 8, fp);
	if (r != 8)
	{
		perror("read section name string table offset");
		exit(2);
	}
	printf("section name string table offset: %ld\n", str_table_off);

	r = fread(&str_table_size, 1, 8, fp);
	if (r != 8)
	{
		perror("read section name string table size");
		exit(2);
	}
	printf("section name string table size: %ld\n", str_table_size);
	
	char* buf = (char*)malloc(str_table_size);
	if (!buf)
	{
		perror("Allocate memory for section name string table");
		exit(3);
	}
	fseek(fp, str_table_off, SEEK_SET);
	r = fread(buf, 1, str_table_size, fp);
	if (r != str_table_size)
	{
		perror("read section name string table");
		free(buf);
		exit(2);
	}
	uint16_t i;
	for (i = 0; i < str_table_size; ++i)
	{
		if (buf[i] == 0)
			printf("\n");
		else
			printf("%c", buf[i]);
	}
	printf("\n");
	free(buf);
	return 0;
}
