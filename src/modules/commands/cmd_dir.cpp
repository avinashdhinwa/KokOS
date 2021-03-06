#include <c/stdio.h>

#include <cpp/string.hpp>
#include <cpp/vector.hpp>

#include <drivers/storage/fat.h>
#include <modules/shell_global.hpp>

void cmd_dir(const string& strArgs)
{
    vector<string> vecArgs = strArgs.split(' ', true);
    
    if (vecArgs.size() >= 2)
    {
        print("Invalid arguments!\n");
        print("Syntax: dir [Directory Path]\n");
        
        vecArgs.dispose();
        return;
    }

    if (vecArgs.size() == 0)
    {
        listDirectory(Shell::activePart, Shell::activeDir);
    }
    else
    {			
        uint32_t pathCluster = resolvePath(Shell::activePart, Shell::activeDir, vecArgs[0].c_str());

        if (pathCluster)
        {
            listDirectory(Shell::activePart, pathCluster);
        }
        else
        {
            print("Invalid directory path!\n");
        }
    }

    vecArgs.dispose();
}
