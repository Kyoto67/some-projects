#include "file_IO_lib.h"
#include "bmp_struct_lib.h"
#include "image_IO_lib.h"
#include "image_rotate_lib.h"


int main( int argc, char** argv ) {


    if(argc != 3){
        fprintf(stderr, "Invalid arguments. Expected: %s input.bmp output.bmp", argv[0]);
        return -1;
    }

    FILE* read_file = NULL;
    FILE* write_file = NULL;



    if(!open_file(&read_file, argv[1], "rb")){
        fprintf(stderr, "Cannot open file: %s for reading\n", argv[1]);
        return -1;
    }

    if(!open_file(&write_file, argv[2], "wb")){
        fprintf(stderr, "Cannot open file: %s for writing\n", argv[2]);
        return -1;
    }

    struct image* image = NULL;
    enum read_status status = from_bmp(read_file, &image);
    if(status != 0){
        printf("Read error: %d", status);
        return status;
    }

    struct image* rotated = NULL;
    rotate_image(image, &rotated);
    free_image(image);

    enum write_status write_status = to_bmp(write_file, rotated);
    if(write_status != WRITE_OK){
        printf("Write error: %d", write_status);
        free_image(rotated);
        return write_status;
    }

    free_image(rotated);

    if(!close_file(read_file)){
        printf("Error on file closing");
        return -1;
    }

    return 0;
}
