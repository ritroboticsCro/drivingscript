#include "roscoreinit.h"
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


RosCoreInit::RosCoreInit()
{

    system("gnome-terminal -x sh -c 'roscore'");


}

