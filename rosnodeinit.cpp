#include "rosnodeinit.h"
#include <stdlib.h>

RosNodeInit::RosNodeInit()
{

    system("gnome-terminal -x sh -c 'rosrun urg_node urg_node _ip_address:=192.168.0.10'");
}

