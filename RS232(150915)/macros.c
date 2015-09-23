


const char *Int_to_Array_2(unsigned int input_value, unsigned char Array_Length){
     static char Array_Out[10];
 //   unsigned char *Array_Out;
    int loop =0;

    for(loop = 0; loop < 10; loop++)
        Array_Out[loop] = 0x00;
    // some vars are redundant, clean up
    unsigned int Power_Value =0;
    unsigned int Remainder =0;
    unsigned int Value = input_value;
    unsigned int Current_Value =0;
    unsigned char Current_Character =0;

//// Pow(base, exponent)
    for (loop =0; loop < Array_Length; loop++){
        ///// convert int t to ascii
        Power_Value = pow(10, (Array_Length-(loop+1)));
        /// Pow when the Exponent is 0, it will return 0 /
       /// DONT DIVIDE BY ZERO!!!!!!!!!!!
        if(Power_Value == 0 )
            Power_Value = 1;

        Remainder = (Value % Power_Value);
        Current_Value = (Value / Power_Value);

        Current_Character = Current_Value + 0x30;
        Array_Out[loop] = Current_Character;

       // printf("\n %d %d %d %d 0x%x ", Value, Remainder, Current_Value,(Array_Length-(loop+1)),  Array_Out[loop]);
        Value = Remainder;
    }

    return Array_Out;
}


unsigned char Int_to_Array(unsigned int input_value, unsigned char *Array_Out, unsigned char Array_Length){
    int loop =0;

    // some vars are redundant, clean up
    unsigned int Power_Value =0;
    unsigned int Remainder =0;
    unsigned int Value = input_value;
    unsigned int Current_Value =0;
    unsigned char Current_Character =0;

    printf(" WHY ");
//// Pow(base, exponent)
    for (loop =0; loop < Array_Length; loop++){
        ///// convert int t to ascii
        Power_Value = pow(10, (Array_Length-(loop+1)));
        /// Pow when the Exponent is 0, it will return 0 /
       /// DONT DIVIDE BY ZERO!!!!!!!!!!!
        if(Power_Value == 0 )
            Power_Value = 1;

        Remainder = (Value % Power_Value);
        Current_Value = (Value / Power_Value);

        Current_Character = Current_Value + 0x30;
        Array_Out[loop] = Current_Character;

        printf("\n %d %d %d %d 0x%x ", Value, Remainder, Current_Value,(Array_Length-(loop+1)),  Array_Out[loop]);
        Value = Remainder;
    }


    return 0;
}
