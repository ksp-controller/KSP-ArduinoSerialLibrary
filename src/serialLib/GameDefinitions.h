#ifndef GameDefinitions_h
#define GameDefinitions_h
   const int SERIAL_BAUDRATE = 57600;
   const int MAX_PACKET_SIZE = 255;
   const int CONTROL_GROUP_COUNT = 11;
   const byte PACKET_ACK = 0xAE;
   const byte PACKET_VERIFIER = 0xEE;
   const byte PACKET_HEADER_SIZE = 3;
   struct VesselData
    {
         byte id;             //1
         float AP;            //2
         float PE;            //3
         float SemiMajorAxis; //4
         float SemiMinorAxis; //5
         float VVI;           //6
         float e;             //7
         float inc;           //8
         float G;             //9
         long TAp;             //10
         long TPe;             //11
         float TrueAnomaly;   //12
         float Density;       //13
         long period;          //14
         float RAlt;          //15
         float Alt;           //16
         float Vsurf;         //17
         float Lat;           //18
         float Lon;           //19
         float LiquidFuelTot; //20
         float LiquidFuel;    //21
         float OxidizerTot;   //22
         float Oxidizer;      //23
         float EChargeTot;    //24
         float ECharge;       //25
         float MonoPropTot;   //26
         float MonoProp;      //27
         float IntakeAirTot;  //28
         float IntakeAir;     //29
         float SolidFuelTot;  //30
         float SolidFuel;     //31
         float XenonGasTot;   //32
         float XenonGas;      //33
         float LiquidFuelTotS;//34
         float LiquidFuelS;   //35
         float OxidizerTotS;  //36
         float OxidizerS;     //37
         uint32_t MissionTime;  //38
         float VOrbit;        //40
         uint32_t MNTime;       //41
         float MNDeltaV;      //42
         float Pitch;         //43
         float Roll;          //44
         float Heading;       //45
         uint16_t ActionGroups; //46  status bit order:SAS, RCS, Light, Gear, Brakes, Abort, Custom01 - 10
         byte SOINumber;      //47  SOI Number (decimal format: sun-planet-moon e.g. 130 = kerbin, 131 = mun)
         byte MaxOverHeat;    //48  Max part overheat (% percent)
         float MachNumber;    //49
         float IAS;           //50  Indicated Air Speed
         byte CurrentStage;   //51  Current stage number
         byte TotalStage;     //52  TotalNumber of stages
         float TargetDist;    //53  Distance to targeted vessel (m)
         float TargetV;       //54  Target vessel relative velocity (m/s)
         byte NavballSASMode; //55  Combined byte for navball target mode and SAS mode
        // First four bits indicate AutoPilot mode:
        // 0 SAS is off  //1 = Regular Stability Assist //2 = Prograde
        // 3 = RetroGrade //4 = Normal //5 = Antinormal //6 = Radial In
        // 7 = Radial Out //8 = Target //9 = Anti-Target //10 = Maneuver node
        // Last 4 bits set navball mode. (0=ignore,1=ORBIT,2=SURFACE,3=TARGET)
    };
    struct VesselControls
    {
         bool SAS;
         bool RCS;
         bool Light;
         bool Gear;
         bool Brakes;
         bool Abort;
         bool Stage;
         int Mode;
         int SASMode;
         int SpeedMode;
         bool ControlGroup[];
         float Pitch;
         float Roll;
         float Yaw;
         float TX;
         float TY;
         float TZ;
         float WheelSteer;
         float Throttle;
         float WheelThrottle;
    };
    struct SerializedVesselControls
    {
        byte MainControls;                  //SAS RCS Lights Gear Brakes Precision Abort Stage
        byte Mode;                          //0 = stage, 1 = docking, 2 = map
        unsigned int ControlGroup;                //control groups 1-10 in 2 bytes
        byte NavballSASMode;                //AutoPilot mode (See above for AutoPilot modes)(Ignored if the equal to zero or out of bounds (>10)) //Navball mode
        byte AdditionalControlByte1;
        short Pitch;                        //-1000 -> 1000
        short Roll;                         //-1000 -> 1000
        short Yaw;                          //-1000 -> 1000
        short TX;                           //-1000 -> 1000
        short TY;                           //-1000 -> 1000
        short TZ;                           //-1000 -> 1000
        short WheelSteer;                   //-1000 -> 1000
        short Throttle;                     // 0 -> 1000
        short WheelThrottle;                // 0 -> 1000
    };
    enum enumActionGroup : int
    {
        SAS, RCS, Light, Gear, Brakes, Abort
    };
#endif
