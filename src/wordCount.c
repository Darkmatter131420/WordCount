#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void count_characters(FILE *file) {
	int count = 0;
	char c;

	while ((c = fgetc(file)) != EOF) {
		count++;
	}

	printf("�ַ�����%d\n", count);
}

void count_words(FILE *file) {
	int count = 0;
	char c;
	int in_word = 0;

	while ((c = fgetc(file)) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n' || c == ',') {
			if (in_word) {
				count++;
				in_word = 0;
			}
		} else {
			in_word = 1;
		}
	}

	if (in_word) { // �ļ���β����ڵ����У�Ҳ��һ������
		count++;
	}

	printf("��������%d\n", count);
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s [-c | -w] <input_file_name>\n", argv[0]);
		return 1;
	}

	char *parameter = argv[1];
	char *input_file_name = argv[2];

	FILE *file = fopen(input_file_name, "r");
	if (!file) {
		perror("Error opening file");
		return 1;
	}

	if (strcmp(parameter, "-c") == 0) {
		count_characters(file);
	} else if (strcmp(parameter, "-w") == 0) {
		count_words(file);
	} else {
		fprintf(stderr, "Invalid parameter. Use -c for character count or -w for word count.\n");
		fclose(file);
		return 1;
	}

	fclose(file);
	return 0;
}
