#ifndef __ChartClass__
#define __ChartClass__

#include <memory>
#include "ConfigClass.h"
class Matrix;

class ChartClass
{
private:
    std::shared_ptr<ConfigClass> cfg;
    int x_step;         // liczba odcinkow z jakich bedzie sie skladal wykres
    mutable double x_min,x_max; // zakres zmiennej x
    mutable double y_min,y_max; // zakres wartosci przyjmowanych przez funkcje
    double GetFunctionValue(double x) const; // zwraca wartosci rysowanej funkcji

    void line2d(wxDC* dc, const Matrix& mat, double x1,double y1,double x2,double y2) const;
    // powyzej sugerowana funkcja transformujaca odcinki (jesli ktos ma
    // inny pomysl mozna ja usunac)

private:
    void DrawCoordinateSystem(wxDC* dc, int w, int h) const;

    Matrix GetIdentityMatrix() const;
    Matrix GetRotationMatrix(float angle) const;
    Matrix GetScaleMatrix(float scaleX, float scaleY) const;
    Matrix GetTranslationMatrix(float translatioX, float translationY) const;
    Matrix GetToScreenMatrix(double width, double height) const;

public:
    explicit ChartClass(std::shared_ptr<ConfigClass> c);
    void Set_Range() const;   // ustala wartosci zmiennych x_min,y_min,x_max,y_max
    double Get_Y_min() const; // zwraca y_min
    double Get_Y_max() const; // zwraca y_max
    void Draw(wxDC *dc, int w, int h);  // rysuje wykres
};

#endif
