#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t BYTE;
bool is_jpg_header(BYTE buffer[]);

#define BLOCK 512
#define FILENAME_SIZE 8

int main(int argc, char *argv[])
{
	#define BLOCK 512
	#define FILENAME_SIZE 8

	//correct usage
	if (argc != 2)
	{
		printf("Usage: ./recover image\n");
		return 1;
	}

	//buffer for 512 byte blocks
	BYTE buffer[BLOCK];

	//var to indicate status of whether we found jpg header or not; useful because jpgs are stored back to back
	bool found_jpg_header = false;

	//file count
	int fcount = 0;

	//file in
	FILE* f_in = fopen(argv[1], "r");

	//file out
	FILE* f_out;

	//if opening file successful
	if (fopen(argv[1], "r") != NULL)
	{
		//while fread returns true
		while (fread(buffer, BLOCK, 1, f_in))
		{
			//if current block contains jpg header
			if (is_jpg_header(buffer)) 
			{
				
				//if not yet found jpg header, set found_jpg_header to true
				if (!found_jpg_header)
				{
					found_jpg_header = true;
				}
				else {fclose(f_out);}

				//filename
				char filename[FILENAME_SIZE];
				
				//write filename based on current file count
				sprintf(filename, "%03i.jpg", fcount++); //001.jpg 002.jpg 003.jpg

				//open output file with filename
				f_out = fopen(filename, "w");
				
				//if error opening file
				if (f_out == NULL) {return 1;} //return

				//write one block to f_out
				fwrite(buffer, BLOCK, 1, f_out);
			}
			//continue writing if already found jpg header
			else if (found_jpg_header)
			{
				fwrite(buffer, BLOCK, 1, f_out);
			}
			
		}
		fclose(f_in);
		fclose(f_out);
	}
	//error opening input file
	else {printf("Error opening %s\n", argv[1]);}
	
}

bool is_jpg_header(BYTE buffer[])
{
	//if first 4 bytes match jpg header format, return true else return false
	return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0 ? true: false;
}
