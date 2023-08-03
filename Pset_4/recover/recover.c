#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    else {

        // open the memory card
        FILE *file = fopen(argv[1], "r");
        if (file == NULL) {
            printf("Could not find the fle\n");
            return 2;
        }

        // create the necessary variables
        unsigned char buffer[512];
        int counter = 0;
        FILE *output_file = NULL;
        char *filename = malloc(8 * sizeof(char));

        // loop through the memory card
        while (fread(buffer, sizeof(char), 512, file))
        {
            // look for a beginning of a JPEG file
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {

                if (counter > 0)
                {
                    fclose(output_file);
                }

                // create the filename for the new JPEG file and open it
                sprintf(filename, "%03i.jpg", counter);
                output_file = fopen(filename, "w");
                counter++;
            }
            // write the data to the output fle if it exists
            if (output_file != NULL) {
                fwrite(buffer, sizeof(char), 512, output_file);
            }
        }

        // free the allocated memory and close the files
        free(filename);
        fclose(output_file);
        fclose(file);

        return 0;
    }
}