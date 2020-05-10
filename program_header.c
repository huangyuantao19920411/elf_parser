#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "print_header.h"

int program_header(FILE* fp)
{
	if (!fp)
	{
		perror("open ELF file please.");
		exit(1);
	}

	fseek(fp, 32, SEEK_SET);
	int r = fread(&ph_off, 1, 8, fp);
	if (r != 8)
	{
		perror("read program segment header offset");
		exit(2);
	}
	printf("program header offset in file: %ld (0x%lx)\n", ph_off, ph_off);

	fseek(fp, 14, SEEK_CUR);
	r = fread(&ph_ent_size, 1, 2, fp);
	if (r != 2)
	{
		perror("read program header entry size");
		exit(2);
	}
	printf("program header entry size: %d\n", ph_ent_size);

	r = fread(&ph_num, 1, 2, fp);
	if (r != 2)
	{
		perror("read section header number");
		exit(2);
	}
	printf("program header number: %d\n", ph_num);

	fseek(fp, ph_off, SEEK_SET);
	for (int i = 0; i < ph_num; i++)
	{	
		r = fread(&seg_type, 1, 4, fp);
		if (r != 4)
		{
			perror("read segment type");
			exit(2);
		}
		fseek(fp, 4, SEEK_CUR);
		r = fread(&p_offset, 1, 8, fp);
		fseek(fp, 16, SEEK_CUR);
		r = fread(&p_filesz, 1, 8, fp);
		printf("program header: type 0x%x, offset 0x%lx, filesize 0x%lx\n", seg_type, p_offset, p_filesz);
		
		fseek(fp, 16, SEEK_CUR);
	}

	printf("\n");
	return 0;
}
