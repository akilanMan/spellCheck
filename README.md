In this project, we are tasked to make our own version of a Spellchecker which flags incorrect words with a given dictionary (dict.txt) and test file (test.txt). This project involves the use of POSIX functions to traverse through the dictionary and text files to produce results. The memory and data is managed in a static array with a fixed buffer. Each item in the array is the string of characters which make up the words.

MAKEFILE
    -To run the program,
        -make 
        -./spchk <dictionary> <directory>

TESTPLAN/IMPLEMENTATION

load_dictionary() -->
    -Input a valid dictionary file path and verify that the file opens without errors. If the file does not exist, displays an error message.
    -Provide a dictionary file containing words. 
    -Confirm that the function correctly reads and stores the words from the file.
    -Input words into the dictionary containing different versions of the word for checking (real, REAL, Real)
    -Verify that the function does not add duplicate words to the dictionary array to manage memory.

process_file() -->
    -Input a valid text file path and verify that the file opens without errors.
    -Provide a text file containing words and punctuation. -Verify accurate reporting of invalid words encountered in the text file.
    -Test the function's handling of trailing punctuation marks attached to words. Verify correct removal of trailing punctuation before word validation to prevent false flags.
    -Ensure tracking of line and column numbers while processing the text file. This is for error reporting to identify the location of flagged words.
    -Test the function's performance with text files processing without encountering memory or performance issues. 

traverse_directory
    -Input a valid directory path and verify that the directory opens without errors.
    -Provide a directory containing text files and subdirectories. 
    -Test the function's handling of subdirectories within the specified directory.
    -Ensure that the function retrieves the status of each file correctly. Verify detection of regular files and directories while ignoring "." and ".." entries. 
    -Test the function's performance with directories containing various numbers of files and subdirectories. 


TESTING STRATEGY

-Load Dictionary Test:
    -Load a dictionary file with a set of words.
    -Verify that words are correctly loaded into the dictionary array.
    -Confirm that words are stored in lowercase, capitalized, and uppercase formats as appropriate.

Process Text File Test:
    -Provide a sample text file containing known words, misspelled words, and punctuation.
    -Execute the process_file function with the test file.
    -Check if words are identified and validated against the loaded dictionary.
    -Ensure reporting of flagged words, including their location within the text file.

Traverse Directory Test:
    -Create a directory structure with nested directories and text files.
    -Invoke the traverse_directory function with the root directory.
    -Verify that text files ending with ".txt" are processed correctly.
    -Confirm proper traversal of subdirectories and processing of text files within each directory.

Error Handling Test:
    -Introduce errors such as non-existent files, invalid file permissions, or corrupted files.
    -Validate that appropriate error messages are displayed for each error scenario.
    -Ensure the program gracefully handles errors without crashing or causing unexpected behavior.

Testing various different words and seeing if they get flagged or not
    -This includes symbols, different versions of capitalization, etc
    -\Test includes two test files that test the funcitonallity of such using a dict.txt


EDGE CASES AND ERRORS

Capital Letters
    -Beginning Capitalization
    -Irregular Capitalization
    -Real, real, REAL are the only accepted formats, for example. ReAl would be flagged as incorrect.

Capital Specific Words in Dictionary
    -Words that have capital letters in it should not be considered flagged
    -For example, MacDonald should be flagged if spelled as macdonald
