//****************************************************************************
// @Module        MultiCAN Controller 
// @Filename      CAN.h
// @Project       DAVE_SG.dav
//----------------------------------------------------------------------------
// @Controller    Infineon TC1797
//
// @Compiler      Tasking 3.1
//
// @Codegenerator 1.0
//
// @Description   This file contains all function prototypes and macros for 
//                the CAN module.
//
//----------------------------------------------------------------------------
// @Date          2013-11-20 13:40:30
//
//****************************************************************************

// USER CODE BEGIN (CAN_Header,1)

// USER CODE END



#ifndef _CAN_H_
#define _CAN_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (CAN_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (CAN_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (CAN_Header,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

///  -------------------------------------------------------------------------
///  @Definition of a structure for the CAN data
///  -------------------------------------------------------------------------

// The following data type serves as a software message object. Each access to
// a hardware message object has to be made by forward a pointer to a software
// message object (CAN_SWObj). The data type has the following fields:
//
// usMOCfg:
// this byte contains the "Data Lenght Code" (DLC), the 
// "Extended Identifier" (IDE) and the "Message Direction" (DIR).
//
//
//         7     6     5      4    3     2     1     0
//      |------------------------------------------------|
//      |        DLC            | DIR | IDE |      |     |
//      |------------------------------------------------|
//
// uwID: 
// this field is four bytes long and contains either the 11-bit identifier 
// or the 29-bit identifier
//
// uwMask: 
// this field is four bytes long and contains either the 11-bit mask 
// or the 29-bit mask
//
// ubData[8]:
// 8 bytes containing the data of a frame
//
// usCounter:
// this field is two bytes long and contains the counter value 
//

typedef struct
  {
     ushort usMOCfg;    // message object configuration register
     uword  uwID;       // standard (11-bit)/extended (29-bit) identifier
     uword  uwMask;     // standard (11-bit)/extended (29-bit) mask
     ubyte  ubData[8];  // 8-bit data bytes
     ushort usCounter;  // frame counter
  }CAN_SWObj;

// USER CODE BEGIN (CAN_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (CAN_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (CAN_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void CAN_vInit(void);
void CAN_vGetMsgObj(ubyte ubObjNr, CAN_SWObj *pstObj);
ubyte CAN_ubRequestMsgObj(ubyte ubObjNr);
ubyte CAN_ubNewData(ubyte ubObjNr);
void CAN_vTransmit(ubyte ubObjNr);
void CAN_vConfigMsgObj(ubyte ubObjNr, CAN_SWObj *pstObj);
void CAN_vLoadData(ubyte ubObjNr, ubyte *pubData);
ubyte CAN_ubMsgLost(ubyte ubObjNr);
ubyte CAN_ubDelMsgObj(ubyte ubObjNr);
void CAN_vReleaseObj(ubyte ubObjNr);
void CAN_vSetMSGVAL(ubyte ubObjNr);
ubyte CAN_ubWriteFIFO(ubyte ubObjNr, CAN_SWObj *pstObj);
ubyte CAN_ubReadFIFO(ubyte ubObjNr, CAN_SWObj *pstObj);


// USER CODE BEGIN (CAN_Header,8)

// USER CODE END


//****************************************************************************
// @Macro         CAN_ubGetTxErrorCounter(NODE_NAME) 
//
//----------------------------------------------------------------------------
// @Description   This macro returns the current value of the transmit error 
//                counter of the selected node. 
//                
//                The following definitions for NODE_NAME are available:
//                CAN_NODE0        (node 0)
//                CAN_NODE1        (node 1)
//                CAN_NODE2        (node 2)
//                CAN_NODE3        (node 3)
//                
//
//----------------------------------------------------------------------------
// @Returnvalue   Value of the transmit error counter
//
//----------------------------------------------------------------------------
// @Parameters    NODE_NAME: 
//                Name of the node
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

#define CAN_ubGetTxErrorCounter(NODE_NAME) _GetTxErrorCounter##NODE_NAME()
#define _GetTxErrorCounterCAN_NODE0()   CAN_NECNT0.B.TEC
#define _GetTxErrorCounterCAN_NODE1()   CAN_NECNT1.B.TEC
#define _GetTxErrorCounterCAN_NODE2()   CAN_NECNT2.B.TEC
#define _GetTxErrorCounterCAN_NODE3()   CAN_NECNT3.B.TEC


//****************************************************************************
// @Macro         CAN_ubGetRxErrorCounter(NODE_NAME) 
//
//----------------------------------------------------------------------------
// @Description   This macro returns the current value of the receive error 
//                counter of the selected node. 
//                
//                The following definitions for NODE_NAME are available:
//                CAN_NODE0        (node 0)
//                CAN_NODE1        (node 1)
//                CAN_NODE2        (node 2)
//                CAN_NODE3        (node 3)
//                
//
//----------------------------------------------------------------------------
// @Returnvalue   Value of the receive error counter
//
//----------------------------------------------------------------------------
// @Parameters    NODE_NAME: 
//                Name of the node
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

#define CAN_ubGetRxErrorCounter(NODE_NAME) _GetRxErrorCounter##NODE_NAME()
#define _GetRxErrorCounterCAN_NODE0()  CAN_NECNT0.B.REC
#define _GetRxErrorCounterCAN_NODE1()  CAN_NECNT1.B.REC
#define _GetRxErrorCounterCAN_NODE2()  CAN_NECNT2.B.REC
#define _GetRxErrorCounterCAN_NODE3()  CAN_NECNT3.B.REC


//****************************************************************************
// @Macro         CAN_ubGetErrorTransferDirection(NODE_NAME) 
//
//----------------------------------------------------------------------------
// @Description   This macro returns the current value of the Last Error 
//                Transfer Direction flag. 0 indicates that the last error 
//                occurred while the selected CAN node was receiving a 
//                message. The receive error counter has been incremented. 1 
//                indicates that the last error occurred while the selected 
//                CAN node was transmitting a message. The transmit error 
//                counter has been incremented. 
//                
//                The following definitions for NODE_NAME are available:
//                CAN_NODE0        (node 0)
//                CAN_NODE1        (node 1)
//                CAN_NODE2        (node 2)
//                CAN_NODE3        (node 3)
//                
//
//----------------------------------------------------------------------------
// @Returnvalue   0 receive error, else transmit error
//
//----------------------------------------------------------------------------
// @Parameters    NODE_NAME: 
//                Name of the node
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

#define CAN_ubGetErrorTransferDirection(NODE_NAME) _GetErrorTransferDirection##NODE_NAME()
#define _GetErrorTransferDirectionCAN_NODE0()  CAN_NECNT0.B.LETD
#define _GetErrorTransferDirectionCAN_NODE1()  CAN_NECNT1.B.LETD
#define _GetErrorTransferDirectionCAN_NODE2()  CAN_NECNT2.B.LETD
#define _GetErrorTransferDirectionCAN_NODE3()  CAN_NECNT3.B.LETD


//****************************************************************************
// @Macro         CAN_ubGetErrorIncrement(NODE_NAME) 
//
//----------------------------------------------------------------------------
// @Description   This macro returns the current value of the Last Error 
//                Increment flag. If the Bit Stream Processor itself detects 
//                an error while a transmit operation is running, the 
//                Transmit Error Counter is incremented by 8. An increment of 
//                1 is used, when the error condition was reported by an 
//                external CAN node via an error frame generation. 
//                
//                The following definitions for NODE_NAME are available:
//                CAN_NODE0        (node 0)
//                CAN_NODE1        (node 1)
//                CAN_NODE2        (node 2)
//                CAN_NODE3        (node 3)
//                
//
//----------------------------------------------------------------------------
// @Returnvalue   0 counter is incrementd by 1, counter is incremented by 8
//
//----------------------------------------------------------------------------
// @Parameters    NODE_NAME: 
//                Name of the node
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

#define CAN_ubGetErrorIncrement(NODE_NAME) _GetErrorIncrement##NODE_NAME()
#define _GetErrorIncrementCAN_NODE0()  CAN_NECNT0.B.LEINC
#define _GetErrorIncrementCAN_NODE1()  CAN_NECNT1.B.LEINC
#define _GetErrorIncrementCAN_NODE2()  CAN_NECNT2.B.LEINC
#define _GetErrorIncrementCAN_NODE3()  CAN_NECNT3.B.LEINC


//****************************************************************************
// @Interrupt Vectors
//****************************************************************************

#define CAN_SRN0INT    0x03
#define CAN_SRN1INT    0x01
#define CAN_SRN2INT    0x04
#define CAN_SRN3INT    0x05
#define CAN_SRN4INT    0x06
#define CAN_SRN5INT    0x07
#define CAN_SRN6INT    0x08
#define CAN_SRN7INT    0x09
#define CAN_SRN8INT    0x0A
#define CAN_SRN9INT    0x0B
//'------------------------------------------------------------------------------------------------
//' Macros Defined for message Objects
//'------------------------------------------------------------------------------------------------

#define CAN_MOCTRm_CTR_RESRXPND_MASK    0x00000001
#define CAN_MOCTRm_CTR_RESTXPND_MASK    0x00000002
#define CAN_MOCTRm_CTR_RESRXUPD_MASK    0x00000004
#define CAN_MOCTRm_CTR_RESNEWDAT_MASK   0x00000008
#define CAN_MOCTRm_CTR_RESMSGLST_MASK   0x00000010
#define CAN_MOCTRm_CTR_RESMSGVAL_MASK   0x00000020
#define CAN_MOCTRm_CTR_RESRTSEL_MASK    0x00000040
#define CAN_MOCTRm_CTR_RESRXEN_MASK     0x00000080
#define CAN_MOCTRm_CTR_RESTXRQ_MASK     0x00000100
#define CAN_MOCTRm_CTR_RESTXEN0_MASK    0x00000200
#define CAN_MOCTRm_CTR_RESTXEN1_MASK    0x00000400
#define CAN_MOCTRm_CTR_RESDIR_MASK      0x00000800

// USER CODE BEGIN (CAN_Header,9)

// USER CODE END


#endif  // ifndef _CAN_H_
