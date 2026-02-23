
#include <stdio.h>

#define REQUIRED_ARGS \
    REQUIRED_STRING_ARG(input_file, "input", "Input file path") \
    REQUIRED_STRING_ARG(output_file, "output", "Output file path") \
    REQUIRED_INT_ARG(hi_mom, "greeting", "Say hi to Mom!")

#define OPTIONAL_ARGS \
    OPTIONAL_UINT_ARG(threads, 1, "-t", "threads", "Number of threads to use")

#define BOOLEAN_ARGS \
    BOOLEAN_ARG(help, "-h", "Show help")

#include "easyargs.h"


int main(int argc, char* argv[]) {
    
    args_t args = make_default_args();

    if (!parse_args(argc, argv, &args) || args.help) {
        print_help(argv[0]);
        return 1;
    }

    printf("Processing %s -> %s\n", args.input_file, args.output_file);
    printf("Using %u threads\n", args.threads);

    return 0;
}
