This is a project for a simple encrypted command-line Notebook, dedicated to Windows.
The program allows to create, edit, view and delete text files. All text files are encrypted and stored in Notes/ folder within the project directory. 

A. List of commands 

":ack"<<"Acknowledgement
":create file.txt" - Creates file.txt (if it does not already exist)
":delete file.txt" - Deletes file.txt (if it exists)
":edit file.txt" - Opens file.txt in edit mode. You can modify the content with ":edit", ":erase" and ":insert" commands.
":edit line_nr" - Allows editing of the specified line
":end" - Ends the program
":erase line_nr" - Erase the specified line
":exit" - Exits manual/file (in modify mode, without saving changes)
":help" - Displays the manual
":insert line_nr" - Allows insertion insertion of line(s) after the specified line
":ok" - Acknowledgement
":open file.txt" - Opens file.txt in read only mode (if it exists)
":save" - Saves changes in the current file
":write file.txt" - Opens file.txt in write mode. You can write new content at the end of file.


B. Encryption
The program uses the Vigenere cipher. The cipher table contains: 
-numbers, 
-lowercase and uppercase letters (latin alphabet), 
-following characters!"#$%&'()*+,-./:;<=>?@[\]^_` 
-spaces. 
(ASCII codes from 32 to 122)

**Attention**: if the wrong key is used to decrypt the file, its content will become unrecoverable.