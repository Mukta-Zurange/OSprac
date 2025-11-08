#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 1024
#define FILE_NAME "output.txt"

int main() {
    int pipe1[2], pipe2[2]; // pipe1: P1 -> P2, pipe2: P2 -> P1
    pid_t pid;
    char buffer[MAX];

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {
        // Child Process: counts characters, words, lines
        close(pipe1[1]); // close write end of pipe1
        close(pipe2[0]); // close read end of pipe2

        // Read sentence from parent
        read(pipe1[0], buffer, MAX);

        int chars=0, words=0, lines=0;
        int in_word = 0;
        for (int i=0; buffer[i]; i++) {
            chars++;
            if (buffer[i]=='\n') lines++;
            if (buffer[i]==' ' || buffer[i]=='\n' || buffer[i]=='\t')
                in_word = 0;
            else if (!in_word) {
                words++;
                in_word = 1;
            }
        }

        // Write results to file
        FILE *fp = fopen(FILE_NAME,"w");
        fprintf(fp,"Characters: %d\nWords: %d\nLines: %d\n", chars, words, lines);
        fclose(fp);

        // Read file content and send to parent
        fp = fopen(FILE_NAME,"r");
        char file_content[MAX];
        fread(file_content, 1, MAX, fp);
        fclose(fp);
        write(pipe2[1], file_content, strlen(file_content)+1);

        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);
    }
    else {
        // Parent Process: accepts sentences and displays processed results
        close(pipe1[0]); // close read end of pipe1
        close(pipe2[1]); // close write end of pipe2

        printf("Enter sentences (max 1024 chars, end with ENTER):\n");
        fgets(buffer, MAX, stdin);

        write(pipe1[1], buffer, strlen(buffer)+1);

        // Read result from child
        char result[MAX];
        read(pipe2[0], result, MAX);

        printf("\nProcessed Output from Child:\n%s", result);

        close(pipe1[1]);
        close(pipe2[0]);

        wait(NULL); // wait for child
    }

    return 0;
}
