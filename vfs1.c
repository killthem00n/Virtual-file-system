#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void main()
{
	int file = open("output.txt", O_WRONLY | O_CREAT, 00700);
	char buffer1[128] = {"String from file"};
	char buffer2[128] = { 0 };
	size_t length1 = strlen(buffer1);
	write(file, buffer1, length1);
	close(file);
	file = open("output.txt", O_RDONLY);
	read(file, buffer2, length1);
	printf("%s\n", buffer2);
	close(file);
}
