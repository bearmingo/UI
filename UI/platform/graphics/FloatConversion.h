#ifndef FloatConversion_h__
#define FloatConversion_h__

namespace UI {

    template<typename T>
    float narrowPrecisionToFloat(T);

    template<>
    inline float narrowPrecisionToFloat(double number)
    {
        return static_cast<float>(number);
    }

} //namespace UI

#endif /*Floatconversion_h__*/
