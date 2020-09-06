/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2020. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_ACI                        2       /* callback function: ACI */
#define  PANEL_ACV                        3       /* callback function: ACV */
#define  PANEL_FEEQUENCY                  4       /* callback function: frequency */
#define  PANEL_CAP                        5
#define  PANEL_RESISTOR                   6
#define  PANEL_DCI                        7       /* callback function: DCI */
#define  PANEL_DCV                        8       /* callback function: DCV */
#define  PANEL_ID                         9       /* callback function: WhoAmI */
#define  PANEL_RESET                      10      /* callback function: Reset */
#define  PANEL_EXIT                       11      /* callback function: myExit */
#define  PANEL_IDN                        12
#define  PANEL_CAP_SHOW                   13
#define  PANEL_FREQUENCY_SHOW             14
#define  PANEL_RESISTOR_SHOW              15
#define  PANEL_ACI_SHOW                   16
#define  PANEL_ACV_SHOW                   17
#define  PANEL_DCI_SHOW                   18
#define  PANEL_DCV_SHOW                   19
#define  PANEL_STRING_3                   20
#define  PANEL_STRING_2                   21
#define  PANEL_STRING                     22


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ACI(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ACV(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DCI(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DCV(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK frequency(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK myExit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Reset(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK WhoAmI(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
