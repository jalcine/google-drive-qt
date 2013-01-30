#include "share.h"
#include "share/commontools.h"

Share::Share(QObject *parent) :
    NetworkManager(parent)
{
}

void Share::file(const Items::Data &source)
{
  CommonTools::msg("Not implemented yet");
}
