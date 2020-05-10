#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "print_header.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		perror("Please enter command like this: ./show [file_path]");
		exit(1);
	}
	char* filepath = argv[1];
	FILE* fp = fopen(filepath, "rb");
	section_header(fp);
	program_header(fp);
	map_segment_section(fp);
	
	fclose(fp);
	return  0;
}
