#ifndef _SIMPLE_PRINT_H
#define _SIMPLE_PRINT_H

////////////////////////////////////////////////////////////////////////////////
//
// General functions.
//
////////////////////////////////////////////////////////////////////////////////

extern _INT32 Print(FILE* lpFile,_STRING lpstrFormat,...);
extern _INT32 PrintLine(FILE* lpFile,_STRING lpstrFormat,...);

extern _STRING Format(_STRING lpstrContent,_STRING lpstrFormat,...);
extern _STRING FormatLine(_STRING lpstrContent,_STRING lpstrFormat,...);

extern _BOOL IsEndWithNewLine(_STRING lpstrContent);
extern void ClearEndWithNewLine(_STRING lpstrContent);

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !
