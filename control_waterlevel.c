
// sensors
float H;
// actuators
float Ni, Nf;

//constants
const float R = 0.001f,
        S = 4184,
        B = 4,
        P = 1000,
        Href = 2.5f,
        Vref = Href * B;

const float
        pV = 100,
        iV = 20,
        NfV = 250;


float Verr, Vint = 0;

*float levelactuators(float *Verr, float *Vint, float H){

    if (*Verr > 0){
        *Vint += *Verr * 0.03f;
    }

    *Verr = Vref - (H * B);

    

    //integral proportional water level control

    Ni = (*Verr * pV + *Vint / iV);

    //makes sure the water level never reaches 3 meters
    if (H > 2.9) {
        Nf = -*Verr * NfV / B;
    } else {
        Nf = 0;
    }

    //making NI a number from 0 to 100 to avoid errors with the boiler command
    Ni = clamp(Ni, 0, 100);
    Nf = clamp(Nf, 0, 100);
    float lactuators[2];
    lactuators[1]= Ni;
    lactuators[2]= Nf;
    return lactuators;
};