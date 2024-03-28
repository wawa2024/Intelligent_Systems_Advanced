/******************************************************************************
 * File: ./Software.h
 * Requires: Keypad.h LCD.h NET.h Utils.h
 ******************************************************************************/
namespace Software
{
    void VARstats(void)
    {
        LCD::Clear();
        LCD::Print("WindDirection:"); 
        LCD::SetCursor(0,1);
        LCD::Print("  Value: "); 
        LCD::Print( WindDirection::Value() ); 
        LCD::Print(" deg"); 
        LCD::SetCursor(0,2);
        LCD::Print("WindSpeed:"); 
        LCD::SetCursor(0,3);
        LCD::Print("  Value: "); 
        LCD::Print( WindSpeed::Value() ); 
        LCD::Print(" m/s");
    }

    void IPstats(void)
    {
        LCD::Clear();
        LCD::Print("IP ");     LCD::Print(NET::ip);
        LCD::SetCursor(0,1);    
        LCD::Print("GW ");     LCD::Print(NET::gw);
        LCD::SetCursor(0,2);
        LCD::Print("DNS ");    LCD::Print(NET::dns);
        LCD::SetCursor(0,3);
        LCD::Print("MASK ");   LCD::Print(NET::subnet);
    }

    void HWstats(void)
    {
        LCD::Clear();
        LCD::Print( NET::Status::Hardware() );
        LCD::SetCursor(0,1);
        LCD::Print( NET::Status::Link() );
        LCD::SetCursor(0,2);
        LCD::Print("MAC ");     LCD::Print(NET::mac2string());
        LCD::SetCursor(0,3);
    }

    void Bootmessage(void)
    {
        LCD::Clear();
        LCD::Print("Arduino Boot Online");
        LCD::SetCursor(0,1);
        LCD::Print("Turn DHCP ON?");
        LCD::SetCursor(0,2);
        LCD::Print("yes=*, no=#");
    }

    namespace DHCP 
    {
        static bool flag=true;
        void msg(void)
        {
            LCD::Clear();
            LCD::Print("DHCP ");
            switch( NET::DHCPon ) 
            {
                case true: LCD::Print("ON"); break;
                case false: LCD::Print("OFF"); break;
                default: break;
            }
        }
        void yes(void)
        {
            switch(flag)
            {
                case true: 
                        NET::DHCPon = true; 
                        flag = false;
                        init();
                default: msg(); break;
            }
        }
        void no(void)
        {
            switch(flag)
            {
                case true: 
                        NET::DHCPon = false; 
                        flag = false;
                        init();
                default: msg(); break;
            }
        }
        void init(void)
        {
            NET::Init();
            flag=false;
        }
    } 

    void Default(void)
    {
        LCD::Clear();
        LCD::Print("Unmapped key");
    }

    inline void Init(void)
    {
        for(uint8_t i=0 ; i < Keypad::num_keys ; i++)
            Keypad::AttachKeyHandler(i,Default);

        Keypad::AttachKeyHandler(16,Bootmessage);
        Keypad::AttachKeyHandler( KEY(STAR), DHCP::yes );
        Keypad::AttachKeyHandler( KEY(HASH), DHCP::no );

        Keypad::AttachKeyHandler( KEY(A) ,IPstats);
        Keypad::AttachKeyHandler( KEY(B) ,HWstats);
        Keypad::AttachKeyHandler( KEY(D) ,VARstats);
    }
}
