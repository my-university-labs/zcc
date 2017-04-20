/* author: dongchangzhang */
/* time: Thu Apr 20 14:48:28 2017 */

#include "symboltablemanager.h"

SymbolTableManager::SymbolTableManager()
{
    main_table = do_create_new_table(START_INDEX);
    cursor = main_table;
}