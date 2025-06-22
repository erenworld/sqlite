/*
** EREN TURKOGLU, 2025
** sqlite
** File description:
** cursor
**
** This module defines the Cursor abstraction, which is used to iterate over rows in a table.
** Cursors provide a consistent way to traverse rows during execution of queries like SELECT and INSERT.
** 
**  A Cursor is a pointer-like structure that keeps track of where you are in the table. It holds:
**  - The current row number
**  - A reference to the table
**  - A flag for whether you’re at the end of the table
**
** Functions:
** - table_start(): Returns a cursor pointing to the beginning of the table.
** - table_end():   Returns a cursor pointing just past the last row (used to signal the end of iteration).
**
** Usage:
**   Cursors simplify row navigation logic, especially when more advanced features like paging or B-trees are added later.
**   This makes your database engine modular, extensible, and easier to maintain.
*/

#include "../include/cursor.h"

Cursor *table_start(Table *table)
{
    Cursor *cursor = malloc(sizeof(cursor));

    if (cursor == NULL)
        return NULL;
    cursor->table = table;
    cursor->row_num = 0;
    cursor->end_of_table = (table->num_rows == 0);

    return cursor;
}

Cursor *table_end(Table *table)
{
    Cursor *cursor = malloc(sizeof(cursor));

    if (cursor == NULL)
        return NULL;
    cursor->table = table;
    cursor->row_num = table->num_rows;
    cursor->end_of_table = true;

    return cursor;
}
