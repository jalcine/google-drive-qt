#ifndef OPERATION_H
#define OPERATION_H

#include "network/queries.h"

class Operation
{
public:
    Operation();

public:
    void updatePanelContent(bool opposite);

protected:
      Queries queries;
};

#endif // OPERATION_H
