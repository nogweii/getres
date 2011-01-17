/*
Created by Colin 'Evaryont' Shea <colin@evaryont.me>

The following code is licensed under the MIT/X11 license:

Copyright (C) 2011 by Colin Shea

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 */

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

void usage();

int main(int argc, char *argv[]){

    char *displayName = "";
    int argIndex = 0;
    // loop through argv and parse any parameters/flags
    for (argIndex = 1; argIndex < argc; argIndex++) {
        char *arg = argv[argIndex];
        if (arg[0] == '-') {
            switch (arg[1]) {
                case 'd':      /* -display host:display */
                    if (++argIndex >= argc) usage();
                    displayName = argv[argIndex];
                    continue;
                default:      /* if we've reached here, pebcak issue */
                    fprintf(stderr, "Invalid parameters.\n");
                    usage();
                    return 1;
            }   /* End switch */
        }
    }   /* End for */
    // We must have 2 parameters: the application and the resource
    if (argv[argIndex-2] == NULL || argv[argIndex-1] == NULL) {
        fprintf(stderr, "Not enough parameters.\n");
        usage();
        return 1;
    }

    // Open the specified display (or default if none given)
    Display *dsp = XOpenDisplay( displayName );
    if( !dsp ) {
        // Ensure a connection
        printf("ERROR: Cannot open display! Exiting...\n");
        return 1;
    }

    // Use XGetDefault to get the value
    char *value = "";
    if ((value = XGetDefault(dsp, argv[argIndex-2], argv[argIndex-1])) != NULL)
        printf("%s\n", value); // Output it if successful

    // Clean up, exit.
    XCloseDisplay( dsp );
    return 0;
}

/**
 * Outputs a quick usage line, and exits with status code 1
 */
void usage() {
    fprintf(stderr, "usage: getres [-display DISPLAY] APPLICATION RESOURCE\n");
    exit(EXIT_FAILURE);
}
