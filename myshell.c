#include "String.h"
#include "Shell.h"
#include <stdio.h>


int main(int argc, char *argv[]) {
    Shell *shell = newShell();
    shell->userPrompt(shell);
    return 0;
}


/**
 * Gets command line arguments. Sets to usable defaults if none are given.
 */
// void readArguments(
//     int        *argc,
//     const char * argv[],
//     long       *lgPageSize,
//     long       *pageSize,
//     long       *logicalMemorySize,
//     String    **pageReplacementAlgorythm,
//     long       *nbrFrames,
//     long       *verbose,
//     String   **fileName
// ) {
//     // when no values are provided, load these
//     if (*argc < 5) {
//         argv[1] = "10";
//         argv[2] = "16";
//         argv[3] = "FIFO";
//         argv[4] = "16";
//         argv[5] = "0";
//         argv[6] = "randomHexValues.txt";
//         *argc   = 7;
//     }
//     if (*argc < 6) {
//         argv[5] = "0";
//         *argc   = 6;
//     }
//     if (*argc < 7) argv[6] = "";

//     *lgPageSize                = cStrToDouble(argv[1]);
//     int lgLogicSize            = cStrToLong(argv[2]);
//     *pageReplacementAlgorythm  = newString(argv[3]);
//     *nbrFrames                 = cStrToLong(argv[4]);
//     *verbose                   = cStrToLong(argv[5]);
//     *fileName                  = newString(argv[6]);

//     if (*verbose) {
//         printf("Page size: %lu bits\n",           *pageSize);
//         printf("logical memory size: %lu bits\n", *logicalMemorySize);
//         printf("algorithm: %s\n",                (*pageReplacementAlgorythm)->cString);
//         printf("Nbr of Frames: %lu\n",            *nbrFrames);
//     }
// }
