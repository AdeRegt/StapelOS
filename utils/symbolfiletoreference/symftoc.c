#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <symbol_file_in> <c_code_out> \n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    FILE *outfile = fopen(argv[2],"w");
    fprintf(outfile,"#include <stdint.h>\n#include \"../include/reflection.h\" \n\nchar* getSymbolnameForAddress(uint64_t input){\n\tchar* res;\n");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        if(strcmp(line,"getSymbolnameForAddress") == 0){
            continue;
        }
        fprintf(outfile,"\textern void %s();\n\tif(input>=((uint64_t)&%s)){\n\t\tres = \"%s\";\n\t}\n",line,line,line);
    }


    fprintf(outfile,"\treturn res;\n}\n");

    fclose(file);
    fclose(outfile);
    return EXIT_SUCCESS;
}