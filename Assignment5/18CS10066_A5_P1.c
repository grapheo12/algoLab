/* Name : Shubham Mishra
 * Roll No: 18CS10066
 * Assignment 5 Part 1
 */

#include <stdio.h>
#include <stdlib.h>
#define INPUT_FILE "log.txt"
#define OUTPUT_FILE "output.txt"
#define MAX_WORD_SIZE 1000

int main(){
	FILE *fi = fopen(INPUT_FILE, "r");
	int n_words;
	fscanf(fi, "%d", &n_words);
	fgetc(fi);

	int frequency[36];
	/* Indices:
	 * a - z: 0 - 25
	 * 0 - 9: 26 - 35
	 */


	char buff[MAX_WORD_SIZE];
	int i, j;

	for (i = 0; i < 36; i++)
		frequency[i] = 0;

	for (j = 0; j < n_words; j++){
		fgets(buff, MAX_WORD_SIZE, fi);
		printf("Current Word: %s\n", buff);
		for (i = 0; buff[i] != '\0'; i++){
			if (buff[i] >= 'a' && buff[i] <= 'z'){
				frequency[buff[i] - 'a']++;
			}else if (buff[i] >= '0' && buff[i] <= '9'){
				frequency[buff[i] - '0' + 26]++;
			}
		}
	}

	FILE *fo = fopen(OUTPUT_FILE, "w");
	for (i = 0; i < 26; i++){
		fprintf(fo, "%c=%d,", (char)(i + 'a'), frequency[i]);
	}
	for (i = 26; i < 36; i++){
		fprintf(fo, "%c=%d,", (char)(i + '0' - 26), frequency[i]);
	}
	fprintf(fo, "\n");

	fclose(fi);
	fclose(fo);

	return 0;
}