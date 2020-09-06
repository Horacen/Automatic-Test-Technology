#include "windows.h" 
#include <visa.h>
#include <analysis.h>
//#include <formatio.h>
#include <userint.h>
//#include <cvirte.h>   
#include <ansi_c.h>
//#include <utility.h>
#include "gui.h"


int hpanel;   
float resetVal = 0;

int   CVICALLBACK MainCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);  

ViStatus   st;	     
ViSession  defRM;	
ViSession  dso;	    


ViChar     desc[128]="TCPIP0::192.168.2.5::inst0::INSTR";  

char inbuf[128];   
int  cnt;		

void IniDso(void);

int main(int argc, char *argv[ ])   {
	
    if ((hpanel = LoadPanel (0, "gui.uir", PANEL)) < 0)
        return -1;
	
	IniDso();
	
   	/* Display the panel and run the UI -- the menubar was attached to the   */
    /* panel already in the UIR Editor.                                      */
	
    DisplayPanel (hpanel);  
	
	InstallMainCallback (MainCallback, 0, 1);  
	
    RunUserInterface ();                                                        
    
    /* Free resources and return */
	
    DiscardPanel (hpanel);
  
	
    return 0;
	
}

int   CVICALLBACK MainCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_CLOSE :                 
				viClose(defRM);	     
				QuitUserInterface(0);break;
        case EVENT_COMMIT:
             break;
        case EVENT_IDLE:
			break;
	}

	return 0;
}






void IniDso(void)
{
	st = viOpenDefaultRM(&defRM);   				  //打开系统资源
	st = viOpen(defRM, desc, VI_NULL, VI_NULL, &dso); //打开仪器会话
	st = viSetAttribute(dso,VI_ATTR_TMO_VALUE, 10000);//
	
	st = viPrintf(dso,"*RST\n"); //复位仪器
//	st = viPrintf(dso,":HEADER OFF\n");   
	
//	st = viPrintf(dso, ":DATA INIT\n" );

	st = viPrintf(dso, ":AUTOSET EXECUTE;*WAI;*OPC?\n"); //自动捕获信号

}




/***-------------------------------------------------------------------***/

/* reset function */
int  CVICALLBACK Reset(int panel, int control, int event, void *callbackData, int eventData1, int eventData2){

	   if(event == EVENT_COMMIT){
			 
			st = viPrintf(dso,"*RST\n"); 		
		//	st = viPrintf(dso,":HEADER OFF\n");   
		//	st = viPrintf(dso, ":DATA INIT\n" );
			st = viPrintf(dso, ":AUTOSET EXECUTE;*WAI;*OPC?\n"); 
			
			strcpy(inbuf, " ");
			
			SetCtrlAttribute (panel, PANEL_IDN, ATTR_CTRL_VAL, inbuf);  //display data  
			SetCtrlAttribute (panel, PANEL_DCV_SHOW, ATTR_CTRL_VAL, resetVal);
			SetCtrlAttribute (panel, PANEL_ACV_SHOW, ATTR_CTRL_VAL, resetVal);  //display data 
			SetCtrlAttribute (panel, PANEL_DCI_SHOW, ATTR_CTRL_VAL, resetVal);  //display data   
			SetCtrlAttribute (panel, PANEL_ACI_SHOW, ATTR_CTRL_VAL, resetVal);  //display data 
			SetCtrlAttribute (panel, PANEL_FREQUENCY_SHOW, ATTR_CTRL_VAL,resetVal);  //display data 
			
		   
	   }
	   return 0;
}



/* IDN */
int  CVICALLBACK WhoAmI(int panel, int control, int event, void *callbackData, int eventData1, int eventData2){
	
	   if(event == EVENT_COMMIT){
			 
			st = viWrite(dso, "*IDN?",5,&cnt); 
			st = viRead(dso,  inbuf,128,&cnt);				     //

			/* display the measure data to GUI  */
			SetCtrlAttribute (panel, PANEL_IDN, ATTR_CTRL_VAL, inbuf);  //display data

	   }
	return 0;	
}


int  CVICALLBACK DCV(int panel, int control, int event, void *callbackData, int eventData1, int eventData2){
	
	float dcv=0; /* measure data */
	int   result = 0;
	if(event == EVENT_COMMIT){
		result = viQueryf(dso,"MEAS:VOLT:DC?\n","%f",&dcv);   //measure data
		if(result == -1){
			printf("error ,time out \n"); 
		}
		else{ /* display data to the GUI */ //dcv
			SetCtrlAttribute (panel, PANEL_DCV_SHOW, ATTR_CTRL_VAL, resetVal);  //display data 
			SetCtrlAttribute (panel, PANEL_DCV_SHOW, ATTR_CTRL_VAL, dcv);  //display data
		}
	}
	return 0;
}

int  CVICALLBACK ACV(int panel, int control, int event, void *callbackData, int eventData1, int eventData2){

	float acv=0; /* measure data */
	int   result=0;
	if(event == EVENT_COMMIT){
		result = viQueryf(dso,"MEAS:VOLT:AC?\n","%f",&acv);   //measure data
		if(result == -1){
			printf("error ,time out \n"); 
		}
		else{ /* display data to the GUI */ //acv
			SetCtrlAttribute (panel, PANEL_ACV_SHOW, ATTR_CTRL_VAL, resetVal);  //display data  
			SetCtrlAttribute (panel, PANEL_ACV_SHOW, ATTR_CTRL_VAL, acv);  //display data
		}
	}
	return 0;
}

int  CVICALLBACK DCI(int panel, int control, int event, void *callbackData, int eventData1, int eventData2){
	float dci=0; /* measure data */
	int   result=0;
	if(event == EVENT_COMMIT){
		result = viQueryf(dso,"MEAS:CURR:DC?\n","%f",&dci);   //measure data
		if(result == -1){
			printf("error ,time out \n"); 
		}
		else{ /* display data to the GUI */ //dci
			SetCtrlAttribute (panel, PANEL_DCI_SHOW, ATTR_CTRL_VAL, resetVal);  //display data   
			SetCtrlAttribute (panel, PANEL_DCI_SHOW, ATTR_CTRL_VAL, dci);  //display data
		}
	}
	return 0;
}

int  CVICALLBACK ACI(int panel, int control, int event, void *callbackData, int eventData1, int eventData2){
	float aci=0; /* measure data */
	int   result=0;
	if(event == EVENT_COMMIT){
		result = viQueryf(dso,"MEAS:CURR:AC?\n","%f",&aci);   //measure data
		if(result == -1){
			printf("error ,time out \n"); 
		}
		else{ /* display data to the GUI */ //aci
			SetCtrlAttribute (panel, PANEL_ACI_SHOW, ATTR_CTRL_VAL, resetVal);  //display data   
			SetCtrlAttribute (panel, PANEL_ACI_SHOW, ATTR_CTRL_VAL, aci);  //display data

		}
	}
	return 0;
}


int  CVICALLBACK frequency(int panel, int control, int event, void *callbackData, int eventData1, int eventData2) {
	float freq=0; /* measure data */
	int   result=0;
	if(event == EVENT_COMMIT){
		result = viQueryf(dso,"MEAS:FREQ?\n","%f",&freq);   //measure data
		if(result == -1){
			printf("error ,time out \n"); 
		}
		else{ /* display data to the GUI */ //dcv
			SetCtrlAttribute (panel, PANEL_FREQUENCY_SHOW, ATTR_CTRL_VAL, resetVal);  //display data   
			SetCtrlAttribute (panel, PANEL_FREQUENCY_SHOW, ATTR_CTRL_VAL, freq);  //display data
		}
	}
	return 0;
}


int  CVICALLBACK myExit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2){
	if(event == EVENT_COMMIT){
		viClose(defRM);	
		QuitUserInterface(0); 	
	}
	return 0;
}

