#ifndef pnl_h
#define pnl_h

void pnl_resizeScreen (PANEL* pnl, BOOL setShow);

void pnl_centerX (PANEL* pnl, BOOL setShow);
void pnl_relY (PANEL* pnl, var f, BOOL setShow);

void pnl_setShow (PANEL* pnl, BOOL setShow);

#include "pnl.c"

#endif /* pnl_h */