//****************************************************************************
// @Module        MultiCAN Controller 
// @Filename      CAN.c
// @Project       DAVE_SG.dav
//----------------------------------------------------------------------------
// @Controller    Infineon TC1797
//
// @Compiler      Tasking 3.1
//
// @Codegenerator 1.0
//
// @Description   This file contains functions that use the CAN module.
//
//----------------------------------------------------------------------------
// @Date          2013-11-20 13:40:30
//
//****************************************************************************

// USER CODE BEGIN (CAN_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.h"

// USER CODE BEGIN (CAN_General,2)
#include <string.h>
#include <sfr/regtc1797.sfr>
#include "constants.h"
#include "configs.h"
#include "kernel.h"
#include "led.h"
#include <time.h>

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

#define SetListCommand(Value) CAN_PANCTR.U = Value; while (CAN_PANCTR.B.BUSY);

// USER CODE BEGIN (CAN_General,3)
#if 0
extern swc_t swc_1;
extern swc_t swc_2;
extern swc_t swc_3;
extern swc_t swc_4;
extern swc_t swc_5;
#endif

void callback(uint32_t swc_id, uint32_t flag);

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// Structure for a single MultiCAN object
// A total of 128 such object structures exists

struct stCanObj 
{
  uword  uwMOFCR;    // Function Control Register
  uword  uwMOFGPR;   // FIFO/Gateway Pointer Register
  uword  uwMOIPR;    // Interrupt Pointer Register
  uword  uwMOAMR;    // Acceptance Mask Register
  ubyte  ubData[8];  // Message Data 0..7
  uword  uwMOAR;     // Arbitration Register
  uword  uwMOCTR;    // Control Register
};

#define CAN_HWOBJ ((struct stCanObj volatile *) 0xF0005000)

// USER CODE BEGIN (CAN_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (CAN_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (CAN_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

static ubyte aubFIFOWritePtr[128];
static ubyte aubFIFOReadPtr[128];

// USER CODE BEGIN (CAN_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (CAN_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (CAN_General,9)

// USER CODE END


//****************************************************************************
// @Function      void CAN_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the CAN function 
//                library. It is assumed that the SFRs used by this library 
//                are in their reset state. 
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (Init,1)

// USER CODE END

void CAN_vInit(void)
{
ubyte i;

  // USER CODE BEGIN (Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of the Module Clock:
  ///  -----------------------------------------------------------------------

  ///  - the CAN module is stopped during sleep mode
  ///  - normal divider mode is selected
  ///  - required CAN module clock is 90.00 MHz
  ///  - real CAN module clock is 90.00 MHz

  MAIN_vResetENDINIT();
  CAN_CLC.U      = 0x00000000;   // load clock control register
  while ((CAN_CLC.U & 0x00000002)==2);  //wait until module is enabled
  CAN_FDR.U      = 0x000043FF;   // load fractional divider register
  MAIN_vSetENDINIT();

  //   - wait until Panel has finished the initialisation
  while (CAN_PANCTR.B.BUSY);

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 0:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 0:
  ///  - set INIT and CCE

  CAN_NCR0.U     = 0x00000041;   // load node 0 control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 1:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 1:
  ///  - set INIT and CCE

  CAN_NCR1.U     = 0x00000041;   // load node 1 control register
  CAN_NIPR1.U    = 0x00000000;   // load node 1 interrupt pointer register

  ///  Configuration of the Node 1 Error Counter:
  ///  - the error warning threshold value (warning level) is 96

  CAN_NECNT1.U   = 0x00600000;   // load node 1 error counter register


  CAN_NPCR1.U    = 0x00000000;   // load node 1 port control register

  ///  Configuration of the used CAN Port Pins:
  ///  - P6.10 is used as  CAN node 1 input signal 1 ( RXDCAN1)
  ///  - the pull-up device is assigned
  ///  - output driver characteristic: strong driver, sharp edge

  P6_IOCR8.U     = (P6_IOCR8.U & ~0x00F00000) | 0x00200000; // load control 
                                                            // register

  ///  - P6.11 is used as  CAN node 1 output signal 1 ( TXDCAN1)
  ///  - the push/pull function is activated
  ///  - output driver characteristic: strong driver, sharp edge

  P6_IOCR8.U     = (P6_IOCR8.U & ~0xF0000000) | 0x90000000; // load control 
                                                            // register

  ///  Configuration of the Node 1 Baud Rate:
  ///  - required baud rate = 1000000 baud
  ///  - real baud rate     = 1000000 baud
  ///  - sample point       = 80.00 %
  ///  - there are 11 time quanta before sample point
  ///  - there are 3 time quanta after sample point
  ///  - the (re)synchronization jump width is 1 time quanta

  CAN_NBTR1.U    = 0x00002A05;   // load  node 1 bit timing register

  ///  Configuration of the Frame Counter:
  ///  - Frame Counter Mode: the counter is incremented upon the reception 
  ///    and transmission of frames
  ///  - frame counter: 0x0000

  CAN_NFCR1.U    = 0x00000000;   // load  node 1 frame counter register

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 2:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 2:
  ///  - set INIT and CCE

  CAN_NCR2.U     = 0x00000041;   // load node 2 control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 3:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 3:
  ///  - set INIT and CCE

  CAN_NCR3.U     = 0x00000041;   // load node 3 control register

  ///  -----------------------------------------------------------------------
  ///  Configuration of the CAN Message Object List Structure:
  ///  -----------------------------------------------------------------------
  ///  Allocate MOs for list 2:
  SetListCommand(0x02000002);  // MO0 for list 2
  SetListCommand(0x02010002);  // MO1 for list 2
  SetListCommand(0x02020002);  // MO2 for list 2
  SetListCommand(0x02030002);  // MO3 for list 2
  SetListCommand(0x02040002);  // MO4 for list 2
  SetListCommand(0x02050002);  // MO5 for list 2
  SetListCommand(0x02060002);  // MO6 for list 2
  SetListCommand(0x02070002);  // MO7 for list 2
  SetListCommand(0x02080002);  // MO8 for list 2
  SetListCommand(0x02090002);  // MO9 for list 2
  SetListCommand(0x020A0002);  // MO10 for list 2
  SetListCommand(0x020B0002);  // MO11 for list 2
  SetListCommand(0x020C0002);  // MO12 for list 2
  SetListCommand(0x020D0002);  // MO13 for list 2
  SetListCommand(0x020E0002);  // MO14 for list 2
  SetListCommand(0x020F0002);  // MO15 for list 2
  SetListCommand(0x02100002);  // MO16 for list 2
  SetListCommand(0x02110002);  // MO17 for list 2
  SetListCommand(0x02120002);  // MO18 for list 2
  SetListCommand(0x02130002);  // MO19 for list 2
  SetListCommand(0x02140002);  // MO20 for list 2
  SetListCommand(0x02150002);  // MO21 for list 2
  SetListCommand(0x02160002);  // MO22 for list 2
  SetListCommand(0x02170002);  // MO23 for list 2
  SetListCommand(0x02180002);  // MO24 for list 2
  SetListCommand(0x02190002);  // MO25 for list 2
  SetListCommand(0x021A0002);  // MO26 for list 2
  SetListCommand(0x021B0002);  // MO27 for list 2
  SetListCommand(0x021C0002);  // MO28 for list 2
  SetListCommand(0x021D0002);  // MO29 for list 2

  ///  -----------------------------------------------------------------------
  ///  Configuration of the CAN Message Objects 0 - 127:
  ///  -----------------------------------------------------------------------
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 0:
  ///  -----------------------------------------------------------------------
  ///  - message object 0 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR0.U   = 0x0EA80000;   // load MO0 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR0.U   = 0x08000000;   // load MO0 function control register


  CAN_MOFGPR0.U  = 0x00000000;   // load MO0 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR0.U   = 0x3FFFFFFF;   // load MO0 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7FF

  CAN_MOAR0.U    = 0xDFFC0000;   // load MO0 arbitration register

  CAN_MODATAL0.U  = 0x00000000;  // load MO0 data register low
  CAN_MODATAH0.U  = 0x00000000;  // load MO0 data register high

  ///  - use message pending register 0 bit position 0

  CAN_MOIPR0.U   = 0x00000000;   // load MO0 interrupt pointer register
  CAN_MOCTR0.U   = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 1:
  ///  -----------------------------------------------------------------------
  ///  - message object 1 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR1.U   = 0x0EA80000;   // load MO1 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR1.U   = 0x08000000;   // load MO1 function control register


  CAN_MOFGPR1.U  = 0x00000000;   // load MO1 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR1.U   = 0x3FFFFFFF;   // load MO1 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7FE

  CAN_MOAR1.U    = 0xDFF80000;   // load MO1 arbitration register

  CAN_MODATAL1.U  = 0x00000000;  // load MO1 data register low
  CAN_MODATAH1.U  = 0x00000000;  // load MO1 data register high

  ///  - use message pending register 0 bit position 1

  CAN_MOIPR1.U   = 0x00000101;   // load MO1 interrupt pointer register
  CAN_MOCTR1.U   = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 2:
  ///  -----------------------------------------------------------------------
  ///  - message object 2 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR2.U   = 0x00A00000;   // load MO2 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

  CAN_MOFCR2.U   = 0x08010000;   // load MO2 function control register


  CAN_MOFGPR2.U  = 0x00000000;   // load MO2 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR2.U   = 0x3FFFFFFF;   // load MO2 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7FD

  CAN_MOAR2.U    = 0xDFF40000;   // load MO2 arbitration register

  ///  - use message pending register 0 bit position 2
  ///  - receive interrupt node pointer: MultiCAN SRN 2

  CAN_MOIPR2.U   = 0x00000202;   // load MO2 interrupt pointer register
  CAN_MOCTR2.U   = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 3:
  ///  -----------------------------------------------------------------------
  ///  - message object 3 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR3.U   = 0x00A00000;   // load MO3 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

  CAN_MOFCR3.U   = 0x08010000;   // load MO3 function control register


  CAN_MOFGPR3.U  = 0x00000000;   // load MO3 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR3.U   = 0x3FFFFFFF;   // load MO3 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7FC

  CAN_MOAR3.U    = 0xDFF00000;   // load MO3 arbitration register

  ///  - use message pending register 0 bit position 3
  ///  - receive interrupt node pointer: MultiCAN SRN 3

  CAN_MOIPR3.U   = 0x00000303;   // load MO3 interrupt pointer register
  CAN_MOCTR3.U   = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 4:
  ///  -----------------------------------------------------------------------
  ///  - message object 4 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR4.U   = 0x00A00000;   // load MO4 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

  CAN_MOFCR4.U   = 0x08010000;   // load MO4 function control register


  CAN_MOFGPR4.U  = 0x00000000;   // load MO4 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR4.U   = 0x3FFFFFFF;   // load MO4 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7FB

  CAN_MOAR4.U    = 0xDFEC0000;   // load MO4 arbitration register

  ///  - use message pending register 0 bit position 4
  ///  - receive interrupt node pointer: MultiCAN SRN 4

  CAN_MOIPR4.U   = 0x00000404;   // load MO4 interrupt pointer register
  CAN_MOCTR4.U   = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 5:
  ///  -----------------------------------------------------------------------
  ///  - message object 5 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR5.U   = 0x00A00000;   // load MO5 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

  CAN_MOFCR5.U   = 0x08010000;   // load MO5 function control register


  CAN_MOFGPR5.U  = 0x00000000;   // load MO5 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR5.U   = 0x3FFFFFFF;   // load MO5 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7FA

  CAN_MOAR5.U    = 0xDFE80000;   // load MO5 arbitration register

  ///  - use message pending register 0 bit position 5
  ///  - receive interrupt node pointer: MultiCAN SRN 5

  CAN_MOIPR5.U   = 0x00000505;   // load MO5 interrupt pointer register
  CAN_MOCTR5.U   = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 6:
  ///  -----------------------------------------------------------------------
  ///  - message object 6 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR6.U   = 0x00A00000;   // load MO6 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

  CAN_MOFCR6.U   = 0x08010000;   // load MO6 function control register


  CAN_MOFGPR6.U  = 0x00000000;   // load MO6 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR6.U   = 0x3FFFFFFF;   // load MO6 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7F9

  CAN_MOAR6.U    = 0xDFE40000;   // load MO6 arbitration register

  ///  - use message pending register 0 bit position 6
  ///  - receive interrupt node pointer: MultiCAN SRN 6

  CAN_MOIPR6.U   = 0x00000606;   // load MO6 interrupt pointer register
  CAN_MOCTR6.U   = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 7:
  ///  -----------------------------------------------------------------------
  ///  - message object 7 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR7.U   = 0x00A00000;   // load MO7 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

  CAN_MOFCR7.U   = 0x08010000;   // load MO7 function control register


  CAN_MOFGPR7.U  = 0x00000000;   // load MO7 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR7.U   = 0x3FFFFFFF;   // load MO7 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7F8

  CAN_MOAR7.U    = 0xDFE00000;   // load MO7 arbitration register

  ///  - use message pending register 0 bit position 7
  ///  - receive interrupt node pointer: MultiCAN SRN 7

  CAN_MOIPR7.U   = 0x00000707;   // load MO7 interrupt pointer register
  CAN_MOCTR7.U   = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 8:
  ///  -----------------------------------------------------------------------
  ///  - message object 8 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR8.U   = 0x00A00000;   // load MO8 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

  CAN_MOFCR8.U   = 0x08010000;   // load MO8 function control register


  CAN_MOFGPR8.U  = 0x00000000;   // load MO8 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR8.U   = 0x3FFFFFFF;   // load MO8 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7F7

  CAN_MOAR8.U    = 0xDFDC0000;   // load MO8 arbitration register

  ///  - use message pending register 0 bit position 8
  ///  - receive interrupt node pointer: MultiCAN SRN 8

  CAN_MOIPR8.U   = 0x00000808;   // load MO8 interrupt pointer register
  CAN_MOCTR8.U   = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 9:
  ///  -----------------------------------------------------------------------
  ///  - message object 9 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR9.U   = 0x00A00000;   // load MO9 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

  CAN_MOFCR9.U   = 0x08010000;   // load MO9 function control register


  CAN_MOFGPR9.U  = 0x00000000;   // load MO9 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR9.U   = 0x3FFFFFFF;   // load MO9 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7F6

  CAN_MOAR9.U    = 0xDFD80000;   // load MO9 arbitration register

  ///  - use message pending register 0 bit position 9
  ///  - receive interrupt node pointer: MultiCAN SRN 9

  CAN_MOIPR9.U   = 0x00000909;   // load MO9 interrupt pointer register
  CAN_MOCTR9.U   = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 10:
  ///  -----------------------------------------------------------------------
  ///  - message object 10 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR10.U  = 0x00A00000;   // load MO10 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR10.U  = 0x08000000;   // load MO10 function control register


  CAN_MOFGPR10.U  = 0x00000000;  // load MO10 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR10.U  = 0x3FFFFFFF;   // load MO10 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7F5

  CAN_MOAR10.U   = 0xDFD40000;   // load MO10 arbitration register

  ///  - use message pending register 0 bit position 10

  CAN_MOIPR10.U  = 0x00000A00;   // load MO10 interrupt pointer register
  CAN_MOCTR10.U  = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 11:
  ///  -----------------------------------------------------------------------
  ///  - message object 11 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR11.U  = 0x0EA80000;   // load MO11 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR11.U  = 0x08000000;   // load MO11 function control register


  CAN_MOFGPR11.U  = 0x00000000;  // load MO11 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR11.U  = 0x3FFFFFFF;   // load MO11 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7F4

  CAN_MOAR11.U   = 0xDFD00000;   // load MO11 arbitration register

  CAN_MODATAL11.U  = 0x00000000; // load MO11 data register low
  CAN_MODATAH11.U  = 0x00000000; // load MO11 data register high

  ///  - use message pending register 0 bit position 11

  CAN_MOIPR11.U  = 0x00000B00;   // load MO11 interrupt pointer register
  CAN_MOCTR11.U  = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 12:
  ///  -----------------------------------------------------------------------
  ///  - message object 12 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR12.U  = 0x0EA80000;   // load MO12 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR12.U  = 0x08000000;   // load MO12 function control register


  CAN_MOFGPR12.U  = 0x00000000;  // load MO12 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR12.U  = 0x3FFFFFFF;   // load MO12 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7F3

  CAN_MOAR12.U   = 0xDFCC0000;   // load MO12 arbitration register

  CAN_MODATAL12.U  = 0x00000000; // load MO12 data register low
  CAN_MODATAH12.U  = 0x00000000; // load MO12 data register high

  ///  - use message pending register 0 bit position 12

  CAN_MOIPR12.U  = 0x00000C00;   // load MO12 interrupt pointer register
  CAN_MOCTR12.U  = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 13:
  ///  -----------------------------------------------------------------------
  ///  - message object 13 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR13.U  = 0x0EA80000;   // load MO13 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR13.U  = 0x08000000;   // load MO13 function control register


  CAN_MOFGPR13.U  = 0x00000000;  // load MO13 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR13.U  = 0x3FFFFFFF;   // load MO13 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7F2

  CAN_MOAR13.U   = 0xDFC80000;   // load MO13 arbitration register

  CAN_MODATAL13.U  = 0x00000000; // load MO13 data register low
  CAN_MODATAH13.U  = 0x00000000; // load MO13 data register high

  ///  - use message pending register 0 bit position 13

  CAN_MOIPR13.U  = 0x00000D00;   // load MO13 interrupt pointer register
  CAN_MOCTR13.U  = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 14:
  ///  -----------------------------------------------------------------------
  ///  - message object 14 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR14.U  = 0x0EA80000;   // load MO14 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR14.U  = 0x08000000;   // load MO14 function control register


  CAN_MOFGPR14.U  = 0x00000000;  // load MO14 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR14.U  = 0x3FFFFFFF;   // load MO14 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7F1

  CAN_MOAR14.U   = 0xDFC40000;   // load MO14 arbitration register

  CAN_MODATAL14.U  = 0x00000000; // load MO14 data register low
  CAN_MODATAH14.U  = 0x00000000; // load MO14 data register high

  ///  - use message pending register 0 bit position 14

  CAN_MOIPR14.U  = 0x00000E00;   // load MO14 interrupt pointer register
  CAN_MOCTR14.U  = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 15:
  ///  -----------------------------------------------------------------------
  ///  - message object 15 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR15.U  = 0x0EA80000;   // load MO15 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR15.U  = 0x08000000;   // load MO15 function control register


  CAN_MOFGPR15.U  = 0x00000000;  // load MO15 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR15.U  = 0x3FFFFFFF;   // load MO15 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7F0

  CAN_MOAR15.U   = 0xDFC00000;   // load MO15 arbitration register

  CAN_MODATAL15.U  = 0x00000000; // load MO15 data register low
  CAN_MODATAH15.U  = 0x00000000; // load MO15 data register high

  ///  - use message pending register 0 bit position 15

  CAN_MOIPR15.U  = 0x00000F00;   // load MO15 interrupt pointer register
  CAN_MOCTR15.U  = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 16:
  ///  -----------------------------------------------------------------------
  ///  - message object 16 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR16.U  = 0x0EA80000;   // load MO16 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR16.U  = 0x08000000;   // load MO16 function control register


  CAN_MOFGPR16.U  = 0x00000000;  // load MO16 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR16.U  = 0x3FFFFFFF;   // load MO16 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7EF

  CAN_MOAR16.U   = 0xDFBC0000;   // load MO16 arbitration register

  CAN_MODATAL16.U  = 0x00000000; // load MO16 data register low
  CAN_MODATAH16.U  = 0x00000000; // load MO16 data register high

  ///  - use message pending register 0 bit position 16

  CAN_MOIPR16.U  = 0x00001000;   // load MO16 interrupt pointer register
  CAN_MOCTR16.U  = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 17:
  ///  -----------------------------------------------------------------------
  ///  - message object 17 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR17.U  = 0x0EA80000;   // load MO17 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR17.U  = 0x08000000;   // load MO17 function control register


  CAN_MOFGPR17.U  = 0x00000000;  // load MO17 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR17.U  = 0x3FFFFFFF;   // load MO17 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7EE

  CAN_MOAR17.U   = 0xDFB80000;   // load MO17 arbitration register

  CAN_MODATAL17.U  = 0x00000000; // load MO17 data register low
  CAN_MODATAH17.U  = 0x00000000; // load MO17 data register high

  ///  - use message pending register 0 bit position 17

  CAN_MOIPR17.U  = 0x00001100;   // load MO17 interrupt pointer register
  CAN_MOCTR17.U  = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 18:
  ///  -----------------------------------------------------------------------
  ///  - message object 18 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR18.U  = 0x0EA80000;   // load MO18 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR18.U  = 0x08000000;   // load MO18 function control register


  CAN_MOFGPR18.U  = 0x00000000;  // load MO18 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR18.U  = 0x3FFFFFFF;   // load MO18 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7ED

  CAN_MOAR18.U   = 0xDFB40000;   // load MO18 arbitration register

  CAN_MODATAL18.U  = 0x00000000; // load MO18 data register low
  CAN_MODATAH18.U  = 0x00000000; // load MO18 data register high

  ///  - use message pending register 0 bit position 18

  CAN_MOIPR18.U  = 0x00001200;   // load MO18 interrupt pointer register
  CAN_MOCTR18.U  = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 19:
  ///  -----------------------------------------------------------------------
  ///  - message object 19 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR19.U  = 0x0EA80000;   // load MO19 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR19.U  = 0x08000000;   // load MO19 function control register


  CAN_MOFGPR19.U  = 0x00000000;  // load MO19 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR19.U  = 0x3FFFFFFF;   // load MO19 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7EC

  CAN_MOAR19.U   = 0xDFB00000;   // load MO19 arbitration register

  CAN_MODATAL19.U  = 0x00000000; // load MO19 data register low
  CAN_MODATAH19.U  = 0x00000000; // load MO19 data register high

  ///  - use message pending register 0 bit position 19

  CAN_MOIPR19.U  = 0x00001300;   // load MO19 interrupt pointer register
  CAN_MOCTR19.U  = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 20:
  ///  -----------------------------------------------------------------------
  ///  - message object 20 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR20.U  = 0x0EA80000;   // load MO20 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR20.U  = 0x08000000;   // load MO20 function control register


  CAN_MOFGPR20.U  = 0x00000000;  // load MO20 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR20.U  = 0x3FFFFFFF;   // load MO20 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7EB

  CAN_MOAR20.U   = 0xDFAC0000;   // load MO20 arbitration register

  CAN_MODATAL20.U  = 0x00000000; // load MO20 data register low
  CAN_MODATAH20.U  = 0x00000000; // load MO20 data register high

  ///  - use message pending register 0 bit position 20

  CAN_MOIPR20.U  = 0x00001400;   // load MO20 interrupt pointer register
  CAN_MOCTR20.U  = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 21:
  ///  -----------------------------------------------------------------------
  ///  - message object 21 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR21.U  = 0x0EA80000;   // load MO21 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR21.U  = 0x08000000;   // load MO21 function control register


  CAN_MOFGPR21.U  = 0x00000000;  // load MO21 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR21.U  = 0x3FFFFFFF;   // load MO21 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7EA

  CAN_MOAR21.U   = 0xDFA80000;   // load MO21 arbitration register

  CAN_MODATAL21.U  = 0x00000000; // load MO21 data register low
  CAN_MODATAH21.U  = 0x00000000; // load MO21 data register high

  ///  - use message pending register 0 bit position 21

  CAN_MOIPR21.U  = 0x00001500;   // load MO21 interrupt pointer register
  CAN_MOCTR21.U  = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 22:
  ///  -----------------------------------------------------------------------
  ///  - message object 22 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR22.U  = 0x0EA80000;   // load MO22 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR22.U  = 0x08000000;   // load MO22 function control register


  CAN_MOFGPR22.U  = 0x00000000;  // load MO22 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR22.U  = 0x3FFFFFFF;   // load MO22 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7E9

  CAN_MOAR22.U   = 0xDFA40000;   // load MO22 arbitration register

  CAN_MODATAL22.U  = 0x00000000; // load MO22 data register low
  CAN_MODATAH22.U  = 0x00000000; // load MO22 data register high

  ///  - use message pending register 0 bit position 22

  CAN_MOIPR22.U  = 0x00001600;   // load MO22 interrupt pointer register
  CAN_MOCTR22.U  = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 23:
  ///  -----------------------------------------------------------------------
  ///  - message object 23 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR23.U  = 0x0EA80000;   // load MO23 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR23.U  = 0x08000000;   // load MO23 function control register


  CAN_MOFGPR23.U  = 0x00000000;  // load MO23 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR23.U  = 0x3FFFFFFF;   // load MO23 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7E8

  CAN_MOAR23.U   = 0xDFA00000;   // load MO23 arbitration register

  CAN_MODATAL23.U  = 0x00000000; // load MO23 data register low
  CAN_MODATAH23.U  = 0x00000000; // load MO23 data register high

  ///  - use message pending register 0 bit position 23

  CAN_MOIPR23.U  = 0x00001700;   // load MO23 interrupt pointer register
  CAN_MOCTR23.U  = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 24:
  ///  -----------------------------------------------------------------------
  ///  - message object 24 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR24.U  = 0x0EA80000;   // load MO24 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR24.U  = 0x08000000;   // load MO24 function control register


  CAN_MOFGPR24.U  = 0x00000000;  // load MO24 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR24.U  = 0x3FFFFFFF;   // load MO24 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7E7

  CAN_MOAR24.U   = 0xDF9C0000;   // load MO24 arbitration register

  CAN_MODATAL24.U  = 0x00000000; // load MO24 data register low
  CAN_MODATAH24.U  = 0x00000000; // load MO24 data register high

  ///  - use message pending register 0 bit position 24

  CAN_MOIPR24.U  = 0x00001800;   // load MO24 interrupt pointer register
  CAN_MOCTR24.U  = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 25:
  ///  -----------------------------------------------------------------------
  ///  - message object 25 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR25.U  = 0x0EA80000;   // load MO25 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR25.U  = 0x08000000;   // load MO25 function control register


  CAN_MOFGPR25.U  = 0x00000000;  // load MO25 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR25.U  = 0x3FFFFFFF;   // load MO25 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7E6

  CAN_MOAR25.U   = 0xDF980000;   // load MO25 arbitration register

  CAN_MODATAL25.U  = 0x00000000; // load MO25 data register low
  CAN_MODATAH25.U  = 0x00000000; // load MO25 data register high

  ///  - use message pending register 0 bit position 25

  CAN_MOIPR25.U  = 0x00001900;   // load MO25 interrupt pointer register
  CAN_MOCTR25.U  = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 26:
  ///  -----------------------------------------------------------------------
  ///  - message object 26 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR26.U  = 0x0EA80000;   // load MO26 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR26.U  = 0x08000000;   // load MO26 function control register


  CAN_MOFGPR26.U  = 0x00000000;  // load MO26 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR26.U  = 0x3FFFFFFF;   // load MO26 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7E5

  CAN_MOAR26.U   = 0xDF940000;   // load MO26 arbitration register

  CAN_MODATAL26.U  = 0x00000000; // load MO26 data register low
  CAN_MODATAH26.U  = 0x00000000; // load MO26 data register high

  ///  - use message pending register 0 bit position 26

  CAN_MOIPR26.U  = 0x00001A00;   // load MO26 interrupt pointer register
  CAN_MOCTR26.U  = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 27:
  ///  -----------------------------------------------------------------------
  ///  - message object 27 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR27.U  = 0x0EA80000;   // load MO27 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR27.U  = 0x08000000;   // load MO27 function control register


  CAN_MOFGPR27.U  = 0x00000000;  // load MO27 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR27.U  = 0x3FFFFFFF;   // load MO27 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7E4

  CAN_MOAR27.U   = 0xDF900000;   // load MO27 arbitration register

  CAN_MODATAL27.U  = 0x00000000; // load MO27 data register low
  CAN_MODATAH27.U  = 0x00000000; // load MO27 data register high

  ///  - use message pending register 0 bit position 27

  CAN_MOIPR27.U  = 0x00001B00;   // load MO27 interrupt pointer register
  CAN_MOCTR27.U  = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 28:
  ///  -----------------------------------------------------------------------
  ///  - message object 28 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR28.U  = 0x0EA80000;   // load MO28 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes

  CAN_MOFCR28.U  = 0x08000000;   // load MO28 function control register


  CAN_MOFGPR28.U  = 0x00000000;  // load MO28 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR28.U  = 0x3FFFFFFF;   // load MO28 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7E3

  CAN_MOAR28.U   = 0xDF8C0000;   // load MO28 arbitration register

  CAN_MODATAL28.U  = 0x00000000; // load MO28 data register low
  CAN_MODATAH28.U  = 0x00000000; // load MO28 data register high

  ///  - use message pending register 0 bit position 28

  CAN_MOIPR28.U  = 0x00001C00;   // load MO28 interrupt pointer register
  CAN_MOCTR28.U  = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 29:
  ///  -----------------------------------------------------------------------
  ///  - message object 29 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

  CAN_MOCTR29.U  = 0x00A00000;   // load MO29 control register

  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

  CAN_MOFCR29.U  = 0x08010000;   // load MO29 function control register


  CAN_MOFGPR29.U  = 0x00000000;  // load MO29 FIFO/gateway pointer register

  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 11-bit: 0x7FF

  CAN_MOAMR29.U  = 0x3FFFFFFF;   // load MO29 acceptance mask register

  ///  - priority class 3; transmit acceptance filtering is based on the list 
  ///    order (like class 1)
  ///  - standard 11-bit identifier
  ///  - identifier 11-bit:      0x7E2

  CAN_MOAR29.U   = 0xDF880000;   // load MO29 arbitration register

  ///  - use message pending register 0 bit position 29
  ///  - receive interrupt node pointer: MultiCAN SRN 3

  CAN_MOIPR29.U  = 0x00001D03;   // load MO29 interrupt pointer register
  CAN_MOCTR29.U  = 0x00200000;   // set MSGVAL

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 30:
  ///  -----------------------------------------------------------------------
  ///  - message object 30 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 31:
  ///  -----------------------------------------------------------------------
  ///  - message object 31 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 32:
  ///  -----------------------------------------------------------------------
  ///  - message object 32 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 33:
  ///  -----------------------------------------------------------------------
  ///  - message object 33 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 34:
  ///  -----------------------------------------------------------------------
  ///  - message object 34 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 35:
  ///  -----------------------------------------------------------------------
  ///  - message object 35 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 36:
  ///  -----------------------------------------------------------------------
  ///  - message object 36 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 37:
  ///  -----------------------------------------------------------------------
  ///  - message object 37 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 38:
  ///  -----------------------------------------------------------------------
  ///  - message object 38 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 39:
  ///  -----------------------------------------------------------------------
  ///  - message object 39 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 40:
  ///  -----------------------------------------------------------------------
  ///  - message object 40 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 41:
  ///  -----------------------------------------------------------------------
  ///  - message object 41 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 42:
  ///  -----------------------------------------------------------------------
  ///  - message object 42 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 43:
  ///  -----------------------------------------------------------------------
  ///  - message object 43 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 44:
  ///  -----------------------------------------------------------------------
  ///  - message object 44 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 45:
  ///  -----------------------------------------------------------------------
  ///  - message object 45 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 46:
  ///  -----------------------------------------------------------------------
  ///  - message object 46 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 47:
  ///  -----------------------------------------------------------------------
  ///  - message object 47 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 48:
  ///  -----------------------------------------------------------------------
  ///  - message object 48 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 49:
  ///  -----------------------------------------------------------------------
  ///  - message object 49 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 50:
  ///  -----------------------------------------------------------------------
  ///  - message object 50 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 51:
  ///  -----------------------------------------------------------------------
  ///  - message object 51 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 52:
  ///  -----------------------------------------------------------------------
  ///  - message object 52 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 53:
  ///  -----------------------------------------------------------------------
  ///  - message object 53 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 54:
  ///  -----------------------------------------------------------------------
  ///  - message object 54 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 55:
  ///  -----------------------------------------------------------------------
  ///  - message object 55 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 56:
  ///  -----------------------------------------------------------------------
  ///  - message object 56 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 57:
  ///  -----------------------------------------------------------------------
  ///  - message object 57 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 58:
  ///  -----------------------------------------------------------------------
  ///  - message object 58 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 59:
  ///  -----------------------------------------------------------------------
  ///  - message object 59 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 60:
  ///  -----------------------------------------------------------------------
  ///  - message object 60 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 61:
  ///  -----------------------------------------------------------------------
  ///  - message object 61 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 62:
  ///  -----------------------------------------------------------------------
  ///  - message object 62 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 63:
  ///  -----------------------------------------------------------------------
  ///  - message object 63 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 64:
  ///  -----------------------------------------------------------------------
  ///  - message object 64 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 65:
  ///  -----------------------------------------------------------------------
  ///  - message object 65 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 66:
  ///  -----------------------------------------------------------------------
  ///  - message object 66 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 67:
  ///  -----------------------------------------------------------------------
  ///  - message object 67 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 68:
  ///  -----------------------------------------------------------------------
  ///  - message object 68 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 69:
  ///  -----------------------------------------------------------------------
  ///  - message object 69 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 70:
  ///  -----------------------------------------------------------------------
  ///  - message object 70 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 71:
  ///  -----------------------------------------------------------------------
  ///  - message object 71 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 72:
  ///  -----------------------------------------------------------------------
  ///  - message object 72 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 73:
  ///  -----------------------------------------------------------------------
  ///  - message object 73 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 74:
  ///  -----------------------------------------------------------------------
  ///  - message object 74 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 75:
  ///  -----------------------------------------------------------------------
  ///  - message object 75 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 76:
  ///  -----------------------------------------------------------------------
  ///  - message object 76 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 77:
  ///  -----------------------------------------------------------------------
  ///  - message object 77 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 78:
  ///  -----------------------------------------------------------------------
  ///  - message object 78 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 79:
  ///  -----------------------------------------------------------------------
  ///  - message object 79 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 80:
  ///  -----------------------------------------------------------------------
  ///  - message object 80 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 81:
  ///  -----------------------------------------------------------------------
  ///  - message object 81 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 82:
  ///  -----------------------------------------------------------------------
  ///  - message object 82 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 83:
  ///  -----------------------------------------------------------------------
  ///  - message object 83 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 84:
  ///  -----------------------------------------------------------------------
  ///  - message object 84 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 85:
  ///  -----------------------------------------------------------------------
  ///  - message object 85 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 86:
  ///  -----------------------------------------------------------------------
  ///  - message object 86 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 87:
  ///  -----------------------------------------------------------------------
  ///  - message object 87 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 88:
  ///  -----------------------------------------------------------------------
  ///  - message object 88 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 89:
  ///  -----------------------------------------------------------------------
  ///  - message object 89 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 90:
  ///  -----------------------------------------------------------------------
  ///  - message object 90 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 91:
  ///  -----------------------------------------------------------------------
  ///  - message object 91 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 92:
  ///  -----------------------------------------------------------------------
  ///  - message object 92 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 93:
  ///  -----------------------------------------------------------------------
  ///  - message object 93 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 94:
  ///  -----------------------------------------------------------------------
  ///  - message object 94 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 95:
  ///  -----------------------------------------------------------------------
  ///  - message object 95 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 96:
  ///  -----------------------------------------------------------------------
  ///  - message object 96 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 97:
  ///  -----------------------------------------------------------------------
  ///  - message object 97 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 98:
  ///  -----------------------------------------------------------------------
  ///  - message object 98 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 99:
  ///  -----------------------------------------------------------------------
  ///  - message object 99 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 100:
  ///  -----------------------------------------------------------------------
  ///  - message object 100 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 101:
  ///  -----------------------------------------------------------------------
  ///  - message object 101 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 102:
  ///  -----------------------------------------------------------------------
  ///  - message object 102 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 103:
  ///  -----------------------------------------------------------------------
  ///  - message object 103 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 104:
  ///  -----------------------------------------------------------------------
  ///  - message object 104 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 105:
  ///  -----------------------------------------------------------------------
  ///  - message object 105 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 106:
  ///  -----------------------------------------------------------------------
  ///  - message object 106 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 107:
  ///  -----------------------------------------------------------------------
  ///  - message object 107 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 108:
  ///  -----------------------------------------------------------------------
  ///  - message object 108 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 109:
  ///  -----------------------------------------------------------------------
  ///  - message object 109 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 110:
  ///  -----------------------------------------------------------------------
  ///  - message object 110 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 111:
  ///  -----------------------------------------------------------------------
  ///  - message object 111 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 112:
  ///  -----------------------------------------------------------------------
  ///  - message object 112 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 113:
  ///  -----------------------------------------------------------------------
  ///  - message object 113 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 114:
  ///  -----------------------------------------------------------------------
  ///  - message object 114 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 115:
  ///  -----------------------------------------------------------------------
  ///  - message object 115 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 116:
  ///  -----------------------------------------------------------------------
  ///  - message object 116 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 117:
  ///  -----------------------------------------------------------------------
  ///  - message object 117 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 118:
  ///  -----------------------------------------------------------------------
  ///  - message object 118 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 119:
  ///  -----------------------------------------------------------------------
  ///  - message object 119 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 120:
  ///  -----------------------------------------------------------------------
  ///  - message object 120 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 121:
  ///  -----------------------------------------------------------------------
  ///  - message object 121 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 122:
  ///  -----------------------------------------------------------------------
  ///  - message object 122 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 123:
  ///  -----------------------------------------------------------------------
  ///  - message object 123 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 124:
  ///  -----------------------------------------------------------------------
  ///  - message object 124 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 125:
  ///  -----------------------------------------------------------------------
  ///  - message object 125 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 126:
  ///  -----------------------------------------------------------------------
  ///  - message object 126 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 127:
  ///  -----------------------------------------------------------------------
  ///  - message object 127 is not valid

  ///  -----------------------------------------------------------------------
  ///  Configuration of Service Request Nodes 0 - 15:
  ///  -----------------------------------------------------------------------
  ///  - SRN0 service request node configuration:
  ///  - SRN0 interrupt priority level (SRPN) = 3
  ///  - SRN0 CPU interrupt is selected

  CAN_SRC0.U     = 0x00001003;   // set service request control register

  ///  - SRN1 service request node configuration:
  ///  - SRN1 interrupt priority level (SRPN) = 1
  ///  - SRN1 CPU interrupt is selected

  CAN_SRC1.U     = 0x00001001;   // set service request control register

  ///  - SRN2 service request node configuration:
  ///  - SRN2 interrupt priority level (SRPN) = 4
  ///  - SRN2 CPU interrupt is selected

  CAN_SRC2.U     = 0x00001004;   // set service request control register

  ///  - SRN3 service request node configuration:
  ///  - SRN3 interrupt priority level (SRPN) = 5
  ///  - SRN3 CPU interrupt is selected

  CAN_SRC3.U     = 0x00001005;   // set service request control register

  ///  - SRN4 service request node configuration:
  ///  - SRN4 interrupt priority level (SRPN) = 6
  ///  - SRN4 CPU interrupt is selected

  CAN_SRC4.U     = 0x00001006;   // set service request control register

  ///  - SRN5 service request node configuration:
  ///  - SRN5 interrupt priority level (SRPN) = 7
  ///  - SRN5 CPU interrupt is selected

  CAN_SRC5.U     = 0x00001007;   // set service request control register

  ///  - SRN6 service request node configuration:
  ///  - SRN6 interrupt priority level (SRPN) = 8
  ///  - SRN6 CPU interrupt is selected

  CAN_SRC6.U     = 0x00001008;   // set service request control register

  ///  - SRN7 service request node configuration:
  ///  - SRN7 interrupt priority level (SRPN) = 9
  ///  - SRN7 CPU interrupt is selected

  CAN_SRC7.U     = 0x00001009;   // set service request control register

  ///  - SRN8 service request node configuration:
  ///  - SRN8 interrupt priority level (SRPN) = 10
  ///  - SRN8 CPU interrupt is selected

  CAN_SRC8.U     = 0x0000100A;   // set service request control register

  ///  - SRN9 service request node configuration:
  ///  - SRN9 interrupt priority level (SRPN) = 11
  ///  - SRN9 CPU interrupt is selected

  CAN_SRC9.U     = 0x0000100B;   // set service request control register

  ///  -----------------------------------------------------------------------
  ///  Initialization of the FIFO Pointer:
  ///  -----------------------------------------------------------------------

  for (i = 0; i < 127; i++)
  {
    aubFIFOWritePtr[i] = (CAN_HWOBJ[i].uwMOFGPR & 0x000000ff);
    aubFIFOReadPtr[i]  = (CAN_HWOBJ[i].uwMOFGPR & 0x000000ff);
  }

  //   -----------------------------------------------------------------------
  //   Start the CAN Nodes:
  //   -----------------------------------------------------------------------
  CAN_NCR1.U    &= ~0x00000041;  // reset INIT and CCE


  // USER CODE BEGIN (Init,3)

  // USER CODE END

} //  End of function CAN_vInit


//****************************************************************************
// @Function      void CAN_vGetMsgObj(ubyte ubObjNr, CAN_SWObj *pstObj) 
//
//----------------------------------------------------------------------------
// @Description   This function fills the forwarded SW message object with 
//                the content of the chosen HW message object.
//                
//                The structure of the SW message object is defined in the 
//                header file CAN.h (see CAN_SWObj).
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object to be read (0-127)
// @Parameters    *pstObj: 
//                Pointer on a message object to be filled by this function
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (GetMsgObj,1)

// USER CODE END

void CAN_vGetMsgObj(ubyte ubObjNr, CAN_SWObj *pstObj)
{
  ubyte i;

  // get DLC
  pstObj->usMOCfg  = (CAN_HWOBJ[ubObjNr].uwMOFCR & 0x0f000000) >> 24;
  for(i = 0; i < pstObj->usMOCfg; i++)
  {
    pstObj->ubData[i] = CAN_HWOBJ[ubObjNr].ubData[i];
  }

  pstObj->usMOCfg  = (pstObj->usMOCfg << 4);    // shift DLC
  if(CAN_HWOBJ[ubObjNr].uwMOCTR & 0x00000800)   // if transmit object
  {
    pstObj->usMOCfg  = pstObj->usMOCfg | 0x08;  // set DIR
  }

  if(CAN_HWOBJ[ubObjNr].uwMOAR & 0x20000000)    // extended identifier
  {
    pstObj->uwID     = CAN_HWOBJ[ubObjNr].uwMOAR & 0x1fffffff;
    pstObj->uwMask   = CAN_HWOBJ[ubObjNr].uwMOAMR & 0x1fffffff;
    pstObj->usMOCfg  = pstObj->usMOCfg | 0x04;  // set IDE
  }
  else                                          // standard identifier 
  {
    pstObj->uwID   = (CAN_HWOBJ[ubObjNr].uwMOAR & 0x1fffffff) >> 18;
    pstObj->uwMask = (CAN_HWOBJ[ubObjNr].uwMOAMR & 0x1fffffff) >> 18;
  }

  pstObj->usCounter = (CAN_HWOBJ[ubObjNr].uwMOIPR & 0xffff0000) >> 16;

} //  End of function CAN_vGetMsgObj


//****************************************************************************
// @Function      ubyte CAN_ubRequestMsgObj(ubyte ubObjNr) 
//
//----------------------------------------------------------------------------
// @Description   If a TRANSMIT OBJECT is to be reconfigured it must first be 
//                accessed. The access to the transmit object is exclusive. 
//                This function checks whether the choosen message object is 
//                still executing a transmit request, or if the object can be 
//                accessed exclusively.
//                After the message object is reserved, it can be 
//                reconfigured by using the function CAN_vConfigMsgObj or 
//                CAN_vLoadData.
//                Both functions enable access to the object for the CAN 
//                controller. 
//                By calling the function CAN_vTransmit transfering of data 
//                is started.
//
//----------------------------------------------------------------------------
// @Returnvalue   0 message object is busy (a transfer is active), else 1
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object (0-127)
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (RequestMsgObj,1)

// USER CODE END

ubyte CAN_ubRequestMsgObj(ubyte ubObjNr)
{
  ubyte ubReturn;

  ubReturn = 0;
  if((CAN_HWOBJ[ubObjNr].uwMOCTR & 0x00000100) == 0x00000000)  // if reset TXRQ 
  {
    CAN_HWOBJ[ubObjNr].uwMOCTR = 0x00000020;                   // reset MSGVAL 
    ubReturn = 1;
  }
  return(ubReturn);

} //  End of function CAN_ubRequestMsgObj


//****************************************************************************
// @Function      ubyte CAN_ubNewData(ubyte ubObjNr) 
//
//----------------------------------------------------------------------------
// @Description   This function checks whether the selected RECEIVE OBJECT 
//                has received a new message. If so the function returns the 
//                value '1'.
//
//----------------------------------------------------------------------------
// @Returnvalue   1 the message object has received a new message, else 0
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object (0-127)
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (NewData,1)

// USER CODE END

ubyte CAN_ubNewData(ubyte ubObjNr)
{
  ubyte ubReturn;

  ubReturn = 0;
  if((CAN_HWOBJ[ubObjNr].uwMOCTR & 0x00000008))    // if NEWDAT 
  {
    ubReturn = 1;
  }
  return(ubReturn);

} //  End of function CAN_ubNewData


//****************************************************************************
// @Function      void CAN_vTransmit(ubyte ubObjNr) 
//
//----------------------------------------------------------------------------
// @Description   This function triggers the CAN controller to send the 
//                selected message.
//                If the selected message object is a TRANSMIT OBJECT then 
//                this function triggers the sending of a data frame. If 
//                however the selected message object is a RECEIVE OBJECT 
//                this function triggers the sending of a remote frame.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object (0-127)
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (Transmit,1)

// USER CODE END

void CAN_vTransmit(ubyte ubObjNr)
{
  CAN_HWOBJ[ubObjNr].uwMOCTR = 0x07000000;  // set TXRQ,TXEN0,TXEN1

} //  End of function CAN_vTransmit


//****************************************************************************
// @Function      void CAN_vConfigMsgObj(ubyte ubObjNr, CAN_SWObj *pstObj) 
//
//----------------------------------------------------------------------------
// @Description   This function sets up the message objects. This includes 
//                the 8 data bytes, the identifier (11- or 29-bit), the 
//                acceptance mask (11- or 29-bit), the data number (0-8 
//                bytes), the frame counter value and the EDE-bit (standard 
//                or extended identifier).  The direction bit (DIR) can not 
//                be changed. 
//                The message is not sent; for this the function 
//                CAN_vTransmit must be called.
//                
//                The structure of the SW message object is defined in the 
//                header file CAN.h (see CAN_SWObj).
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object to be configured (0-127)
// @Parameters    *pstObj: 
//                Pointer on a message object
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (ConfigMsgObj,1)

// USER CODE END

void CAN_vConfigMsgObj(ubyte ubObjNr, CAN_SWObj *pstObj)
{
  ubyte i;

  CAN_HWOBJ[ubObjNr].uwMOCTR = 0x00000020;     // reset MSGVAL

  if(pstObj->usMOCfg & 0x0004)                 // extended identifier
  {
    CAN_HWOBJ[ubObjNr].uwMOAR  &= ~0x3fffffff;
    CAN_HWOBJ[ubObjNr].uwMOAR  |= 0x20000000 | pstObj->uwID ;
    CAN_HWOBJ[ubObjNr].uwMOAMR &= ~0x1fffffff;
    CAN_HWOBJ[ubObjNr].uwMOAMR |= pstObj->uwMask ;
  }
  else                                         // standard identifier
  {
    CAN_HWOBJ[ubObjNr].uwMOAR  &= ~0x3fffffff;
    CAN_HWOBJ[ubObjNr].uwMOAR  |= pstObj->uwID << 18 ;
    CAN_HWOBJ[ubObjNr].uwMOAMR &= ~0x1fffffff;
    CAN_HWOBJ[ubObjNr].uwMOAMR |= pstObj->uwMask << 18 ;
  }

  CAN_HWOBJ[ubObjNr].uwMOIPR &= ~0xffff0000;
  CAN_HWOBJ[ubObjNr].uwMOIPR |= pstObj->usCounter << 16;

  CAN_HWOBJ[ubObjNr].uwMOFCR  = (CAN_HWOBJ[ubObjNr].uwMOFCR & ~0x0f000000) | ((pstObj->usMOCfg & 0x00f0) << 20);

  if(CAN_HWOBJ[ubObjNr].uwMOCTR & 0x00000800)  // if transmit direction
  {
    for(i = 0; i < (pstObj->usMOCfg & 0x00f0) >> 4; i++)
    {
      CAN_HWOBJ[ubObjNr].ubData[i] = pstObj->ubData[i];
    }
    CAN_HWOBJ[ubObjNr].uwMOCTR  = 0x06280040;  // set NEWDAT, reset RTSEL, 
  }                                            // set MSGVAL, set TXEN0, TXEN1
  else                                         // if receive direction
  {
    CAN_HWOBJ[ubObjNr].uwMOCTR  = 0x00200040;  // reset RTSEL, set MSGVAL
  }

} //  End of function CAN_vConfigMsgObj


//****************************************************************************
// @Function      void CAN_vLoadData(ubyte ubObjNr, ubyte *pubData) 
//
//----------------------------------------------------------------------------
// @Description   If a hardware TRANSMIT OBJECT has to be loaded with data 
//                but not with a new identifier, this function may be used 
//                instead of the function CAN_vConfigMsgObj. The message 
//                object should be accessed by calling the function 
//                CAN_ubRequestMsgObj before calling this function. This 
//                prevents the CAN controller from working with invalid data.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object to be configured (0-127)
// @Parameters    *pubData: 
//                Pointer on a data buffer
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (LoadData,1)

// USER CODE END

void CAN_vLoadData(ubyte ubObjNr, ubyte *pubData)
{
  ubyte i;

  CAN_HWOBJ[ubObjNr].uwMOCTR = 0x00080000;       // set NEWDAT

  for(i = 0; i < (CAN_HWOBJ[ubObjNr].uwMOFCR & 0x0f000000) >> 24; i++)
  {
    CAN_HWOBJ[ubObjNr].ubData[i] = *(pubData++);
  }

  CAN_HWOBJ[ubObjNr].uwMOCTR = 0x00200040;       // reset RTSEL, set MSGVAL

} //  End of function CAN_vLoadData


//****************************************************************************
// @Function      ubyte CAN_ubMsgLost(ubyte ubObjNr) 
//
//----------------------------------------------------------------------------
// @Description   If a RECEIVE OBJECT receives new data before the old object 
//                has been read, the old object is lost. The CAN controller 
//                indicates this by setting the message lost bit (MSGLST). 
//                This function returns the status of this bit. 
//                
//                Note:
//                This function resets the message lost bit (MSGLST).
//
//----------------------------------------------------------------------------
// @Returnvalue   1 the message object has lost a message, else 0
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object (0-127)
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (MsgLost,1)

// USER CODE END

ubyte CAN_ubMsgLost(ubyte ubObjNr)
{
  ubyte ubReturn;

  ubReturn = 0;
  if(CAN_HWOBJ[ubObjNr].uwMOCTR & 0x00000010)  // if set MSGLST 
  {
    CAN_HWOBJ[ubObjNr].uwMOCTR = 0x00000010;   // reset MSGLST 
    ubReturn = 1;
  }
  return(ubReturn);

} //  End of function CAN_ubMsgLost


//****************************************************************************
// @Function      ubyte CAN_ubDelMsgObj(ubyte ubObjNr) 
//
//----------------------------------------------------------------------------
// @Description   This function marks the selected message object as not 
//                valid. This means that this object cannot be sent or 
//                receive data. If the selected object is busy (meaning the 
//                object is transmitting a message or has received a new 
//                message) this function returns the value "0" and the object 
//                is not deleted.
//
//----------------------------------------------------------------------------
// @Returnvalue   1 the message object was deleted, else 0
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object (0-127)
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (DelMsgObj,1)

// USER CODE END

ubyte CAN_ubDelMsgObj(ubyte ubObjNr)
{
  ubyte ubReturn;

  ubReturn = 0;
  if(!(CAN_HWOBJ[ubObjNr].uwMOCTR & 0x00000108)) // if set TXRQ or NEWDAT
  {
    CAN_HWOBJ[ubObjNr].uwMOCTR = 0x00000020;     // reset MSGVAL
    ubReturn = 1;
  }
  return(ubReturn);

} //  End of function CAN_ubDelMsgObj


//****************************************************************************
// @Function      void CAN_vReleaseObj(ubyte ubObjNr) 
//
//----------------------------------------------------------------------------
// @Description   This function resets the NEWDAT flag of the selected 
//                RECEIVE OBJECT, so that the CAN controller have access to 
//                it. This function must be called if the function 
//                CAN_ubNewData detects, that new data are present in the 
//                message object and the actual data have been read by 
//                calling the function CAN_vGetMsgObj. 
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object (0-127)
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (ReleaseObj,1)

// USER CODE END

void CAN_vReleaseObj(ubyte ubObjNr)
{
  CAN_HWOBJ[ubObjNr].uwMOCTR = 0x00000008;     // reset NEWDAT

} //  End of function CAN_vReleaseObj


//****************************************************************************
// @Function      void CAN_vSetMSGVAL(ubyte ubObjNr) 
//
//----------------------------------------------------------------------------
// @Description   This function sets the MSGVAL flag of the selected object. 
//                This is only necessary if the single data transfer mode 
//                (SDT) for the selected object is enabled. If SDT is set to 
//                '1', the CAN controller automatically resets bit MSGVAL 
//                after receiving or tranmission of a frame.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object (0-127)
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (SetMSGVAL,1)

// USER CODE END

void CAN_vSetMSGVAL(ubyte ubObjNr)
{
  CAN_HWOBJ[ubObjNr].uwMOCTR = 0x00200000;     // set MSGVAL

} //  End of function CAN_vSetMSGVAL


//****************************************************************************
// @Function      ubyte CAN_ubWriteFIFO(ubyte ubObjNr, CAN_SWObj *pstObj) 
//
//----------------------------------------------------------------------------
// @Description   This function sets up the next free TRANSMIT message object 
//                which is part of a FIFO. This includes the 8 data bytes, 
//                the identifier (11- or 29-bit) and the data number (0-8 
//                bytes). The direction bit (DIR) and the EDE-bit can not be 
//                changed. The acceptance mask register and the Frame Counter 
//                remains unchanged. This function checks whether the choosen 
//                message object is still executing a transmit request, or if 
//                the object can be accessed exclusively. 
//                The structure of the SW message object is defined in the 
//                header file CAN.h (see CAN_SWObj).
//                Note: 
//                This function can only used for TRANSMIT objects which are 
//                configured for FIFO base functionality. 
//
//----------------------------------------------------------------------------
// @Returnvalue   0: message object is busy (a transfer is active); 1: the 
//                message object was configured and the transmite is 
//                requested; 2: this is not a FIFO base object
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the FIFO base object
// @Parameters    *pstObj: 
//                Pointer on a message object
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (WriteFIFO,1)

// USER CODE END

ubyte CAN_ubWriteFIFO(ubyte ubObjNr, CAN_SWObj *pstObj)
{
  ubyte i,j;
  ubyte ubReturn;

  ubReturn = 2;

  if((CAN_HWOBJ[ubObjNr].uwMOFCR & 0x0000000f) == 0x00000002)  // if transmit FIFO base object 
  {
    j = aubFIFOWritePtr[ubObjNr];

    ubReturn = 0;
    if((CAN_HWOBJ[j].uwMOCTR & 0x00000100) == 0x00000000) // if reset TXRQ 
    {
      if(j == (CAN_HWOBJ[j].uwMOCTR & 0xff000000) >> 24)  // last MO in a list
      {
        // WritePtr = BOT of the base object
        aubFIFOWritePtr[ubObjNr] = (CAN_HWOBJ[ubObjNr].uwMOFGPR & 0x000000ff);
      }
      else
      {
        // WritePtr = PNEXT of the current selected slave
        aubFIFOWritePtr[ubObjNr] = (CAN_HWOBJ[j].uwMOCTR & 0xff000000) >> 24;
      }

      CAN_HWOBJ[j].uwMOCTR = 0x00000008;                  // reset NEWDAT 

      if(CAN_HWOBJ[j].uwMOAR & 0x20000000)                // extended identifier
      {
        CAN_HWOBJ[j].uwMOAR  &= ~0x3fffffff;
        CAN_HWOBJ[j].uwMOAR  |= 0x20000000 | pstObj->uwID;
      }
      else                                                // if standard identifier
      {
        CAN_HWOBJ[j].uwMOAR  &= ~0x3fffffff;
        CAN_HWOBJ[j].uwMOAR  |= pstObj->uwID << 18 ;
      }

      CAN_HWOBJ[j].uwMOFCR  = (CAN_HWOBJ[j].uwMOFCR & ~0x0f000000) | ((pstObj->usMOCfg & 0x00f0) << 20);

      for(i = 0; i < (pstObj->usMOCfg & 0x00f0) >> 4; i++)
      {
        CAN_HWOBJ[j].ubData[i] = pstObj->ubData[i];
      }
      CAN_HWOBJ[j].uwMOCTR  = 0x01280000;                 // set TXRQ, NEWDAT, MSGVAL 
                                              
      ubReturn = 1;
    }
  }
  return(ubReturn);

} //  End of function CAN_ubWriteFIFO


//****************************************************************************
// @Function      ubyte CAN_ubReadFIFO(ubyte ubObjNr, CAN_SWObj *pstObj) 
//
//----------------------------------------------------------------------------
// @Description   This function reads the next RECEIVE message object which 
//                is part of a FIFO. It checks whether the selected RECEIVE 
//                OBJECT has received a new message. If so the forwarded SW 
//                message object is filled with the content of the HW message 
//                object and the functions returns the value "1". The 
//                structure of the SW message object is defined in the header 
//                file CAN.h (see CAN_SWObj).
//                Note: 
//                This function can only used for RECEIVE objects which are 
//                configured for FIFO base functionality. 
//                Be sure that no interrupt is enabled for the FIFO objects. 
//
//----------------------------------------------------------------------------
// @Returnvalue   0: the message object has not received a new message; 1: 
//                the message object has received a new message; 2: this is 
//                not a FIFO base object; 3: a previous message was lost; 4: 
//                the received message is corrupted
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the FIFO base object
// @Parameters    *pstObj: 
//                Pointer on a message object to be filled by this function
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (ReadFIFO,1)

// USER CODE END

ubyte CAN_ubReadFIFO(ubyte ubObjNr, CAN_SWObj *pstObj)
{
  ubyte i,j;
  ubyte ubReturn;

  ubReturn = 2;

  if((CAN_HWOBJ[ubObjNr].uwMOFCR & 0x0000000f) == 0x00000001)  // if receive FIFO base object 
  {
    j = aubFIFOReadPtr[ubObjNr];

    ubReturn = 0;
    if(CAN_HWOBJ[j].uwMOCTR & 0x00000008)                 // if NEWDAT 
    {
      CAN_HWOBJ[j].uwMOCTR = 0x00000008;                  // clear NEWDAT

      if(j == (CAN_HWOBJ[j].uwMOCTR & 0xff000000) >> 24)  // last MO in a list
      {
        // ReadPtr = BOT of the base object
        aubFIFOReadPtr[ubObjNr] = (CAN_HWOBJ[ubObjNr].uwMOFGPR & 0x000000ff);
      }
      else
      {
        // ReadPtr = PNEXT of the current selected slave
        aubFIFOReadPtr[ubObjNr] = (CAN_HWOBJ[j].uwMOCTR & 0xff000000) >> 24;
      }

      // check if the previous message was lost 
      if(CAN_HWOBJ[j].uwMOCTR & 0x00000010)               // if set MSGLST 
      {
        CAN_HWOBJ[j].uwMOCTR = 0x00000010;                // reset MSGLST 
        return(3);
      }

      pstObj->usMOCfg  = (CAN_HWOBJ[j].uwMOFCR & 0x0f000000) >> 24;
      for(i = 0; i < pstObj->usMOCfg; i++)
      {
        pstObj->ubData[i] = CAN_HWOBJ[j].ubData[i];
      }

      pstObj->usMOCfg  = (pstObj->usMOCfg << 4);
      if(CAN_HWOBJ[j].uwMOCTR & 0x00000800)               // transmit object
      {
        pstObj->usMOCfg  = pstObj->usMOCfg | 0x08;
      }

      if(CAN_HWOBJ[j].uwMOAR & 0x20000000)                // extended identifier
      {
        pstObj->uwID     = CAN_HWOBJ[j].uwMOAR & 0x1fffffff;
        pstObj->usMOCfg  = pstObj->usMOCfg | 0x04;
      }
      else                                                // standard identifier 
      {
        pstObj->uwID   = (CAN_HWOBJ[j].uwMOAR & 0x1fffffff) >> 18;
      }

      pstObj->usCounter = (CAN_HWOBJ[j].uwMOIPR & 0xffff0000) >> 16;

      // check if the message was corrupted 
      if(CAN_HWOBJ[j].uwMOCTR & 0x00000008)               // if NEWDAT 
      {
        CAN_HWOBJ[j].uwMOCTR = 0x00000008;                // clear NEWDAT
        return(4);
      }
      ubReturn = 1;
    }
  }
  return(ubReturn);

} //  End of function CAN_ubReadFIFO


//****************************************************************************
// @Function      void CAN_viSRN0(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the Service 
//                Request Node 0 of the MultiCAN module. 
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (SRN0,1)

// USER CODE END

void INTERRUPT (CAN_SRN0INT) CAN_viSRN0(void)
{


  // USER CODE BEGIN (SRN0,2)

  // USER CODE END


  // USER CODE BEGIN (SRN0,15)

  // USER CODE END

} //  End of function CAN_viSRN0


//****************************************************************************
// @Function      void CAN_viSRN1(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the Service 
//                Request Node 1 of the MultiCAN module. 
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (SRN1,1)

// USER CODE END

void INTERRUPT (CAN_SRN1INT) CAN_viSRN1(void)
{


  // USER CODE BEGIN (SRN1,2)

  // USER CODE END


  // USER CODE BEGIN (SRN1,15)

  // USER CODE END

} //  End of function CAN_viSRN1


//****************************************************************************
// @Function      void CAN_viSRN2(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the Service 
//                Request Node 2 of the MultiCAN module. 
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (SRN2,1)

// USER CODE END

void INTERRUPT (CAN_SRN2INT) CAN_viSRN2(void)
{


  // USER CODE BEGIN (SRN2,2)

  // USER CODE END

      CAN_MSIMASK.U  = 0x00000004; // set message index mask register
  while (CAN_MSID0.U != 0x00000020)
  {
    switch(CAN_MSID0.U){

    case 2: // message object 2 interrupt 
    
      if(CAN_MOSTAT2.B.RXPND)      // if message object 2 receive interrupt
      {

        if(CAN_MOSTAT2.B.NEWDAT)     // if NEWDAT is set
        {

          if (CAN_MOSTAT2.B.MSGLST)  // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            CAN_MOCTR2.U = CAN_MOCTRm_CTR_RESMSGLST_MASK;    // reset MSGLST

            // USER CODE BEGIN (SRN2_OBJ2,1)

            // USER CODE END
          }
          else
          {
            // The CAN controller has stored a new message
            // into this object.

            // USER CODE BEGIN (SRN2_OBJ2,2)

            // USER CODE END
          }

          CAN_MOCTR2.U = CAN_MOCTRm_CTR_RESNEWDAT_MASK;      // reset NEWDAT
        }

       CAN_MOCTR2.U = CAN_MOCTRm_CTR_RESRXPND_MASK;         // reset RXPND
      }  // End of RXPND2


       CAN_MSPND0.U =  ~0x00000004; // reset PND bit

      // USER CODE BEGIN (SRN2_OBJ2,7)

      // USER CODE END

      break;

    default:

      // USER CODE BEGIN (SRN2,3)

      // USER CODE END

      break;

    }  // end switch 

    // USER CODE BEGIN (SRN2,7)

    // USER CODE END

  }  // end of while CAN_MSID


  // USER CODE BEGIN (SRN2,15)

  // USER CODE END

} //  End of function CAN_viSRN2


//****************************************************************************
// @Function      void CAN_viSRN3(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the Service 
//                Request Node 3 of the MultiCAN module. 
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (SRN3,1)

// USER CODE END

void INTERRUPT (CAN_SRN3INT) CAN_viSRN3(void)
{


  // USER CODE BEGIN (SRN3,2)
	CAN_SWObj obj;
	uint32_t swc_id;
	uint32_t is_active;

  // USER CODE END

      CAN_MSIMASK.U  = 0x20000008; // set message index mask register
  while (CAN_MSID0.U != 0x00000020)
  {
    switch(CAN_MSID0.U){

    case 3: // message object 3 interrupt 
    
      if(CAN_MOSTAT3.B.RXPND)      // if message object 3 receive interrupt
      {

        if(CAN_MOSTAT3.B.NEWDAT)     // if NEWDAT is set
        {

          if (CAN_MOSTAT3.B.MSGLST)  // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            CAN_MOCTR3.U = CAN_MOCTRm_CTR_RESMSGLST_MASK;    // reset MSGLST

            // USER CODE BEGIN (SRN3_OBJ3,1)

            // USER CODE END
          }
          else
          {
            // The CAN controller has stored a new message
            // into this object.

            // USER CODE BEGIN (SRN3_OBJ3,2)

            // USER CODE END
          }

          CAN_MOCTR3.U = CAN_MOCTRm_CTR_RESNEWDAT_MASK;      // reset NEWDAT
        }

       CAN_MOCTR3.U = CAN_MOCTRm_CTR_RESRXPND_MASK;         // reset RXPND
      }  // End of RXPND3


       CAN_MSPND0.U =  ~0x00000008; // reset PND bit

      // USER CODE BEGIN (SRN3_OBJ3,7)

      // USER CODE END

      break;


    case 29: // message object 29 interrupt 
    
      if(CAN_MOSTAT29.B.RXPND)      // if message object 29 receive interrupt
      {

        if(CAN_MOSTAT29.B.NEWDAT)     // if NEWDAT is set
        {

          if (CAN_MOSTAT29.B.MSGLST)  // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            CAN_MOCTR29.U = CAN_MOCTRm_CTR_RESMSGLST_MASK;    // reset MSGLST

            // USER CODE BEGIN (SRN3_OBJ29,1)

            // USER CODE END
          }
          else
          {
            // The CAN controller has stored a new message
            // into this object.

            // USER CODE BEGIN (SRN3_OBJ29,2)
        	  CAN_vGetMsgObj(29, &obj);
        	  CAN_vReleaseObj(29);
        	  memcpy(&swc_id, &obj.ubData[0], 4);
        	  memcpy(&is_active, &obj.ubData[4], 4);

        	  if (get_jiffies() > 1000) {
        		  callback(swc_id, is_active);
        	  }
            // USER CODE END
          }

          CAN_MOCTR29.U = CAN_MOCTRm_CTR_RESNEWDAT_MASK;      // reset NEWDAT
        }

       CAN_MOCTR29.U = CAN_MOCTRm_CTR_RESRXPND_MASK;         // reset RXPND
      }  // End of RXPND29


       CAN_MSPND0.U =  ~0x20000000; // reset PND bit

      // USER CODE BEGIN (SRN3_OBJ29,7)

      // USER CODE END

      break;

    default:

      // USER CODE BEGIN (SRN3,3)

      // USER CODE END

      break;

    }  // end switch 

    // USER CODE BEGIN (SRN3,7)

    // USER CODE END

  }  // end of while CAN_MSID


  // USER CODE BEGIN (SRN3,15)

  // USER CODE END

} //  End of function CAN_viSRN3


//****************************************************************************
// @Function      void CAN_viSRN4(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the Service 
//                Request Node 4 of the MultiCAN module. 
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (SRN4,1)

// USER CODE END

void INTERRUPT (CAN_SRN4INT) CAN_viSRN4(void)
{


  // USER CODE BEGIN (SRN4,2)

  // USER CODE END

      CAN_MSIMASK.U  = 0x00000010; // set message index mask register
  while (CAN_MSID0.U != 0x00000020)
  {
    switch(CAN_MSID0.U){

    case 4: // message object 4 interrupt 
    
      if(CAN_MOSTAT4.B.RXPND)      // if message object 4 receive interrupt
      {

        if(CAN_MOSTAT4.B.NEWDAT)     // if NEWDAT is set
        {

          if (CAN_MOSTAT4.B.MSGLST)  // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            CAN_MOCTR4.U = CAN_MOCTRm_CTR_RESMSGLST_MASK;    // reset MSGLST

            // USER CODE BEGIN (SRN4_OBJ4,1)

            // USER CODE END
          }
          else
          {
            // The CAN controller has stored a new message
            // into this object.

            // USER CODE BEGIN (SRN4_OBJ4,2)

            // USER CODE END
          }

          CAN_MOCTR4.U = CAN_MOCTRm_CTR_RESNEWDAT_MASK;      // reset NEWDAT
        }

       CAN_MOCTR4.U = CAN_MOCTRm_CTR_RESRXPND_MASK;         // reset RXPND
      }  // End of RXPND4


       CAN_MSPND0.U =  ~0x00000010; // reset PND bit

      // USER CODE BEGIN (SRN4_OBJ4,7)

      // USER CODE END

      break;

    default:

      // USER CODE BEGIN (SRN4,3)

      // USER CODE END

      break;

    }  // end switch 

    // USER CODE BEGIN (SRN4,7)

    // USER CODE END

  }  // end of while CAN_MSID


  // USER CODE BEGIN (SRN4,15)

  // USER CODE END

} //  End of function CAN_viSRN4


//****************************************************************************
// @Function      void CAN_viSRN5(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the Service 
//                Request Node 5 of the MultiCAN module. 
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (SRN5,1)

// USER CODE END

void INTERRUPT (CAN_SRN5INT) CAN_viSRN5(void)
{


  // USER CODE BEGIN (SRN5,2)

  // USER CODE END

      CAN_MSIMASK.U  = 0x00000020; // set message index mask register
  while (CAN_MSID0.U != 0x00000020)
  {
    switch(CAN_MSID0.U){

    case 5: // message object 5 interrupt 
    
      if(CAN_MOSTAT5.B.RXPND)      // if message object 5 receive interrupt
      {

        if(CAN_MOSTAT5.B.NEWDAT)     // if NEWDAT is set
        {

          if (CAN_MOSTAT5.B.MSGLST)  // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            CAN_MOCTR5.U = CAN_MOCTRm_CTR_RESMSGLST_MASK;    // reset MSGLST

            // USER CODE BEGIN (SRN5_OBJ5,1)

            // USER CODE END
          }
          else
          {
            // The CAN controller has stored a new message
            // into this object.

            // USER CODE BEGIN (SRN5_OBJ5,2)

            // USER CODE END
          }

          CAN_MOCTR5.U = CAN_MOCTRm_CTR_RESNEWDAT_MASK;      // reset NEWDAT
        }

       CAN_MOCTR5.U = CAN_MOCTRm_CTR_RESRXPND_MASK;         // reset RXPND
      }  // End of RXPND5


       CAN_MSPND0.U =  ~0x00000020; // reset PND bit

      // USER CODE BEGIN (SRN5_OBJ5,7)

      // USER CODE END

      break;

    default:

      // USER CODE BEGIN (SRN5,3)

      // USER CODE END

      break;

    }  // end switch 

    // USER CODE BEGIN (SRN5,7)

    // USER CODE END

  }  // end of while CAN_MSID


  // USER CODE BEGIN (SRN5,15)

  // USER CODE END

} //  End of function CAN_viSRN5


//****************************************************************************
// @Function      void CAN_viSRN6(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the Service 
//                Request Node 6 of the MultiCAN module. 
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (SRN6,1)

// USER CODE END

void INTERRUPT (CAN_SRN6INT) CAN_viSRN6(void)
{


  // USER CODE BEGIN (SRN6,2)

  // USER CODE END

      CAN_MSIMASK.U  = 0x00000040; // set message index mask register
  while (CAN_MSID0.U != 0x00000020)
  {
    switch(CAN_MSID0.U){

    case 6: // message object 6 interrupt 
    
      if(CAN_MOSTAT6.B.RXPND)      // if message object 6 receive interrupt
      {

        if(CAN_MOSTAT6.B.NEWDAT)     // if NEWDAT is set
        {

          if (CAN_MOSTAT6.B.MSGLST)  // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            CAN_MOCTR6.U = CAN_MOCTRm_CTR_RESMSGLST_MASK;    // reset MSGLST

            // USER CODE BEGIN (SRN6_OBJ6,1)

            // USER CODE END
          }
          else
          {
            // The CAN controller has stored a new message
            // into this object.

            // USER CODE BEGIN (SRN6_OBJ6,2)

            // USER CODE END
          }

          CAN_MOCTR6.U = CAN_MOCTRm_CTR_RESNEWDAT_MASK;      // reset NEWDAT
        }

       CAN_MOCTR6.U = CAN_MOCTRm_CTR_RESRXPND_MASK;         // reset RXPND
      }  // End of RXPND6


       CAN_MSPND0.U =  ~0x00000040; // reset PND bit

      // USER CODE BEGIN (SRN6_OBJ6,7)

      // USER CODE END

      break;

    default:

      // USER CODE BEGIN (SRN6,3)

      // USER CODE END

      break;

    }  // end switch 

    // USER CODE BEGIN (SRN6,7)

    // USER CODE END

  }  // end of while CAN_MSID


  // USER CODE BEGIN (SRN6,15)

  // USER CODE END

} //  End of function CAN_viSRN6


//****************************************************************************
// @Function      void CAN_viSRN7(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the Service 
//                Request Node 7 of the MultiCAN module. 
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (SRN7,1)

// USER CODE END

void INTERRUPT (CAN_SRN7INT) CAN_viSRN7(void)
{


  // USER CODE BEGIN (SRN7,2)

  // USER CODE END

      CAN_MSIMASK.U  = 0x00000080; // set message index mask register
  while (CAN_MSID0.U != 0x00000020)
  {
    switch(CAN_MSID0.U){

    case 7: // message object 7 interrupt 
    
      if(CAN_MOSTAT7.B.RXPND)      // if message object 7 receive interrupt
      {

        if(CAN_MOSTAT7.B.NEWDAT)     // if NEWDAT is set
        {

          if (CAN_MOSTAT7.B.MSGLST)  // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            CAN_MOCTR7.U = CAN_MOCTRm_CTR_RESMSGLST_MASK;    // reset MSGLST

            // USER CODE BEGIN (SRN7_OBJ7,1)

            // USER CODE END
          }
          else
          {
            // The CAN controller has stored a new message
            // into this object.

            // USER CODE BEGIN (SRN7_OBJ7,2)

            // USER CODE END
          }

          CAN_MOCTR7.U = CAN_MOCTRm_CTR_RESNEWDAT_MASK;      // reset NEWDAT
        }

       CAN_MOCTR7.U = CAN_MOCTRm_CTR_RESRXPND_MASK;         // reset RXPND
      }  // End of RXPND7


       CAN_MSPND0.U =  ~0x00000080; // reset PND bit

      // USER CODE BEGIN (SRN7_OBJ7,7)

      // USER CODE END

      break;

    default:

      // USER CODE BEGIN (SRN7,3)

      // USER CODE END

      break;

    }  // end switch 

    // USER CODE BEGIN (SRN7,7)

    // USER CODE END

  }  // end of while CAN_MSID


  // USER CODE BEGIN (SRN7,15)

  // USER CODE END

} //  End of function CAN_viSRN7


//****************************************************************************
// @Function      void CAN_viSRN8(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the Service 
//                Request Node 8 of the MultiCAN module. 
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (SRN8,1)

// USER CODE END

void INTERRUPT (CAN_SRN8INT) CAN_viSRN8(void)
{


  // USER CODE BEGIN (SRN8,2)

  // USER CODE END

      CAN_MSIMASK.U  = 0x00000100; // set message index mask register
  while (CAN_MSID0.U != 0x00000020)
  {
    switch(CAN_MSID0.U){

    case 8: // message object 8 interrupt 
    
      if(CAN_MOSTAT8.B.RXPND)      // if message object 8 receive interrupt
      {

        if(CAN_MOSTAT8.B.NEWDAT)     // if NEWDAT is set
        {

          if (CAN_MOSTAT8.B.MSGLST)  // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            CAN_MOCTR8.U = CAN_MOCTRm_CTR_RESMSGLST_MASK;    // reset MSGLST

            // USER CODE BEGIN (SRN8_OBJ8,1)

            // USER CODE END
          }
          else
          {
            // The CAN controller has stored a new message
            // into this object.

            // USER CODE BEGIN (SRN8_OBJ8,2)

            // USER CODE END
          }

          CAN_MOCTR8.U = CAN_MOCTRm_CTR_RESNEWDAT_MASK;      // reset NEWDAT
        }

       CAN_MOCTR8.U = CAN_MOCTRm_CTR_RESRXPND_MASK;         // reset RXPND
      }  // End of RXPND8


       CAN_MSPND0.U =  ~0x00000100; // reset PND bit

      // USER CODE BEGIN (SRN8_OBJ8,7)

      // USER CODE END

      break;

    default:

      // USER CODE BEGIN (SRN8,3)

      // USER CODE END

      break;

    }  // end switch 

    // USER CODE BEGIN (SRN8,7)

    // USER CODE END

  }  // end of while CAN_MSID


  // USER CODE BEGIN (SRN8,15)

  // USER CODE END

} //  End of function CAN_viSRN8


//****************************************************************************
// @Function      void CAN_viSRN9(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the interrupt service routine for the Service 
//                Request Node 9 of the MultiCAN module. 
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2013-11-20
//
//****************************************************************************

// USER CODE BEGIN (SRN9,1)

// USER CODE END

void INTERRUPT (CAN_SRN9INT) CAN_viSRN9(void)
{


  // USER CODE BEGIN (SRN9,2)

  // USER CODE END

      CAN_MSIMASK.U  = 0x00000200; // set message index mask register
  while (CAN_MSID0.U != 0x00000020)
  {
    switch(CAN_MSID0.U){

    case 9: // message object 9 interrupt 
    
      if(CAN_MOSTAT9.B.RXPND)      // if message object 9 receive interrupt
      {

        if(CAN_MOSTAT9.B.NEWDAT)     // if NEWDAT is set
        {

          if (CAN_MOSTAT9.B.MSGLST)  // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            CAN_MOCTR9.U = CAN_MOCTRm_CTR_RESMSGLST_MASK;    // reset MSGLST

            // USER CODE BEGIN (SRN9_OBJ9,1)

            // USER CODE END
          }
          else
          {
            // The CAN controller has stored a new message
            // into this object.

            // USER CODE BEGIN (SRN9_OBJ9,2)

            // USER CODE END
          }

          CAN_MOCTR9.U = CAN_MOCTRm_CTR_RESNEWDAT_MASK;      // reset NEWDAT
        }

       CAN_MOCTR9.U = CAN_MOCTRm_CTR_RESRXPND_MASK;         // reset RXPND
      }  // End of RXPND9


       CAN_MSPND0.U =  ~0x00000200; // reset PND bit

      // USER CODE BEGIN (SRN9_OBJ9,7)

      // USER CODE END

      break;

    default:

      // USER CODE BEGIN (SRN9,3)

      // USER CODE END

      break;

    }  // end switch 

    // USER CODE BEGIN (SRN9,7)

    // USER CODE END

  }  // end of while CAN_MSID


  // USER CODE BEGIN (SRN9,15)

  // USER CODE END

} //  End of function CAN_viSRN9



// USER CODE BEGIN (CAN_General,10)

// USER CODE END

