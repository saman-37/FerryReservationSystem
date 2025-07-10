//************************************************************
// main.cpp
//************************************************************
// Purpose: Main entry point for the FerryReserver application.
// July 9, 2025 Revision 1 - Created initial coding convention document. Team-wide agreement.
//************************************************************ 

//************************************************************
// Coding Convention for FerryReserver Project (CMPT 276 A3)
//************************************************************

/*


General Style:
--------------
-	All .h files and .cpp files begin with a divider comment, file name, purpose and revision history
-	Use consistent 3-space indentation throughout the project
-	Opening braces ‘{‘ go on the same line as the function header and ‘}’ is placed on the next line from where function ended. The same rule applies to loops and switches.
        E.g. function (string a) {
                // function body
            }
-	Always include spaces around assignment and arithmetic operators ( ‘=’ , ‘+’, ‘-‘ ).
        E.g. x = y + z;

-	One space after comma is used in argument lists.
        E.g. function( int a, int b, int c)

Spelling: 
---------
-	The first letter of a function is lower case, and the first letter of every embedded word in a function name is capitalized.
        E.g. void printSailingReport();

-	Class names use PascalCase with first letter and every embedded word capitalized as well.
        E.g. class Sailing, SailingControl

-	The first letter of variable is lower case, and the first letter of every embedded word in a variable name is capitalized.
        E.g. vesselName

-	Constants are completely capitalized and with underscores.
        E.g. const SAILING_ID_LENGTH


Version Control:
----------------
-	Every file has a “Revision History” at the top with:
-	Version number or date
-	Author initials or name
-	Brief description of the change

Comments:
---------
-	Use single-line comments for brief explanations and multi-line comments for detailed descriptions.
-	Each file begins with the following pattern:
//************************************************************
// [filename].h
//************************************************************
// Purpose: [One-line description of the class/module's role]
// [Date] Revision 1 - [Team member(s)]
//************************************************************ 

*/