#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
	char c;
	char buffer[64];
	unsigned i = 0;
	unsigned totalLines = 0;
  unsigned totalChar = 0;
  unsigned totalWords = 0;
	while(read(STDIN_FILENO, &c, 1) != 0) {
    if(c == '\n') {
      totalLines++;
      buffer[i] = '\0';
      i = 0;
      if(strlen(buffer) != 0) {
        totalWords++;
      }
    } else {
      if(c != ' ') {
        buffer[i] = c;
        i++;
      } else {
        buffer[i] = '\0';
        i = 0;
        if(strlen(buffer) != 0) {
          totalWords++;
        }
      }
    }
    totalChar++;
	}
	printf("Líneas: %u, Palabras: %u, Caracteres: %u\n", totalLines, totalWords, totalChar);
	return 0;	
}